/******************************************************************************
* File Name          : I2CInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 3/1/2014
* Description        : This defines functions for the I2C Interface
*
*******************************************************************************/
#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

/* Includes ------------------------------------------------------------------*/

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"
//#include "DefaultSettings.h"
#include "Peripherals/TimerInterface.h"
#include "Containers/CircularBuffer.h"
//#include "I2C_Hardware.h"
#include "DMAInterface.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
class I2CHardware;

enum I2C_PORT_NUM{
	PORT_I2C0,
	PORT_I2C1,
	PORT_I2C2,
};

/** IRQ states */
enum I2C_STATE {
		I2C_STATE_IDLE, 
		I2C_STATE_WAIT_START, 
		I2C_STATE_WAIT_ADDRESS, 
		I2C_STATE_WAIT_WRITE, 
		I2C_STATE_WAIT_LAST_WRITE, 
		I2C_STATE_WAIT_READ,
		I2C_STATE_WAIT_STOP,
		I2C_STATE_ERROR, 
};

//enum I2C_STATUS{
//	I2C_STATUS_IDLE,
//	I2C_STATUS_INPROGRESS,
//	I2C_STATUS_FINISHED,
//	I2C_STATUS_ERROR,
//	I2C_STATUS_DEVNOTFOUND,
//	I2C_STATUS_TIMEOUT,
//	I2C_STATUS_ISBUSY,
//};

enum I2C_Rate{
	I2C_Rate_100kHz,
	I2C_Rate_250kHz,
	I2C_Rate_400kHz,
	I2C_Rate_1MHz,
};

class I2CPort{
	public:
		I2CPort(AF_Periph i2c_port_num, IO_Pin* pin_sda, IO_Pin* pin_scl,I2C_Rate rate);
		void doTasks();
		
		PERIPH_STATUS StartTransfer(uint8_t txbyte, CircularBuffer* rxbuf, uint8_t num_rx_bytes, volatile PERIPH_TRANSACTION_STATE* transaction_state, uint8_t dev_id);
		PERIPH_STATUS StartTransfer(CircularBuffer* txbuf, CircularBuffer* rxbuf, uint8_t num_rx_bytes, volatile PERIPH_TRANSACTION_STATE* transaction_state, uint8_t dev_id);
		void EndTransfer(PERIPH_TRANSACTION_STATE state);
		
		//Setup Functions
		PERIPH_STATUS setClkFreq(uint32_t des_freq);
		void useDMA_Tx(uint8_t stream_num);
		void useDMA_Rx(uint8_t stream_num);
		void useINT_Tx();
		void useINT_Rx();
	
		//PERIPH_STATUS TxRx(uint8_t txByte, CircularBuffer* rxBuf, uint32_t numRxBytes, uint8_t dev_id);
		PERIPH_STATUS TxBlocking(CircularBuffer* txBuf);	
	
		//uint8_t TxRxByte(uint8_t byte);
		
		bool isLocked(){return Locked;};
		bool isEnabled();
		
		void RunStateMachine(); //Called by interrupt
		void RunErrorCheck();		//Called by interrupt
	private:
		~I2CPort();
		void ResetErrorCnt();
		void setTransactionState(PERIPH_TRANSACTION_STATE state);
		void* I2CBase;
		AF_Periph AF_I2Cx;
		uint32_t ClkFreq;
		IO_Pin* PinSDA;
		IO_Pin*	PinSCL;
	
		DMAInterface* DMAPort;
		bool usingDMA_Tx;
		bool usingDMA_Rx;
		bool usingINT;
	
		uint8_t DevID;
	
		//Transaction values
		CircularBuffer* TxBuf;
		CircularBuffer* RxBuf;
		volatile uint8_t numRxBytesRemaining;
		volatile PERIPH_TRANSACTION_STATE* pTransactionState;
		volatile bool Locked;
		Timer* TimeoutTimer;
		uint32_t numTimeouts;
		uint32_t numErrors;
		uint32_t numHuh;
	
		I2C_STATE State;
		//Functions defined in I2CHardware.cpp
		PERIPH_STATUS HardwareInit();	
		PERIPH_STATUS HardwareStartTransaction();
		PERIPH_STATUS HardwareEndTransaction();
		
		bool isBusy();
		PERIPH_STATUS ClearBus();
		void Enable();
		void Disable();

};

#endif //__I2C_H
