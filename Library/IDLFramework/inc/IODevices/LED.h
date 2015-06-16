/*********************************************************************
* Company: 	QFO Labs
* Project: 	Mimix Controller
* Author:	John Condon
* File: 	LED.c
* 
* Description: This file contains the functions for LED Control
**********************************************************************/

#ifndef LED_H
	#define LED_H

#include "Peripherals/TimerInterface.h"
#include "Peripherals/PWMSoftware.h"
#include "Peripherals/IOInterface.h"

const uint16_t LED_NumPulseIncrements = 100;

class LED{
	public:
		LED(PWMSoftware* pwm_pin);
		void doTasks();
	
		void TurnOn();
		void TurnOff();
		void setFlash(uint32_t* flash_periods,uint8_t num_states);
		void setPulse(uint32_t pulse_period);
		void setFade(uint32_t fade_period);
		void setSolid();
		void setSolid(float solid_brightness);
		void setBrightness(float min_brightness, float max_brightness);
		PWMSoftware* PWMPin;
		
	private:
		~LED();
		bool Flash;
		bool Pulse;
		float PulseIncrement;
		uint32_t NumStates;
		uint32_t State;
		uint32_t* FlashTimes;
		bool GoingUp;
		
		float MinBrightness;
		float MaxBrightness;
		float Brightness;

		Timer* StateTimer;
};



#endif


