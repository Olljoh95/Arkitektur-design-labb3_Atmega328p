#include <avr/io.h>

#include "timer.h"

void timer_init0() {

    //TC0 Control Register A
    //Enable Fast PWM-mode on Timer0, Control Register A
    //Clear OC0A on compare match, OC0A bottom(non inverting mode)
    TCCR0A |= (1<<COM0A1); //8th bit set to 1
    TCCR0A &= ~(1<<COM0A0); //7th bit set to 0

    //6'th and 5'th bit defaults to 0 and are in this case ignored.
    //TCCR0A &= ~(1<<COM0B1); 
    //TCCR0A &= ~(1<<COM0B0); 

    TCCR0A |= (1<<WGM01) | (1<<WGM00); //First and second bit set to 1

    //-----------------------------------------------------------

    //TC0 Control Register B
    //Set prescaler to 64
    
    //8'th and 7'th bit ignored, no Force Output Compare needed in this scenario
    //TCCR0B &= ~(1<<FOC0A); 
    //TCCR0B &= ~(1<<FOC0B); 
    TCCR0B &= ~(1<<WGM02); //4'th bit set to 0
    TCCR0B &= ~(1<<CS02); //Third bit set to 0
    TCCR0B |= (1<<CS01) | (1<<CS00); //First and second bit set to 1

    //16000000/prescale(64) = 250 000
    //TOP set to 255 - 1 for correction

    OCR0A = 0xff-1; 
}

