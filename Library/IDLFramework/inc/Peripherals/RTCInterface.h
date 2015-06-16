/*******************************************************************************
* File Name          : RTCInterface.h
* Author             : John P Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Real Time Clock Interface
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef RTCINTERFACE_H_
  #define RTCINTERFACE_H_

#include "Generic/GenericTypeDef.h"
#include "Comms/Protocol.h"
#include "Comms/PacketBuilder.h"
//#include "SettingTypes.h"
#include "Comms/VariableAccess.h"

//Time Values stored in BCD
//I.e. 07:15:24 -> 0x07; 0x15; 0x24;
typedef union{
	uint32_t val;
	struct{
		uint8_t Second;	//0-60
		uint8_t Minute;	//0-60
		uint8_t Hour;		//0-23
		uint8_t Unused;
	};
}TIME_VAL;

//Time Values stored in BCD
//I.e. 21st of January, 2015 (Wednesday) -> 0x21; 0x01; 0x15; 0x3;
typedef union{
	uint32_t val;
	struct{
		uint8_t Day;		//1-31
		uint8_t Month;	//1-12
		uint8_t Year;		//0-99
		uint8_t Weekday; //1-7
	};
}DATE_VAL;

enum WEEKDAY{
	WEEKDAY_NONE 	= 0,
	DAY_MON 			= 1,
	DAY_TUES 			= 2,
	DAY_WED 			= 3,
	DAY_THURS 		= 4,
	DAY_FRI 			= 5,
	DAY_SAT 			= 6,
	DAY_SUN 			= 7
};

class RealTimeClock{
	 public:
		//RealTimeClock();
	  static int init(bool use_lse);
		static int setDate(DATE_VAL& date);
		static int setTime(TIME_VAL& time);
	 
		static void getTime(TIME_VAL& time);
		static void getDate(DATE_VAL& date);
	 
		static EV_ID Tx_RESP_DATETIME(Port* destPort,PACKET_TYPE packet_type); 
	 protected:
		 
	 private:  
		//~RealTimeClock();
		static int initHardware(bool use_lse);
	 
		static bool isInitialized;
	 	static Variable*       var;
	  static uint8_t RTC_Enabled;
		static EV_ID Parse_CMD_GET_DATETIME(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_SET_DATETIME(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
	 
};//End Class

#endif


