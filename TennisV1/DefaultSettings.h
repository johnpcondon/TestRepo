/****************************************************************************
* File Name          : DefaultSettings.h
* Author             : John Condon / Adam Becker
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Default Settings
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include "Generic/genericTypeDef.h"
#include "Comms/Protocol.h"
#include "RadioHardware.h"


const DEV_TYPE	MY_DEV_TYPE = DEV_TYPE::TENNIS; 
const uint16_t	HWREV  =	1;
const uint16_t	SWREV  =	2;
const char Device_Name[] = "RdoBoard";

#define MAX_NUM_THREADS 1 //Set =1 if no RTOS used

//------------------------------------------------------
//----------------Boot Parameters-----------------------
//------------------------------------------------------

//Packet Parsing Parameters
const uint8_t MAX_NUM_HANDLED_STATUS 		 	= 1;
const uint8_t MAX_NUM_HANDLED_CMDS 			 	= 35;
const uint8_t MAX_NUM_HANDLED_RESPS 		 	= 5;
const uint8_t MAX_NUM_HANDLED_APPCMDS 	 	= 10;
const uint8_t MAX_NUM_HANDLED_APPRESPS 	 	= 2;

// Variable Access Settings
const uint8_t MAX_NUM_OUTPUTSETS					=	10;
const uint8_t MAX_NUM_VARGROUPS						=	5;
const uint8_t MAX_NUM_VARIABLES						= 15;

const uint8_t MAX_NUM_TIMERS 							= 45;
const uint8_t MAX_NUM_PORTS 							= 10;
const uint8_t MAX_NUM_SUBSCRIPTIONS 			= 25;
//------------------------------------------------------
//----------------Sensor Parameters---------------------
//------------------------------------------------------
const uint8_t ACCLGYRO_NUMSAMPLES_BUFF = 16;

//------------------------------------------------------
//----------------Radio Parameters----------------------
//------------------------------------------------------
const RADIO_MODE RdoMode = RDOMODE_DEVICE;
const char RDO_DATA_PIPE_1_NAME[] 	= "RdoData1";

const int8_t  				RDO_DATA_TX_POWER  		= 4; //dBm
const int8_t 					RDO_PAIRING_TX_POWER 	= 4; //dBm
const RADIO_DATARATE 	RDO_DATARATE 			= RDO_DATARATE_1Mbit;

const uint8_t 		RDO_CHAN_TABLE[] = {70,40,30,55,60,50,20,80,25,15,65,45,10,75,35};

// Radio Pipe, Port Settings
const int32_t		RDO_DATA_PIPE_RXBUF_SIZE 							 = 300;
const int32_t		RDO_DATA_PIPE_TXBUF_SIZE 							 = 1024;
const int32_t	 	RDO_DATA_OUTPUTSET_BUF_SIZE 					 = 256;
const uint32_t 	RDO_DATA_OUTPUTSET_FLUSH_TIME 				 = 10000;
const uint32_t 	RDO_DATA_OUTPUTSET_WATERMARK_REMAINING = 100;

//------------------------------------------------------
//------------Communication Interface Parameters--------
//------------------------------------------------------
const uint32_t SPI_TIMEOUT_SLACK 			= 10000; //Amount of extra time before timeout

//------------------------------------------------------
//----------------SUBSCRIPTION Parameters---------------
//------------------------------------------------------
const uint8_t MAX_NUM_SUBSCRIBERS_PER_PUBLISHER = 2;

//------------------------------------------------------
//------------LED Parameters----------------------------
//------------------------------------------------------
// LED Settings
const uint32_t BLINK_ON 	 			= 50000;  //uS
const uint32_t BLINK_OFF 	 			= 50000;  //uS
const uint32_t BLINK_PAUSE 			= 490000; //
const uint32_t BLINK_PERIODS[] 	= {BLINK_PAUSE, 
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF,
																	 BLINK_ON, BLINK_OFF};


//------------------------------------------------------
//------------Button Parameters----------------------------
//------------------------------------------------------
const uint8_t MAX_NUM_BUTTON_STATES 	= 4;
const uint8_t MAX_NUM_BUTTONS 				= 2;
const uint32_t BUTTON_DEBOUNCE_TIME 	= 1000;

#endif


