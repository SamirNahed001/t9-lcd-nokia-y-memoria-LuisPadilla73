/**
 *	Code for the initialization and handling of SPI
 *  Edited on: 15 abril 2024
 *  Author:	J. Luis Pizano Escalante
 *  Editors: L. Gerardo Padilla Torres, luis.padilla@iteso.mx
 *  		 S. Nahed Garcia, ie719805@iteso.mx
 */

 

#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include "stdint.h"
#include "SPI.h"
#include "Delay.h"
#include "bits.h"

#define IMAGE_SIZE 				504

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
extern const uint8_t ITESO[IMAGE_SIZE];
extern uint8_t g_master_rxBuffImage_1[IMAGE_SIZE];
extern uint8_t g_master_rxBuffImage_2[IMAGE_SIZE];
extern uint8_t g_master_rxBuffImage_3[IMAGE_SIZE];
extern uint8_t g_master_rxBuffImage_4[IMAGE_SIZE];
extern uint8_t g_master_rxBuffImage_5[IMAGE_SIZE];

int main(void)
{

	SPI_config();

	LCD_nokia_init(); /*! Configuration function for the LCD */

	for(;;) {
		LCD_nokia_clear();/*! It clears the information printed in the LCD*/
		LCD_nokia_bitmap(ITESO); /*! It prints an array that hold an image, in this case is the initial picture*/
		delay(65000);
		LCD_nokia_clear();
		Recive_Data(bit_1);
		Recive_Data(bit_1);
		Recive_Data(bit_1);
		Recive_Data(bit_1);
		Recive_Data(bit_1);
		LCD_nokia_bitmap(g_master_rxBuffImage_1);
		delay(65000);
		LCD_nokia_clear();
		Recive_Data(bit_1);
		Recive_Data(bit_5);
		Recive_Data(bit_4);
		Recive_Data(bit_3);
		Recive_Data(bit_2);
		LCD_nokia_bitmap(g_master_rxBuffImage_2);
		delay(65000);
		LCD_nokia_clear();
		Recive_Data(bit_2);
		Recive_Data(bit_1);
		Recive_Data(bit_5);
		Recive_Data(bit_4);
		Recive_Data(bit_3);
		LCD_nokia_bitmap(g_master_rxBuffImage_3);
		delay(65000);
		LCD_nokia_clear();
		Recive_Data(bit_4);
		Recive_Data(bit_4);
		Recive_Data(bit_4);
		Recive_Data(bit_4);
		Recive_Data(bit_4);
		LCD_nokia_bitmap(g_master_rxBuffImage_4);
		delay(65000);
		LCD_nokia_clear();
		Recive_Data(bit_1);
		Recive_Data(bit_2);
		Recive_Data(bit_3);
		Recive_Data(bit_4);
		Recive_Data(bit_5);
		LCD_nokia_bitmap(g_master_rxBuffImage_5);
		delay(65000);
	}
	
	return 0;
}

