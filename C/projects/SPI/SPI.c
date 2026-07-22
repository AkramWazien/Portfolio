#include <avr/io.h>
#include <util/delay.h>

void spi_init(void)
{
    // Set MOSI, SCK, SS as outputs
    DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
    // Set MISO as inputs
    DDRB &= ~(1 << PB3);
    // Set SS as high
    PORTB |= (1 << PB0);
    // Enable SPI as master, clock rate = f/16;
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    // Clear SPIF by reading SPSR and SPDR
    (void)SPSR;
    (void)SPDR;
    _delay_ms(10);
}

uint8_t spi_transfer(uint8_t data)
{
    // Load data into register
    SPDR = data;
    // Wait for transmission to end
    while (!(SPSR & (1 << SPIF)))
        ;
    // Return received data
    return SPDR;
}

uint8_t rc522_read_register(uint8_t reg)
{
    // Select rc522
    PORTB &= ~(1 << PB0);
    // Send register address
    spi_transfer(reg | 0x80);
    // Dummy data
    uint8_t value = spi_transfer(0x00);
    // Deselect SS
    PORTB |= (1 << PB0);
    // Return value received
    return value;
}

void rc522_write_register(uint8_t reg, uint8_t value)
{
    // Select rc522
    PORTB &= ~(1 << PB0);
    // Set as write
    spi_transfer(reg & 0x7F);
    // Send data to write
    spi_transfer(value);
    // Deselect rc522
    PORTB |= (1 << PB0);
}

void rc522_reset(void)
{
    DDRL |= (1 << PL1);
    PORTL &= ~(1 << PL1);
    _delay_ms(10);
    PORTL |= (1 << PL1);
    _delay_ms(50);
    // Soft reset
    rc522_write_register(0x01, 0x80);
    _delay_ms(50);
}

void rc522_init(void)
{
    rc522_reset();

    rc522_write_register(0x2A, 0x84);               // TModeReg
    rc522_write_register(0x2B, 0x0A);               // TPrescalerReg
    rc522_write_register(0X2D, 0x3E);               // TReloadReg
    rc522_write_register(0x2C, 0x00);               // TAutoReg
    rc522_write_register(0x15, 0x40);               // ModeReg
    rc522_write_register(0x11, 0x3D);               // RxSelReg
    uint8_t tx_control = rc522_read_register(0x14); // TxControlReg
    tx_control |= (1 << 3) | (1 << 2);              // Set TxRFEn
    rc522_write_register(0x14, tx_control);         //
    rc522_write_register(0x12, 0x3F);               // RxGainReg
}

uint8_t rc522_request(uint8_t *tag_type)
{
    // Flush FIFO buffer
    rc522_write_register(0x0A, 0x80);
    _delay_us(10);

    // Write REQA command
    rc522_write_register(0x09, 0x26);
    _delay_us(10);

    // Start transceive command
    rc522_write_register(0x01, 0x0C);
    _delay_us(10);
    rc522_write_register(0x01, 0x0C);

    // Wait for completion
    uint8_t timeout = 100;
    while (timeout--)
    {
        uint8_t status = rc522_read_register(0x04);
        if (status & 0x10)
            break;
        _delay_ms(1);
    }

    if (timeout == 0)
        return 0;

    // Check for errors
    uint8_t error = rc522_read_register(0x06);
    if (error & 0xDF)
        return 0;

    // Read FIFO level
    uint8_t level = rc522_read_register(0x0A);
    if (level != 2)
        return 0;

    // Read response
    tag_type[0] = rc522_read_register(0x09);
    tag_type[1] = rc522_read_register(0x09);

    // **CRITICAL VALIDATION: Check if the bytes are complementary**
    // For a valid card: byte0 ^ byte1 == 0xFF
    if ((tag_type[0] ^ tag_type[1]) != 0xFF)
        return 0; // Invalid response - probably noise!

    // **Also check for valid card types**
    if (tag_type[0] != 0x44 && tag_type[0] != 0x04)
        return 0; // Unknown card type - probably noise!

    return 1; // Valid card detected!
}

int main(void)
{
    // Set pin 12 as output
    DDRB |= (1 << PB6);
    // Create array for tag type
    uint8_t tag_type[2] = {0};
    spi_init();
    rc522_init();

    PORTB |= (1 << PB6);
    _delay_ms(1000);
    PORTB &= ~(1 << PB6);
    // Check rc522 version
    uint8_t version = rc522_read_register(0xEE);
    if (version == 0x91 || version == 0x92)
    {
        for (int i = 0; i < 2; i++)
        {
            PORTB |= (1 << PB6);
            _delay_ms(500);
            PORTB &= ~(1 << PB6);
            _delay_ms(500);
        }
    }
    while (1)
    {
        if (rc522_request(tag_type))
        {
            PORTB |= (1 << PB6);
            _delay_ms(100);
            PORTB &= ~(1 << PB6);
            _delay_ms(100);
        }
        else
        {
            _delay_ms(200);
        }
    }
}