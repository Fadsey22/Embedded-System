/** 
 **************************************************************
 * @file mylib/s4529663_reg_pb.c
 * @author Fardeen Bhuiyan - 4529663
 * @date 8032021
 * @brief The Pushbutton Register Driver enables and disables a pushbutton or an Input Signal
          Synchroniser (ISS) input signal. The pushbutton and ISS input signals must be connected to
          a GPIO pin. GPIO EXTI interrupts must be generated
 * REFERENCE: csse3010_mylib_reg_pushbutton.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 * *s4529663_reg_iss_synchroniser
(unsigned char signal source index) - Synchronise the input signal
with debouncing in the ISR's
 ***************************************************************
 * s4529663_reg pb on init() () - enable GPIO OUTPUTS and INTERRUPTS
 * s4529663 reg pb on isr() - Onboard Pushbutton Interrupt service routine. Must
be called from the corresponding GPIO EXTI interrupt service routine in the ‘isr hander.c‘
*s4529663 reg pb iss init() - Enabled the ISS pin source, e.g. enables GPIO input
and interrupt.
*  ISS pin source Interrupt service routine. Must be
called from the corresponding GPIO EXTI interrupt
service routine in the ‘isr hander.c‘.
s4529663 reg pb iss isr()  - ISS pin source Interrupt service routine. Must be
called from the corresponding GPIO EXTI interrupt
service routine in the ‘isr hander.c‘.
***********************************************************************************/


#include "board.h"
#include "processor_hal.h"
#include "s4529663_reg_lta1000g.h"
#include "s4529663_reg_iss.h"
#include <stdbool.h>

/**
 * function that initialises pushbutton as GPIO input
 * @return - void
 * @param - void
 **/

void s4529663_reg_pb_on_init(void) {
    __GPIOC_CLK_ENABLE();

    GPIOC->OSPEEDR |= (GPIO_SPEED_FAST << 13);	//Set fast speed.
	GPIOC->PUPDR &= ~(0x03 << (13 * 2));			//Clear bits for no push/pull
	GPIOC->MODER &= ~(0x03 << (13 * 2));			//Clear bits for input mode
	// Enable EXTI clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//select trigger source (port c, pin 13) on EXTICR4.
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	SYSCFG->EXTICR[3] &= ~(0x000F);

	EXTI->RTSR |= EXTI_RTSR_TR13;	//enable rising dedge
	EXTI->FTSR |= EXTI_FTSR_TR13;	//disable falling edge
	EXTI->IMR |= EXTI_IMR_IM13;		//Enable external interrupt
	//Enable priority and interrupt callback.
	NVIC_SetPriority(EXTI15_10_IRQn, 1);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
} 

/**
 * ISR for pushbutton 
 * @return - void
 * @param - void
 **/

void s4529663_reg_pb_on_isr(void) {
    
	    s452663_reg_iss_synchroniser(1);

	  	EXTI->PR |= EXTI_PR_PR13;	//Clear interrupt flag.

}


/**
 * function that intialises pin A3 as gpio input for xenon
 * @return - void
 * @param - void
 **/

void s4529663_reg_pb_iss_init(void)
{
  __GPIOA_CLK_ENABLE();

  GPIOA->OSPEEDR |= (GPIO_SPEED_FAST << 3); //Set fast speed.
  GPIOA->PUPDR &= ~(0x03 << (3 * 2));       //Clear bits for no push/pull
  GPIOA->MODER &= ~(0x03 << (3 * 2));       //Clear bits for input mode
  // Enable EXTI clock
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC;
  SYSCFG->EXTICR[0] &= ~(0xF000);

  EXTI->RTSR |= EXTI_RTSR_TR3;  //enable rising dedge
  EXTI->FTSR &= ~EXTI_FTSR_TR3; //disable falling edge
  EXTI->IMR |= EXTI_IMR_IM3;    //Enable external interrupt
  //Enable priority and interrupt callback.
  NVIC_SetPriority(EXTI3_IRQn, 10);
  NVIC_EnableIRQ(EXTI3_IRQn);
}

/**
 * ISR for xenon monitor
 * @return - void
 * @param - void
 **/
void s4529663_reg_pb_iss_isr(void)
{
    s452663_reg_iss_synchroniser(0);
   
    EXTI->PR |= EXTI_PR_PR3;
  
}