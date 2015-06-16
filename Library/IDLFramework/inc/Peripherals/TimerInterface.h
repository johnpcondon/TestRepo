/****************************************************************************
* File Name          : Timers.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module will implements general purpose software timers
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef TIMERS_H_
  #define TIMERS_H_

#include "Generic/genericTypedef.h"
#include "Containers/JCVect.h"

//Uses the marker timer as its base with 1uS resolution
//These timers are designed to be polled for completion
//Max Timeout is 71.5 mins

#define MARKER_TICK_TIME 1E-6

class Timer{
	 public:
		Timer();
		Timer(uint32_t period_us);
	 
		bool set_uS(uint32_t period_us);
		bool set_mS(uint32_t period_ms);
		bool set_S(uint32_t period_s);
		uint32_t getPeriod_uS(){return Period_uS_;};
		void setPeriod_uS(uint32_t period){Period_uS_ = period;};
		bool reset();
		bool isRunning();
		void Disable();
		bool isExpired();
		bool isExpired(bool resetTimer);
		
		static void delay_clockless(uint32_t delay);
		static void delay_uS(uint32_t period_us); //Don't use this in interrupts!
		static int getNumTimers();
		static void clearWrap(int timerNum);
		static void clearTimerWraps(void);
	 
		static void Boot(uint8_t max_num_timers);
	 protected:
		 
	 
	 private:  
		~Timer();
		void init(void);
		
		bool Enabled_;
		uint32_t Period_uS_;
		volatile uint32_t Expiration_; 
		volatile bool Wrap_;		//This wrap is cleared when the marker Upper overflows
		
		uint8_t Index_;
	 
		static Timer* pDelayTimer;
    static vector<Timer*>* Timers; //Vector of all timers
		
};//End Class

#endif


