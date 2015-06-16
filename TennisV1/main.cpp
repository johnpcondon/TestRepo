/*********************************************************************
* Company:  Innovative Design Labs
* Project:  Tennis Board
* Author:	  John Condon / Adam Becker
* File:			main.cpp
* Descript: Main file for the Tennis Board using the Gazelle protocol. 
* Notes: 		Targets Rev. 1.
* Date:			6/3/2015
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

// Processor Specific Includes
#include "nrf.h"

//Application Specific Includes
#include "Application.h"
#include "DefaultSettings.h"
#include "hardwaredef.h"

// Standard Includes
#include "Generic/Device.h"

// Peripheral Includes
#include "Peripherals/ClockInterface.h"
#include "Peripherals/MarkerInterface.h"
#include "Peripherals/UARTInterface.h"
#include "Peripherals/IOInterface.h"
#include "Peripherals/PWMSoftware.h"
#include "Peripherals/PWMInterface.h"
#include "Peripherals/TimerInterface.h"
#include "Peripherals/ADCInterface.h"

//IO Devices
#include "IODevices/LED.h"
#include "IODevices/Buttons.h"
#include "IODevices/Buzzer.h"

//Radio
#include "NRFRadio_multipair.h"

//Comms
#include "Comms/VariableAccess.h"

//Containers
#include "Containers/Buffer.h"

// Sensor Includes
#include "Sensors/AcclGyro_LSM9DS1_SPI.h"
#include "Sensors/Mag_LSM9DS1_SPI.h"

//Peripheral Globals
NRFRadio* pRadio;
SPIPort* 	pSpiSns;
AcclGyro* pAcclGyro;
LED* 			pLEDStatus;
UartPort* pUart;
Port* 		pRdoData;
Buzzer* 	pBuzzer;
Button* 	pPwrButton;
ADCInterface* pADC;
ADCChannel* 	pADCPwrButton;

//IO Pin Globals
//These are pins not wrapped in higher level peripherals
//Or need to be access outside of their peripherals
IO_Pin* IO_ENLDO;
IO_Pin* IO_DEN_AG;
IO_Pin* IO_DRDY_AG;
IO_Pin* IO_DRDY_MAG;
//IO_Pin* IO_SPI_AG_CS;
//IO_Pin* IO_SPI_MAG_CS;

uint32_t HeapUsage = 0;

void InitHardware();
void IDLFramework_Boot();

int main(void)
{
	IDLFramework_Boot();
	InitHardware();
	
	// IDL Comms Protocol Setup
	PacketParser::setMasterPort(pRdoData); 
	PacketParser::setAsEndNode();
	
	PacketParser::enablePacketType(PACKET_TYPE::COMMAND);
	PacketParser::enablePacketType(PACKET_TYPE::RADIOCMD);
	PacketParser::enablePacketType(PACKET_TYPE::RADIORESP);
	PacketParser::enablePacketType(PACKET_TYPE::STATUS);	

	// Init IMU
	IO_DEN_AG->TurnOn();
	
	Timer::delay_uS(100000); //Delay if we want to.
	Timer* Timer1Hz = new Timer(PERIOD_1Hz);
	uint32_t statusMarker = Marker::get32();
	OutputSet* osStatus  = new OutputSet("Status",&statusMarker, PERIOD_1Hz,0,1);
	
	pLEDStatus->setPulse(PERIOD_5Hz);
	
	Application* pApp = Application::getInstance();
	pApp->Init(pRdoData,pAcclGyro);
	
	bool IndicatePaired = false;
	
	
  while(true)
  {
		pRadio->doTasks();
		pSpiSns->doTasks();
		pAcclGyro->doTasks();
		pLEDStatus->doTasks();
		//pBuzzer->doTasks();
		pApp->doTasks();
		
		if(Timer1Hz->isExpired(true))
		{
			//pBuzzer->Beep();
			Port::updateAllRateMeas();
			
			statusMarker = Marker::get32();
			osStatus->NotifySubs();
			
			//Flash LED when paired
			if(pRadio->isDevicePaired())
			{
				if(IndicatePaired == false)
				{
					IndicatePaired = true;
					pLEDStatus->setFlash((uint32_t*)BLINK_PERIODS,(2*pRadio->getNumPipesPaired()));
				}
			}
			else if(IndicatePaired == true)
			{
				IndicatePaired = false;
				pLEDStatus->setPulse(PERIOD_10Hz);
			}

			
			// Send info on what is subscribed
			OutputSet::Tx_RESP_ALLPORT_ALLSUBINFO(pRdoData,PACKET_TYPE::RESPONSE);
			HeapUsage = Device::getTotalHeapUsage();
		}
	}
}

void AcclGyro::Accl_SnsToBody(Vect3<int16_t>& sns, Vect3<int16_t>& body)
{
	//For TENNIS
  body(0) = sns(1);
  body(1) = -sns(0);
  body(2) = -sns(2);
}
void AcclGyro::Gyro_SnsToBody(Vect3<int16_t>& sns, Vect3<int16_t>& body)
{
	//For TENNIS
  body(0) = sns(1);
  body(1) = -sns(0);
  body(2) = -sns(2);
}
void Mag::Mag_SnsToBody(Vect3<int16_t>& sns, Vect3<int16_t>& body)
{
	//For TENNIS
  body(0) = sns(1);
  body(1) = sns(0);
  body(2) = -sns(2);
}

uint16_t Device::getVBat_mV()
{
	return 0; //Not implemented yet...
}

//Initialize Hardware Peripherals
void InitHardware()
{
	Device::getInstance();	
		
	// Initialize Timer for software timers and button debounce
	Marker::getInstance();
  __enable_irq();

	// IO Pin Setup
	IO_Pin* IO_LEDStatus = new IO_Pin(PIN_LED_STATUS);
	PWMSoftware* PWMPin_LED = new PWMSoftware(IO_LEDStatus,true,IO_ACTIVE_HIGH,PERIOD_100Hz);
	pLEDStatus = new LED(PWMPin_LED);

	// Setup IO Pins for sensors
	IO_Pin* IO_DEN_AG = new IO_Pin(PIN_DEN_AG);
	IO_DEN_AG->setMode(IO_MODE_Out_PP);
	IO_DEN_AG->setActiveLevel(IO_ACTIVE_HIGH);
	IO_DEN_AG->TurnOff();
	
	IO_Pin* IO_DRDY_AG = new IO_Pin(PIN_INT1_AG);
	IO_DRDY_AG->setMode(IO_MODE_In_Float);
	IO_DRDY_AG->setActiveLevel(IO_ACTIVE_HIGH);
	
	IO_Pin* IO_DRDY_MAG = new IO_Pin(PIN_DRDY_MAG);
	IO_DRDY_MAG->setMode(IO_MODE_In_Float);
	IO_DRDY_MAG->setActiveLevel(IO_ACTIVE_HIGH);
	
	IO_Pin* IO_SPI_AG_CS = new IO_Pin(PIN_CS_AG);
	IO_SPI_AG_CS->setMode(IO_MODE_Out_PP);
	IO_SPI_AG_CS->setActiveLevel(IO_ACTIVE_LOW);
	IO_SPI_AG_CS->TurnOff();
	
	IO_Pin* IO_SPI_MAG_CS = new IO_Pin(PIN_CS_MAG);
	IO_SPI_MAG_CS->setMode(IO_MODE_Out_PP);
	IO_SPI_MAG_CS->setActiveLevel(IO_ACTIVE_LOW);
	IO_SPI_MAG_CS->TurnOff();
	
	// Setup SPI for Sensors
	IO_Pin* IO_SPI_Sns_SCK  = new IO_Pin(PIN_SNS_SCK);
	IO_Pin* IO_SPI_Sns_MOSI = new IO_Pin(PIN_SNS_MOSI);
	IO_Pin* IO_SPI_Sns_MISO = new IO_Pin(PIN_SNS_MISO);
	
	pSpiSns = new SPIPort(AF_SPI0,IO_SPI_Sns_SCK,IO_SPI_Sns_MOSI,IO_SPI_Sns_MISO,FREQ_1MHz,SPI_TIMEOUT_SLACK);
	pSpiSns->useINT(IRQ_PRIORITY_SPI);

	//Power Off Circuitry setup
	IO_ENLDO = new IO_Pin(PIN_ENLDO_SNS);
	IO_ENLDO->setMode(IO_MODE_In_Float);

	//Shutdown button setup
	//(Disabled for a hardware constraint)
	//pADC = new ADCInterface(AF_ADC1, PERIOD_100Hz, ADC_UPDATE_REF_PERIOD);
	//pADCPwrButton = pADC->AddChannel("PwrBtn",IO_ENLDO);
	//pPwrButton = new Button(pADCPwrButton,PWR_BUTTON_ADC_THRESH);
	
	// Radio Setup
	pRadio = new NRFRadio(Device::getDevType(),RdoMode);	
	pRdoData = pRadio->addPipe(RDO_DATA_PIPE_1_NAME,
															true,
															false,
															RDO_DATA_PIPE_RXBUF_SIZE,
															RDO_DATA_PIPE_TXBUF_SIZE,
															RDO_DATA_OUTPUTSET_BUF_SIZE,
															RDO_DATA_OUTPUTSET_FLUSH_TIME,
															RDO_DATA_OUTPUTSET_WATERMARK_REMAINING);
															
	pRadio->init(RDO_DATARATE,RDO_PAIRING_TX_POWER,RDO_DATA_TX_POWER,RDO_CHAN_TABLE,sizeof(RDO_CHAN_TABLE));
	pRadio->EnableAutoPair();

	//Buzzer Setup
	IO_Pin* IO_Buzzer = new IO_Pin(PIN_BUZZER);
	//pBuzzer = new Buzzer(IO_Buzzer,BUZZER_INIT_FREQ,BUZZER_INIT_DUTYCYCLE);
	
	//Sensor Instantiation
	pAcclGyro = new AcclGyro(pSpiSns,IO_SPI_AG_CS,IO_DRDY_AG,ACCLGYRO_NUMSAMPLES_BUFF);

}

//This function is only needed by Rev 1 silicon to fix an old PAN
void PAN_Rev1(void)
{   
	if ((((*(uint32_t *)0xF0000FE8) >> 4) & 0x0000000F) == 1)
	{
			*(uint32_t *)0x40000504 = 0xC007FFDF;
			*(uint32_t *)0x40006C18 = 0x00008000;
	}
}

//This is called before main is reached
void SystemInit()
{
	//SystemInit();	
	NRF_POWER->RAMON = POWER_RAMON_ONRAM0_RAM0On   << POWER_RAMON_ONRAM0_Pos
									 | POWER_RAMON_ONRAM1_RAM1On 	 << POWER_RAMON_ONRAM1_Pos;

	// Take manual control of the clock (it takes too long to turn on/off, ~800us)
	Clocks::setSysClock(HSE_CLK_FREQ);

}

void Clocks::setSysClock(uint32_t clk_freq)
{
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;   
	NRF_CLOCK->TASKS_HFCLKSTART = 1;   
	while(NRF_CLOCK->EVENTS_HFCLKSTARTED == 0){}; 
	Clocks::SysClkFreq = clk_freq;
}

void IDLFramework_Boot()
{
	//Order matters here
	Port::Boot(MAX_NUM_PORTS);
	PacketParser::Boot(MAX_NUM_HANDLED_STATUS,MAX_NUM_HANDLED_CMDS,MAX_NUM_HANDLED_RESPS,MAX_NUM_HANDLED_APPCMDS,MAX_NUM_HANDLED_APPRESPS);
	PacketBuilder::Boot(MAX_NUM_THREADS);
	Device::Boot(MY_DEV_TYPE,HWREV,SWREV,Device_Name,*SN_ADDR);
	Variable::Boot(MAX_NUM_VARIABLES,MAX_NUM_VARGROUPS,FLASH_SETTINGS_PAGE);
	Marker::Boot(MARKER_TIMER,IRQ_PRIORITY_MARKER);
	Timer::Boot(MAX_NUM_TIMERS);
	OutputSet::Boot(MAX_NUM_OUTPUTSETS);
	Button::Boot(MAX_NUM_BUTTONS);
	Subscription::Boot(MAX_NUM_SUBSCRIPTIONS);
	
}

////Function used as a callback when the shutdown button is pressed
//void ShutdownBtnPressed( Button* btn )
//{
//	pLEDStatus->setSolid( 1.0f );
//	
//	while( btn->wasReleased() == false )
//	{
//		Button::doTasks();
//		pADC->doTasks();
//		if( btn->getOutputState() == BUTTON_PRESS_VLONG )
//		{
//			pLEDStatus->setPulse( PERIOD_5Hz );
//			return; //Don't Shut down
//		}
//	};
//	
//	Timer::delay_uS( 10000 );
//	Device::startShutdown();
//}


//Hardware Specific Implimentation to shutdown the device
RESULT Device::startShutdown()
{
	// TODO: Do Preshutdown tasks here
	pADC->Disable();
	//pSDHC->DisablePower();
	Timer::delay_uS( 10000 );
	IO_ENLDO->TurnOn();
	IO_ENLDO->setMode( IO_MODE_Out_OD );
	IO_ENLDO->setSpeed( IO_SPEED_MAX );
	IO_ENLDO->TurnOff();

	return RESULT_SUCCESS;	//Should be off by here

}

//Hardware Specific Implimentation to put the device in a low power state
RESULT Device::startLowPower()
{
	return RESULT_FAILURE; //Not implemented
}
