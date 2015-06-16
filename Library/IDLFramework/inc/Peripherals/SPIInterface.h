/******************************************************************************
* File Name          : SPIInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/5/2015
* Description        : This defines functions for the SPI Interface
* This is a thin interface and most of the functions are defined in the hardware file
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

/* Includes ------------------------------------------------------------------*/

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Containers/Buffer.h"
#include "DMAInterface.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

class SPIPort{
	public:
		SPIPort(AF_Periph spi_num, IO_Pin* pin_sclk, IO_Pin* pin_mosi, IO_Pin* pin_miso,uint32_t clk_freq,uint32_t timeout_slack);
		void doTasks();
	
		PERIPH_STATUS StartTransfer(uint8_t txbyte, Buffer* rxbuf, uint32_t num_rx_bytes, volatile PERIPH_TRANSACTION_STATE* transaction_state, IO_Pin* pin_cs);
		PERIPH_STATUS StartTransfer(Buffer* txbuf, Buffer* rxbuf, uint32_t num_rx_bytes, volatile PERIPH_TRANSACTION_STATE* transaction_state, IO_Pin* pin_cs);
		void EndTransfer(PERIPH_TRANSACTION_STATE state);
	
		//Setup Functions
		PERIPH_STATUS setClkFreq(uint32_t des_freq);
		void useDMA_Tx(uint8_t stream_num);
		void useDMA_Rx(uint8_t stream_num);
		void useINT(INTERRUPT_PRIORITY irq_priority);
	
		bool isLocked(){return Locked;}

		PERIPH_STATUS Rx(Buffer* rxBuf, uint32_t numTxBytes, IO_Pin* pin_cs);	
		PERIPH_STATUS Tx(Buffer* txBuf, IO_Pin* pin_cs);	
		PERIPH_STATUS TxRx(uint8_t txByte, Buffer* rxBuf, uint32_t numRxBytes, IO_Pin* pin_cs);
		
		//These require manual control of CS pin
		PERIPH_STATUS RxBlocking(Buffer* rxBuf, uint32_t numTxBytes);	
		PERIPH_STATUS TxBlocking(Buffer* txBuf);	
		PERIPH_STATUS TxRxBlocking(uint8_t txByte, Buffer* rxBuf, uint32_t numRxBytes);
		PERIPH_STATUS TxRxBlocking(uint8_t txByte, uint8_t &rxByte);
		
		//Interrupt Callback function
		void IRQCallback(void);
		
		uint8_t TxRxByte(uint8_t byte);
	
	private:
		~SPIPort();
		void ResetErrorCnt();
		void setTransactionState(PERIPH_TRANSACTION_STATE state);
		volatile void* SPIBase;
		AF_Periph AF_SPIx;
		uint32_t ClkFreq;
		uint32_t BytePeriod_uS; //Time to transmit 1 byte
		IO_Pin* PinSCLK;
		IO_Pin*	PinMOSI;
		IO_Pin*	PinMISO;
		IO_Pin* PinCS;
		bool is1DataLine; //Uses MOSI for bidirectional data
	
		DMAInterface* DMAPort_Tx;
		DMAInterface* DMAPort_Rx;
		bool usingDMA_Tx;
		bool usingDMA_Rx;
		bool usingINT;
	
		//Transaction values
		Buffer* TxBuf;
		Buffer* RxBuf;
		volatile int32_t numRxBytesRemaining;
		volatile PERIPH_TRANSACTION_STATE* pTransactionState;
		volatile bool Locked;
		Timer* TimeoutTimer;
		uint32_t numTimeouts;
		uint32_t numErrors;
		uint32_t TimeoutSlack;

		//Functions Defined in SPIHardware.cpp
		PERIPH_STATUS HardwareInit();	
		PERIPH_STATUS HardwareStartTransaction();
		PERIPH_STATUS HardwareEndTransaction();
		bool isTxReady();
		bool isRxNReady();
		bool isBusy();
		PERIPH_STATUS Disable();
		PERIPH_STATUS Enable();
	
};


#endif 
