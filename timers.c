#include "timers.h"


void timer0init(void) {
    // Set mode 2 (CTC) (p. )
    TCCR0A |= (1<<WGM01);
    // Set pre-scaler to 1024 (p. 142)
    TCCR0B |= (1<<CS00) | (1<<CS02);
    // Timer 0 output compare A match interrupt enable (p.)
    TIMSK0 |= (1<<OCIE0A);
    // Set value for output compare register A (p. )
    OCR0A = 100;
}


void timer1init(void) {
    // Set pre-scaler to 256 (p. 173) and mode 4 (p.171)
    TCCR1B |= (1<<CS12) | (1<<WGM12);
    // Timer 0 output compare A match interrupt enable (p. 184)
    TIMSK1 |= (1<<OCIE1A);
    // Set value for output compare register A (p.)
    OCR1A = 15624;
}


void timer2init(void) {

    // Set mode 2 (CTC) (p. 203)
    TCCR2A |= (1<<WGM21);
    // Set pre-scaler to 1024 (p. 206)
    TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22);
    // Timer 0 output compare A match interrupt enable (p. 211)
    TIMSK2 |= (1<<OCIE2A);
    // Set value for output compare register A (p. 209)
    OCR2A = 194; 
}

////////////////////////////////////////////////////////////////////////////////
// IRSs will go into main.c since they include business logic.
////////////////////////////////////////////////////////////////////////////////

/*

ISR (TIMER0_COMPA_vect) {
    PORTC ^= (1<<PC5);
}

ISR (TIMER1_COMPA_vect) {
    PORTC ^= (1<<PC5);
}
    
ISR (TIMER2_COMPA_vect) {
    PORTC ^= (1<<PC5);
}
 
 */
