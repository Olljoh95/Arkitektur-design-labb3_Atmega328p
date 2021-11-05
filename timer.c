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
    OCR0A = 156.25;

    //Start timer0 clock at 0
    TCNT0 = 0;
}

