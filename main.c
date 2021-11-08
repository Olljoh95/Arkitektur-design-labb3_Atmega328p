#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"
#include "adc.h"

void main (void) {

	LED_init();
	uart_init();
	timer_init0();
	button_init();
    adc_init();
	
	while (1) {
        checkButtonState();
	}
}

void checkButtonState() {
    static uint8_t currentState = 0; //placeholder for button state
    static uint8_t prevState = 0; 	//placeholder for previous button state

    if(PINB & (1<<PORTB4)) {
        currentState = 1;
		PORTD |= (1<<PD6); //Turn led on
    }
	else if(!(PINB & (1<<PORTB4))) {
        currentState = 0;
		PORTD &= ~(1<<PD6); //turn led off;
    }

    if(currentState == 1 && prevState == 0) {
        printf_P(PSTR("Pushed\r\n"));
		

    } else if(currentState == 0 && prevState == 1){
        printf_P(PSTR("Released\r\n"));
    }
    prevState = currentState;
}