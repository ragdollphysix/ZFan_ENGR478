/*
 * ADC.h
 *
 *  Created on: May 7, 2026
 *      Author: ragdo
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32l476xx.h"


extern volatile uint32_t adc_result; //Declaration of global variable to store sampled ADC data
extern volatile float adc_temperature;

// Modular function to wake up ADC1 from the deep-power-down mode
void ADC1_Wakeup (void);

// Modular function to initialize ADC external input channels
// In this sample, PA1 (ADC12_IN6) is used
void ADC_Pin_Init(void);

// Modular function to configure ADC common registers
void ADC_Common_Configuration(void);

// Modular function to initialize ADC
void ADC_Init(void);

uint32_t Sample_once(void);


#endif /* ADC_H_ */
