/*******************************************************************************
* File Name          : Baro_LPS25H.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/5/2015
* Description        : Interface to ST Micro LPS25H Barometer
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef BARO_LPS25H_H
#define BARO_LPS25H_H

#include "Comms/OutputSet.h"
#include "Sensors/Baro_LPS25H_RegVals.h"
#include "Peripherals/SPIInterface.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/ExtTrigger_Interface.h"


const int32_t BARO_TX_MAXSIZE = 80;
const int32_t BARO_RX_MAXSIZE = 80;

const uint8_t MAX_NUM_SUBSCRIBERS_BARO = 4;
class OutputSet;
class Output;

class Baro
{
  public:
	  //SPI Specific Functions
	  Baro(SPIPort* spi,IO_Pin* pin_CS,IO_Pin* pin_datardy);
	
		//Common Functions
		void doTasks();
		bool isReady(){return Pin_DataRdy->isOn();}; 
		void Reset();
	
		//Barometer Only Functions
		void Init(ODR_B_VAL datarate);
		void setDataRate(ODR_B_VAL datarate);
		//void setBias(Vect3<float_t,3>& bias){Bias = bias;};
		//Vect3<float_t,3>* getBiasBaro(){return &BaroBias;};
		//float	getScaleFactorBaro(){return BaroScaleFactor;};
	
		void Enable();
		void Disable();
		bool SelfTest();
		
		//Baro Variables
		OutputSet*	OutputSet_RawVal;
		Output* 		Output_PressRawVal;
		Output* 		Output_TempRawVal;
		OutputSet*	OutputSet_EngVal;
		Output* 		Output_PressEngVal;
		Output* 		Output_TempEngVal;
		
		//Common Variables 
		uint32_t Marker; 
		int32_t Period;
		volatile uint32_t NewMarker; //(used by interrupt)
		volatile uint16_t PendReads; //(used by interrupt)

		static Baro* getPointer(void){return Baro::pBaro;};
  private:
		//Common Functions
		~Baro();
		void ParseData();
		void ProcessCntrlRegs();
		PERIPH_STATUS 	ReqData(LPS25H_ADDR reg_addr);	
		PERIPH_STATUS 	ReqData(LPS25H_ADDR reg_addr,uint8_t numBytes);	
		PERIPH_STATUS 	getRegister(LPS25H_ADDR addr, uint8_t &reg_val);	
		PERIPH_STATUS		setRegister(LPS25H_ADDR addr, uint8_t &reg_val);
	
		//Common Variables
		static Baro* pBaro;
		SPIPort* SPIx;
		Buffer* TxBuf;
		Buffer* RxBuf;
		volatile PERIPH_TRANSACTION_STATE TransactionState;
		IO_Pin* Pin_DataRdy;
		IO_Pin* Pin_CS;
		ExtTrigger* ExtTrigDrdy;
		uint16_t	MissedReads;
		uint32_t minPeriod_uS;
	  uint32_t maxPeriod_uS;
		
		//Barometer Variables
		int32_t PressVal_Raw;
		float PressVal_Eng;
		float PressScaleFactor;
		float PressBias;
		
		int16_t TempVal_Raw;
		float TempVal_Eng;
		float TempScaleFactor;
		float TempBias;
		
		bool BaroPassedSelfTest;
		bool BaroEnabled;
		
		//Registers
		STATUS_B_VAL Status;
		CTRL_REG1_B_VAL	Cntrl1;
		CTRL_REG2_B_VAL	Cntrl2;
		CTRL_REG3_B_VAL	Cntrl3;
		CTRL_REG4_B_VAL	Cntrl4;

		
	
};



#endif




