/******************************************************************************
* File Name          : Marker.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This is the header file for the Marker functionality
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef MARKER_H
#define MARKER_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/InterruptsInterface.h"
#include "Peripherals/IOInterface.h"
#include "Comms/Protocol.h"
#include "Peripherals/PortInterface.h"

class Port;

class Marker{
	public:
		static Marker* getInstance();
		
		static uint32_t get32();
		static uint64_t get64();
		
		static void set(uint32_t val){Marker::setHW(val);};
		static void set64(uint64_t val);
		
		static float conv2Sec(uint32_t val);
		static int32_t getDelta(uint32_t prev, uint32_t curr);
		static int32_t getDelta(uint32_t prev);
		
		static const float Tick;
		
		void incrementMarker64(uint64_t increment_val);
		
		static EV_ID Tx_RESP_MARKER(Port* destPort, PACKET_TYPE packet_type);
		
		static void Boot(AF_Periph marker_timer, INTERRUPT_PRIORITY marker_priority);
	private:
		static Marker* pMarker;	
		Marker(AF_Periph marker_timer, INTERRUPT_PRIORITY marker_priority);
		~Marker();
		
		//static void init();
		void initHardware(AF_Periph marker_timer, INTERRUPT_PRIORITY marker_priority);
		static uint32_t getHW();
		static void setHW(uint32_t val);
	
		static void IRQMarker_TimerOverflow(IRQ_TYPE irqsrc);
		static uint64_t Marker64; //Lowest bits set by marker timer
		static EV_ID Parse_CMD_GET_MARKER(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_SET_MARKER(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
};

#endif
				
