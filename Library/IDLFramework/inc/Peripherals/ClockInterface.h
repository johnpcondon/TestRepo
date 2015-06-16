/****************************************************************************
* File Name          : ClockInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 7/3/2013
* Description        : This module implements GPIO Functions
******************************************************************************/
#ifndef ClockInterface_H
#define ClockInterface_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"

//Pure Virtual Class
class Clocks{
	public:
		
		static void setSysClock(uint32_t SysClkFreq); //This function should be implemented per project in main
		static void EnableClock(AF_Periph periph);
		static void DisableClock(AF_Periph periph);
		
		static uint32_t getSysClkFreq(){return SysClkFreq;};
		static uint32_t getSysTick();
		static void setSysTick_Freq(uint32_t tick_freq_Hz);
		
	private:
		Clocks();
		~Clocks();
	
		static uint32_t SysClkFreq;
	
		
}; //End Class

#endif
