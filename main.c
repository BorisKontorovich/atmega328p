/*
 * File:   main.c
 * Author: Boris Kontorovich
 *
 * Created on November 23, 2019, 9:06 PM
 * 
 * This is just some code to test out setup libraries.
 */

#ifndef F_CPU
#define F_CPU   8000000UL
#endif


#include <xc.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "timers.h"
#include "usart.h"
#include "adc.h"


char messageOne[] = "Start up done.\n\r";
char messageTwo[] = "ADC read performed.\n\r";
char newLine[] = "\n\r";
char adcValueString[10];
uint8_t volatile timer1Flag = 0;
uint8_t tempAdcValue = 0;
uint8_t counter = 0;


int main(void) {
    DDRC |= (1<<PC5);  
    timer1init(); 
    usartSetup(F_CPU);
    adcSingleInit();
    adcEnable();
    sei();   
    serialWrite(messageOne);
    serialWrite(messageTwo);
    serialWrite(newLine);
    while (1) {
            
        if (timer1Flag == 1) {
            PORTC ^= (1<<PC5);
            itoa(adcSingleExecute(), adcValueString, 10);
            serialWrite(adcValueString);
            serialWrite(newLine);
            timer1Flag = 0;
        }
    }  
    return (0);
}

ISR (TIMER1_COMPA_vect) {
    timer1Flag = 1;
}