/** 
 **************************************************************
 * @file mylib/s4529663_reg.joystick.c
 * @author Fardeen Bhuiyan - 45296635
 * @date 220321
 * @brief  The Joystick Register Driver processes the Joystick X, Y and Z inputs. Joystick X and Y are
analog voltage inputs and Z is a digital on/off input.
 * REFERENCE: csse3010_mylib_reg_joystick.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *s4529663_reg_joystick_init() - Initialise GPIO pins and ADC
 int joystick readxy(ADC Handler) - Internal generic function to read X or Y joystick value
 #define S4529663 REG JOYSTICK X READ() - #define for internal generic function to read X value
 #define S4529663 REG JOYSTICK Y READ() - #define for internal generic function to read Y value'
 #define S4529663 REG JOYSTICK Z READ() - #define for function to read Z value

 *************************************************************** 
 */


#include "board.h"
#include "processor_hal.h"
#include "stm32f429xx.h"
#include "s4529663_reg_iss.h"
#include <stdint.h>
ADC_HandleTypeDef AdcHandle1;
ADC_ChannelConfTypeDef AdcChanConfig1;
ADC_HandleTypeDef AdcHandle2;
ADC_ChannelConfTypeDef AdcChanConfig2;


#define S4529663_REG_JOYSTICK_X_READ() joystick_readxy(AdcHandle1); // returns x value of joystick
#define S4529663_REG_JOYSTICK_Y_READ() joystick_readxy(AdcHandle2) // returns y value of joystick
#define S4529663_REG_JOYSTICK_Z_READ() 2



/**
 * Function initilaises joystick for GPIO inputs
 * Initialises ADC
 * @param - void
 * @return - void
 **/

void s4529663_reg_joystick_init(void) {
    __GPIOA_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    GPIOC->OSPEEDR |= (GPIO_SPEED_FAST << 3);	//Set fast speed.
	GPIOC->PUPDR |= (0x01 << (3 * 2));			//Clear bits for no push/pull
	GPIOC->MODER &= ~(0x03 << (3 * 2));			//Clear bits for input mode
	// Enable EXTI clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//select trigger source (port c, pin 13) on EXTICR4.
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3; // CR
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC; // CR
	SYSCFG->EXTICR[0] &= ~(0x000F); //CR

	EXTI->RTSR |= EXTI_RTSR_TR3;	//enable rising dedge
	EXTI->FTSR &= ~EXTI_FTSR_TR3;	//disable falling edge
	EXTI->IMR |= EXTI_IMR_IM3;		//Enable external interrupt
	//Enable priority and interrupt callback.
	NVIC_SetPriority(EXTI3_IRQn, 10);
	NVIC_EnableIRQ(EXTI3_IRQn);
	

	// Initalise PA3 as an Analog input.
  	GPIOA->MODER |= (0x03 << (3 * 2));			//Set bits for Analog input mode

  	GPIOA->OSPEEDR &= ~(0x03<<(3 * 2));
	GPIOA->OSPEEDR |= 0x02<<(3 * 2);  			// Fast speed

	GPIOA->PUPDR &= ~(0x03 << (3 * 2));			//Clear bits for no push/pull
	



    // Init PC0

    // Initalise PC0 as an Analog input.
  	GPIOC->MODER |= (0x03 << (0 * 2));			//Set bits for Analog input mode

  	GPIOC->OSPEEDR &= ~(0x03<<(0 * 2));
	GPIOC->OSPEEDR |= 0x01<<(0 * 2);  			// Fast speed

	GPIOC->PUPDR &= ~(0x03 << (0 * 2));			//Clear bits for no push/pull


	__ADC1_CLK_ENABLE();					//Enable ADC1 clock
    __ADC3_CLK_ENABLE();

	AdcHandle1.Instance = (ADC_TypeDef *)(ADC1_BASE);						//Use ADC1 (For PA3)
	AdcHandle1.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	AdcHandle1.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	AdcHandle1.Init.ScanConvMode          = DISABLE;
	AdcHandle1.Init.ContinuousConvMode    = DISABLE;
	AdcHandle1.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle1.Init.NbrOfDiscConversion   = 0;
	AdcHandle1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	AdcHandle1.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	AdcHandle1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	AdcHandle1.Init.NbrOfConversion       = 1;
	AdcHandle1.Init.DMAContinuousRequests = DISABLE;
	AdcHandle1.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&AdcHandle1);		//Initialise ADC

	// Configure ADC Channel
	AdcChanConfig1.Channel = ADC_CHANNEL_3;					//PA3 has Analog Channel 3 connected
	AdcChanConfig1.Rank         = 1;
	AdcChanConfig1.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	AdcChanConfig1.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle1, &AdcChanConfig1);		//Initialise ADC Channel


	AdcHandle2.Instance = (ADC_TypeDef *)(ADC3_BASE);						//Use ADC2 (For PC0)
	AdcHandle2.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	AdcHandle2.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	AdcHandle2.Init.ScanConvMode          = DISABLE;
	AdcHandle2.Init.ContinuousConvMode    = DISABLE;
	AdcHandle2.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle2.Init.NbrOfDiscConversion   = 0;
	AdcHandle2.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	AdcHandle2.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	AdcHandle2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	AdcHandle2.Init.NbrOfConversion       = 1;
	AdcHandle2.Init.DMAContinuousRequests = DISABLE;
	AdcHandle2.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&AdcHandle2);		//Initialise ADC

	// Configure ADC Channel
	AdcChanConfig2.Channel = ADC_CHANNEL_10;					//PA3 has Analog Channel 3 connected
	AdcChanConfig2.Rank         = 1;
	AdcChanConfig2.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	AdcChanConfig2.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle2, &AdcChanConfig2);		//Initialise ADC Channel


}
/**
 * Function reads joystick x or y value
 * @param - ADC hanlder to determine wether its x or y value that needs to be read
 * @return - ADC value
 **/

int joystick_readxy(ADC_HandleTypeDef Handler) {
    if(Handler.Instance == (ADC_TypeDef *)(ADC3_BASE)) { // checks if it is Y value
        return ADC3->DR;
    }
    if(Handler.Instance == (ADC_TypeDef *)(ADC1_BASE)) {  // checks if it is X value
        return ADC1->DR;
    }
}


/**
 * Call back for joystick z axis
 * enables debouncing
 * @param - void
 * @return - void
 **/
void joystickz_callback(void) {
    s452663_reg_iss_synchroniser(2); // syncrhoniser for debouncing
    EXTI->PR |= EXTI_PR_PR3;
}