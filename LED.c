#include "LED.h"

// PC5-9

#define LED_PIN    5

volatile unsigned long counter = 0;

void configure_LED_pin(){
  // 1. Enable the clock to GPIO Port C
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
		
	// 2. Configure GPIO Mode to 'Output': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOC->MODER &= ~(0b111111111111<<(2*LED_PIN));
	GPIOC->MODER |=   0b010101010101<<(2*LED_PIN);      // Output(01)

	// 3. Configure GPIO Output Type to 'Push-Pull': Output push-pull (0), Output open drain (1) 
	GPIOC->OTYPER &= ~(0b111111<<LED_PIN);      // Push-pull
	
	// 4. Configure GPIO Push-Pull to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOC->PUPDR  &= ~(0b111111111111<<(2*LED_PIN));  // No pull-up, no pull-down
}

void rotary_shift(){
	if (counter == 5) {
	  	counter = 0;
	}
	  	GPIOC->ODR &= ~(0b11111<<5);
	  	GPIOC->ODR |= 0b111110<<counter;

}

// Modular function to turn on the LD2 LED.
void turn_on_LED(){
	GPIOC->ODR |= 1 << 10;
}

// Modular function to turn off the LD2 LED.
void turn_off_LED(){

	GPIOC->ODR &= ~(1 << 10);

}

// Modular function to toggle the LD2 LED.
void toggle_LED(){
	GPIOC->ODR ^= (1 << LED_PIN);
}
