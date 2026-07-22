#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t counter = 0;
volatile uint8_t interrupt_flag = 1;

ISR(INT0_vect)
{
	interrupt_flag = 0;
}

int main(void)
{
	//Set pin 21 as input and pull-up
	DDRD &= ~(1 << PD0);
	PORTD |= (1 << PD0);

	//Set interrupt on falling edge and int0
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);

	sei();

	//Set pin 10 as output
	DDRB |= (1 << PB4);

	//Set PWM mode
	TCCR2A = (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);

	//Set prescaler to lowest
	TCCR2B |= (1 << CS20);
	
	while(interrupt_flag)
	{
		PORTB |= (1 << PB4);
		_delay_ms(500);
		PORTB &= ~(1 << PB4);
		counter++;
		_delay_ms(500);
	}

	for (uint8_t count = 0; count < 256; count++)
	{
		OCR2A = count;
		_delay_ms(50);
	}
	
	return 0;
}