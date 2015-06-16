/****************************************************************************
* File Name          : Buzzer.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module will implements general buzzer interface
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef BUZZER_H_
  #define BUZZER_H_

#include "Peripherals/IOInterface.h"
#include "Peripherals/PWMInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Comms/VariableAccess.h"

const uint8_t 	BeepSeq_NumStates = 4;
const uint32_t 	BeepSeq_Freq[BeepSeq_NumStates] = {500,1000,1200,1500};
const uint32_t 	BeepSeq_Duration[BeepSeq_NumStates] = {100000,100000,100000,100000};

class Buzzer{
	public:
		Buzzer(IO_Pin* pin,uint32_t freq, float dutycycle);
		void Init(uint32_t freq, float duty);
		void doTasks();
		
		bool isActive(){return Active;};
		
		void Beep(uint32_t duration);
		//void Beep(uint32_t freq,uint32_t duration, uint32_t duty);
		void BeepSequence();		
		void FreqModulate();
		
		void setBeep(uint32_t freq,uint32_t duration, float duty);
		void Disable();
	private:
		~Buzzer();
	
		//Buzzer Parameters
		uint32_t 	Freq;
		uint32_t 	Duration;
		float 		DutyCycle;
		bool 			Active;
	
		uint8_t 			CmdBeep;
		uint8_t				SeqState;
	
		//Buzzer Hardware
		IO_Pin* Pin;
		PWMOutput* PWMPin;
		Timer* Timer_ToneLen;
	
		//Buzzer Variable Access
		VariableGroup* 	VarGrp;
		Variable*       Var_Freq;
		Variable*       Var_Duration;
		Variable*				Var_Duty;
		Variable*				Var_CmdBeep;
		
};


#endif
