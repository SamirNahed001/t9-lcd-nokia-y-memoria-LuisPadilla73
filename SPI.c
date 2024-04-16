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

extern uint8_t g_master_rxBuffImage[][IMAGE_MEMORY_SIZE];

void SPI_config(void)
{
    const port_pin_config_t button_config = {kPORT_PullDisable, kPORT_FastSlewRate, kPORT_PassiveFilterDisable, kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAlt2, kPORT_UnlockRegister};
    const uint32_t srcClock_Hz = DSPI_MASTER_CLK_FREQ;

    CLOCK_EnableClock(kCLOCK_Spi0);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortB);

    for (int i = 0; i < 4; ++i)
    {
        PORT_SetPinConfig(PORTD, PIN0_IDX + i, &button_config);
    }

    dspi_master_config_t masterConfig;

    /* Master config for LCD */
    masterConfig.whichCtar = kDSPI_Ctar0;
    masterConfig.ctarConfig.baudRate = TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.bitsPerFrame = 8U;
    masterConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
    masterConfig.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.whichPcs = kDSPI_Pcs0;
    masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;
    masterConfig.enableContinuousSCK = false;
    masterConfig.enableRxFifoOverWrite = false;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint = kDSPI_SckToSin0Clock;

    DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);

    /* Master config for Memory */
    masterConfig.whichCtar = kDSPI_Ctar1;
    masterConfig.ctarConfig.baudRate = TRANSFER_BAUDRATE_MEMORY;
    masterConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
    masterConfig.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
    masterConfig.whichPcs = kDSPI_Pcs1;

    DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);
}

void Recive_Data(uint8_t x)
{
    dspi_half_duplex_transfer_t TransferMemory;

    const uint8_t g_master_txADDRImage[][4] = {{0x03, 0x04, 0x00, 0x00}, {0x03, 0x04, 0x10, 0x00}, {0x03, 0x04, 0x20, 0x00}, {0x03, 0x04, 0x30, 0x00}, {0x03, 0x04, 0x40, 0x00}};

    uint8_t *rxBuffer = g_master_rxBuffImage[x - 1];

    TransferMemory.txData = g_master_txADDRImage[x - 1];
    TransferMemory.rxData = rxBuffer;
    TransferMemory.txDataSize = 4;
    TransferMemory.rxDataSize = IMAGE_MEMORY_SIZE;
    TransferMemory.isTransmitFirst = true;
    TransferMemory.isPcsAssertInTransfer = true;
    TransferMemory.configFlags = (x == 5) ? kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous : kDSPI_MasterCtar1 | kDSPI_MasterPcs1 | kDSPI_MasterPcsContinuous;

    DSPI_MasterHalfDuplexTransferBlocking(EXAMPLE_DSPI_MASTER_BASEADDR, &TransferMemory);
}



