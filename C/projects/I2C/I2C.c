#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void i2c_init(void)
{
    // Set SDA and SCL as output
    DDRD |= (1 << PD1) | (1 << PD0);
    PORTD |= (1 << PORTD1) | (1 << PORTD0);
    // Set comm to 25kHz
    TWBR = 200;
    TWCR = (1 << TWEN);
}

void i2c_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO);
}

uint8_t i2c_write_byte(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    return (TWSR & 0XF8) == 0x28;
}

uint8_t i2c_test_address(uint8_t addr)
{
    i2c_start();
    uint8_t ack = i2c_write_byte(addr);
    i2c_stop();
    return ack;
}

void lcd_send_byte(uint8_t data, uint8_t mode)
{
    uint8_t high = (data & 0xF0) | mode | 0x08;
    uint8_t low = ((data << 4) & 0xF0) | mode | 0x08;

    i2c_start();
    i2c_write_byte(0x27 << 1);
    i2c_write_byte(high | 0x04);
    _delay_us(1);
    i2c_write_byte(high & ~(0x04));
    _delay_us(50);
    i2c_write_byte(low | 0x04);
    _delay_us(1);
    i2c_write_byte(low & ~(0x04));
    _delay_us(50);
    i2c_stop();
}

void lcd_init(void)
{
    _delay_ms(50);
    lcd_send_byte(0x30, 0x00);
    _delay_ms(5);
    lcd_send_byte(0x30, 0x00);
    _delay_us(150);
    lcd_send_byte(0x20, 0x00);
    _delay_ms(1);
    lcd_send_byte(0x28, 0x00); // 4-bit, 2 lines
    _delay_ms(1);
    lcd_send_byte(0x08, 0x00); // Display off
    _delay_ms(1);
    lcd_send_byte(0x01, 0x00); // Clear
    _delay_ms(2);
    lcd_send_byte(0x06, 0x00); // Entry mode
    _delay_ms(1);
    lcd_send_byte(0x0C, 0x00); // Display on, cursor off, blink off
    _delay_ms(1);
}

void lcd_print(const char *str)
{
    while (*str)
    {
        lcd_send_byte(*str++, 0x01);
        _delay_us(50);
    }
}

void lcd_clear(void)
{
    lcd_send_byte(0x01, 0x00);
    _delay_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address;
    if (row == 0)
    {
        address = 0x00 + col;
    }
    else
    {
        address = 0x40 + col;
    }
    lcd_send_byte(0x80 | address, 0x00);
}

int main(void)
{
    // Set pin 13 as output
    DDRB |= (1 << PB6);
    _delay_ms(1000);
    i2c_init();

    // Check for address
    if (i2c_test_address(0x27))
    {
        PORTB |= (1 << PB6);
        _delay_ms(500);
        PORTB &= ~(1 << PB6);
        _delay_ms(500);
    }

    lcd_init();
    _delay_ms(50);

    lcd_set_cursor(0, 0);
    lcd_print("Hello, World!");
    lcd_set_cursor(1, 0);
    lcd_print("Arduino Mega");

    while (1)
    {
    };
    return 0;
}