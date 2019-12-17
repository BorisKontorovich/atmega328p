 
#ifndef ADC_H
#define	ADC_H

#include <xc.h>

void adcSingleInit(void);
void adcEnable(void);
void adcDisable(void);
uint8_t adcSingleExecute(void);

#endif

