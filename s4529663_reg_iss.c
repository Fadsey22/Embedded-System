/** 
 **************************************************************
 * @file mylib/s4529663_reg_iss.c
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

#include <stdint.h>
#include "board.h"
#include "stm32f429xx.h"
#include "processor_hal.h"

#define S4529663_REG_ISS_SOURCE_1 0
#define S4529663_REG_ISS_SOURCE_2 1
#define S4529663_REG_ISS_SOURCE_3 2
#define S4529663_REG_ISS_SOURCE_4 3
uint32_t iss_eventcounter_val[4];
uint32_t iss_lasttimer_val[4];
uint32_t iss_delay_val[4];

/**
 * Function that initallises all ISS values 
 * @return - void
 * @param - void
 **/


void s4529663_reg_iss_init(void) {
    for(int i = 0;  i < 4; i++) {
        iss_eventcounter_val[i] = 0;
        iss_lasttimer_val[i] = 0;
        iss_delay_val[i] = 10;
    }
}

/**
* function that reads the event counter of a source
*@return - the count of the number of events
*@param - the source that is being tracked 
**/
uint32_t s4529663_reg_iss_eventcounter_read(unsigned char signal_source_index) {
    return iss_eventcounter_val[signal_source_index];

}

/**
* function that reads the last timer of a source
*@return - the last time a source was utilised
*@param - the source that is being tracked
**/

uint32_t s4529663_reg_iss_lasttimer_read(unsigned char signal_source_index) {
    return iss_lasttimer_val[signal_source_index];
}

/**
*function that resets event counter
*@return - void
*@param - the source that will be set to 0
*/

void s4529663_reg_iss_eventcounter_reset(unsigned char signal_source_index) {
    iss_eventcounter_val[signal_source_index] = 0;
}

/**
 *resets the last timer of a source to 0
 *@return- void
 *@param - the source being set to 0
 **/

void s4529663_reg_iss_lasttimer_reset(unsigned char signal_source_index) {
    iss_lasttimer_val[signal_source_index] == 0;
}

/**
 * function that sets the delay value of a source
 * @return - void
 * @param - source being tracked and delay value
 **/
void s4529663_reg_iss_delaytimer_ctrl(unsigned char signal_source_index, int delay_value) {
    iss_delay_val[signal_source_index] = delay_value;
}


/**
 * Function that handles debouncing of a signal
 * @return- void
 * @param - source to be debounced
 * */

void s452663_reg_iss_synchroniser(unsigned char signal_source_index) {
    switch (signal_source_index) // checks source 
    {
        case S4529663_REG_ISS_SOURCE_1:
   
            if(s4529663_reg_iss_lasttimer_read(S4529663_REG_ISS_SOURCE_1) == 0) {
            iss_lasttimer_val[S4529663_REG_ISS_SOURCE_1] = HAL_GetTick();
        }
            else if(HAL_GetTick() - s4529663_reg_iss_lasttimer_read(S4529663_REG_ISS_SOURCE_1)  >= 50) { // waits 50ms before registering event
            iss_lasttimer_val[S4529663_REG_ISS_SOURCE_1] = 0;
            iss_eventcounter_val[S4529663_REG_ISS_SOURCE_1]++;
            s4529663_reg_iss_lasttimer_reset(S4529663_REG_ISS_SOURCE_1);

        }
        else {
            s4529663_reg_iss_lasttimer_reset(S4529663_REG_ISS_SOURCE_1);
        }
        break;
        case S4529663_REG_ISS_SOURCE_2:
            if(s4529663_reg_iss_lasttimer_read(S4529663_REG_ISS_SOURCE_2) == 0) {
                iss_lasttimer_val[S4529663_REG_ISS_SOURCE_2] = HAL_GetTick();
            }
            else if(HAL_GetTick() - s4529663_reg_iss_lasttimer_read(S4529663_REG_ISS_SOURCE_2)  >= 50) {
                iss_lasttimer_val[S4529663_REG_ISS_SOURCE_2] = 0;
                iss_eventcounter_val[S4529663_REG_ISS_SOURCE_2]++;
                s4529663_reg_iss_lasttimer_reset(S4529663_REG_ISS_SOURCE_2);
            }
            else {
                s4529663_reg_iss_lasttimer_reset(S4529663_REG_ISS_SOURCE_2);
            }
            break;
        case S4529663_REG_ISS_SOURCE_3:
               if(s4529663_reg_iss_lasttimer_read(S4529663_REG_ISS_SOURCE_3) == 0) {
                iss_lasttimer_val[S4529663_REG_ISS_SOURCE_3] = HAL_GetTick();
            }
            else if(HAL_GetTick() - s4529663_reg_iss_lasttimer_read(S4529663_REG_ISS_SOURCE_3)  >= 50) {
                iss_lasttimer_val[S4529663_REG_ISS_SOURCE_3] = 0;
                iss_eventcounter_val[S4529663_REG_ISS_SOURCE_3]++;
                s4529663_reg_iss_lasttimer_reset(S4529663_REG_ISS_SOURCE_3);
            }
            else {
                s4529663_reg_iss_lasttimer_reset(S4529663_REG_ISS_SOURCE_3);
            }
            break;
     }
}