/*
  @file    main.c
  @author  Xiaorong Zhang
  @date    Fall-2023
  @editor  Elijah Chua
 */

#include "stm32l476xx.h"
#include "LED.h"
#include "Systick_timer.h"
#include "button.h"
#include "ADC.h"

volatile int mode;


/* One Motor Driver to Motor
 * 5 LED's
 * Three buttons
 * One Temperature Sensor
 *
 *
 *
 * */


// MODE MUST START IN MANUAL

int main(void){

	//1. Invoke configure_LED_pin() to initialize PA5 as an output pin, interfacing with the LD2 LED.
	configure_LED_pin();

	//3. Initialize PC2 and PC3 as an input pin
	configure_Push_Button_pin();

	//4. configure interrupts
	configure_EXTI();

	turn_on_LED();

	// system starts on manual mode and not temperature mode
	GPIOC->ODR |= 1<<5;

	Motor_pin_init();

	SysTick_Init(400);

	mode = 0;

 	while(1){

 		if ((GPIOC->IDR & (1UL<<3)) == 1<<3) {
 			for(volatile int i=0; i<50000;i++);
 			while((GPIOC->IDR & (1UL<<3)) == 1<<3);

 			for (int t=0; t<200000;t++) {

 				if ((GPIOC->IDR & (1UL<<3)) == 1<<3) {
 					for(volatile int i=0; i<50000;i++);
 					while((GPIOC->IDR & (1UL<<3)) == 1<<3);

 					if ((GPIOC->ODR & 1<<5) == 1<<5) {
 						GPIOC->ODR &= ~(0b11111<<5);
 						NVIC_DisableIRQ(EXTI2_IRQn);
 						// code to disable the interrupt for ADC and Systick

 					} else {
 						NVIC_EnableIRQ(EXTI2_IRQn);
 						counter = 0;
 					 	mask_shift();
 					 	// code to enable the interrupt for ADC and Systick

 					}
 					break;
 				}
 			}
 			/*
 			if (mode == 0) {
 				counter = 0;
 				rotary_shift();

 			}
 			*/



 			// insert code here for mode change

 			// change to temperature mode


 			// change to manual mode

 		}
 	}
}
