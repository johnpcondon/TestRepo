/****************************************************************************
* File Name          : PWMInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module will implements PWM Functions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef PWMInterface_H
#define PWMInterface_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"

class PWMOutput{
  
public:
	virtual void doTasks() = 0;

  virtual void Enable() = 0;
  virtual void Disable() = 0;
  
  virtual void setPeriod(uint32_t period) = 0;
	virtual void setFrequency(uint32_t freq) = 0;
  virtual void setDuty(float dutycycle) = 0;

	virtual bool isEnabled(){return isEn;};
protected:
	virtual ~PWMOutput(){};
	IO_Pin* Pin;
	bool isEn;
	float DutyCycle;
	uint32_t Period;
private:
  
}; //End Class

#endif
