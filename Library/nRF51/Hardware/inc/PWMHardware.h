/****************************************************************************
* File Name          : PWMHardware.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 5/16/14
* Description        : This module will implements hardware based PWM Functions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef PWMHardware_H
#define PWMHardware_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Peripherals/PWMInterface.h"
#include "nrf.h"

class PWMHardware:public PWMOutput{
	 
  public:
		PWMHardware(IO_Pin* pin, bool is_push_pull, IO_ACTIVE_LEVEL active_high, uint32_t period, AF_Periph AF_timx, uint8_t channel);
		virtual void setDuty(float duty);
		virtual void setFrequency(uint32_t freq);
		virtual void setPeriod(uint32_t period);
		virtual void doTasks();
		virtual void Enable();
		virtual void Disable();
	
		//Public only for interrupts
		NRF_TIMER_Type* TIMx;
		uint16_t ScaledPeriod; //Value in register
		uint16_t ScaledDuty; //Value in register
		uint8_t			OutputCh;
		void ApplyModulation();
	protected:
		virtual ~PWMHardware(){};
  private:
		PWMOutput* PWMx;
		IO_ACTIVE_LEVEL ActiveLevel;
		uint16_t Prescaler;
		uint32_t Frequency;
		
		
}; //End Class

#endif
