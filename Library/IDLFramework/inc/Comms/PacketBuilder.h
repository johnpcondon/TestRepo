/****************************************************************************
* File Name          : PacketBuilder.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module builds packets
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "Generic/GenericTypeDef.h"
#include "Comms/Protocol.h"
#include "Peripherals/PortInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Containers/JCVect.h"
#include "Containers/Buffer.h"
#include "Containers/CircularBuffer.h"
#include "Peripherals/MarkerInterface.h"

class Port;
//Static class used to create and push packets
class PacketBuilder{
	public:
	 static PacketBuilder* getInstance();
	 
	 void StartPacket(Port* destPort,uint8_t dest_index, PACKET_TYPE packet_type);
	 bool FinishPacket();	//Sets data len, calculates checksum
	 
	 static void ForwardPacket(Port* destPort,uint8_t dest_index, PACKET_TYPE packet_type,Buffer* data);
	 static void TxEvent(Port* destPort, uint8_t dest_index, EV_ID ev, PACKET_TYPE packet_type, uint8_t packet_id);	 

	 Buffer* Payload;
	 static void Boot(uint8_t max_num_threads);
	
	private:
		PacketBuilder(); //Called by parser constructor
		~PacketBuilder();
		void Reset(); 	
	
		//void start_packet(Port* destPort,uint8_t dest_index, uint8_t packet_type);
		//bool finish_packet();	//Sets data len, calculates checksum
	
		Port* 	 		DestPort;
		uint8_t  		DestIndex;
		PACKET_TYPE PacketType;
		uint8_t  		Checksum;
	
	static vector<uint32_t>* ThreadID;
	static vector<PacketBuilder*>* pPacketBuilder;
};

#endif

