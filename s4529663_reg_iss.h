/** 
 **************************************************************
 * @file mylib/s4529663_reg_iss.h
 * @author Fardeen Bhuiyan - 45296635
 * @date 8032021
 * @brief The Input Signal Synchroniser Mylib Register Driver is used to synchronise signals from
inputs such as pushbuttons and switches. It ’debounces’ an input signal and ensures that only
signals with with a minimum period of 50ms is considered to be an event
 * REFERENCE: csse3010_mylib_reg_iss.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *s4529663 reg iss init() - initialise the counters
 *s4529663_reg_iss_synchroniser
(unsigned char signal source index) - Synchronise the input signal
with debouncing
s4529663_reg_iss_eventcounter_read
(unsigned char signal source index) - Returns the specified event counter value
s4529663_reg_iss_lasttimer_read
(unsigned char signal source index) - Returns the specified last time value
s4529663 reg iss eventcounter reset - Reset the specified event counter value
(unsigned char signal source index)
s4529663 reg iss lasttimer reset
(unsigned char signal source index) - Reset the specified last time value.
sxxxxxx reg iss delaytimer ctrl
(unsigned char signal source index,
int delay value) - Set the delay value for the specified source.

 *************************************************************** 
 */


#include "board.h"
#include "processor_hal.h"
#include "stm32f429xx.h"

#define S4529663_REG_ISS_SOURCE_1 0
#define S4529663_REG_ISS_SOURCE_2 1
#define S4529663_REG_ISS_SOURCE_3 2
#define S4529663_REG_ISS_SOURCE_4 3
uint32_t iss_eventcounter_val[3];
uint32_t iss_lasttimer_val[3];
uint32_t iss_delay_val[3];
void s4529663_reg_iss_init(void);
uint32_t s4529663_reg_iss_eventcounter_read(unsigned char signal_source_index);
uint32_t s4529663_reg_iss_lasttimer_read(unsigned char signal_source_index);
void s4529663_reg_iss_eventcounter_reset(unsigned char signal_source_index);
void s4529663_reg_iss_lasttimer_reset(unsigned char signal_source_index);
void s4529663_reg_iss_delaytimer_ctrl(unsigned char signal_source_index, int delay_value);
void s452663_reg_iss_synchroniser(unsigned char signal_source_index);

//#endif