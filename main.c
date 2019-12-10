/*
 * File:   main.c
 * Author: Boris Kontorovich
 *
 * Created on November 23, 2019, 9:06 PM
 */

#ifndef F_CPU
#define F_CPU   8000000UL
#endif
#define BAUD    9600
#define BRC     ((F_CPU/16/BAUD) - 1)
#define TX_BUFFER_SIZE 128


#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

// Timers
void timer0init(void); 
void timer1init(void); 
void timer2init(void);
// Serial
void usartSetup(void);
void appendSerial(char c);
void serialWrite(char c[], int size);

// Serial
char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

char messageOne[] = "Hello yo!\n\r";


int main(void) {
    DDRC |= (1<<PC5);  
    timer1init(); 
    usartSetup();
    sei();   
    //serialWrite(messageOne);
    serialWrite(messageOne, sizeof(messageOne));
    while (1) {}  
    return (0);
}


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

ISR (TIMER0_COMPA_vect) {
    PORTC ^= (1<<PC5);
}

ISR (TIMER1_COMPA_vect) {
    PORTC ^= (1<<PC5);
}
    
ISR (TIMER2_COMPA_vect) {
    PORTC ^= (1<<PC5);
}

void usartSetup(void) {
    UBRR0H = (BRC>>8);
    UBRR0L = BRC;

    // Control register B (p.)
    UCSR0B = (1<<TXEN0) | (1<<TXCIE0);
    // Control register C (p.)
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void appendSerial(char c) {
    serialBuffer[serialWritePos] = c;
    serialWritePos++;
  
    if(serialWritePos >= TX_BUFFER_SIZE) {
        serialWritePos = 0;
    }
}


void serialWrite(char c[], int size) {
    for (uint8_t i=0; i < size; i++) {
        appendSerial(c[i]);
    }
    
    if (UCSR0A & (1<<UDRE0)) {
        UDR0 = 0;
    }
}

ISR(USART_TX_vect) {
    if(serialReadPos != serialWritePos) {
        UDR0 = serialBuffer[serialReadPos];
        serialReadPos++;

        if(serialReadPos >= TX_BUFFER_SIZE) {
            serialReadPos++;
        }
    }
}