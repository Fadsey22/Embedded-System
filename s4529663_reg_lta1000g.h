/** 
 **************************************************************
 * @file mylib/s4529663_reg_lta1000g.h
 * @author Fardeen Bhuiyan - 45296635
 * @date 8032021
 * @brief  The LED Bar Display Register Driver controls the 10 Segment LED Bar (See LTA1000G
           LED Bar datasheet on Bslackboard). The 10 Segment LED Bar is connected to GPIO pins
          on the Nucleo platform. Each GPIO pin will turn a LED Bar segment on or off. You must
          manipulate the GPIO registers, directly
 * REFERENCE:  csse3010_mylib_reg_lta1000g.pdf
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
  * s4529663_reg_lta1000g_init() - initialise LED BAR GPIO pins as OUTPUTS
 * s4529663_lta1000g_seg_set() - Set the value (0 or 1) for the corresponding
LED Bar segment GPIO pin. (Internal
* s4529663_reg_lta1000g_write() Write LED BAR segnments high or low
function) 
 *************************************************************** 
 */




#include "board.h"
#include "processor_hal.h"


void s4529663_reg_lta1000g_init(void);
void lta1000g_seg_set(int segment, unsigned char segment_value);
void s4529663_reg_lta1000g_write(unsigned short value);

//#endif