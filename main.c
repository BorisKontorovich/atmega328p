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
#include "adc.h"

char messageOne[] = "Start up done.\n\r";
char messageTwo[] = "ADC read performed.\n\r";
char adcValueString[10];
uint8_t volatile timer1Flag = 0;

int main(void) {
    DDRC |= (1<<PC5);  
    timer1init(); 
    usartSetup(F_CPU);
    adcSingleInit();
    adcEnable();
    sei();   
    serialWrite(messageOne, sizeof(messageOne));
    while (1) {
        if (timer1Flag == 1) {
            PORTC ^= (1<<PC5);
            uint8_t tempAdcValue = 0;
            tempAdcValue = adcSingleExecute();
            adcToString(tempAdcValue, adcValueString);
            serialWrite(adcValueString, sizeof(adcValueString));
            timer1Flag = 0;
        }
    }  
    return (0);
}

ISR (TIMER1_COMPA_vect) {
    timer1Flag = 1;
}