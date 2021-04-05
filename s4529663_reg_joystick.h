/** 
 **************************************************************
 * @file mylib/s4529663_reg.joystick.h
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
void s4529663_reg_joystick_init(void);
int joystick_readxy(ADC_HandleTypeDef Handler);
void joystickz_callback(void);