/****************************************************************************
* File Name          : PacketParser.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module implements packet parsing
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include "Generic/GenericTypeDef.h"
#include "Comms/Protocol.h"
#include "Peripherals/PortInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Containers/JCVect.h"
#include "Containers/Buffer.h"
#include "Containers/CircularBuffer.h"
#include "Peripherals/MarkerInterface.h"

enum class PACKET_STATE
{
  	IDLE,        //Waiting for Start Sync
  	GET_OPCODE,  //Waiting for Opcode
  	GET_LEN8,    //Waiting for Payload Length (8-bit)
  	GET_LEN16,    //Waiting for Payload Length (16-bit)
  	GET_PAYLOAD, //Waiting for Rest of Packet
  	PROCESSING,  //Waiting for Packet to be processed
};

//Debug only
extern int badlen;

const uint8_t HEADERSIZE = 3; //StartSync, OpCode, Payload Len
const uint8_t FOOTERSIZE = 2; //CRC and EndSync
const uint8_t PACKET_OVERHEAD = HEADERSIZE + FOOTERSIZE;

//Forward declarations
class Port; 

typedef EV_ID (*ParseFcn)(Port* resp_port, Buffer* buf, uint8_t DataLen, PACKET_TYPE packet_type); //Define a Parsing functions
				
class PacketParser{
public:
	PacketParser(Port* srcport);
	void setCorrupt();

	void ParseIncoming();

	//Global Packet Routing functions
	static void setLocalPort(Port* local_port){LocalPort = local_port;};
	static void setMasterPort(Port* master_port){MasterPort = master_port;};	
	static void setAsEndNode(void){isEndNode = true;};
	
	//Global Packet Handling Functions
	static void	enablePacketType(PACKET_TYPE packet_type);
	static bool addHandler(PACKET_TYPE packet_type,EV_ID packetID, ParseFcn fcn);
	static bool addHandler(PACKET_TYPE packet_type,CMD_ID packetID, ParseFcn fcn);
	static bool addHandler(PACKET_TYPE packet_type,RESP_ID packetID, ParseFcn fcn);
	//static bool addHandler(PACKET_TYPE packet_type,APP_CMD packetID, ParseFcn fcn);
	//static bool addHandler(PACKET_TYPE packet_type,APP_RESP packetID, ParseFcn fcn);
	static bool addHandler(PACKET_TYPE packet_type,uint8_t packetID, ParseFcn fcn);
	static bool isPacketTypeEnabled(PACKET_TYPE packet_type);
	static void Boot(uint8_t max_num_handled_status,
										uint8_t max_num_handled_cmds,
										uint8_t max_num_handled_resps,
										uint8_t max_num_handled_appcmds,
										uint8_t max_num_handled_appresps);
private:
	~PacketParser();
	EV_ID Process(Port* src_port, PACKET_TYPE packet_type);
	EV_ID ProcessAppCmd(Port* src_port);	
	EV_ID ProcessStatus(Port* src_port);
	EV_ID ProcessCmd(Port* src_port);
	EV_ID ProcessResp(Port* src_port);
	EV_ID ProcessRadioCmd(Port* src_port);
	EV_ID ProcessRadioResp(Port* src_port);
	
	void ResetPacket();

	PACKET_STATE	State;

	Port*				SrcPort; 			//Source Port
	uint16_t		ReqLen;				//Length Required to process next state
	uint8_t 		OpCode;				//Packet Type + Source Index
	uint8_t			PacketID;			//Packet ID
	PACKET_TYPE	PacketType;		//Packet Type
	uint8_t			PortIndex;		//Port Index of Incoming
	uint16_t 		Payload_Len; 
	uint8_t			Checksum;
	bool				isCorrupt;	//Packet was corrupted during Rx, throw away
	//int32_t			iPayload;
	
	bool 			PacketReady;
	Timer*			pTimeOut;
	uint32_t		PacketMarker;

	static Buffer*			Payload;

	static Port*				LocalPort;		//Local Port to pass unknown messages to
	static bool					isEndNode;
	static Port* 				MasterPort;		//Port to get to master
	static uint16_t			HandledPacketTypes; //Binary Map to all of the handled packets
	
	uint32_t 		BadCheckSums;
	
		
	static vector<uint8_t>* Handled_StatusIDs;							//Vector of CmdIDs that we can handle
	static vector<ParseFcn>* ParseFcn_StatusIDs; //Vector of Function Pointers to Parsing Functions

	static vector<uint8_t>* Handled_CmdIDs;							//Vector of CmdIDs that we can handle
	static vector<ParseFcn>* ParseFcn_CmdIDs; //Vector of Function Pointers to Parsing Functions

	static vector<uint8_t>* Handled_RespIDs;							//Vector of CmdIDs that we can handle
	static vector<ParseFcn>* ParseFcn_RespIDs; //Vector of Function Pointers to Parsing Functions

	static vector<uint8_t>* Handled_AppCmdIDs;							//Vector of CmdIDs that we can handle
	static vector<ParseFcn>* ParseFcn_AppCmdIDs; //Vector of Function Pointers to Parsing Functions
	
	static vector<uint8_t>* Handled_AppRespIDs;							//Vector of CmdIDs that we can handle
	static vector<ParseFcn>* ParseFcn_AppRespIDs; //Vector of Function Pointers to Parsing Functions
	
	static EV_ID Parse_Event(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
};


#endif

