/*
 * 	SPI.c
 *	brief
 *		Code for the initialization and handling of SPI
 *  Edited on: 15 abril 2024
 *  Author:	J. Luis Pizano Escalante
 *  Editors: L. Gerardo Padilla Torres, luis.padilla@iteso.mx
 *  		 S. Nahed Garcia, ie719805@iteso.mx
 *
 */

#include "bits.h"
#include "SPI.h"
#include "fsl_dspi.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "clock_config.h"
#include "delay.h"

extern uint8_t g_master_rxBuffImage_1[IMAGE_MEMORY_SIZE];
extern uint8_t g_master_rxBuffImage_2[IMAGE_MEMORY_SIZE];
extern uint8_t g_master_rxBuffImage_3[IMAGE_MEMORY_SIZE];
extern uint8_t g_master_rxBuffImage_4[IMAGE_MEMORY_SIZE];
extern uint8_t g_master_rxBuffImage_5[IMAGE_MEMORY_SIZE];

void SPI_config(void)
{

	uint32_t srcClock_Hz;

	const port_pin_config_t button_config = { //Falta configurar aqui
			kPORT_PullDisable,
			kPORT_FastSlewRate,
	        kPORT_PassiveFilterDisable,
	        kPORT_OpenDrainDisable,
	        kPORT_LowDriveStrength,
	        kPORT_MuxAlt2,
	 	 	kPORT_UnlockRegister
	};

	CLOCK_EnableClock(kCLOCK_Spi0);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortB);

	PORT_SetPinConfig(PORTD, PIN0_IDX, &button_config);
	PORT_SetPinConfig(PORTD, PIN1_IDX, &button_config);
	PORT_SetPinConfig(PORTD, PIN2_IDX, &button_config);
	PORT_SetPinConfig(PORTD, PIN3_IDX, &button_config);

	/* Master config */
	dspi_master_config_t masterConfig;

	masterConfig.whichCtar                                = kDSPI_Ctar0;
	masterConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.bitsPerFrame                  = 8U;
	masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
	masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
	masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;

	masterConfig.whichPcs           = kDSPI_Pcs0;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

	masterConfig.enableContinuousSCK        = false;
	masterConfig.enableRxFifoOverWrite      = false; //Tienes FIFOS; recuibe mas de un byte a la vez, "quiero que me sobrescribas el valor mas alto o no"
	masterConfig.enableModifiedTimingFormat = false;
	masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

	srcClock_Hz = DSPI_MASTER_CLK_FREQ;
	DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);


	/* For Memory */

	masterConfig.whichCtar                                = kDSPI_Ctar1;
	masterConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE_MEMORY;
	masterConfig.ctarConfig.bitsPerFrame                  = 8U;
	masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveLow;
	masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseSecondEdge;
	masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE_MEMORY;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE_MEMORY;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE_MEMORY;

	masterConfig.whichPcs           = kDSPI_Pcs1;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

	masterConfig.enableContinuousSCK        = false; //Caracteristicas del SPI, que el reloj siempre se este generando
	masterConfig.enableRxFifoOverWrite      = false; //Tienes FIFOS; recuibe mas de un byte a la vez, "quiero que me sobrescribas el valor mas alto o no"
	masterConfig.enableModifiedTimingFormat = false;
	masterConfig.samplePoint                = kDSPI_SckToSin0Clock; //Nos sirve para ajustar la comunicacion

	DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);

	/*Fin de la configuración*/

}
void Recive_Data(uint8_t x){
	dspi_half_duplex_transfer_t TransferMemory;

	uint8_t g_master_txADDRImage_1[bit_4] = {0x03, 0x04, 0x00, 0x00};
	uint8_t g_master_txADDRImage_2[bit_4] = {0x03, 0x04, 0x10, 0x00};
	uint8_t g_master_txADDRImage_3[bit_4] = {0x03, 0x04, 0x20, 0x00};
	uint8_t g_master_txADDRImage_4[bit_4] = {0x03, 0x04, 0x30, 0x00};
	uint8_t g_master_txADDRImage_5[bit_4] = {0x03, 0x04, 0x40, 0x00};

	switch(x){
	case bit_1:
		TransferMemory.txData					= g_master_txADDRImage_1;
		TransferMemory.rxData					= g_master_rxBuffImage_1;
		break;

	case bit_2:
		TransferMemory.txData					= g_master_txADDRImage_2;
		TransferMemory.rxData					= g_master_rxBuffImage_2;
		break;

	case bit_3:
		TransferMemory.txData					= g_master_txADDRImage_3;
		TransferMemory.rxData					= g_master_rxBuffImage_3;
		break;

	case bit_4:
		TransferMemory.txData					= g_master_txADDRImage_4;
		TransferMemory.rxData					= g_master_rxBuffImage_4;
		break;

	case bit_5:
		TransferMemory.txData					= g_master_txADDRImage_5;
		TransferMemory.rxData					= g_master_rxBuffImage_5;
		break;

	default:
		TransferMemory.txData					= g_master_txADDRImage_1;
		TransferMemory.rxData					= g_master_rxBuffImage_1;
		break;
	}

	TransferMemory.txDataSize				= bit_4;
	TransferMemory.rxDataSize				= IMAGE_MEMORY_SIZE;
	TransferMemory.isTransmitFirst			= true;
	TransferMemory.isPcsAssertInTransfer	= true;
	TransferMemory.configFlags				= kDSPI_MasterCtar1 | kDSPI_MasterPcs1 | kDSPI_MasterPcsContinuous;

	DSPI_MasterHalfDuplexTransferBlocking(EXAMPLE_DSPI_MASTER_BASEADDR, &TransferMemory);
}



