#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

void main (void) {

	LED_init();
	uart_init();
	timer_init();

	DDRD &= ~(1<<PD2); //Input Switch
	DDRD |= (1<<PD6); //Output led
	
	while (1) {
		if(!(PIND & (1<<PD2))) { // Switch on pin 2 is Low,
			PORTD &= ~(1<<PD6); //Invert pin 6 bit
		}
		else {
			PORTD |= (1<<PD6);
		}
	}
}

/* remove this once you've verified it works 
	printf_P(PSTR("Hello there\n"));
	_delay_ms(1000);
*/

