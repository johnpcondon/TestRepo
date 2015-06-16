/******************************************************************************
* File Name          : UARTInterface.h
* Author             : John Condon
* Version            : V 2.0
* Date               : 6/3/2015
* Description        : Hardware agnostic UART Port Interface
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef UARTINTERFACE_H
#define UARTINTERFACE_H

#include "Peripherals/PortInterface.h"
#include "Containers/CircularBuffer.h"
#include "Peripherals/IOInterface.h"
#include "DMAInterface.h"

enum UART_Baudrate{
	UART_Baudrate_4800,
	UART_Baudrate_9600,
	UART_Baudrate_14400,
	UART_Baudrate_19200,
	UART_Baudrate_28800,
	UART_Baudrate_38400,
	UART_Baudrate_57600,
	UART_Baudrate_115200,
	UART_Baudrate_230400,
	UART_Baudrate_250000,
	UART_Baudrate_460800,
	UART_Baudrate_921600,
};

enum UART_Wordlength{
	UART_Wordlength_8,
	UART_Wordlength_9,
};

enum UART_Parity{
	UART_Parity_None,
	UART_Parity_Even,
	UART_Parity_Odd,
};

enum UART_Stopbits{
	UART_Stopbits_0_5,
	UART_Stopbits_1,
	UART_Stopbits_1_5,
	UART_Stopbits_2,
};

//enum UART_FlowControl{
//	UART_FlowControl_Hardware,
//	UART_FlowControl_None,
//};

//enum UART_Num{
//	UART_Num_0,
//	UART_Num_1,
//	UART_Num_2,
//	UART_Num_3,
//	UART_Num_4,
//};

 //Uart Class, inherits from port class
class UartPort:public Port{
      
    public:
		UartPort(const char* name,
							AF_Periph uart_periph,
							IO_Pin* pin_rx,
							IO_Pin* pin_tx,
							IO_Pin* pin_rts,
							IO_Pin* pin_cts,
						 int32_t bufSizeRx,
						 int32_t bufSizeTx,
						 uint32_t tx_timeout,
						 int32_t bufSizeOutputStream,
						 uint32_t outputstream_timeout,
						 uint32_t outstream_watermark_remaining) ;

		UartPort(const char* name,
							AF_Periph uart_periph,
							IO_Pin* pin_rx,
							IO_Pin* pin_tx,
						 int32_t bufSizeRx,
						 int32_t bufSizeTx,
						 uint32_t tx_timeout,
						 int32_t bufSizeOutputStream,
						 uint32_t outputstream_timeout,
						 uint32_t outstream_watermark_remaining);		
	  void doTasks();  //Call continously to perform Uart tasks
		
		//Initializes Hardware
		void Init(UART_Baudrate baudrate,
							UART_Wordlength wordlength,
							UART_Parity parity,
							UART_Stopbits stopbits);

		void useDMA_Tx(uint8_t stream_num);
		void useDMA_Rx(uint8_t stream_num);
		void useINT_Tx();
		void useINT_Rx();
		//void addCTS(IO_Pin* pin_cts); //Adds the implementation of just CTS, call before init
		//void addRTS(IO_Pin* pin_rts);	//Adds the implementation of just RTS, call before init
		
		Timer* TimeoutTimer;
		//--------------------------------------------------------
		//Hardware Functions Implemented in UARTHardware.h
		//--------------------------------------------------------
		int32_t ProcessRx();	//Process all Rx functions
		int32_t ProcessTx();  //Process all Tx functions
		bool isTxLocked(){return TxLocked;}; //return true if Tx is ready for more data
		void lockTx(){TxLocked = true;};
		void unlockTx(){TxLocked = false;};
		
		private:
			~UartPort();
		
			void init(const char* name,
					AF_Periph uart_periph,
					IO_Pin* pin_rx,
					IO_Pin* pin_tx,
					IO_Pin* pin_rts,
					IO_Pin* pin_cts,
				 int32_t bufSizeRx,
				 int32_t bufSizeTx,
				 uint32_t tx_timeout,
				 int32_t bufSizeOutputStream,
				 uint32_t outputstream_timeout);
			
			UartPort* pUart;
			bool HardwareInit();
			static void IRQCallback(IRQ_TYPE irqsrc);
		
			AF_Periph AF_UARTx;
			void* 	UARTBase;
			IO_Pin* PinRx;
			IO_Pin* PinTx;
			IO_Pin* PinRTS;
		  IO_Pin* PinCTS;
			DMAInterface* DMAPort_Tx;
			DMAInterface* DMAPort_Rx;
		
			bool usingDMA_Tx;
			bool usingDMA_Rx;
			bool usingINT_Tx;
			bool usingINT_Rx;
			bool TxLocked;
			UART_Baudrate BaudRate;
			UART_Wordlength WordLength;
			UART_Parity	Parity;
			UART_Stopbits StopBits;
			
			uint32_t TxTimeout;
}; //End Class
	 

#endif




