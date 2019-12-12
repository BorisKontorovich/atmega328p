/*
 * File:   main.c
 * Author: Boris Kontorovich
 *
 * Created on November 23, 2019, 9:06 PM
 */

#ifndef F_CPU
#define F_CPU   8000000UL
#endif

#include <xc.h>
#include <avr/interrupt.h>

#include "timers.h"
#include "usart.h"

char messageOne[] = "Hello yo!\n\r";

int main(void) {
    DDRC |= (1<<PC5);  
    timer1init(); 
    usartSetup(F_CPU);
    sei();   
    serialWrite(messageOne, sizeof(messageOne));
    while (1) {}  
    return (0);
}