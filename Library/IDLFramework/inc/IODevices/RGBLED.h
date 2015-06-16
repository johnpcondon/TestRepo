/*********************************************************************
* Company: 	QFO Labs
* Project: 	Mimix Controller
* Author:	John Condon
* File: 	LED.c
* 
* Description: This file contains the functions for LED Control
**********************************************************************/

#ifndef RGBLED_H
	#define RGBLED_H

#include "Peripherals/TimerInterface.h"
#include "Peripherals/PWMSoftware.h"

class RGBLED;

const uint16_t RGB_NumPulseIncrements = 1000;

class RGBLED{
	public:
		RGBLED(PWMOutput* red, PWMOutput* green, PWMOutput* blue);
		void doTasks();
	
		void TurnOn();
		void TurnOff();
		void setFlash(uint32_t* flash_periods,uint8_t num_states);
		void setPulse(uint32_t pulse_period);
		void setFade(uint32_t fade_period);
		void setSolid();
		void setSolid(float solid_brightness);
		bool setColor(uint8_t iColor);
		bool setColor(float red_percent,float green_percent, float blue_percent);
		void setBrightness(float min_brightness, float max_brightness);
		PWMOutput* Red;
		PWMOutput* Grn;
		PWMOutput* Blu;	
	
	private:
		~RGBLED();
		bool Flash;
		bool Pulse;
		float PulseIncrement;
		uint32_t NumStates;
		uint32_t State;
		uint32_t* FlashTimes;
		bool GoingUp;
		
		float Color[3];
		float MinBrightness;
		float MaxBrightness;
		float Brightness;

		Timer* StateTimer;
};



#endif


