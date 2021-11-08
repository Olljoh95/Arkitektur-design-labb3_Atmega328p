#include <avr/io.h>
#include "button.h"


void button_init() {
    //Button switch declared on digital pin 12.
    DDRB &= ~(1<<PORTB4); //Invert bit to keep button on LOW-state until pressed
}