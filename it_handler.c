/** 
 **************************************************************
 * @file stages/s2/it_handler.c
 * @author Fardeen Bhuiyan - 45296635
 * @date 220321
 * @brief  interrupt service routine for z axis push button and on board push button
 * REFERENCE: csse3010_mylib_reg_pantilt.pdf  and csse3010_mylib_reg_joystick.pdf
 */



#include "processor_hal.h"
#include "board.h"
#include "stm32f429xx.h"
#include "s4529663_reg_iss.h"
#include "s4529663_reg_pantilt.h"
#include "s4529663_reg_joystick.h"
#include "s4529663_reg_pb.h"
#include <stdint.h>
#include <stdbool.h>

/**
*call back that calls ISR for joystick push button
*@return - void
*@param- void
**/
void EXTI3_IRQHandler(void) {
    joystickz_callback();
}

/**
*call back that calls ISR for on board push button
*@return - void
*@param- void
**/
void EXTI15_10_IRQHandler(void) {
    s4529663_reg_pb_on_isr();   // Callback for C13
}