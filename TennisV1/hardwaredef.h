/*******************************************************************************
* File Name          : HardwareDef.h
* Author             : John P Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Contains hardware/pin definitions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef __HARDWARE_DEF_H__
#define __HARDWARE_DEF_H__

//****************************************************************
//Radio Board w/ Nordic
//NRF51822_AA
//****************************************************************
//#include "IOInterface.h"
#include "nrf.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/InterruptsInterface.h"


/********Resources Used ************

Interrupt Priorities (0-highest, 
	Radio/Gazelle Timer					0
	Gazelle Callback Functions	1
	ADC Sampling								2

Peripherials
	ADC			VSupply, other ADC sampling
	TWI1		
	Radio		Gazelle
	Timer0	Marker Timer
	Timer1	
	Timer2	Gazelle
	PPI0		Gazelle
	PPI1		Gazelle
	PPI2		Gazelle
	UART1		Data Output
	
Radio Pipes
	Gazelle Pairing 0
	Gazelle Data 		1-7
	
***********************************/


const uint32_t HSE_CLK_FREQ = 16000000;


//Flash Storage
const uint8_t 		FLASH_SETTINGS_PAGE = 127;

//Serial Number
const uint64_t* const SN_ADDR = (const uint64_t*)(&NRF_FICR->DEVICEID[0]); //Yep, I'm casting a voltatile to a const... it's constant... deal with it compiler!

//-------------------------------------------
//Device Settings
//-------------------------------------------
#define HWFC           true

//Pin Definitions
#define PIN_ENLDO_SNS     IO_PIN_0
#define PIN_DEN_AG     		IO_PIN_1
#define PIN_INT2_AG     	IO_PIN_2
#define PIN_INT1_AG     	IO_PIN_3
#define PIN_INT1_MAG     	IO_PIN_4
#define PIN_DRDY_MAG     	IO_PIN_5
#define PIN_CS_MAG     		IO_PIN_6
#define PIN_CS_AG     		IO_PIN_7
#define PIN_SNS_MISO   		IO_PIN_8
#define PIN_SNS_MOSI   		IO_PIN_9
#define PIN_SNS_SCK		    IO_PIN_10
#define PIN_USART0_TX		  IO_PIN_11
#define PIN_USART0_RX		  IO_PIN_12
#define PIN_BUZZER		    IO_PIN_25
#define PIN_LED_STATUS    IO_PIN_29
#define PIN_VBUS_DET			IO_PIN_30

const uint8_t	PPI_CH_GAZELLE0 = 0;
const uint8_t	PPI_CH_GAZELLE1 = 1;
const uint8_t	PPI_CH_GAZELLE2 = 2;
const uint8_t	PPI_CH_I2C 			= 3;

const uint8_t	PWM_CHANNEL			= 2; //Uses PPI*2 and PPI*2+1

const AF_Periph MARKER_TIMER = AF_TIM0; //Do not change

//Interrupt Priority Table
//const uint8_t IRQ_PREEMPTN_ACCLGYRO_RDY = 2;
//const uint8_t IRQ_PREEMPTN_MAG_RDY  		= 2;
const INTERRUPT_PRIORITY IRQ_PRIORITY_MARKER 				= IRQ_PRIOR_1;
const INTERRUPT_PRIORITY IRQ_PRIORITY_SPI 					= IRQ_PRIOR_1;
const INTERRUPT_PRIORITY IRQ_PRIORITY_UART0 				= IRQ_PRIOR_2;
const INTERRUPT_PRIORITY IRQ_PRIORITY_MAG_RDY 			= IRQ_PRIOR_2;

#endif

