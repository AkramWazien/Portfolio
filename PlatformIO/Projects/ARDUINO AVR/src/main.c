#include <avr/io.h>
#include <util/delay.h>

void uart_init()
{
    // Set low and high bit
    UBR1L = 8;
    UBR1H = 0;
    // Enable transmitter and receiver
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);
    // 1 stop bit, no parity, 8-bit data and asyn usart
    UCSR1C = (1 << UCSZ1) | (1 << UCSZ0);
}

void uart_send_byte(uint8_t data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
}

void uart_send_string(const char *str)
{
    while (*str)
    {
        uart_send_byte(*str++);
    }
}

void uart_send_number(uint16_t num)
{
    char buffer[16];
    int i = 0;

    if (num == 0)
    {
        uart_send_byte('0');
        return;
    }

    while (num > 0)
    {
        buffer[i] = '0' + (num % 10);
        num /= 10;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        uart_send_byte(buffer[j]);
    }
}

void adc_init()
{
    // Set ref voltage = 5 and select channel 1
    ADMUX = (1 << REFS0) | (1 << MUX0);

    // Enable ADC and prescaler = 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(void)
{
    // Start conv
    ADCSRA |= (1 << ADSC);
    // Wait for completion
    while (ADCSRA & (1 << ADSC))
        ;
    // return ADC value
    return ADC;
}

int main(void)
{
    // Init uart and adc
    uart_init();
    adc_init();

    uart_send_string("ADC reader ready!\r\n");

    while (1)
    {
        uint16_t value = adc_read;

        uart_send_string("ADC = ");
        uart_send_number(value);
        uart_send_string("\r\n");

        _delay_ms(200);
    }

    return 0;
}