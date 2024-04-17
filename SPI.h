/*
 * 	SPI.h
 *
 *  Edited on: 15 abril 2024
 *  Author:	J. Luis Pizano Escalante
 *  Editors: L. Gerardo Padilla Torres, luis.padilla@iteso.mx
 *  		 S. Nahed Garcia, ie719805@iteso.mx
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include "MK64F12.h"

#define EXAMPLE_DSPI_MASTER_BASEADDR         SPI0
#define DSPI_MASTER_CLK_SRC                  DSPI0_CLK_SRC
#define DSPI_MASTER_CLK_FREQ                 CLOCK_GetFreq(DSPI0_CLK_SRC)
#define EXAMPLE_DSPI_MASTER_PCS_FOR_INIT     kDSPI_Pcs0
#define EXAMPLE_DSPI_MASTER_PCS_FOR_TRANSFER kDSPI_MasterPcs0
#define EXAMPLE_DSPI_DEALY_COUNT             0xfffffU

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */

#define TRANSFER_SIZE     				64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 				1000000U /*! Transfer baudrate - 1M */
#define TRANSFER_BAUDRATE_MEMORY 		2000000U /*! Transfer baudrate - 2M */
#define IMAGE_MEMORY_SIZE				504		/* Images have size of 504 bytes */

void SPI_config(void);

void Recive_Data(uint8_t x);

#endif /* SPI_H_ */
