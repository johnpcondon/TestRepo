/****************************************************************************
* File Name          : Buttons.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module creates button reading and debounce functions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

#include "Generic/GenericTypeDef.h"
#include "Containers/JCVect.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/ADCInterface.h"

class ButtonState;
class Button;
typedef void (*BtnCallback)(Button* btn); //Interrupt callback function.  Return if to clear flag


//Base Class
class Button{
	public:
		Button(IO_Pin* pin, uint8_t max_num_states,uint32_t debonuce_time_us);
		Button(ADCChannel* analog_ch, uint16_t analog_threshold,uint8_t max_num_states,uint32_t debouce_time_us);
		
		RESULT addState(uint32_t press_time,BtnCallback callback_onpress,BtnCallback callback_onrelease);
	
		bool isPressed(); //Can Be Polled
		uint32_t getPressTime();
		
		static void doTasks(); //Call as fast as possible (~100Hz works)
		static void Boot(uint8_t max_num_buttons);
	private:
		
		void debounce();
		void Reset();
		bool isPressed_;
	
		IO_Pin* Pin;
		bool isAnalogButton;
		ADCChannel* AnalogCH;
		uint16_t ADCVal;
		uint16_t AnalogThreshold;
	
		ButtonState* ActiveState;
		uint32_t PressedMarker;
		uint32_t ReleasedMarker;
		uint32_t DebounceTime;
	
		vector<ButtonState*>* ButtonStates;
		static vector<Button*>* Buttons;
};

//Button States are added to buttons to define what actions need to be performed after certain press times
class ButtonState{
	friend class Button;
	protected:
		ButtonState(uint32_t press_time, BtnCallback callback_onpress, BtnCallback callback_onrelease);
		void TriggerCallback(Button* btn,bool was_released);
		uint32_t getTriggerTime(){return PressTriggerTime;};
	private:
		uint32_t PressTriggerTime;
		BtnCallback CallBack_onRelease;
		BtnCallback CallBack_onPress;
};


#endif

