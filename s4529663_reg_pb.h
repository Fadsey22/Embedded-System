/** 
 **************************************************************
 * @file mylib/s4529663_reg_pb.h
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
#include "s4529663_reg_iss.h"

void s4529663_reg_pb_on_init(void);
void s4529663_reg_pb_on_isr(void);
void s4529663_reg_pb_iss_init(void);
void s4529663_reg_pb_iss_isr(void);

//#endif