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

int main (void) {

	LED_init();
	uart_init();
	timer0_init();
    timer2_init();
	button_init();
    adc_init();
    sei();
	
	while (1) {}
}

ISR(TIMER2_COMPA_vect) {
    /*When an interrupt is triggered, 
    set ADSC bit to 1 in ADC Control & Status Register A
    to start sampling
    */
    ADCSRA |= (1<<ADSC); 
    OCR0A = get_ADC_val(); //Put the current value of the ADC in the output compare register
                           //This allows us to control the duty cycle of the led using a potentiometer
    checkButtonState(); //use the timer2 interval of 10ms to debounce button
}

void checkButtonState() {
    static uint8_t currentState = 0;
    static uint8_t prevState = 0;
    if(PINB & (1<<PORTB4)) { //Check if digital pin 12 is HIGH
        currentState = 1; //change state variable

    } else if(!(PINB & (1<<PORTB4))) { //if pin is LOW
        currentState = 0; //Set variable to zero
    }

    if(currentState == 1 && prevState == 0) { //Compare previous and current state
        printf_P(PSTR("Pushed\r\n"));

    } else if(currentState == 0 && prevState == 1){
       printf_P(PSTR("Released\r\n"));
    }
    prevState = currentState; //Change previous state
}