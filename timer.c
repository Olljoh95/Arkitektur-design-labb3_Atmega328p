#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer0_init() {

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

}

void timer2_init() {
    //TC2 Control Register A
    //Timer2 in CTC-mode
    //Clear OCR2A on Compare Match on channel A
    TCCR2A |= (1<<COM2A1); //8'th bit set to 1
    TCCR2A &= ~(1<<COM2A0); //7'th bit set to 0
    TCCR2A |= (1<<WGM21); //Second bit set to 1
    TCCR2A &= ~(1<<WGM20); //First bit set to 0

    //Channel b not used, COM2Bn bits ignored
    //TCCR2A &= ~(1<<COM2B1);
    //TCCR2A &= ~(1<<COM2B2);

    //-----------------------------------------------
    
    //TC2 Control Register B
    //Force Output Compare not used and therefore ignored
    //TCCR2B &= ~(1<<FOC2A);
    //TCCR2B &= ~(1<<FOC2B);

    //Set prescale to 1024
    TCCR2B &= ~(1<<WGM22); //3'rd bit set to 0
    TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); //CS2[2:0] set to 1

    //-----------------------------------------------

    //TCNT2 = 0; Probably redundant

    //------------------------------------------------


    //TC2 Output Compare Register A

    //Prescale value: 16 000 000 / 1024 = 15625
    //Multiply with desired time period (10ms): 15625 * 0.010 = 157.25
    //Subtract 1 for value correction: 157-1 = 156
    OCR2A = 156;

    //------------------------------------------------

    //TC2 Interrupt Mask Register
    TIMSK2 &= ~(1<<OCIE2B); //3'rd bit set to 0
    TIMSK2 |= (1<<OCIE2A); //2'nd bit set to 1
    TIMSK2 &= ~(1<<TOIE2); //First bit set to 0
}
