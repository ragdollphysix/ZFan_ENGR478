/*
 * button.c
 *
 *  Created on: Apr 21, 2026
 *      Author: ragdo
 */

#include "button.h"
#include "LED.h"
#include "Systick_timer.h"

extern volatile uint32_t duty_cycle;



void configure_Push_Button_pin(){
	// Enable PC2 and PC3
		RCC->AHB2ENR |= 0x4;

		// Configured to input (00)
		GPIOC->MODER &= ~(15<<2*2);

		// No pull up or pull down
		GPIOC->PUPDR &= ~(15<<(2*2));
}

void configure_EXTI(void){

	//enable syscfg clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//route exti2 and exti3 to Port C
	SYSCFG->EXTICR[0] &= ~((0xF << 8) | (0xF << 12));
	SYSCFG->EXTICR[0] |= ((0x2 << 8) | (0x2 << 12)); // port C = 0010

	//unmask exti2 and exti3
	EXTI->IMR1 |= (1UL << 2);
	EXTI->IMR1 |= (1UL << 3);

	//define rising and falling edges
		//SW1 - press = rising
	EXTI->RTSR1 |= (1UL << SW1_PIN);
	EXTI->FTSR1 &= ~(1UL << SW1_PIN);
		//SW2 - press = rising
	EXTI->RTSR1 |= (1UL << SW2_PIN);
	EXTI->FTSR1 &= ~(1UL << SW2_PIN);

	//clear flags
	EXTI->PR1 = (1UL << SW1_PIN) | (1UL << SW2_PIN);

	NVIC_EnableIRQ(EXTI2_IRQn);
	//NVIC_EnableIRQ(EXTI3_IRQn);

}

// ['85

// ISR (interrupt handler) for EXTI15_10. Interrupt handlers are initially defined in startup_stml476xx.s.

// Button for manual mode, speed change
void EXTI2_IRQHandler(void) {
	if (EXTI->PR1 & (1UL << SW1_PIN)){
  		//EXTI->PR1 = (1UL << SW1_PIN); //clear flag
		NVIC_DisableIRQ(EXTI2_IRQn);
		for (int i = 0; 68500 > i;i++); // delay for debouncing, 415.5ms
		EXTI->PR1 |= 1<<2;
		NVIC_EnableIRQ(EXTI2_IRQn);


  			counter = counter + 1;
  			mask_shift();
  			if (counter == 0) {
  				duty_cycle = 50;
  			}
  			else if (counter == 1) {
  				duty_cycle = 35;
  			}
  			else if (counter == 2) {
  				duty_cycle = 25;
  			}
  			else if (counter == 3) {
  				duty_cycle = 15;
  			}
  			else if (counter == 4) {
  				duty_cycle = 1;
  			}

	}

	// debouncing block
//	NVIC_DisableIRQ(EXTI2_IRQn);
//	for (int i = 0; 68500 > i;i++); // delay for debouncing, 415.5ms
//	EXTI->PR1 |= 1<<2;
//	NVIC_EnableIRQ(EXTI2_IRQn);
}

// Button for mode change
/*
void EXTI3_IRQHandler(void) {
	if (EXTI->PR1 & (1UL << SW2_PIN)){
		EXTI->PR1 = (1UL << SW2_PIN); //clear flag

		// rising edge trigger
		// if held for three seconds without a detected falling edge, then shut down

		// if not, then check state of mode, then transition accordingly.

		SysTick_Init(4000000);

	}
	// debouncing block
	NVIC_DisableIRQ(EXTI3_IRQn);
	for (int i = 0; 80000 > i;i++);// delay for debouncing, 415.5ms
	EXTI->PR1 |= 1<<3;
	NVIC_EnableIRQ(EXTI3_IRQn);


}
*/
