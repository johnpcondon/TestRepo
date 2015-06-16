/****************************************************************************
* File Name          : Port.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module implements the generic Port class
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/


#ifndef PORT_H
  #define PORT_H

#include <inttypes.h> 
#include "Comms/Protocol.h"
#include "Comms/PacketBuilder.h"
#include "Comms/PacketParser.h"
#include "Containers/JCVect.h"
#include "Comms/Pubsub.h"
#include "Containers/CircularBuffer.h"
#include "Peripherals/TimerInterface.h"
#include "Containers/PingPongBuffer.h"

enum PORT_TYPE{
  PORT_NONE			= 0x00,
  PORT_UART 		= 0x01,
  PORT_SPI  		= 0x02,
  PORT_I2C  		= 0x03,
  PORT_SDCard 	= 0x04,  
  PORT_USB 			= 0x05,
	PORT_RDO_DATA	= 0x06,
	PORT_RDO_PAIR = 0x07
};



//Forward Declaration
class PacketParser;
class Subscriber;
class Publisher;

//const uint8_t TEST_DUMMY_DATABYTE = 0xAA;

  //Port abstraction layer
	class Port : public Subscriber{   
		friend class PacketBuilder;
		friend class PacketParser;
    public: 
			void reset();
			
			void setRxCorrupt();
			bool LockPush();
			void UnLockPush(){LockedPush = false;};
		
			int getCount_RxBuf(){return rxBuf->getCount();};
			int getCount_TxBuf(){return txBuf->getCount();};
			int getSize_RxBuf(){return rxBuf->getSize();};
			int getSize_TxBuf(){return txBuf->getSize();};
			int getFreeBytes_RxBuf(){return rxBuf->getFree();};
			int getFreeBytes_TxBuf(){return txBuf->getFree();};
			uint32_t getByteRate_Rx(){return ByteRate_Rx;};
			uint32_t getByteRate_Tx(){return ByteRate_Tx;};
			
			//Port Abstraction Functions
			uint8_t getIndex(){return Index_;};
			const char* getName(){return Name_;};
			virtual void update(Publisher* who);
			void PerformTests();
			
			//Push/Pop functions for application layer port interface
			int push(uint8_t *srcData, int32_t numelements);	
			template<typename T>int push(T data);
			template<Buffer*>int push(Buffer* data);
			
			int pop(uint8_t *destData, int32_t numelements);
			template<typename T>int pop(T* data);
			
			int peek_Tx(uint8_t* destData, int32_t baseindex, int32_t offset);  //Get data without impacting buffers

			void setOutputStreamSettings(int32_t outstream_watermark, uint32_t outstream_timeout_us);
			void getOutputStreamSettings(int32_t &outstream_watermark, uint32_t &outstream_timeout_us);			
			//Test Functions
			void enableTestTx(uint32_t period_us,uint32_t data_size); //Outputs test packets data on port
			void enableReqTest(uint32_t period_us,uint32_t data_size);
			void disableTestTx();
			void disableReqTest();
			void resetTest();
			
			void enableTxTimeouts(uint32_t timeout_time_us);
			void enableRxTimeouts(uint32_t timeout_time_us);
			void startRxTimeoutTimer();
			void startTxTimeoutTimer();
			void stopRxTimeoutTimer();
			void stopTxTimeoutTimer();
			
			static Port* getPort(uint8_t portIndex);
			static uint8_t getPortIndex(Port* port);
			static uint8_t numPorts(){return Ports->getCnt();};

			static const char* getName(uint8_t port_index);			
			static void updateAllRateMeas();
			
			//Packet Handling Functions
			void Tx_OUTPUTSET();
			static EV_ID Tx_CMD_GET_TESTPACKET(Port* dest_port,uint8_t test_datasize,PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_PINGPORT(Port* dest_port,uint32_t marker_time,PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_TESTPACKET(Port* dest_port,uint32_t reqmarker,uint8_t test_datasize,PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_ALLPORTINFO(Port* dest_port,PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_PORTSUBINFO(Port* destPort,Port* subscribing_port,int8_t iSubscription,PACKET_TYPE packet_type);
		
			static EV_ID Tx_RESP_ALLSUBINFO(Port* destPort,Port* subscribing_port,PACKET_TYPE packet_type);

			static void Boot(uint8_t max_num_ports);
			void incDroppedTxPacket(){DroppedTxPacket++;};
	
			//Peripheral Functions (only used by low level hardware, these should be made protected)
			int periph_push(uint8_t data);
			int periph_push(uint8_t *data, int32_t numBytes);
			int periph_push(Buffer* buf);
			int periph_push(PingPongBuffer* buf);
		
			int periph_pop(uint8_t *destData); 
			int periph_pop(uint8_t *destData, int32_t numBytes); 
			bool isPeriphPopLocked(){return txBuf->isLocked();}
			bool isPeriphPushLocked(){return rxBuf->isLocked();}
			
    protected:			
			Port(const char* name,
			PORT_TYPE PortType,
			int32_t rxbufSize,
			int32_t txbufSize,
			int32_t bufSizeOutputStream,
			uint32_t outstream_timeout,
			uint32_t outstream_watermark_remaining);

			Timer* 	RxTimeoutTimer;
			Timer* 	TxTimeoutTimer;
			
			void ChangePortName(const char* name);
			void ParseRx();
			bool checkOutputStream(void);
			
			//Dangerous Functions... use with caution (for low level code only)
			int setWriteIndex_Rx(uint16_t index);
			int setReadIndex_Tx(uint16_t index);
			uint8_t* getBase_RxBuf(){return rxBuf->getHead();};
			uint8_t* getBase_TxBuf(){return txBuf->getHead();};
			
			int32_t getReadFromIndex_Rx(){return rxBuf->getReadFromIndex();};
			int32_t getReadFromIndex_Tx(){return txBuf->getReadFromIndex();};
			
    private:
			~Port();
			uint8_t 			Index_;
			const char*		Name_;
			PORT_TYPE			PortType_;
		
			bool LockedPush;
			CircularBuffer* 	rxBuf; 
			CircularBuffer* 	txBuf; //This buffer should be created by the peripheral class

			Buffer*				OutStreamBuf;
			Timer* 				OutStreamTimer_;
			uint32_t 			OutStreamWaterMark_;

			uint32_t portByteAccum_Rx;
			uint32_t portByteAccum_Tx;	
			uint32_t ByteRate_Rx;
			uint32_t ByteRate_Tx;
			
			uint32_t DroppedTxPacket;
			//Test Variables
			bool TestTx_Enabled;
			bool ReqTest_Enabled;
			bool TestToRadio;
			Timer* TestTx_Timer;
			uint32_t TestTx_DataSize;
			uint32_t TestTx_PacketsSent;
			//uint32_t TestTx_ErrorCnt;
			
			uint32_t RxTest_DataSize;
			uint32_t RxTest_PacketsReq;
			uint32_t RxTest_PacketsRecv;
			uint32_t RxTest_PacketsDropped;
			int32_t RxTest_LoopTime;
			uint32_t RxTest_TestUnitMarker;
			uint32_t RxTest_TestPacketNum;
			uint32_t RxTest_DiffPacketNum;
			
			uint32_t BadPacket_NotImplemented;
			uint32_t BadPacket_Err;
			uint32_t BadPacket_BadParam;
			uint32_t BadPacket_Chksum;
			uint32_t BadPacket_InvalidCmd;
			
			PacketParser*	packetparser;
			void updateRateMeas();		
			static vector<Port*>* Ports;     

			int getPortInfo(Buffer* destPort);
			uint16_t getPortInfo_Size();
			static int getAllPortInfo(Buffer* destPort);
			static uint16_t getAllPortInfo_Size();
			
			static EV_ID Parse_CMD_PINGPORT(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_PORTS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_TESTPACKET(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_RESP_TESTPACKET(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
}; //End Class


template<typename T>int Port::push(T data){
	return txBuf->push(data);
}

template<Buffer*>int Port::push(Buffer* data){
	int numBytes = txBuf->push(data);
	return numBytes;
}

template<typename T>int Port::pop(T* data){
	return rxBuf->pop(data);
}

#endif 

