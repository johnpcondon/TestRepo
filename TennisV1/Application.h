/****************************************************************************
* File Name          : Timers.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module will implements general purpose software timers
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef APPLICATION_H_
  #define APPLICATION_H_

//#include "DefaultSettings.h"
#include "Comms/Protocol.h"
#include "Comms/PacketParser.h"
#include "Comms/VariableAccess.h"
#include "Comms/Pubsub.h"
#include "Comms/OutputSet.h"
#include "Sensors/AcclGyro_LSM9DS1_SPI.h"
#include "Peripherals/TimerInterface.h"

class Port;

//---------------------------------
//Application Defined Packet IDs
//---------------------------------
enum class APP_CMD : uint8_t
{
	INVALID 					= 0x00, //Invalid Command ID
	FORCE_STROKE 			= 0x01, //Manually trigger a swing
	SEND_TEST_PACKET 	= 0x02, //Send a test swing packet
};

enum class APP_RESP : uint8_t
{
	INVALID						= 0x00, //Invalid Response ID
	STROKE_DETECTED  	= 0x01, //Stroke Information
	SAMPLE_BUFFER	  	= 0x02, //Stroke Information
};

//---------------------------------
//Application Settings
//---------------------------------
const uint32_t APPLICATION_ACCL_DOWNSAMPLE = 0;
const uint32_t APPLICATION_GYRO_DOWNSAMPLE = 0;

const float DEFAULT_STROKE_ACCLTHRESH = 2.0; //G
const float DEFAULT_STROKE_GYROTHRESH = 2.0; //Rads/Sec

const uint16_t NUM_SAMPLES_TO_BUFFER = 51; //Should be odd number
const uint8_t NUM_STROKE_THRESH_CROSSES = 3;
const uint32_t STROKE_HOLDOFF_TIME_uS = 500000; //uS of holdoff time between strokes

const ODR_XL_VAL 	Accl_SampleRate 	= ODR_XL_238;
const FS_XL_VAL 	Accl_FullScale 		= FS_XL_16G;

const ODR_G_VAL 	Gyro_SampleRate 	= ODR_G_238;
const FS_G_VAL 		Gyro_FullScale 		= FS_G_2000;
const BW_G_VAL		Gyro_Bandwidth		= BW_G_VHIGH;

const uint32_t		AcclGyro_FIFOSize = 32;

const uint8_t			NUM_SAMPLES_PER_BLOCK = 20; //Don't exceed max packet size


//Application Class
//---------------------------------
class Application:public Subscriber{
	public:
		static Application* getInstance();
		void Init(Port* dest_port, AcclGyro* pAcclGyro);
		void doTasks();
		
		//Application Methods
		RESULT setStroke_GyroThresh(float val);
		RESULT setStroke_AcclThresh(float val);
		RESULT TriggerStroke(uint32_t marker);
		
		static EV_ID Tx_APP_STROKE_DETECTED(Port* dest_port);
		static EV_ID Tx_APP_SAMPLE_BUFFER(Port* dest_port,uint16_t start_index, uint8_t num_samples);
	private:
		Application();
		~Application(); //This should never be called (no deallocation should exist)
		static Application* pApp;
	
		//Application variables
		uint32_t Accl_dT;	//Expected from Accl
		uint32_t Gyro_dT;	//Expected from Gyro
		uint32_t Sample_dT; //Actual
		uint32_t SampleMarker;
		float Stroke_AcclThresh;
		float Stroke_GyroThresh;
		int32_t Stroke_AcclThreshCounts; //Converted threshold squared in counts
		int32_t Stroke_GyroThreshCounts; //Converted threshold squared in counts
		uint8_t Stroke_numThreshCrosses;
	
		uint32_t Stroke_StartTime;
		uint32_t Stroke_Count;
		bool Stroke_Active;
		bool LockBuffer;
		uint32_t Stroke_Index;
		uint32_t Sample_Index;
		uint32_t Stop_Index;
		Timer* StrokeHoldoff;
		Vect3<int16_t> GyroBuffer[NUM_SAMPLES_TO_BUFFER];
		Vect3<int16_t> AcclBuffer[NUM_SAMPLES_TO_BUFFER];
	
		//Application Private Functions
		
		//Subscription methods (called when new data is available)
		virtual void update(Publisher* who);
	
		//Pointers to the Accl and Gyro objects
		AcclGyro* pAcclGyro;
		void AcclGyroUpdate(uint32_t marker, Vect3<int16_t> &pAcclVal, Vect3<int16_t> &pGyroVal);
		
		//Subscribed value pointers
		OutputSet* 			pAcclPub; 
		uint32_t* 			pAcclMarker;
		Vect3<int16_t>* 	pAcclVal;
	
		OutputSet* 			pGyroPub;
		uint32_t* 			pGyroMarker;
		Vect3<int16_t>* 	pGyroVal;
	
		//Output Sets
		OutputSet*  		OutputSet_Stroke;
		Output* 	  		Output_Stroke_Count;
	
		//Variables
		static EV_ID updateVariable(Variable *var);
		VariableGroup* 	VarGrp;
		Variable*       Var_Stroke_GyroThresh;
		Variable*       Var_Stroke_AcclThresh;
	
		//Port to send messages to
		Port* DestPort;
		
		//Packet Parsing Callbacks
		static EV_ID Parse_APP_CMD_FORCE_STROKE(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_APP_CMD_SEND_TEST_PACKET(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		
};


#endif
