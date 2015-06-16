/****************************************************************************
* File Name          : PWMSoftware.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module will implements software based PWM Functions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef PWMSoftware_H
#define PWMSoftware_H

#include "Peripherals/IOInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Peripherals/PWMInterface.h"

class PWMSoftware:public PWMOutput{
	 
  public:
		PWMSoftware(IO_Pin* pin, bool push_pull, IO_ACTIVE_LEVEL active_level, uint32_t period);
		virtual void setDuty(float duty);
		virtual void setFrequency(uint32_t freq);
		virtual void setPeriod(uint32_t period);
		virtual void doTasks();
		virtual void Enable();
		virtual void Disable();
  private:
		virtual ~PWMSoftware(){};
		uint32_t Period;
		uint32_t TimeOn;
		uint32_t TimeOff;
		
		Timer* DutyCycleTimer;
}; //End Class

#endif
