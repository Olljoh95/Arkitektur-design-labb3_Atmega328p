#include <avr/io.h>

#include "timer.h"

void timer_init() {

    //TC0 Control Register A
    //Enable Fast PWM-mode on Timer0, Control Register A
    //Clear OC0A on compare match, OC0A bottom(non inverting mode)
    TCCR0A |= (1<<COM0A1); //8th bit set to 1
    TCCR0A &= ~(1<<COM0A0); //7th bit set to 0

    TCCR0A |= (1<<WGM01) | (1<<WGM00); //First and second bit set to 1

    //-----------------------------------------------------------

    //TC0 Control Register B
    //Set prescaler to 1024
    TCCR0B &= ~(1<<WGM02);
    TCCR0B &= ~(1<<CS02);
    TCCR0B |= (1<<CS01) | (1<<CS00);

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

