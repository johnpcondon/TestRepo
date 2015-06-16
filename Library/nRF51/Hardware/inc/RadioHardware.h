/******************************************************************************
* File Name          : RadioHardware.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 4-30-2015
* Description        : Nordic nRF51822 Radio Hardware Functions
*******************************************************************************/
#ifndef RADIOHARDWARE_H
#define RADIOHARDWARE_H

#include "Generic/GenericTypeDef.h"

//Radio Constants (defined by radio capability, not protocol)
#define MAX_RDO_CHANNEL 100 //Should be in a radio constants file

enum RADIO_DATARATE : uint8_t
{
	RDO_DATARATE_250kbit 	= 0,
	RDO_DATARATE_1Mbit 		= 1,
	RDO_DATARATE_2Mbit 		= 2,
	RDO_DATARATE_1MbitBLE = 3
};

enum RADIO_TXPOWER : uint8_t
{
	RDO_TXPWR_4dBm 			= 0x04,
	RDO_TXPWR_0dBm 			= 0x00,
	RDO_TXPWR_Neg4dBm 	= 0xFC,
	RDO_TXPWR_Neg8dBm 	= 0xF8,
	RDO_TXPWR_Neg12dBm 	= 0xF4,
	RDO_TXPWR_Neg16dBm 	= 0xF0,
	RDO_TXPWR_Neg20dBm 	= 0xEC,
	RDO_TXPWR_Neg30dBm 	= 0xD8
};

enum RADIO_STATE : uint8_t
{
	RDO_STATE_Disabled 	= 0,
	RDO_STATE_RxRU		 	= 1,
	RDO_STATE_RxIdle	 	= 2,
	RDO_STATE_Rx			 	= 3,
	RDO_STATE_RxDisable = 4,
	RDO_STATE_TxRU		 	= 9,
	RDO_STATE_TxIdle	 	= 10,
	RDO_STATE_Tx			 	= 11,
	RDO_STATE_TxDisable = 12
};

enum RADIO_MODE : uint8_t
{
	RDOMODE_HOST = 0,
	RDOMODE_DEVICE = 1
};

//Implements Low Level Radio Functions
//Warning: These functions should be used with caution
//They may conflict with current radio operations
class Radio
{
	public:
		
		// Radio Hardware Methods
		static void Power(bool on);
		static void Disable();
		static void TxEn();
		static void RxEn();
		
		static RADIO_TXPOWER getTxPower();
		static RADIO_DATARATE getDataRate();
		static uint8_t getCurrentChannel();
		static uint32_t getCurrentFrequency();
		static RADIO_STATE getCurrentState();
		static bool isWhiteningEnabled();
		
		static RESULT setTxPower(RADIO_TXPOWER power);
		static RESULT setDataRate(RADIO_DATARATE daterate);
		static RESULT setChannel(uint8_t channel);
		static RESULT setWhitening(bool val);
		
		//Test Modes
		static RESULT TestTone(bool PLLLock_enabled);
	
	private:
		Radio();
		~Radio();
	
};



#endif

