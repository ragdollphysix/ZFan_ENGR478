/*
 * button.h
 *
 *  Created on: Apr 21, 2026
 *      Author: ragdo
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32l476xx.h"

extern volatile unsigned long counter; // global variable counter
#define SW1_PIN 2
#define SW2_PIN 3

void configure_Push_Button_pin();
void configure_EXTI(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);

#endif /* BUTTON_H_ */
