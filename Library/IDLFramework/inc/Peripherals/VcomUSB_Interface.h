/*******************************************************************************
* File Name          : VcomUSB_Interface.h
* Author             : Adam Becker
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Virtual Com Port Interface for USB
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef VcomUSB_H
#define VcomUSB_H

#include "genericTypedef.h"
#include "IOInterface.h"
#include "Timers.h"
#include "PWMInterface.h"
#include "port.h"
#include "circular_buffer.h"
#include "IOInterface.h"
#include "stm32f4xx.h"
#include "usbd_def.h"
#include "usbd_desc.h"

class VcomUsbPort : public Port
{ 
  public:
		VcomUsbPort(const char* name,
							AF_Periph periph,
							IO_Pin* pin_n,
							IO_Pin* pin_p,
							IO_Pin* pin_v,
							IO_Pin* pin_i,
							int32_t bufSizeRx,
							int32_t bufSizeTx,
							uint32_t tx_timeout,
							int32_t bufSizeOutputStream,
							uint32_t outputstream_timeout,
							uint32_t outstream_watermark_remaining);
		
	  void doTasks();  //Call continously to perform Uart tasks
		void Init(); 		//Initializes Hardware
		
		int32_t ProcessRx();	//Process all Rx functions
		int32_t ProcessTx();  //Process all Tx functions
	protected:
			void init(const char* name,
							AF_Periph periph,
							IO_Pin* pin_n,
							IO_Pin* pin_p,
							IO_Pin* pin_v,
							IO_Pin* pin_i,
						 int32_t bufSizeRx,
						 int32_t bufSizeTx,
						 int32_t bufSizeOutputStream,
						 uint32_t outputstream_timeou);
  private:
		~VcomUsbPort();
		bool HardwareInit();
			
		AF_Periph AF_USBx;
		void* 	UARTBase;
		IO_Pin* PinN;
		IO_Pin* PinP;
		IO_Pin* PinV;
		IO_Pin* PinI;
}; //End Class

#endif
