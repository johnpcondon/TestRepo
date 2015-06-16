/****************************************************************************
* File Name          : ExtClock_Interface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 11/12/14
* Description        : This module implements External Clock output (MCO)
******************************************************************************/
#ifndef ExtClockInterface_H
#define ExtClockInterface_H

#include "genericTypeDef.h"
#include "IOInterface.h"

///********************************************************************
//**This should be done before enabling external oscilators and PLLs**
///********************************************************************
enum EXT_CLK_SRC{
	EXT_CLK_SRC_HSI,
	EXT_CLK_SRC_HSE,
	EXT_CLK_SRC_LSE,
	EXT_CLK_SRC_PLL,
	EXT_CLK_SRC_SYSCLK,
	EXT_CLK_SRC_PLLI2S,
};
class ExtClock{
	public:
		ExtClock(AF_Periph mco_periph, IO_Pin* pin, EXT_CLK_SRC clksrc, uint8_t div);
		uint32_t setFreq(uint32_t freq);
		void Enable();
		void Disable();
	
	private:
		AF_Periph MCOPeriph;
		EXT_CLK_SRC ClkSrc;
		IO_Pin* MCOPin;
		~ExtClock();
	
}; //End Class

#endif
