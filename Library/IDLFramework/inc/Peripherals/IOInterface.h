/****************************************************************************
* File Name          : IOInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module implements GPIO Functions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef IOInterface_H
#define IOInterface_H

#include "Generic/GenericTypeDef.h"

enum IO_ACTIVE_LEVEL{
	IO_ACTIVE_DEFAULT = 0,
	IO_ACTIVE_HIGH = 1,
	IO_ACTIVE_LOW  = 2,
};

enum IO_EXTI_TRIGGER{
		IO_EXTI_TRIGGER_RISING 		= 0,
		IO_EXTI_TRIGGER_FALLING 	= 1,
		IO_EXTI_TRIGGER_RISEFALL 	= 2,
	
};

enum IO_PORT_NUM{
	IO_PORT_0 = 0, //Nordic
	IO_PORT_A,		 //ST
	IO_PORT_B,		 //ST
	IO_PORT_C,		 //ST
	IO_PORT_D,		 //ST
	IO_PORT_E,			//ST
	IO_PORT_F,			//ST
	IO_PORT_G,			//ST
};

enum IO_SPEED{
	IO_SPEED_NA,
	IO_SPEED_LOW,
	IO_SPEED_MED,
	IO_SPEED_FAST,
	IO_SPEED_MAX,
};

enum IO_OUTPUTTYPE{
	IO_OUT_NA,
	IO_OUT_PUSHPULL,
	IO_OUT_OPENDRAIN,
};

enum IO_DRIVE_MODE{
	IO_MODE_DISABLED = 0,
	
	IO_MODE_In_Analog,
	IO_MODE_In_Float, 
	IO_MODE_In_PullUp,
	IO_MODE_In_PullDown,
	
	IO_MODE_Out_OD, 
	IO_MODE_Out_PP, 
	IO_MODE_AFOut_OD,
	IO_MODE_AFOut_PP,
	IO_MODE_AFIn_Float,
	IO_MODE_AFIn_PullUp,
	IO_MODE_AFIn_PullDown,
};

enum IO_PULL{
	IO_PULL_NONE,
	IO_PULL_UP,
	IO_PULL_DOWN,
	IO_PULL_RES,
};

enum IO_PIN_NUM{
  IO_PIN_0 = 0,
	IO_PIN_1 = 1,
	IO_PIN_2 = 2,
	IO_PIN_3 = 3,
	IO_PIN_4 = 4,
	IO_PIN_5 = 5,
	IO_PIN_6 = 6,
	IO_PIN_7 = 7,
	IO_PIN_8 = 8,
	IO_PIN_9 = 9,
	IO_PIN_10 = 10,
	IO_PIN_11 = 11,
	IO_PIN_12 = 12,
	IO_PIN_13 = 13,
	IO_PIN_14 = 14,
	IO_PIN_15 = 15,
	IO_PIN_16 = 16,
	IO_PIN_17 = 17,
	IO_PIN_18 = 18,
	IO_PIN_19 = 19,
	IO_PIN_20 = 20,
	IO_PIN_21 = 21,
	IO_PIN_22 = 22,
	IO_PIN_23 = 23,
	IO_PIN_24 = 24,
	IO_PIN_25 = 25,
	IO_PIN_26 = 26,
	IO_PIN_27 = 27,
	IO_PIN_28 = 28,
	IO_PIN_29 = 29,
	IO_PIN_30 = 30,
	IO_PIN_31 = 31,
	IO_PIN_NONE = 0xFF,
};

//Peripheral with GPIO pin associations
enum AF_Periph{
	AF_NA = 0,
	AF_MCO1,
	AF_MCO2,
	AF_JTAG,
	AF_RTC,
	AF_TRACE,
	AF_PWR,
	AF_CRC,
	
	AF_GPIOA,
	AF_GPIOB,
	AF_GPIOC,
	AF_GPIOD,
	AF_GPIOE,
	AF_GPIOF,
	AF_GPIOG,
	AF_GPIOH,
	AF_GPIOI,
	
	AF_DMA1,
	AF_DMA2,
	
	AF_ADC1,
	AF_ADC2,
	AF_ADC3,
	
	AF_TIM0,
	AF_TIM1,
	AF_TIM2,
	AF_TIM3,
	AF_TIM4,
	AF_TIM5,
	AF_TIM6,
	AF_TIM7,
	AF_TIM8,
	AF_TIM9,
	AF_TIM10,
	AF_TIM11,
	
	AF_I2C0,
	AF_I2C1,
	AF_I2C2,
	AF_I2C3,
	
	AF_SPI0,
	AF_SPI1,
	AF_SPI2,
	AF_SPI3,
	AF_SPI4,
	AF_SPI5,
	AF_I2S1,
	AF_I2S2,
	AF_I2S3,
	AF_I2S4,
	AF_I2S5,
	
	AF_UART0,
	AF_UART1,
	AF_UART2,
	AF_UART3,
	AF_UART4,
	AF_UART5,
	AF_UART6,
	
	AF_SDIO,
	AF_USB_FS,
	AF_EVENTOUT,
	AF_MEM2MEM,
};
	
class IO_Pin{
	public:
		IO_Pin(IO_PORT_NUM port_num,IO_PIN_NUM pin_num);
		IO_Pin(IO_PIN_NUM pin_num); //only use if no port label exists
	
		//Interface Implemented Functions
		void setActiveLevel(IO_ACTIVE_LEVEL ActiveLevel);
		void set(bool val);
		bool isLow();
		bool isHigh();
		bool isOn();
		bool isOff();
		void TurnOn();	
		void TurnOff();
		IO_PORT_NUM 		getPortNum(){return PortNum;};
		IO_PIN_NUM 			getPinNum(){return PinNum;};
		IO_ACTIVE_LEVEL getActiveLevel(){return ActiveLevel;};
		IO_DRIVE_MODE 	getDriveMode(){return DriveMode;};
		
		//Hardware Specific Functions (Defined in IO_Hardware.h)
		void setMode(IO_DRIVE_MODE drive_mode);
		//void cfg_pin(IO_MODE mode, IO_PULL pull, IO_SPEED speed);
		void setHigh();
		void setLow();
		void Toggle();	
		bool get();
		//void setMode(IO_MODE mode);
		void setPull(IO_PULL pull);
		void setSpeed(IO_SPEED speed);
		void setOutputType(IO_OUTPUTTYPE outputtype);
		
		static void* getPeriphBase(AF_Periph periph);
		static AF_Periph getPeriphFromBase(void* periph_base);
		static uint32_t getPinNum(IO_PIN_NUM pin_num);
	private:
		~IO_Pin(){};
		IO_PORT_NUM PortNum;
		IO_PIN_NUM	PinNum;
		IO_ACTIVE_LEVEL ActiveLevel;
		IO_DRIVE_MODE DriveMode;
		
		//IO_MODE Mode;
		IO_PULL Pull;
		IO_SPEED Speed;
		IO_OUTPUTTYPE OutputType;
		
}; //End Class

#endif
