#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

volatile uint16_t ADC_val = 255;

void adc_init() {
    DDRC |= (1<<DDC0); //Set Port C Data Direction Register to 1, enableing output on analog pin 0

    //ADC Multiplexer Selection Register
    //AVCC with external capacitor at AREF pin & ADC left adjust
    ADMUX &= ~(1<<REFS1); //7'th bit is set to 0
    ADMUX |= (1<<REFS0);  //6'th bit is set to 1
    ADMUX |= (1<<ADLAR);  //5'th bit is set to 1

    //Analog Channel Selection [MUX3:0]
    //Bit 0-3 set to 0
    //Mode: Single ended output ADC0
    ADMUX &= ~(1<<MUX3);
    ADMUX &= ~(1<<MUX2);
    ADMUX &= ~(1<<MUX1);
    ADMUX &= ~(1<<MUX0);

    /* !!! ALWAYS SELECT CHANNEL BEFORE STARTING CONVERSION !!! */
    //--------------------------------------------------------------------
    /* !!! ALWAYS SELECT CHANNEL BEFORE STARTING CONVERSION !!! */

    //ADC Control and Status Register A
    //Enable ADC(ADEN), Enable Interrputs(ADIE), Set prescale to 8(APS[2:0])
    ADCSRA |= (1<<ADEN); //8'th bit set to 1
    //ADCSRA |= (1<<ADSC); Start Conversion, regulates start of conversion
    //ADCSRA |= (1<<ADATE); Auto trigger
    //ADCSRA |= (1<<ADIF); Interrupt flag, is set when a conversion is complete
    ADCSRA |= (1<<ADIE); //4'th bit set to 1, this along with I-bit in SREG allows ADC Conversion Complete Interrupt
    ADCSRA &= ~(1<<ADPS2); //Third bit set to 0
    ADCSRA |= (1<<ADPS1) | (1<<ADPS0); //First and second bit set to 1

    //---------------------------------------------------------------------
    /*
    ADCL & ADCH depends on the ADLAR-bit in ADMUX-register.
    !!! In this case ADLAR is 1(Left adjusted). Consequently only ADCH will be read. !!!
    */

    //ADC Control and Status Register B
    //In this case this register will be used to set to Timer/Counter0 Compare Match A (ADTS[2:0] = 011)

    ADCSRB &= ~(1<<ADTS2); //Third bit set to 0
    ADCSRB |= (1<<ADTS1) | (1<<ADTS0); //Second and first bit set to 1
}

ISR(ADC_vect) {
    ADC_val = ADCH;
}

uint16_t get_ADC_val() {
    return ADC_val;
}