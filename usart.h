#ifndef USART_H
#define	USART_H

#define BAUD    9600
#define TX_BUFFER_SIZE 128

#include <xc.h>
#include <avr/interrupt.h>


// Serial
void usartSetup(uint32_t fcpu);
void appendSerial(char c);
void serialWrite(char c[], int size);

#endif

