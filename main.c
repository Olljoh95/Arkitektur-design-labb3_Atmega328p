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
	//PORTD |= (1<<PD6); //Turn led on
	
	while (1) {
		PORTD |= (1<<PD6); //Turn led on
		if((TIFR0 &(1<<OCF0A))) { //If timer0 flag is enabled
			checkButtonState();	 //
			TIFR0 |= (1<<OCF0A); //Enable OCF0A Flag to reset
		}
	}
}

void checkButtonState() {
    static uint8_t currentState = 0; //placeholder for button state
    static uint8_t prevState = 0; 	//placeholder for previous button state

    if(PINB & (1<<PORTB4)) { //
        currentState = 1;
    }
	else if(!(PINB & (1<<PORTB4))) {
        currentState = 0;
    }

    if(currentState == 1 && prevState == 0) {
        printf_P(PSTR("Pushed\r\n"));
    } else if(currentState == 0 && prevState == 1){
        printf_P(PSTR("Released\r\n"));
    }
    prevState = currentState;
}


/*
if(!(PIND & (1<<PD2))) { // Switch on pin 2 is Low,
	PORTD &= ~(1<<PD6); //Turn led off
}else {
PORTD |= (1<<PD6); //Turn led on
OCR0A = simple_ramp();
}
*/

/*
i = checkButtonState();
if(i == 1) {
	printf_P(PSTR("Pushed\r\n"));
} else if(i == 2) {
printf_P(PSTR("Released\r\n"));
}
*/

/*
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
*/
