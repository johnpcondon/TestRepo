/****************************************************************************
* File Name          : ExtTrigger_Interface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module implements External Interrupts on GPIO Pins
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef ExtTrigger_H
#define ExtTrigger_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/InterruptsInterface.h"

enum EXT_TRIGGER_EDGE{
	EXT_TRIG_RISING,
	EXT_TRIG_FALLING,
	EXT_TRIG_RISINGFALLING,
};

class ExtTrigger{
	public:
		ExtTrigger(IO_Pin* pin,EXT_TRIGGER_EDGE edge);
		void EnableEventInterrupt(IntCallback fcn,INTERRUPT_PRIORITY priority);
		void GenerateSWInterrupt();
		bool EventOccured();
		void Enable();
		void Disable();
	
	private:
		~ExtTrigger();
		IO_Pin* Pin;
		EXT_TRIGGER_EDGE Edge;
		uint8_t EXTI_Ch;
		
		bool TriggerInterrupt;
		bool isEnabled;
}; //End Class

#endif
