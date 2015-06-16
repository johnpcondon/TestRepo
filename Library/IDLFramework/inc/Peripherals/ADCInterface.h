/******************************************************************************
* File Name          : ADCInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This defines functions for the ADC Peripheral
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"
#include "Containers/JCVect.h"
#include "Peripherals/TimerInterface.h"
#include "DMAInterface.h"

typedef struct
{
  uint32_t marker;
  uint16_t val; //mV
} ADC_DATA;

enum ADC_CH_NUM{
	ADC_CH_NUM_0,
	ADC_CH_NUM_1,
	ADC_CH_NUM_2,
	ADC_CH_NUM_3,
	ADC_CH_NUM_4,
	ADC_CH_NUM_5,
	ADC_CH_NUM_6,
	ADC_CH_NUM_7,
	ADC_CH_NUM_8,
	ADC_CH_NUM_9,
	ADC_CH_NUM_10,
	ADC_CH_NUM_11,
	ADC_CH_NUM_12,
	ADC_CH_NUM_13,
	ADC_CH_NUM_14,
	ADC_CH_NUM_15,
	ADC_CH_NUM_16,
	ADC_CH_NUM_17,
	ADC_CH_NUM_18,
	ADC_CH_VDD,
};

enum ADC_REF_CHECK{
	ADC_REF_VINT_TEMP = 0,
	ADC_REF_VBAT,
};

class ADCInterface;

class ADCChannel
{
	friend class ADCInterface;
	public:
		uint16_t getVal_Scaled(); //Get raw ADC value
		uint16_t getVal_mVScaled(); //Get value in mV
		uint16_t getVal_Raw(); //Get raw ADC value
		uint16_t getVal_mV(); //Get value in mV
		void setScaling(float scalefactor);
		void setOffset(uint16_t offset);
		ADC_CH_NUM getChNum(){return ADC_Ch_Num;};
	protected:
		//Only ADCInterface should call this constructor
		ADCChannel(const char* name, ADCInterface* ADCx, ADC_CH_NUM adc_ch_num, uint8_t buff_offset);
	private:
		
		~ADCChannel();
		ADC_CH_NUM ADC_Ch_Num;
		const char*		Name_;
		uint8_t iBuf;
		float ScaleFactor;
		uint16_t Offset;
		ADCInterface* ADCx;
};

class ADCInterface
{
	friend class ADCChannel;
	public:
		static ADCInterface* getInstance(AF_Periph adcx);
		
	  ADCInterface(AF_Periph AF_adcx, uint8_t max_num_channels, uint32_t update_val_period,uint32_t update_ref_period);
		ADCChannel* AddChannel(const char* name, IO_Pin* pin);
		ADCChannel* AddChannel(const char* name, ADC_CH_NUM ch_num);
	
		void Enable();
		void Disable();
		bool isEnabled(){return isEnabled_;};
		
		void useDMA(uint8_t stream_num);
		void useInterrupts();
		
	  void doTasks();
		void updateVref();
		uint16_t getVBat_mV(){return Vbat_mV;};

		void setScale_VBat(float scale,uint16_t bias);
	protected:
		uint16_t getVal_Raw(uint8_t iBuf){return ADCBuf_RawSamples[iBuf];};
		uint16_t getVal_mV(uint8_t iBuf){return ((float)ADCBuf_RawSamples[iBuf] * Raw2mV_ConvFactor);};
	private:
		~ADCInterface();
		
		void doTasks_Hardware();
		void init_Hardware(); //Function defined in ADC_Hardware.cpp
		ADC_CH_NUM getADCChannel(IO_Pin* pin);
		uint8_t AddChannel_Hardware(ADC_CH_NUM adc_ch);
	
		AF_Periph AF_ADCx;
		float Raw2mV_ConvFactor;
		uint16_t Vcc_mV;
		uint16_t Vbat_mV;
		uint16_t Temp;
		ADC_REF_CHECK refCheck;
		bool isEnabled_;
		bool usingDMA;
		bool usingInts;

		uint32_t Marker_Ref;
		uint32_t Marker_Vals;
	
		ADCChannel* AN_CH_Vref;
		ADCChannel* AN_CH_Temp;
		ADCChannel* AN_CH_VBat;
		
		DMAInterface* DMAPort;
		Timer* Timer_updateRef;
		Timer* Timer_updateVals;
		
		vector<ADCChannel*>* ADC_Channels;   
		
		//Values used in interrupts
		static void ADC_IRQCallback(IRQ_TYPE irqsrc);
		volatile uint16_t* ADCBuf_RawSamples;
		volatile uint8_t iADC;
		
};



#endif



