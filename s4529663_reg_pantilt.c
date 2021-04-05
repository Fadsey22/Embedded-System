/** 
 **************************************************************
 * @file mylib/s4529663_reg_pantilt.c
 * @author Fardeen Bhuiyan - 45296635
 * @date 220321
 * @brief  The Joystick Register Driver processes the Joystick X, Y and Z inputs. Joystick X and Y are
analog voltage inputs and Z is a digital on/off input.
 * REFERENCE: csse3010_mylib_reg_pantilt.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 s4529663_reg_pantilt_init() - initialise servo (GPIO, PWM, etc)
 s4529663_pantilt_angle_write(int type, int angle) - Generic function for writing an angle 
 (0 ◦to ±90 ◦) (type is 0 for pan or 1 for tilt)
 s4529663_pantilt_angle_read(int type) - Read the current pan servo angle (0 ◦
to ±90 ◦
#define S45296663 REG PANTILT PAN WRITE(int angle) - Use a #define function, to access generic angle write function
for the pan
#define S4529663 REG PANTILT PAN READ() - Use a #define function, to access generic angle read function
for the pan.
#define S4529663 REG PANTILT TILT READ() - Use a #define function, to access generic angle read function
for the tilt.
 *********************************************************************************
 */

#include "board.h"
#include "processor_hal.h"
#include "stm32f429xx.h"
#include "s4529663_reg_pantilt.h"
#include <stdint.h>

//Global Variables
#define TIMER_RUNNING_FREQ  				245000       				//Frequency (in Hz)
#define PWM_PULSE_WIDTH_SECONDS				2						//2s
#define PWM_PULSE_WIDTH_TICKS				10000 					//((PWM_PULSE_WIDTH_SECONDS)/(1/TIMER_RUNNING_FREQ))		//Period in timer ticks
#define PWM_PERCENT2TICKS_DUTYCYCLE(value)	(uint16_t)(value*PWM_PULSE_WIDTH_TICKS/100)				//Duty Cycle on time in timer ticks

#define S4529663_REG_PANTILT_PAN_WRITE(angle) s4529663_pantilt_angle_write(0,angle)) // function that sets pan angle
#define S4529663_REG_PANTILT_PAN_READ ()  s4529663_pantilt_angle_read(0) // function that reads pan angle
#define S4529663_REG_PANTILT_TILT_WRITE(angle) s4529663_pantilt_angle_write(1,angle) // function that writes the tilt angle
#define S4529663_REG_PANTILT_TILT_READ() s4529663_pantilt_angle_read(1)  // function that reads the tilt angle.

/**
 * Initialises the GPIO PIN E9 for the pan/tilt
 * Enables PMW
 * @param - void
 * @return void
 **/



void s4529663_reg_pantilt_init(void){
	// Enable GPIOC Clock
	__GPIOE_CLK_ENABLE();

    GPIOE->OSPEEDR |= (GPIO_SPEED_FAST << 9);		//Set fast speed.
	GPIOE->PUPDR &= ~(0x03 << (9 * 2));				//Clear bits for no push/pull
	GPIOE->MODER &= ~(0x03 << (9 * 2));				//Clear bits
	GPIOE->MODER |= (GPIO_MODE_AF_PP << (9 * 2));  	//Set Alternate Function Push Pull Mode
	
	GPIOE->AFR[1] &= ~((0x0F) << (1 * 4));			//Clear Alternate Function for pin (lower ARF register)
	GPIOE->AFR[1] |= (GPIO_AF1_TIM1<< (1 * 4));	//Set Alternate Function for pin (lower ARF register) 


	GPIOE->OSPEEDR |= (GPIO_SPEED_FAST << 11);		//Set fast speed.
	GPIOE->PUPDR &= ~(0x03 << (11 * 2));				//Clear bits for no push/pull
	GPIOE->MODER &= ~(0x03 << (11 * 2));				//Clear bits
	GPIOE->MODER |= (GPIO_MODE_AF_PP << (11 * 2));  

	GPIOE->AFR[1] &= ~((0x0F) << (3 * 4));			//Clear Alternate Function for pin (lower ARF register)
	GPIOE->AFR[1] |= (GPIO_AF1_TIM1<< (3 * 4));	//Set Alternate Function for pin (lower ARF register) 

	// Timer 1 clock enable
	__TIM1_CLK_ENABLE();

	/* Compute the prescaler value
	   Set the clock prescaler to 50kHz
	   SystemCoreClock is the system clock frequency */
	TIM1->PSC = ((SystemCoreClock / 2) / TIMER_RUNNING_FREQ) - 1;

	// Counting direction: 0 = up-counting, 1 = down-counting (Timer Control Register 1)
	TIM1->CR1 &= ~TIM_CR1_DIR; 

	TIM1->ARR = 10000; 		//Set pulse period to 
	double poffset = (double)S4529663_REG_PANTILT_PAN_ZERO_CAL_OFFSET / 18; // converting degrees to duty cycle
	TIM1->CCR1 = PWM_PERCENT2TICKS_DUTYCYCLE(7.25 + S4529663_REG_PANTILT_PAN_ZERO_CAL_OFFSET);	//Set pulse width to 0% duty cycle.
	TIM1->CCMR1 &= ~(TIM_CCMR1_OC1M); 	// Clear OC1M (Channel 1) 

	TIM1->CCMR1 |= (0x6 << 4); 		// Enable PWM Mode 1, upcounting, on Channel 1 
	TIM1->CCMR1 |= (TIM_CCMR1_OC1PE); 	// Enable output preload bit for channel 1
	
	TIM1->CR1  |= (TIM_CR1_ARPE); 	// Set Auto-Reload Preload Enable 
	TIM1->CCER |= TIM_CCER_CC1E; 	// Set CC2E Bit
	TIM1->CCER &= ~TIM_CCER_CC2NE; 	// Clear CC2NE Bit for active high output
	
	/* Set Main Output Enable (MOE) bit
	   Set Off-State Selection for Run mode (OSSR) bit
	   Set Off-State Selection for Idle mode (OSSI) bit */
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSR | TIM_BDTR_OSSI; 

	TIM1->CR1 |= TIM_CR1_CEN;
	double toffset = (double)S4529663_REG_PANTILT_TILT_ZERO_CAL_OFFSET/18; // converting degrees to duty cyle

	TIM1->CCR2 = PWM_PERCENT2TICKS_DUTYCYCLE(7.25 + S4529663_REG_PANTILT_TILT_ZERO_CAL_OFFSET);

	TIM1->CCMR1 &= ~(TIM_CCMR1_OC2M); 	// Clear OC2M (Channel 2) 
	TIM1->CCMR1 |= (0x6 << 12); 		// Enable PWM Mode 1, upcounting, on Channel 2 
	TIM1->CCMR1 |= (TIM_CCMR1_OC2PE); 	// Enable output preload bit for channel 2 
	TIM1->CCER |= TIM_CCER_CC2E; 	// Set CC2E Bit 
    
}


/**
 * function that writes the angle to the pan or tilt
 * @return - void
 * @param- type to indentify pan or tilt and angle to be set
 **/
void s4529663_pantilt_angle_write(int type, int angle) {
	double poffset = (double)S4529663_REG_PANTILT_PAN_ZERO_CAL_OFFSET/18;
	double toffset = (double)S4529663_REG_PANTILT_TILT_ZERO_CAL_OFFSET/18;
	if(type == 0) {
		TIM1->CCR1 = PWM_PERCENT2TICKS_DUTYCYCLE((angle+(18*(7.25+poffset)))/18);
	}
	if(type == 1) {
		TIM1->CCR2 = PWM_PERCENT2TICKS_DUTYCYCLE((angle+(18*(7.25+toffset)))/18);
	}
	

}

/**
 * function that reads the angle 
 * @return -  angle
 * @param - type to identify  whether it is pan or tilt
 **/
double s4529663_pantilt_angle_read(int type) {
	double val1;
	double val2;
	double gradpan;
	double minpan;
	double gradtilt;
	double mintilt;
	double ledpan;
	double ledtilt;
	double poffset = (double)S4529663_REG_PANTILT_PAN_ZERO_CAL_OFFSET/18;
	double toffset = (double)S4529663_REG_PANTILT_TILT_ZERO_CAL_OFFSET/18;
	if(type == 0) {
		val1 = (TIM1->CCR1)/(PWM_PULSE_WIDTH_TICKS/100);
		gradpan = 18*val1;
		minpan = 18*(7.25+poffset);

		ledpan = gradpan - minpan;
		return ledpan;

	}
	if(type == 1) {
		val2 = (TIM1->CCR2)/(PWM_PULSE_WIDTH_TICKS/100);
		gradtilt = 18* val2;
		mintilt = 18*(7.25+toffset);
		ledtilt = gradtilt - mintilt;
		return ledtilt;
	}

}

