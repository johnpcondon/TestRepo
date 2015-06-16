/******************************************************************************
* File Name          : OutputSet.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/5/2015
* Description        : This is the header file for the Sensor abstraction
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef OUTPUTSET_H
#define OUTPUTSET_H

#include "Generic/genericTypedef.h"
#include "Generic/DataTypes.h"

#include "Comms/pubsub.h"
#include "Comms/PacketBuilder.h"

#include "Containers/Buffer.h"
#include "Containers/CircularBuffer.h"
#include "Containers/JCVect.h"

#include "Peripherals/PortInterface.h"

class Port;

class Output{
	public:
		template <typename T> Output(const char* Name,T* pVal);
		void pushValue(Buffer* destBuf);  //Push value into buffer
	
		uint8_t getSize(void);
		int getInfo(Buffer* destPort);
		uint16_t getInfo_Size();
		void* getDataPointer(){return pVal_;};
		const char* getName(){return Name_;};
	  
	private:
		~Output();
		const char* Name_;
		void* pVal_;
		uint8_t NumBytes_;
		DATA_TYPE DataType_;
	
};

template <typename T> 
Output::Output(const char* Name, T* pVal){
 	Name_ = Name;
	pVal_ = (void*)pVal;	//pointer to the actual value
	NumBytes_ = getDataTypeSize(pVal);
	DataType_ = getDataType(pVal);
}

class OutputSet : public Publisher{
public:
		//OutputSet(const char* name, uint32_t* pMarker,uint8_t num_outputs_in_set);
  	OutputSet(const char* name, uint32_t* pMarker, uint32_t expectedPeriod,uint8_t num_outputs_in_set,uint8_t max_num_subscribers);
  	void add(Output* output);
	  virtual void pushValue(Buffer* destbuf);  //Overrides publisher pushValue function
	 
	 uint8_t getIndex(){return Index_;};
	 const char* getName(){return Name_;}; 
	 Output* getOutput(uint8_t output_index);
	 void* getDataPointer(uint8_t output_index){return (*Outputs)[output_index]->getDataPointer();};
	 uint8_t numOutputs() { return Outputs->getCnt(); };	 
	 int getOutputSetInfo(Buffer* destBuf);	//Get Set info
	 
	 static uint8_t numSets(){return OutputSets->getCnt();};
	 static const char* getOutputName(uint8_t set_index, uint8_t output_index);
	 static const char* getName(uint8_t set_index);
 	 static int getAllOutputSetInfo(Buffer* destBuf);
	 static OutputSet* getOutputSet(uint8_t index);
	 static uint16_t getAllOutputSetInfo_Size(void);
	 
	 static EV_ID Tx_RESP_ALLSUBINFO(Port* destPort, Port* subscribing_port,PACKET_TYPE packet_type);
	 static EV_ID Tx_RESP_ALLPORT_ALLSUBINFO(Port* destPort, PACKET_TYPE packet_type);
	 static EV_ID Tx_RESP_OUTPUTSETS(Port* destPort,PACKET_TYPE packet_type);
	 static EV_ID Tx_RESP_OUTPUTSETRATE(Port* destPort,uint8_t iSubscriberPort, uint8_t iOutputSet,PACKET_TYPE packet_type);
	 
	 static void Boot(uint8_t max_num_outputsets);
	private:
		~OutputSet();  	
		vector<Output*>* Outputs;
		const char* Name_;		//Name of output set
		uint8_t Index_;		//Set Index
		int32_t numBytes_;	//Number of bytes in value
		DATA_TYPE DataType_;
		
		static vector<OutputSet*>* OutputSets;
	
		//Packet Handling Functions
		static EV_ID Parse_CMD_GET_OUTPUTSETS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_SUB_OUTPUTSETS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_STOP_OUTPUTSETS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_GET_OUTPUTSETRATE(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
};
#endif
