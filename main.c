/** 
 **************************************************************
 * @file stages/s2/main.c
 * @author Fardeen Bhuiyan - 45296635
 * @date 220321
 * @brief  controls servo movement, pwm generation, led bar counter display
 * REFERENCE: csse3010_stage2
 */

#include "processor_hal.h"
#include "board.h"
#include "stm32f429xx.h"
#include "s4529663_reg_iss.h"
#include "s4529663_reg_pantilt.h"
#include "s4529663_reg_joystick.h"
#include "s4529663_reg_pb.h"
#include "s4529663_reg_lta1000g.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * function that controls led value for tilt angle
 * @return - uint16_t led bar value
 * @param - angle value
 * */


uint16_t tiltled(int angle) {
	uint16_t ret = 0;
	// if statments to map each angle range to an led
	if(angle <= 0) {
		ret = 0b0000000000;
	}
	else if (angle > 0 && angle < 18) {
		ret = 0b0000000001;

	}
	else if (angle > 17 && angle < 36)
	{
		ret = 0b0000000011;
		
	}
	else if(angle > 35 && angle < 54) {
		ret = 0b0000000111;
	}

	else if(angle > 52 && angle < 72) {
		ret = 0b0000001111;
	}
	else if (angle > 71 && angle <= 85) {
		ret = 0b00000011111;
	}

	
	return ret;

}


/**
 * function that controls led value for pan angle
 * @return - uint16_t led bar value
 * @param - angle value
 * */

uint16_t panled(int angle) {
	uint16_t ret = 0;
	// if statments to map each angle range to an led
	if(angle <= 0) {
		ret = 0b0000000000;
	}
	else if (angle > 0 && angle < 18) {
		ret = 0b1000000000;

	}
	else if (angle > 17 && angle < 36)
	{
		ret = 0b1100000000;
		
	}
	else if(angle > 35 && angle < 54) {
		ret = 0b1110000000;
	}

	else if(angle > 52 && angle < 72) {
		ret = 0b1111000000;
	}
	else if (angle > 71 && angle <= 85) {
		ret = 0b1111100000;
	}

	
	return ret;

}

/**
 * main function to execute all functionality
 * including pwm, servo movement, led bar display
 * @return - void
 * @param - void
 * */


int main(void)
{
	
	unsigned int adc_valuey; // y value for joystick
	unsigned int adc_valuex; //x value for joystick

	HAL_Init(); //Initialises HAL Functionality
	s4529663_reg_joystick_init(); // init joystick functionality
	s4529663_reg_pantilt_init(); //init pwm and servo position to 0,0
	s4529663_reg_pb_on_init(); // initialises on board push button
	s4529663_reg_lta1000g_init(); // intialises led bar
	double panangle2 = 0.0; // variable that tracks angle of pan
	double tiltangle2 = 0.0; // variable that tracks angle of tilt angle
	double pangrad = 0.041565; // gradient of linear relationship between adcx and pan angle
	double tiltgrad = 0.041565; // gradient of linear relationship between adcy and tilt angle
	uint16_t lpangle = 0; // variable that controls that led bar based on pan angle
	uint16_t ltangle = 0; // variable that controls that led bar based on tilt angle
	char direction = 'f'; // direction of pan when push button is pressed f is +10 r is -10
	int but = 0; // flag that checks if joystick button has been pressed 
	int offset = 0; // ofset variable that controls were joysick is centered based on push button


	// Main Processing Loop
	while (1)
	{
		if (s4529663_reg_iss_eventcounter_read(2) - 1 == 0) // checks for joystick press. moves it 10 degrees, (direction depends on direction variable)
		{	
			but = 1; // set pushbutton flag to be set
			s4529663_reg_iss_lasttimer_reset(2); // reset time of button pressed
			s4529663_reg_iss_eventcounter_reset(2); // reset eventcoutner pressed
		}

		if(s4529663_reg_iss_eventcounter_read(1) - 1 == 0)  // checks for on board push button press.to set direction
		{
			s4529663_reg_iss_lasttimer_reset(1);
            s4529663_reg_iss_eventcounter_reset(1);
			if(direction == 'f') { // reverses the direction
				direction = 'r';
			}
			else {
				direction = 'f';
			}
		}

		HAL_ADC_Start(&AdcHandle2); // Start ADC conversion
		HAL_ADC_Start(&AdcHandle1);

		// Wait for ADCY conversion to finish
		while (HAL_ADC_PollForConversion(&AdcHandle2, 10) != HAL_OK);
		// Wait for ADCX conversion to finish
		adc_valuey = S4529663_REG_JOYSTICK_Y_READ(); //reads ADC Y value
		while (HAL_ADC_PollForConversion(&AdcHandle1, 10) != HAL_OK);
		adc_valuex = S4529663_REG_JOYSTICK_X_READ(); //reads ADC X value
		panangle2 = ((pangrad*adc_valuex)) - 85; //linear equation that maps adcx to pan angle
		tiltangle2 = ((tiltgrad*adc_valuey)) - 85; //linear equation that maps adcy to tilt angle
		// PAN
		if (panangle2 < 10 && abs(panangle2) < 82) // checks if pan is centered (dead zone)
		{
			panangle2 = 0;
					if(but == 1) { // checks if joystick pb has been pressed
			if(direction == 'f') { // checks direction
				offset += 10; //+ 10 if forward
			if(panangle2 < 10) {
				panangle2 = 10; // offset for deadzone applies as linear eq is not perfect
			}
			}
			else{
				offset -= 10; // -10 if backwards
			}
			but = 0;
			if(offset >70 || offset < -70) { // reset the pan back to zero if it is greater 70 or less than -70
				offset = 0;
			}
		}
			
		}
		if(panangle2 > 82) {
			panangle2 = 85;
			offset = 0;
		}

		if(abs(panangle2) > 82 && panangle2 < 0) {
			panangle2 = -85;
			offset = 0;
		}
		s4529663_pantilt_angle_write(0,panangle2 + offset);
		// TILT

		if (tiltangle2 < 10 && abs(tiltangle2) < 82) // checks if tilt is in deadzone for accuracy
		{
			tiltangle2 = 0;
		}
		if(tiltangle2 > 82) { // checks if it is greater than 82(offset of 3 for accuracy of equation)
			tiltangle2 = 85;
		}
		if(abs(tiltangle2) > 82 && tiltangle2 < 0) { // checks if less than -82
			tiltangle2 = -85;
		}
		s4529663_pantilt_angle_write(1,tiltangle2); // write tilt angle
		lpangle = abs((int) panangle2 + offset);
		ltangle = abs((int)tiltangle2);
		ltangle = tiltled(abs(ltangle));
		lpangle = panled(abs(lpangle));
		uint16_t display = ltangle + lpangle;
		s4529663_reg_lta1000g_write((display)); // display angles on led upper 5 being pan, lower 5 being tilt
	}
}