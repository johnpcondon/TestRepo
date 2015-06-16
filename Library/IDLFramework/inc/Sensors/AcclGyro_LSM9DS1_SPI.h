/*******************************************************************************
* File Name          : AcclGyro_LSM9DS1.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Interface to ST Micro LSM9DS1 Accel and Gyro
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef LSM330DLC_ACCLGYRO_H
#define LSM330DLC_ACCLGYRO_H

#include "Comms/OutputSet.h"
#include "Sensors/AcclGyro_LSM9DS1_RegVals.h"
#include "Peripherals/SPIInterface.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/ExtTrigger_Interface.h"
#include "Math/Vect3.h"

const INTERRUPT_PRIORITY IRQ_PRIORITY_ACCLGYRO_RDY 	= IRQ_PREEMPT_2_SUB_1;
const uint8_t MAX_NUM_SUBSCRIBERS_ACCLGYRO = 4;
class AcclGyro
{
  public:
	  //SPI Specific Functions
	  AcclGyro(SPIPort* spi,IO_Pin* pin_CS,IO_Pin* pin_datardy, uint8_t max_buffered_samples);
	
		//Common Functions
		void doTasks();
		bool isReady(){return Pin_DataRdy->isOn();}; //Assumes common DRDY
		void Reset();
		RESULT SelfTest(bool simple_test);
		void Init();
		
		//Accelerometer Only Functions
		void InitAccl(ODR_XL_VAL datarate,FS_XL_VAL fullscale);
		void setAcclDataRate(ODR_XL_VAL datarate);
	  void setAcclFullScale(FS_XL_VAL fullscale);
		void setAcclBandwidth(BW_XL_VAL bandwidth);
		void setAcclFilterVal(DCF_XL_VAL filterVal);
		void setBiasAccl(Vect3<float_t>& bias){AcclBias = bias;};
		
		Vect3<float_t>* getBiasAccl(){return &AcclBias;};
		Vect3<float_t>* getAcclVal(){return &AcclVal_Eng;};
		float	getScaleFactor_Accl(){return AcclScaleFactor;};
	
		void EnableAccl();
		void DisableAccl();
		//RESULT SelfTestAccl();
		
		//Gyro Only Funcitons
	  void InitGyro(ODR_G_VAL datarate,FS_G_VAL fullscale,BW_G_VAL bandwidth);
		void setGyroDataRate(ODR_G_VAL datarate);
	  void setGyroFullScale(FS_G_VAL fullscale);
		void setGyroBandwidth(BW_G_VAL bandwidth);
		void setBiasGyro(Vect3<float_t>& bias){GyroBias = bias;};
		float	getScaleFactor_Gyro(){return GyroScaleFactor;};
		Vect3<float_t>* getBiasGyro(){return &GyroBias;};
		
		void EnableGyro();
		void DisableGyro();
		void LowPowerGyro(bool enable);
		
		//Accl Variables
		OutputSet*	OutputSet_AcclRawVal;
		Output* 		Output_AcclRawVal;
		OutputSet*	OutputSet_AcclValEng;
		Output* 		Output_AcclValEng;
		
		OutputSet*	OutputSet_GyroRawVal;
		Output* 		Output_GyroRawVal;
		OutputSet*	OutputSet_GyroValEng;
		Output* 		Output_GyroValEng;

		static AcclGyro* getInstance(){return AcclGyro::pAcclGyro;};
  private:
		//Common Functions
		static AcclGyro* pAcclGyro;
		~AcclGyro();
		void Parse_AG_OUT_TEMP_L();
		void Parse_AG_FIFO_SRC();
		void updateVals();
		void ProcessCntrlRegs();
		void EnableFIFO();
		PERIPH_STATUS 	ReqData(LSM9DS1_AG_ADDR reg_addr);	
		PERIPH_STATUS 	ReqData(LSM9DS1_AG_ADDR reg_addr,uint16_t numBytes);	
		PERIPH_STATUS 	getRegister(LSM9DS1_AG_ADDR reg_addr, uint8_t &reg_val);	
		PERIPH_STATUS		setRegister(LSM9DS1_AG_ADDR reg_addr, uint8_t &reg_val);
		bool FactorySelfTest_Accl();
		bool FactorySelfTest_Gyro();
	
		static void AcclGyroDRDY_Fcn(IRQ_TYPE irqsrc); //IRQ Callback fcn
		//Common Variables 
		uint32_t Marker; 
		int32_t Period_uS;
		volatile uint32_t NewMarker; //(used by interrupt)
		volatile bool PendReads; //(used by interrupt)
		uint32_t MaxFifoSamples;
		int8_t NumSamplesBuffered;
		uint32_t NumBytesPerSample;
		uint32_t NumBytesRx;
		LSM9DS1_AG_ADDR ReqReg;
		
		//Common Values
		bool Initialized;
		bool FIFOEnabled;
		Timer* TimeoutTimer;
		uint16_t Timeouts;
		uint32_t TimeoutPeriod_uS;
		uint32_t maxPeriod_uS;
		uint32_t ExpPeriod_uS;
		uint32_t deltaMarker;
		
		//Debug only
		uint16_t TransactionErrors;
//		uint32_t testPeriod;
//		uint32_t prevMarker;
//		uint32_t markerLow;
//		uint32_t markerHigh;
		
		//Sensor to body frame functions (implement in application, PCB specific)
		void Accl_SnsToBody(Vect3<int16_t>& sns, Vect3<int16_t>& body); 
		void Gyro_SnsToBody(Vect3<int16_t>& sns, Vect3<int16_t>& body); 
	
		//Hardware Info
		SPIPort* SPIx;
		IO_Pin* Pin_DataRdy;
		IO_Pin* Pin_CS;
		ExtTrigger* ExtTrigDrdy;
		
		//SPI Values
		Buffer* TxBuf;
		Buffer* RxBuf;
		volatile PERIPH_TRANSACTION_STATE TransactionState;
		
		//Accelerometer Only Variables
		Vect3<int16_t> AcclRawVal;
		Vect3<float_t> AcclVal_Eng;
		Vect3<float_t> AcclBias;
		float AcclScaleFactor;
		bool PassedSelfTest_Accl;
		bool AcclEnabled;
	
		//Gyro Only Variables
		Vect3<int16_t> GyroRawVal;
		Vect3<float_t> GyroVal_Eng;
		//Vect3<float_t> GyroVal_Filt;
		Vect3<float_t> GyroBias;
		float GyroScaleFactor;
		bool PassedSelfTest_Gyro;
		bool GyroEnabled;

		//Temp Data
		INT_GEN_SRC_G_VAL IntGenSrcG;
		INT_GEN_SRC_XL_VAL IntGenSrcXL;
		int16_t Temp;
		
		//Common Registers
		INT1_CTRL_AG_VAL Cntrl_Int1;
		CTRL_REG4_AG_VAL	Cntrl4;
		CTRL_REG8_AG_VAL	Cntrl8;
		CTRL_REG9_AG_VAL	Cntrl9;
		CTRL_REG10_AG_VAL	Cntrl10;
		FIFO_CTRL_AG_VAL	FIFOCntrl;
		FIFO_SRC_AG_VAL	FIFOSRC;
		
		//Gyro Only Registers
		STATUS_REG1_AG_VAL Status1;
		CTRL_REG1_G_VAL	Cntrl1_G;
		CTRL_REG2_G_VAL	Cntrl2_G;
		CTRL_REG3_G_VAL	Cntrl3_G;
		
		//Accl Only Registers
		STATUS_REG2_AG_VAL Status2;
		CTRL_REG5_XL_VAL	Cntrl5_XL;
		CTRL_REG6_XL_VAL 	Cntrl6_XL;
		CTRL_REG7_XL_VAL	Cntrl7_XL;
	
};



#endif




