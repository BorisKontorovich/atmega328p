#include <avr/interrupt.h>
#include <stdlib.h>

void adcSingleInit(void) {
    
    ADMUX |= (1<<ADLAR);
    ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
    // Nohting to set in ADCSRB for single execution
    // ADCSRB |= ();
}

void adcEnable(void){
    ADCSRA |= (1<<ADEN);
}
void adcDisable(void){
    ADCSRA &= ~(1<<ADEN);
}

uint8_t adcSingleExecute(void){
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC)) {} // Wait for adc to complete
    return ADCH;
}

void adcToString(uint8_t value, char *valueSting) {
    itoa(value, valueSting, 10);
}