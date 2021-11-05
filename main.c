#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"

void main (void) {

	LED_init();
	uart_init();
	timer_init();
	button_init();

	//DDRD &= ~(1<<PD2); //Input Switch
	DDRD |= (1<<PD6); //Output led
	int i = 0;
	
	while (1) {
		i = checkButtonState();
		if(i == 1) {
			printf_P(PSTR("Pushed\r\n"));
		} else if(i == 2) {
			printf_P(PSTR("Released\r\n"));
		}
		
	}
}

int checkButtonState() {
	int i = 0;
	if(!(PIND & (1<<PD2))) { // Switch on pin 2 is Low,
		PORTD &= ~(1<<PD6); //Turn led off
		i = 1;
	}
	else {
		PORTD |= (1<<PD6); //Turn led on
		i = 2;
	}
	return i;
	i = 0;
}

