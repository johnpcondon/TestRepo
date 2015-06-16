/**********************************************************************
* Company:  Innovative Design Labs
* Project:  Multi
* Author:	  John Condon / Adam Becker
* File:			NRFRadio.h		
* Descrip: This code contains radio pairing and handling functions
*
						Pairing Notes:
						- Device Requests pairing by sending its unique ID on open pipe
						- Host Receives request
								Finds an open pipe
								Responds with Host ID, Dev ID, and Pipe to pair onto
								Host holds pipe, waits for a response
						- Device Receives pairing command
								Stores Host ID, Device ID, and Data Pipe
								Sets BaseID 1 to Host ID
								Enables Data Pipe and transmits verification message to host
								Starts Ack Timer
						- Host Waits to receive verification message from device
								When received, stores device ID on pipe
								Pairing Complete
						- Host Doesn't recieve verification
								Pipe reopens to future pairing
						- Device Doesn't receive pairing command
								Pairing fails
						- Device Unpair from Host
								Deletes host ID, gets new unique ID
						- Host unpairs single device
								Delete device ID
						- Host unpairs all
								Clear all dev IDs
								Get new Unique ID
								Reset Base 1 Address
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef NRFRADIO_H
#define NRFRADIO_H

//#include "DefaultSettings.h"
#include "Generic/GenericTypeDef.h"
#include "nrf.h"
#include "Containers/Buffer.h"
#include "Comms/Protocol.h"
#include "Peripherals/PortInterface.h"
//#include "nrf_nvmc.h"
#include "Peripherals/RandomNumGenerator.h"
//#include "GazelleWrappers.h"
#include "Comms/PacketBuilder.h"
#include "Comms/PacketParser.h"
#include "RadioHardware.h"
#include "RadioPipe.h"
#include "Comms/VariableAccess.h"
#include "Generic/Device.h"

extern "C"
{
	#include "nrf_gzll.h"
}

//#define NRF_NVMC_FLASH_STORE_ADDR  ((NRF_FICR->CODEPAGESIZE) * (NRF_FICR->CODESIZE - 1))

//Radio Settings
const int32_t		RDO_PAIRING_PIPE_RXBUF_SIZE 							= 300;
const int32_t		RDO_PAIRING_PIPE_TXBUF_SIZE 						  = 1024;
const int32_t	 	RDO_PAIRING_OUTPUTSET_BUF_SIZE 					  = 256;
const uint32_t 	RDO_PAIRING_OUTPUTSET_FLUSH_TIME 				  = 10000;
const uint32_t 	RDO_PAIRING_OUTPUTSET_WATERMARK_REMAINING = 100;

const uint8_t NRF_ID_SIZE 			  = 4;
const uint8_t NRF_PAIRING_PIPE    = 0;
const uint8_t NRF_DEV_DATA_PIPE 	= 1;
const uint8_t NRF_MAX_PAYLOAD_LEN = 32;

const uint8_t 	RDO_PAIRING_PREFIX 			= 0x01;
const uint32_t 	RDO_BASE_ADDRESS_0 			= 0x23344556;

const uint16_t RDO_DEFAULT_NUM_RETRIES 			= 100;
const uint32_t RDO_TIMESLOTS_PER_CH					= 5;
const uint32_t RDO_TIMESLOTS_PER_CH_OUTSYNC = 80;
const uint32_t RDO_TIME_TX_ADVERTISE 				= 1000000; 

const uint32_t RDO_TIME_PAIRING_RETRY				= 1000000; 
const uint8_t  RDO_PAIRING_RETRY 						= 3;


const uint8_t 		RDO_MAX_NUM_DATA_PIPES 	= 2; //THIS VALUE MUST BE THE SAME ON HOST AND DEVICES

const nrf_gzll_device_channel_selection_policy_t RDO_CH_SEL_POLICY = NRF_GZLL_DEVICE_CHANNEL_SELECTION_POLICY_USE_CURRENT;

const uint8_t NUM_RADIO_PIPES_HOST 	 = (RDO_MAX_NUM_DATA_PIPES +1);
const uint8_t NUM_RADIO_PIPES_DEVICE = 2; //One Pairing, one data


class NRFRadio
{
	public:
		// Public interface
		NRFRadio(DEV_TYPE dev_type,RADIO_MODE radio_mode);
		RadioPipe* addPipe(const char* name,
												bool isDataPipe,
												bool isPersistant,
												uint32_t RxBufSize,
												uint32_t TxBufSize,
												int32_t bufSizeOutputStream,
												uint32_t outputstream_timeout,
												uint32_t outstream_watermark_remaining);
		bool init(RADIO_DATARATE datarate,int8_t pairing_tx_power,int8_t data_tx_power,const uint8_t ch_table[],uint8_t num_channels);
		void doTasks();		
	  void EnableAutoPair(){AutoPairEn = true;};
		bool FixPipeToDevType(uint8_t pipe_num, DEV_TYPE dev_type);
	
		// Radio Hardware Methods
		static bool EnableRadio();
		static void DisableRadio();

		// Get and Sets
		DEV_TYPE   getDevType(uint8_t pipe);
		PIPE_STATE getPipeState(uint8_t pipe);
	  uint16_t   getRSSI(uint8_t pipe);
		uint32_t 	 getMyID()		 		    {return My_ID;};
		uint16_t 	 getMaxTxAttempts()   {return MaxTxAttempts;};
		uint8_t  	 getNumPipes()			  {return Pipes->getCnt();};
		uint32_t 	 getAdvertise_Period(){return pAdvertiseTimer->getPeriod_uS();};
		uint8_t 	 getNumPipesPaired();
		uint8_t 	 getTxPower();
		RADIO_DATARATE getDataRate();
		
		bool setDataRate(RADIO_DATARATE datarate);
		bool setTxPower(int8_t power);
		bool setNumRetries(uint16_t max_tx_attempts);
		void setAdvertise_Period(uint32_t period_us){pAdvertiseTimer->set_uS(period_us);};	
		
		bool isDeviceReqPairing();
		bool isDevicePaired();
		bool isValidPipe(uint8_t pipe){return pipe < Pipes->getCnt();};		

		// Callbacks Methods
		static void DevTxSuccess(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info);
		static void DevTxFailed(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info);
		static void HostRxData(uint32_t pipe, nrf_gzll_host_rx_info_t rx_info);
		static void GzllDisabled(void){};
		 
		// Packet Handling Functions
		static EV_ID Parse_CMD_GET_PIPES(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_PAIR_CMD(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_PAIR_REQ(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_PAIR_VERIFY(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_PAIR_UNPAIR(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		
		// Packet Transmission Functions
		static void Tx_RDO_RESP_PIPES(Port* destPort);
		static void Tx_RDO_PAIRING_VERIFY(Port* destPort,uint8_t pipe, uint32_t host_id, uint32_t dev_id);
		static void Tx_RDO_DEVICE_ADVERTISE(Port* destPort, uint16_t rssi, PIPE_STATE pipe_state);
		static void Tx_RDO_PAIRING_REQ(Port* destPort, uint32_t deviceID, DEV_TYPE device_dev_type, bool persistant);
		static void Tx_RDO_PAIRING_CMD(Port* destPort, uint8_t pipe, uint32_t hostID,DEV_TYPE host_dev_type,uint32_t deviceID, bool persistant);
		
		

	private:		
		~NRFRadio();
		static NRFRadio* pRdo;
		
	  Timer* 	   pAdvertiseTimer;
		RADIO_MODE RdoMode;
		uint32_t   My_ID;
	  bool 			 AutoPairEn;
	  uint16_t 	 MaxTxAttempts;
	  int8_t TxDataPower;
		int8_t TxPairingPower;
	
		//Host and Device Methods
		inline uint8_t getPrefix(uint32_t deviceID){return (uint8_t)(deviceID & 0x000000FF);};
		uint32_t GenerateUniqueID();		
		bool SetupPairingPipe(uint32_t pairing_address, uint8_t prefix);
		bool SetupDataPipe(uint8_t pipe, uint32_t host_address, uint8_t prefix);
		void VerifyPairing(uint8_t pipe);
		bool AcceptPairing;
		bool ErasePairing();
	
		//Host Only Methods
		void doTasks_Host();
		bool Pair_Host(uint32_t device_id, DEV_TYPE device_dev_type, bool persistant);
		bool UnPairAll_Host();
		bool UnPair_Host(uint8_t pipe);
		bool RestorePairing_Host();
		bool StorePairing_Host();

		//Device Only Methods
		void doTasks_Device();
		bool Pair_Device(uint8_t pipe, uint32_t host_id, DEV_TYPE dev_type, bool persistant);
		void Device_StopPairingReq(); //Stop requesting pairing
		bool RestorePairing_Device();
		bool StorePairing_Device();
		bool UnPair_Device();
		
		//Diagnotistic
		bool outputSetInit;
	
		//Output Sets
		uint32_t  			pOutputSetMarker;
		Timer* 					pOutputSetTimer;
		
		nrf_gzll_error_code_t SetupErrorCode;	 
		
		//Variables
		Variable* Var_MyID;
		Variable* Var_DevicePairingPipeNum; //Device use only
		
		static vector<RadioPipe*>* Pipes;  
};

#endif

