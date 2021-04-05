/** 
 **************************************************************
 * @file mylib/s4529663_reg_lta1000g.c.c
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
#include "s4529663_reg_lta1000g.h"
//#include <stdbool.h>


/**
 * function that initialises the LED BAR GPIO OUTPUTS
 * @return - void
 * @param - void
 **/
void s4529663_reg_lta1000g_init(void) {
    // Enable the GPIO  Clocks
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();

  //Initialise G9 as an output.
  GPIOC->MODER &= ~(0x03 << (6 * 2));  //clear bits
  GPIOC->MODER |= (0x01 << (6 * 2));   //Set for push pull

  GPIOC->OSPEEDR &= ~(0x03<<(6 * 2));
	GPIOC->OSPEEDR |=   0x02<<(6 * 2);  // Set for Fast speed

  GPIOC->OTYPER &= ~(0x01 << 6);       //Clear Bit for Push/Pull utput

  // Activate the Pull-up or Pull down resistor for the current IO
  GPIOC->PUPDR &= ~(0x03 << (6 * 2));   //Clear Bits
  GPIOC->PUPDR |= ((0x01) << (6 * 2));  //Set for Pull down output

 //Initiliase G14 as an output

  GPIOB->MODER &= ~(0x03 << (15 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (15 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(15 * 2));
	GPIOB->OSPEEDR |=   0x02<<(15* 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 15);       //Clear Bit for Push/Pull utput
  
  // Activate the Pull-up or Pull down resistor for the current IO

  GPIOB->PUPDR &= ~(0x03 << (13 * 2));   //Clear Bits
  GPIOB->PUPDR |= ((0x01) << (13 * 2));  //Set for Pull down output


  //Initilaise F15 as input

  GPIOB->MODER &= ~(0x03 << (13 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (13 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(13 * 2));
	GPIOB->OSPEEDR |=   0x02<<(13* 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 13);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOB->PUPDR &= ~(0x03 << (13 * 2));   //Clear Bits
  GPIOB->PUPDR |= ((0x01) << (13 * 2));  //Set for Pull down output
  



  //Initilaise E13 as input

   GPIOB->MODER &= ~(0x03 << (12 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (12 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(12 * 2));
	GPIOB->OSPEEDR |=   0x02<<(12* 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 12);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOB->PUPDR &= ~(0x03 << (12 * 2));   //Clear Bits
  GPIOB->PUPDR |= ((0x01) << (12 * 2));  //Set for Pull down output

  // Initiliase F14

  GPIOA->MODER &= ~(0x03 << (15 * 2));  //clear bits
  GPIOA->MODER |= (0x01 << (15 * 2));   //Set for push pull

  GPIOA->OSPEEDR &= ~(0x03<<(15 * 2));
	GPIOA->OSPEEDR |=   0x02<<(15* 2);  // Set for Fast speed

  GPIOA->OTYPER &= ~(0x01 << 15);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOA->PUPDR &= ~(0x03 << (15 * 2));   //Clear Bits
  GPIOA->PUPDR |= ((0x01) << (15 * 2));  //Set for Pull down output
  


  // Innitialise E11


  GPIOC->MODER &= ~(0x03 << (7 * 2));  //clear bits
  GPIOC->MODER |= (0x01 << (7 * 2));   //Set for push pull

  GPIOC->OSPEEDR &= ~(0x03<<(7 * 2));
	GPIOC->OSPEEDR |=   0x02<<(7* 2);  // Set for Fast speed

  GPIOC->OTYPER &= ~(0x01 << 7);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOC->PUPDR &= ~(0x03 << (7 * 2));   //Clear Bits
  GPIOC->PUPDR |= ((0x01) << (7 * 2));  //Set for Pull down output


  //Initialise E9
   GPIOB->MODER &= ~(0x03 << (5 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (5 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(5 * 2));
	GPIOB->OSPEEDR |=   0x02<<(5* 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 5);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOB->PUPDR &= ~(0x03 << (5 * 2));   //Clear Bits
  GPIOB->PUPDR |= ((0x01) << (5 * 2));  //Set for Pull down output

  // Init F13


  GPIOB->MODER &= ~(0x03 << (3 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (3 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(3 * 2));
	GPIOB->OSPEEDR |=   0x02<<(3* 2);  // Set for Fast speed
  GPIOB->OTYPER &= ~(0x01 << 3);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOB->PUPDR &= ~(0x03 << (3 * 2));   //Clear Bits
  GPIOB->PUPDR |= ((0x01) << (3 * 2));  //Set for Pull down output

  // Init F12


  GPIOA->MODER &= ~(0x03 << (4 * 2));  //clear bits
  GPIOA->MODER |= (0x01 << (4 * 2));   //Set for push pull

  GPIOA->OSPEEDR &= ~(0x03<<(4 * 2));
	GPIOA->OSPEEDR |=   0x02<<(4* 2);  // Set for Fast speed

  GPIOA->OTYPER &= ~(0x01 << 4);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOA->PUPDR &= ~(0x03 << (4 * 2));   //Clear Bits
  GPIOA->PUPDR |= ((0x01) << (4 * 2));  //Set for Pull down output


  // Init D15


  GPIOB->MODER &= ~(0x03 << (4 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (4 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(4 * 2));
	GPIOB->OSPEEDR |=   0x02<<(4* 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 4);       //Clear Bit for Push/Pull output
 // Activate the Pull-up or Pull down resistor for the current IO
   GPIOB->PUPDR &= ~(0x03 << (4 * 2));   //Clear Bits
  GPIOB->PUPDR |= ((0x01) << (4 * 2));  //Set for Pull down output
} 


/**
 * Function that sets LED segmen to high or low
 * @return - void
 * @param - segment to be set and state to be set 0 for low, 1 for high
 **/


void lta1000g_seg_set(int segment, unsigned char segment_value) {
    switch (segment) {
        case 1:
            if (segment_value == 1) {
                GPIOC->ODR |= (0x01 << 6);
            }
            else {
                GPIOC->ODR &= ~(0x01 << 6);
            }
            break;
        case 2:
            if (segment_value == 1) {
                GPIOB->ODR |= (0x01 << 15);
            }
            if(segment_value == 0) {
                GPIOB->ODR &= ~(0x01 << 15);
            }
            break;
        case 3:
            if (segment_value == 1) {
                GPIOB->ODR |= (0x01 << 13);
            }
            else {
                GPIOB->ODR &= ~(0x01 << 13);
            }
            break;
        case 4:
            if (segment_value == 1) {
                GPIOB->ODR |= (0x01 << 12);
            }
            else {
                GPIOB->ODR &= ~(0x01 << 12);
            }
            break;
        case 5:
          if (segment_value == 1) {
                GPIOA->ODR |= (0x01 << 15);
            }
            else {
                GPIOA->ODR &= ~(0x01 << 15);
            }
            break;
        case 6:
          if (segment_value == 1) {
                GPIOC->ODR |= (0x01 << 7);
            }
            else {
                GPIOC->ODR &= ~(0x01 << 7);
            }
            break;
        case 7:
            if (segment_value == 1) {
                GPIOB->ODR |= (0x01 << 5);
            }
            else {
                GPIOB->ODR &= ~(0x01 << 5);
            }
            break;
        case 8:
              if (segment_value == 1) {
                GPIOB->ODR |= (0x01 << 3);
            }
            else {
                GPIOB->ODR &= ~(0x01 << 3);
            }
            break;
          case 9:
              if (segment_value == 1) {
                GPIOA->ODR |= (0x01 << 4);
            }
            else {
                GPIOA->ODR &= ~(0x01 << 4);
            }
            break;
            case 10:
              if (segment_value == 1) {
                GPIOB->ODR |= (0x01 << 4);
            }
            else {
                GPIOB->ODR &= ~(0x01 << 4);
            }
            break;
        }



}

/**
 * function that can set all of the LED bar segments
 * @return - void
 * @param - binary number which sets the 10 bits of the LED BAR
 **/

void s4529663_reg_lta1000g_write(unsigned short value) {
  int vg = value;
  int endbit = 0;
  for(int i = 1; i < 11; i++) {
    endbit = vg & 1;
    vg = vg >> 1;
    lta1000g_seg_set(i,endbit);
  }
}

    