/******************************************************************************
* File Name          : IRInterface.hpp
* Author             : John Condon
* Version            : V 1.0
* Date               : 4/20/2013
* Description        : This defines functions for the IR Tx and Rx functions
*
*******************************************************************************/
#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H

#include "Peripherals/PWMInterface.h"
//#include "Sensor.hpp"

#define NUM_IR_DATABITS 8 //NUM DATA BITS
#define NUM_IR_BITS     NUM_IR_DATABITS + 3 //Total values to Rx
#define NUM_IR_STATES  (NUM_IR_BITS)*2 + 1 //(Start + Data + Parity + Stop) x2 + PullOff

#define IR_DUTY_CYCLE (float)(0.2)

//IR Times (10uS per count)
#define IR_START_ON     300 
#define IR_START_OFF    300 
#define IR_BIT_HIGH_ON  75 
#define IR_BIT_HIGH_OFF 225 
#define IR_BIT_LOW_ON   225
#define IR_BIT_LOW_OFF  75
#define IR_STOP_ON      300
#define IR_STOP_OFF     300
#define IR_PULLOFF      20000

#define IRRX_BIT_THRESHHOLD 1000

class IRTx;
extern IRTx* pIRTx;

class IRRx;
extern IRRx* pIRRx;

class IRTx{
	public:
	  IRTx(uint16_t modulation_freq);
	  void init();
	  int TxData(uint16_t data);
	  uint16_t RxData();

	  bool 		isLocked;
	  uint16_t 	State;
	  bool		Parity;
	  uint16_t 	TimeBuf[NUM_IR_STATES+1];
	  uint16_t 	NumStates;
	  
	  PWM_Pin* pPWMPin;
	  
  	private:
		~IRTx(){};
	  
};

typedef struct{
  uint32_t marker;
  uint8_t data;
}IRRX_DATA;
 
class IRRx//:Sensor
{
public:
  IRRx();
  void ParseData();
  bool getBit(uint32_t PulsePos);
  uint8_t getData();
  
  volatile int iRxBit;
  volatile uint32_t PulsePeriodBuf[NUM_IR_BITS];
  //volatile uint32_t PulsePosBuf[20];
  volatile uint32_t prevFallMarker;
	volatile bool incomingData;
  IRRX_DATA RxData;
  
private:
  ~IRRx(){};
  int badCnt;
  
  
};


#endif
