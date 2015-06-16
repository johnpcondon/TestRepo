/*********************************************************************
* Company:  Innovative Design Labs
* Project:  Tennis Board Cueing
* Author:	  John Condon / Adam Becker
* File:			Application.cpp
* Descript: Application specific file for the Tennis Board
* Date:			6/3/2015
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#include "HardwareDef.h"
#include "Application.h"

#include "Generic/GenericTypeDef.h"

Application* Application::pApp;

/************************************************************************************
Returns pointer to the application object via a singleton pattern
*************************************************************************************/
Application* Application::getInstance()
{
	if(pApp==nullptr){
		pApp = new Application();
	}
	return pApp;
}

/************************************************************************************
This is the application object constructor
All buffers and allocations should be performed here
*************************************************************************************/
Application::Application()
{
	//Create Swing Output Set
	OutputSet_Stroke = new OutputSet("Stroke",&this->Stroke_StartTime,0,1,1);
	Output_Stroke_Count  = new Output("Count",&this->Stroke_Count);
	OutputSet_Stroke->add(Output_Stroke_Count);
	
	VarGrp = new VariableGroup("Tennis",2);
	Var_Stroke_GyroThresh = new Variable("Stroke_GyroThresh","Rad/S",&this->Stroke_GyroThresh);
	Var_Stroke_GyroThresh->makeSettable(updateVariable);
	//Var_Stroke_GyroThresh->makeSaveable(SETTING_APP,SETTING_APP_STROKE_GYROTHRESH);
	
	Var_Stroke_AcclThresh = new Variable("Stroke_AcclThresh","G",&this->Stroke_AcclThresh);
	Var_Stroke_AcclThresh->makeSettable(updateVariable);
	//Var_Stroke_AcclThresh->makeSaveable(SETTING_APP,SETTING_APP_STROKE_ACCLTHRESH);
	
	VarGrp->add(Var_Stroke_GyroThresh);
	VarGrp->add(Var_Stroke_AcclThresh);
	
	StrokeHoldoff = new Timer();
	
	PacketParser::enablePacketType(PACKET_TYPE::APP_CMD); //Enable parsing of Application Commands
	
	//Enable Parsing of Individual Packet Types
	PacketParser::addHandler(PACKET_TYPE::APP_CMD,(uint8_t)APP_CMD::FORCE_STROKE,Parse_APP_CMD_FORCE_STROKE);
	PacketParser::addHandler(PACKET_TYPE::APP_CMD,(uint8_t)APP_CMD::SEND_TEST_PACKET,Parse_APP_CMD_SEND_TEST_PACKET);
}
/************************************************************************************
This function is called once before the main loop
It should be used to initialize values and perform basic setup
*************************************************************************************/
void Application::Init(Port* dest_port, AcclGyro* accl_gyro_obj)
{
	//Init Accl and Gyro
	DestPort = dest_port;
	pAcclGyro = accl_gyro_obj;
	pAcclGyro->InitAccl(Accl_SampleRate,FS_XL_16G);
	pAcclGyro->InitGyro(Gyro_SampleRate,FS_G_2000,Gyro_Bandwidth);
	
	//Subscribe to Accl and Gyro
	if (pAcclGyro->OutputSet_AcclRawVal != nullptr)
	{
		//Todo: We should change this to try and get the name of the value, not by direct pointer
		pAcclPub 		= pAcclGyro->OutputSet_AcclRawVal;
		pAcclMarker = (uint32_t*)			pAcclGyro->OutputSet_AcclRawVal->getDataPointer(0);
		pAcclVal 		= (Vect3<int16_t>*)pAcclGyro->OutputSet_AcclRawVal->getDataPointer(1);
	}

	if (pAcclGyro->OutputSet_GyroRawVal != nullptr)
	{
		pGyroPub 		= pAcclGyro->OutputSet_GyroRawVal;
		pGyroMarker = (uint32_t*)			pAcclGyro->OutputSet_GyroRawVal->getDataPointer(0);
		pGyroVal 		= (Vect3<int16_t>*)pAcclGyro->OutputSet_GyroRawVal->getDataPointer(1);
	}
	
	if (pAcclPub != nullptr)
	{
		pAcclPub->Subscribe(this,APPLICATION_ACCL_DOWNSAMPLE);
	}
	if (pGyroPub != nullptr)
	{
		pGyroPub->Subscribe(this,APPLICATION_GYRO_DOWNSAMPLE);
	}
		
	//Get Expected Sample Rates
	Accl_dT = pAcclPub->getExpectedPeriod(this);
	Gyro_dT = pGyroPub->getExpectedPeriod(this);
	
	setStroke_AcclThresh(DEFAULT_STROKE_ACCLTHRESH);
	setStroke_GyroThresh(DEFAULT_STROKE_GYROTHRESH);
	
	//Initialize Variables
	Sample_Index 						= 0;
	Stroke_Index 						= 0;
	Stroke_StartTime 				= 0;
	Stroke_numThreshCrosses = 0;
	Stroke_Active 					= false;
	LockBuffer 							= false;
	
}

/************************************************************************************
This function is called by the main loop as quickly as possible
Any processing here should be done quickly to avoid stalling the main loop
*************************************************************************************/
void Application::doTasks()
{
	if(Stroke_Active){
		//Wait until the holdoff time expires before unlocking the buffer
		if(StrokeHoldoff->isExpired(false)){
			LockBuffer = false;
		}
	}
}

/************************************************************************************
This function gets call everytime a subscription has a new value
*************************************************************************************/
void Application::update(Publisher* who)
{
	if(who == pAcclGyro->OutputSet_AcclRawVal){
		AcclGyroUpdate(*pAcclMarker,*pAcclVal,*pGyroVal);
	}
}

/************************************************************************************
Sensor processing function
*************************************************************************************/
void Application::AcclGyroUpdate(uint32_t marker, Vect3<int16_t> &AcclVal, Vect3<int16_t> &GyroVal)
{
	
	Sample_dT = (marker) - SampleMarker;
	SampleMarker = (marker);
	
	//Buffer Samples
	if(LockBuffer == false){
			GyroBuffer[Sample_Index] = GyroVal;
			AcclBuffer[Sample_Index] = AcclVal;
			Sample_Index++;
			if(Sample_Index >= NUM_SAMPLES_TO_BUFFER){
				//Loop buffer pointer
				Sample_Index = 0;
			}
		
		if(Stroke_Active == false){
			//Stroke Detector
			int32_t accl_mean_sq = AcclVal(0)*AcclVal(0)+AcclVal(1)*AcclVal(1)+AcclVal(2)*AcclVal(2);
			int32_t gyro_mean_sq = GyroVal(0)*GyroVal(0)+GyroVal(1)*GyroVal(1)+GyroVal(2)*GyroVal(2);
			
			if(accl_mean_sq > Stroke_AcclThreshCounts || gyro_mean_sq > Stroke_GyroThreshCounts){
				Stroke_numThreshCrosses++;
			}
			else{
				Stroke_numThreshCrosses=0;
			}
			
			if(Stroke_numThreshCrosses > NUM_STROKE_THRESH_CROSSES){
				Stroke_numThreshCrosses = 0;
				TriggerStroke(marker);
			}
		}
		else{
			//Stroke Active, wait until remainder of buffer is filled
			if(Sample_Index == Stop_Index){
				Stroke_Active = false;
				StrokeHoldoff->set_uS(STROKE_HOLDOFF_TIME_uS);
				Tx_APP_STROKE_DETECTED(DestPort); //Transmit Buffer Command
			}
		}
	}
}

/************************************************************************************
Trigger a Stroke 
*************************************************************************************/
RESULT Application::TriggerStroke(uint32_t marker)
{
	Stroke_Active = true;
	Stroke_StartTime = marker;
	Stroke_Count++;
	Stroke_Index = Sample_Index;
	Stop_Index = (Stroke_Index + ((NUM_SAMPLES_TO_BUFFER-1)/2)) % NUM_SAMPLES_TO_BUFFER;
	OutputSet_Stroke->NotifySubs();
	
	return RESULT_SUCCESS;
}

/************************************************************************************
Set the Gyro Threshold for Stroke Detection
*************************************************************************************/
RESULT Application::setStroke_GyroThresh(float val)
{
	//Convert from engineering units to counts
	Stroke_GyroThresh = val;
	float scalefactor = pAcclGyro->getScaleFactor_Gyro();
	Stroke_GyroThreshCounts = (val)/scalefactor; //Stores the square of the threshold
	Stroke_GyroThreshCounts *= Stroke_GyroThreshCounts;
	return RESULT_SUCCESS;
}

/************************************************************************************
Set the Gyro Threshold for Stroke Detection
*************************************************************************************/
RESULT Application::setStroke_AcclThresh(float val)
{
	//Convert from engineering units to counts
	Stroke_AcclThresh = val;
	float scalefactor = pAcclGyro->getScaleFactor_Accl();
	Stroke_AcclThreshCounts = (val)/scalefactor; 
	Stroke_AcclThreshCounts *= Stroke_AcclThreshCounts; //Square threshhold
	return RESULT_SUCCESS;
}

/************************************************************************************
Handles all Variable Callbacks for this object
*************************************************************************************/
EV_ID Application::updateVariable(Variable *var)
{
	Application* pObj = Application::getInstance();
	
	RESULT result;
	
	if(var == pObj->Var_Stroke_GyroThresh){
		result = pObj->setStroke_GyroThresh(pObj->Stroke_GyroThresh);
	}
	else if(var == pObj->Var_Stroke_AcclThresh){
		result = pObj->setStroke_AcclThresh(pObj->Stroke_AcclThresh);
	}
	else{
		return EV_ID::CMDFAILED;
	}
	
	if(result == RESULT_SUCCESS){
		return EV_ID::AOK;
	}
	else{
		return EV_ID::BADPARAM;
	}
}

/************************************************************************************
This static function is can be called to transmit stroke information
*************************************************************************************/
EV_ID Application::Tx_APP_STROKE_DETECTED(Port* dest_port)
{
	Application* pApp = Application::getInstance();
	
	//Create Packet Header Infomation
	PacketBuilder* pPacketBuilder = PacketBuilder::getInstance();
	pPacketBuilder->StartPacket( dest_port, PI_RESPCONSOLE, PACKET_TYPE::APP_RESP );	
  pPacketBuilder->Payload->push( static_cast< uint8_t >( APP_RESP::STROKE_DETECTED ));
  
	//Create Packet Payload
	pPacketBuilder->Payload->push( pApp->Stroke_StartTime ); 			//Time stroke was detected
	pPacketBuilder->Payload->push( NUM_SAMPLES_TO_BUFFER ); //Number of Samples
	pPacketBuilder->Payload->push( pApp->Stroke_Index ); //Sample when stroke was detected
  
	//Finishes packet and moves it into the destination port
	pPacketBuilder->FinishPacket();
	
	//Transmit Sample Buffer
	uint8_t i = 0;
	uint8_t num_samples_to_tx;
	do{
		num_samples_to_tx = ((NUM_SAMPLES_TO_BUFFER-i) > NUM_SAMPLES_PER_BLOCK)? NUM_SAMPLES_PER_BLOCK:(NUM_SAMPLES_TO_BUFFER-i);
		
		Tx_APP_SAMPLE_BUFFER(dest_port,i,num_samples_to_tx);
		i += num_samples_to_tx;
		
	}while(i<NUM_SAMPLES_TO_BUFFER);
	
	return EV_ID::NONE;
}

/************************************************************************************
Transmit Sample Buffer in blocks
*************************************************************************************/
EV_ID Application::Tx_APP_SAMPLE_BUFFER(Port* dest_port, uint16_t start_index, uint8_t num_samples)
{
	Application* pApp = Application::getInstance();
	//Create Packet Header Infomation
	PacketBuilder* pPacketBuilder = PacketBuilder::getInstance();
	pPacketBuilder->StartPacket( dest_port, PI_RESPCONSOLE, PACKET_TYPE::APP_RESP );	
  pPacketBuilder->Payload->push( static_cast< uint8_t >( APP_RESP::SAMPLE_BUFFER ));
  
	//Create Packet Payload
	pPacketBuilder->Payload->push( (uint16_t) start_index ); //Sample when stroke was detected
	pPacketBuilder->Payload->push( (uint8_t*)(pApp->AcclBuffer),sizeof(Vect3<int16_t>)*num_samples);
	pPacketBuilder->Payload->push( (uint8_t*)(pApp->GyroBuffer),sizeof(Vect3<int16_t>)*num_samples);
	
  
	//Finishes packet and moves it into the destination port
	pPacketBuilder->FinishPacket();
	
	return EV_ID::NONE;
}
/************************************************************************************
This static function is called each time the APP_TRIGGER_STROKE message is received
*************************************************************************************/
EV_ID Application::Parse_APP_CMD_FORCE_STROKE(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type)
{
	Application* pApp = Application::getInstance();
	
	pApp->TriggerStroke(Marker::get32());
	
	return EV_ID::AOK;
}

/************************************************************************************
This static function is called each time the APP_TRIGGER_STROKE message is received
*************************************************************************************/
EV_ID Application::Parse_APP_CMD_SEND_TEST_PACKET(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type)
{
	int32_t i;
	Vect3<int16_t> GyroVal;
	Vect3<int16_t> AcclVal;
	//Overwrite sensor buffer
	const int16_t AcclX_Offset = 0x1000;
	const int16_t AcclY_Offset = 0x2000;
	const int16_t AcclZ_Offset = 0x3000;
	const int16_t GyroX_Offset = 0x4000;
	const int16_t GyroY_Offset = 0x5000;
	const int16_t GyroZ_Offset = 0x6000;
	
	Application* pApp = Application::getInstance();
	
	pApp->Stroke_StartTime = Marker::get32();
	pApp->Stroke_Index = pApp->Sample_Index;
	pApp->Stop_Index = (pApp->Stroke_Index + ((NUM_SAMPLES_TO_BUFFER-1)/2)) % NUM_SAMPLES_TO_BUFFER;
	
	i = pApp->Stop_Index + 1;
	
	do{
		if(i >= NUM_SAMPLES_TO_BUFFER){
			i=0;
		}
		
		AcclVal(0) = AcclX_Offset + i;
		AcclVal(1) = AcclY_Offset + i;
		AcclVal(2) = AcclZ_Offset + i;
		
		GyroVal(0) = GyroX_Offset + i;
		GyroVal(1) = GyroY_Offset + i;
		GyroVal(2) = GyroZ_Offset + i;
		
		pApp->GyroBuffer[i] = GyroVal;
		pApp->AcclBuffer[i] = AcclVal;
	
		i++;
	}while(i != pApp->Stop_Index);
	
	Tx_APP_STROKE_DETECTED(RespPort);
	
	return EV_ID::NONE;
}

