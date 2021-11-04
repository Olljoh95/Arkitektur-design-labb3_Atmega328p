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

	uint8_t i = 0;
	
	while (1) {
		if(!(PIND & (1<<PD2))) { // Switch on pin 2 is Low,
			PORTD &= ~(1<<PD6); //Turn led off
			i = 1;
		}
		else {
			PORTD |= (1<<PD6); //Turn led on
			i = 2;
		}
		i = 0;
		printButtonState(i);
	}
}

void printButtonState(uint8_t mode) {
	switch(mode) {
		case 0:
		break;

		case 1:
		printf_P(PSTR("Pushed\r\n"));
		break;

		case 2:
		printf_P(PSTR("Released\r\n"));
		break;

	}

}

