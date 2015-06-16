/****************************************************************************
* File Name          : ExtTrigger_Interface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 11/12/14
* Description        : This module implements External Interrupts on GPIO Pins
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef INTERRUPT_HARDWARE_H
#define INTERRUPT_HARDWARE_H

#include "Generic/GenericTypeDef.h"
#include "nrf.h"

const uint8_t MAX_NUM_INTERRUPTS = 80;

enum IRQ_TYPE{
	IRQ_NMI=0,
	IRQ_HardFault,
	IRQ_SVC,
	IRQ_PendSV,
	IRQ_SysTick,
	IRQ_Default,
	
	IRQ_POWER,
	IRQ_CLOCK,
	
	IRQ_RADIO, 
	
	IRQ_UART0,
	IRQ_SPI0,
	IRQ_SPI1,
	IRQ_TWI0_STOPPED,
	IRQ_TWI0_RXDREADY,
	IRQ_TWI0_TXDSENT,
	IRQ_TWI0_ERROR,
	IRQ_TWI0_BB,
	
	IRQ_TWI1_STOPPED,
	IRQ_TWI1_RXDREADY,
	IRQ_TWI1_TXDSENT,
	IRQ_TWI1_ERROR,
	IRQ_TWI1_BB,

	IRQ_GPIOTE_IN0,
	IRQ_GPIOTE_IN1,
	IRQ_GPIOTE_IN2,
	IRQ_GPIOTE_IN3,
	IRQ_GPIOTE_PORT,
	
	IRQ_ADC1,
	IRQ_ADC2,
	IRQ_ADC3,
	
	IRQ_TIMER0_COMP0,
	IRQ_TIMER0_COMP1,
	IRQ_TIMER0_COMP2,
	IRQ_TIMER0_COMP3,
	
	IRQ_TIMER1_COMP0,
	IRQ_TIMER1_COMP1,
	IRQ_TIMER1_COMP2,
	IRQ_TIMER1_COMP3,
	
	IRQ_TIMER2_COMP0,
	IRQ_TIMER2_COMP1,
	IRQ_TIMER2_COMP2,
	IRQ_TIMER2_COMP3,
	
	IRQ_RTC0_TICK,
	IRQ_RTC0_OVRFLW,
	IRQ_RTC0_COMP0,
	IRQ_RTC0_COMP1,
	IRQ_RTC0_COMP2,
	IRQ_RTC0_COMP3,
	
	IRQ_RTC1_TICK,
	IRQ_RTC1_OVRFLW,
	IRQ_RTC1_COMP0,
	IRQ_RTC1_COMP1,
	IRQ_RTC1_COMP2,
	IRQ_RTC1_COMP3,
	
	IRQ_TEMP_DATARDY,
	IRQ_RNG_VALRDY,
	IRQ_ECB,
	IRQ_CCM,
	IRQ_AAR,
	IRQ_WDT,
	IRQ_QDEC,
	
	IRQ_SWI0,
	IRQ_SWI1,
	IRQ_SWI2,
	IRQ_SWI3,
	IRQ_SWI4,
	IRQ_SWI5,
	
	IRQ_Software
};


#endif
