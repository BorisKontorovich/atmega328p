#include "usart.h"

uint16_t brc = 0;
char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

void usartSetup(uint32_t fcpu) {
    
    brc = (fcpu/16/BAUD) - 1;
    
    UBRR0H = (brc>>8);
    UBRR0L = brc;

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