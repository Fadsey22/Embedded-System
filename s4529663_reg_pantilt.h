/** 
 **************************************************************
 * @file mylib/s4529663_reg_pantilt.h
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
#include <stdint.h>

#define S4529663_REG_PANTILT_PAN_WRITE(angle) s4529663_pantilt_angle_write(0,angle)) // function that sets pan angle
#define S4529663_REG_PANTILT_PAN_READ ()  s4529663_pantilt_angle_read(0) // function that reads pan angle
#define S4529663_REG_PANTILT_TILT_WRITE(angle) s4529663_pantilt_angle_write(1,angle) // function that writes the tilt angle
#define S4529663_REG_PANTILT_TILT_READ() s4529663_pantilt_angle_read(1)  // function that reads the tilt angle.
#define S4529663_REG_PANTILT_PAN_ZERO_CAL_OFFSET 13.5 // this is interms of degrees
#define S4529663_REG_PANTILT_TILT_ZERO_CAL_OFFSET 0 // this is interms of degrees
void s4529663_reg_pantilt_init(void);
void s4529663_pantilt_angle_write(int type, int angle);
double s4529663_pantilt_angle_read(int type);