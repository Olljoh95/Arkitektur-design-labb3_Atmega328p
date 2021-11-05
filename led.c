#include <avr/io.h>
#include "led.h"

void LED_init() {
	DDRD |= (1<<PD6); //Output led
}

uint8_t simple_ramp() {
	static uint8_t count = 0;
	static uint8_t dir = -1;
	if(count == 0 || count == 255) {
		dir *= -1;
	}
	return count += dir;
}
