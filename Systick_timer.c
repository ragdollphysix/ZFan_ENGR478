
#include "Systick_timer.h"

volatile uint32_t pwm_count = 0;

//-------------------------------------------------------------------------------------------
// Initialize SysTick	
//-------------------------------------------------------------------------------------------	
void SysTick_Init(uint32_t Reload){
	
		
	// 1. Disable SysTick Counter before all configurations are done
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;		
	
	// 2. Program reload value by configuring SysTick Reload Value Register. 
	SysTick->LOAD = Reload - 1;    //Note: Time Interval = (Content of the register + 1) � Source_Clock_Period
	
	// 3. Clear reload value by configuring SysTick Current Value Register. 
	SysTick->VAL = 0;
								
	// 4. Enable SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// 5. Select processor clock
	// If CLKSOURCE = 0, the external clock is used. The frequency of SysTick clock is the frequency of the AHB clock divided by 8.
	// If CLKSOURCE = 1, the processor clock is used.
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;		
	
	// 6. Enable SysTick Timer once all configurations are done
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}

void Motor_pin_init(){
  // 1. Enable the clock to GPIO Port B
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// 2. Configure GPIO Mode to 'Output': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOB->MODER &= ~(3UL<<(2*MOTOR_PIN));
	GPIOB->MODER |=   1UL<<(2*MOTOR_PIN);      // Output(01)

	// 3. Configure GPIO Output Type to 'Push-Pull': Output push-pull (0), Output open drain (1)
	GPIOB->OTYPER &= ~(1UL<<MOTOR_PIN);      // Push-pull

	// 4. Configure GPIO Push-Pull to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOB->PUPDR  &= ~(3UL<<(2*MOTOR_PIN));  // No pull-up, no pull-down
}


//-------------------------------------------------------------------------------------------
// SysTick Exception Handler
//-------------------------------------------------------------------------------------------

void SysTick_Handler(void){
	pwm_count++;

	if(pwm_count > 100){
		pwm_count = 0;
	}

	if(pwm_count < duty_cycle){
		GPIOB->ODR |= (1UL << MOTOR_PIN);
	}
	else{
		GPIOB->ODR &= ~(1UL << MOTOR_PIN);
	}

}


