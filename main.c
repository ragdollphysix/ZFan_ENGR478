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
// #include


/* One Motor Driver to Motor
 * 5 LED's
 * Three buttons
 * One Temperature Sensor
 *
 *
 *
 * */

int main(void){

	//1. Invoke configure_LED_pin() to initialize PA5 as an output pin, interfacing with the LD2 LED.
	configure_LED_pin();
	//2. Turn on the LD2 LED
	turn_on_LED();

	//3. Initialize PC13 as an input pin
	configure_Push_Button_pin();

	//4. configure interrupts
	configure_EXTI();

	GPIOC->ODR |= 1<<5;

	//3. Invoke SysTick_Init() to set up SysTick periodic exception.
		//   The default processor clock is 4MHz provided by MSI.
		//   The SysTick reload value is set to 4,000,000 - 1 to generate periodic exception every 1 s
		//   For a silent buzzer, enter 0


 	while(1){


 	}
}
