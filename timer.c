#include <avr/io.h>

#include "timer.h"

void timer_init() {

    //Enable CTC-mode on Timer0, Control Register A
    TCCR0A &= ~(1<<WGM02);
    TCCR0A |= (1<<WGM01);
    TCCR0A &= ~(1<<WGM00);

    //Set prescaler to 1024
    TCCR0B |= (1<<CS02);
    TCCR0B &= ~(1<<CS01);
    TCCR0B |= (1<<CS00);

    //16000000/prescale(1024) = 15625
    //15625 * 0.010(10 milliseconds) = 156.25
    //156.25 - 1 for correction
    OCR0A = 157 - 1;
}

uint8_t timer0CompareMatch() {
    if((TIFR0 &(1<<OCF0A))) {
        return 1;
        TIFR0 |= (1<<OCF0A); //Clear flag
    }
    return 0;
}

