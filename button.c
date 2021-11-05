#include "button.h"

void button_init() {
    DDRD &= ~(1<<PD2); //Input Switch
}