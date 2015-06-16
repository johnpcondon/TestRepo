/**********************************************************************
* Company:  Innovative Design Labs
* Author:	  John Condon / Adam Becker
* File:			RadioPipe.cpp
* Date:			6/3/2015
* Descrip:  RadioPipe Class. Expected to be used only by 
* 					NRFRadio_multipair.cpp  					
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef RADIO_PIPE_H
#define RADIO_PIPE_H

#include "Peripherals/PortInterface.h"
#include "Comms/VariableAccess.h"
#include "Comms/OutputSet.h"

extern "C" 
{ 
	#include "nrf_gzll.h" 
}

enum class PIPE_STATE : uint8_t
{
	DISABLED 				= 0x00,
	LOCKED					= 0x01,
	UNPAIRED				= 0x02,
	ISPAIRING				= 0x03,
	PAIRED					= 0x04,
	IDLE						= 0x05,
};

const uint32_t RDO_TIME_PIPE_MAXIDLE				= 3000000; 
const uint32_t RDO_OUTPUTSET_PERIOD_uS 			= PERIOD_1Hz;
const uint32_t RDO_TIME_PIPE_TX_MAXLATENCY	= 100000; 
const uint8_t  RDO_IDLE_RETRY								= 3;

class RadioPipe : public Port
{
	public:
		RadioPipe( const char* name,
								PORT_TYPE PortType,
								uint8_t pipe,
								uint32_t RxBufSize,
								uint32_t TxBufSize,
								int32_t bufSizeOutputStream,
								uint32_t outputstream_timeout,
								uint32_t outstream_watermark_remaining);
		
		void doTasks( uint8_t* NRF_RxBuf, uint8_t* NRF_TxBuf );
		void SetupPipe( uint32_t id,DEV_TYPE dev_type);
		void Unpair( );

		bool isPairPersistant(){return PersistantPairing;};
		void setPairPersistant(bool val){PersistantPairing = val;};
		PIPE_STATE getState( void ) { return PipeState; };	
		void setState( PIPE_STATE state ) 
		{ 
			if( PipeState != PIPE_STATE::LOCKED ) PipeState = state; 
		};

		uint8_t 	 getPipeNum( void ){ return PipeNum; };
		void 			 setPipeNum( uint8_t pipe_num )
		{ 
			PipeNum = 0x0F & pipe_num;  //Set only the lower nibble
		}
		
		Timer*		IdleTimer;
		bool			NewRxData;
		uint32_t 	PayloadLen_Rx;
		uint32_t 	PayloadLen_Tx;
		uint8_t 	AttemptsRemaining;
		uint32_t	RadioID;
		
		bool 			PairVerified;
		DEV_TYPE	DevType;
		DEV_TYPE	FixedDevType;
		uint16_t 	NumChSwitches;
		uint16_t 	NumTxAttempts;
		int32_t		numFifoPackets;
		int16_t 	RSSI;
		uint8_t		Ch;
		uint32_t	RxMarker;
		
		Variable* Var_PipeID; 	// ID of other end
		Variable* Var_DevType; 	// DevType of Other end
		
		uint32_t				OutSetMarker;
		Timer*					OutputSetTimer;
		uint32_t				OutputSetPeriod;
		OutputSet* 			pOutputSet; 
		Output* 	  		Out_RSSI;
		Output*					Out_Ch;
		
		// Diagnotistic Variables
		nrf_gzll_error_code_t Tx_ErrCode;
		nrf_gzll_error_code_t Rx_ErrCode;		
		uint32_t 							BadPacketCnt;
	private:
		// These are private to force IDL developers to use the setters
		// in NRFRadio as there is logic to prevent erroneous input
		PIPE_STATE 	PipeState;
		uint8_t 		PipeNum;
		bool			PersistantPairing;
	
		uint8_t getSettingPipeID( uint8_t pipe );
		uint8_t getSettingPipeDevType( uint8_t pipe );
		
};


//const char* const PIPE_ID_NAMES[] ={
//	"PipeID0",
//	"PipeID1",
//	"PipeID2",
//	"PipeID3",
//	"PipeID4",
//	"PipeID5",
//	"PipeID6",
//	"PipeID7"
//};
#endif

