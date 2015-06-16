/*******************************************************************************
* File Name          : Mag_LSM9DS1.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/5/2015
* Description        : Interface to ST Micro LSM9DS1 Magnetometer
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef MAG_LSM9DS1_H
#define MAG_LSM9DS1_H

#include "Comms/OutputSet.h"
#include "Sensors/Mag_LSM9DS1_RegVals.h"
#include "Peripherals/SPIInterface.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/ExtTrigger_Interface.h"

const uint8_t MAX_NUM_SUBSCRIBERS_MAG = 4;

class Mag
{
  public:
	  //SPI Specific Functions
	  Mag( SPIPort* spi, IO_Pin* pin_CS, IO_Pin* pin_datardy );
	
		//Common Functions
		void doTasks();
		bool isReady(){ return PinDataRdy->isOn(); }; // Assumes common DRDY
		void Reset();

		void Init( ODR_M_VAL datarate, FS_M_VAL fullscale );
		
		void setMagDataRate(ODR_M_VAL datarate);
	  void setMagFullScale(FS_M_VAL fullscale);
		void setBiasMag(Vect3<float_t>& bias){MagBias = bias;};
		Vect3<float_t>* getBiasMag(){return &MagBias;};
	
		void Enable();
		void Disable();
		RESULT SelfTest(bool simple_test);
		
		//Mag Variables
		OutputSet*	OutputSet_MagRawVal;
		Output* 		Output_MagRawVal;
		OutputSet*	OutputSet_MagValEng;
		Output* 		Output_MagValEng;

		static Mag* getInstance(void){return Mag::pMag;};
  private:
		static Mag* pMag;
		~Mag();
		void ParseData_MAG_DATA();
		void updateVals();
		void ProcessCntrlRegs();
		PERIPH_STATUS 	ReqData(LSM9DS1_M_ADDR reg_addr);	
		PERIPH_STATUS 	ReqData(LSM9DS1_M_ADDR reg_addr,uint8_t numBytes);	
		PERIPH_STATUS 	getRegister(LSM9DS1_M_ADDR addr, uint8_t &reg_val);	
		PERIPH_STATUS		setRegister(LSM9DS1_M_ADDR addr, uint8_t &reg_val);
		
		static void MagDRDY_Fcn( IRQ_TYPE irqsrc ); // Function Called when DRDY is triggered
	
		uint32_t Marker; 
		int32_t Period_uS;
		volatile uint32_t NewMarker; //(used by interrupt)
		volatile uint16_t PendReads; //(used by interrupt)
		uint32_t MaxFifoSamples;
		int8_t NumSamplesBuffered;
		uint32_t NumBytesPerSample;
		uint32_t NumBytesRx;
		LSM9DS1_M_ADDR ReqReg;
	
		bool Initialized;
		bool FIFOEnabled;
		Timer* TimeoutTimer;
		uint16_t Timeouts;
		uint32_t TimeoutPeriod_uS;
		uint32_t maxPeriod_uS;
		uint32_t ExpPeriod_uS;
		uint32_t deltaMarker;
	
		//Magnetometer Functions
		void Mag_SnsToBody(Vect3<int16_t>& sns, Vect3<int16_t>& body); //Implement in main (PCB specific)

		SPIPort* 		SPIx;
		IO_Pin*  		PinDataRdy;
		IO_Pin*  		PinCS;
		ExtTrigger* ExtTrigDrdy;
		
		//SPI Values
		Buffer* 		TxBuf;
		Buffer* 		RxBuf;
		volatile PERIPH_TRANSACTION_STATE TransactionState;
		
		//Magnetometer Variables
		Vect3<int16_t> MagRawVal;
		Vect3<float_t> MagVal_Eng;
		Vect3<float_t> MagVal_Filt;
		Vect3<float_t> MagBias;
		float ScaleFactor;
		bool PassedSelfTest;
		bool Enabled;
		
		//Registers
		STATUS_M_VAL 		Status;
		CTRL_REG1_M_VAL	Cntrl1;
		CTRL_REG2_M_VAL	Cntrl2;
		CTRL_REG3_M_VAL	Cntrl3;
		CTRL_REG4_M_VAL	Cntrl4;
		CTRL_REG5_M_VAL	Cntrl5;
};
#endif




