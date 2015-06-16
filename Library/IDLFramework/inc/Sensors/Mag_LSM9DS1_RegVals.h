/*******************************************************************************
* File Name          : Mag_LSM9DS1_RegVals.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 04/30/13
* Description        : Register Values for the ST Micro LSM9DS1 Magnetometer
*******************************************************************************/
#ifndef MAG_LSM9DS1_REGVALS_H
#define MAG_LSM9DS1_REGVALS_H

#include "Generic/GenericTypeDef.h"

//--------------
//Constants
//--------------

const float MAG_SENS_4GAUS 		= 0.00014;
const float MAG_SENS_8GAUS 		= 0.00029;
const float MAG_SENS_12GAUS 	= 0.00043;
const float MAG_SENS_16GAUS 	= 0.00058;

const uint8_t WHO_AM_I_M_VAL = 0x3D;

const uint8_t READ_M_REG  = 0xC0; //Auto increment
const uint8_t WRITE_M_REG = 0x40; //Auto increment

const uint32_t MAX_MAG_SPI_SLACK = 600; //uS

const uint8_t MAG_MAX_SAMPLE_SIZE = 7; //Num bytes per sample (accl/gyro, only... not temp)

//This uses the SPI's Tx buffer for data transfers.
const int32_t MAG_TX_MAXSIZE = 10; 
const int32_t MAG_RX_MAXSIZE = MAG_MAX_SAMPLE_SIZE+5;

//--------------
//Register Addresses
//--------------
enum LSM9DS1_M_ADDR{
	MAG_NONE							= 0x00,
	MAG_OFFSET_X_REG_L 		= 0x05,
	MAG_OFFSET_X_REG_H 		= 0x06,
	MAG_OFFSET_Y_REG_L 		= 0x07,
	MAG_OFFSET_Y_REG_H 		= 0x08,
	MAG_OFFSET_Z_REG_L 		= 0x09,
	MAG_OFFSET_Z_REG_H 		= 0x0A,
	MAG_WHO_AM_I					= 0x0F,
	MAG_CTRL_REG1				= 0x20,
	MAG_CTRL_REG2				= 0x21,
	MAG_CTRL_REG3				= 0x22,
	MAG_CTRL_REG4				= 0x23,
	MAG_CTRL_REG5				= 0x24,
	MAG_FOOBAR          = 0x26,
	MAG_STATUS_REG				= 0x27,
	MAG_OUT_X_L						= 0x28,
	MAG_OUT_X_H						= 0x29,
	MAG_OUT_Y_L						= 0x2A,
	MAG_OUT_Y_H						= 0x2B,
	MAG_OUT_Z_L						= 0x2C,
	MAG_OUT_Z_H						= 0x2D,
	MAG_INT_CFG						= 0x30,
	MAG_INT_SRC						= 0x31,
	MAG_INT_THS_L					= 0x32,
	MAG_INT_THS_H					= 0x32,
};

//--------------
//CNTRL_REG1_M
//--------------
enum PWR_M_XL_VAL{
	PWR_M_XY_LOW 		= 0,
	PWR_M_XY_MED 		= 1,
	PWR_M_XY_HIGH 	= 2,
	PWR_M_XY_VHIGH 	= 3,
};

enum ODR_M_VAL{
	ODR_M_0P625 	= 0,
	ODR_M_1P25		= 1,
	ODR_M_2P5 		= 2,
	ODR_M_5P0 		= 3,
	ODR_M_10P0 		= 4,
	ODR_M_20P0 		= 5,
	ODR_M_40P0 		= 6,
	ODR_M_80P0 		= 7,
};

typedef union{
	uint8_t  val;
  struct {
		bool 					SelfTestEn	:1;
		bool 					unused			:1;
		ODR_M_VAL			ODR					:3;
		PWR_M_XL_VAL 	Mode				:2;
		bool 					TempCompEn	:1;
	};
}CTRL_REG1_M_VAL;


//--------------
//CNTRL_REG2_M
//--------------
enum FS_M_VAL{
	FS_M_4GAUS  = 0,
	FS_M_8GAUS  = 1,
	FS_M_12GAUS = 2,	
	FS_M_16GAUS = 3,	
};

typedef union{
	uint8_t  val;
  struct {
		uint8_t unused 		:2;
		bool		SOFT_RST	:1;
		bool		REBOOT		:1;
		uint8_t unused2		:1;
		FS_M_VAL FS_M			:2;
		uint8_t unused3		:1;
	};
}CTRL_REG2_M_VAL;

//--------------
//CNTRL_REG3_M
//--------------
enum MODE_M_VAL{
	MODE_M_CONT    = 0,
	MODE_M_SING  	 = 1,
	MODE_M_PWRDWN  = 2,
	MODE_M_PWRDWN2 = 3,
};

enum SIM_M_VAL{
	SIM_M_4WIRE = 0,
	SIM_M_3WIRE = 1,
};

typedef union{
	uint8_t  val;
  struct {
		MODE_M_VAL	MODE_M 	:2;
		SIM_M_VAL	SIM 				:1;	
		uint8_t unused			:2;
		bool LOWPWR_EN			:1;
		uint8_t unused2			:1;
		bool	I2C_DISABLE		:1;
	};
}CTRL_REG3_M_VAL;

//--------------
//CNTRL_REG4_M
//--------------
enum PWR_M_Z_VAL{
	PWR_M_Z_LOW 	= 0,
	PWR_M_Z_MED 	= 1,
	PWR_M_Z_HIGH 	= 2,
	PWR_M_Z_VHIGH = 3,
};

typedef union{
	uint8_t  val;
  struct {
		uint8_t unused			:1;
		bool		BLE					:1;
		PWR_M_Z_VAL PWM_M_Z	:2;
		uint8_t unused2			:4;
	};
}CTRL_REG4_M_VAL;

//--------------
//CNTRL_REG5_M
//--------------
enum BDU_M_VAL{
	BDU_M_CONT 	= 0,
	BDU_M_BLOCK = 1,
};

typedef union{
	uint8_t  val;
  struct {
		uint8_t unused			:6;
		BDU_M_VAL		BDU				:1;
		uint8_t unused2			:1;
	};
}CTRL_REG5_M_VAL;

//--------------
//STATUS_REG
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool XDA 				:1;
		bool YDA 				:1;
		bool ZDA 				:1;
		bool ZYXDA 			:1;
		bool XOR	 			:1;
		bool YOR	 			:1;
		bool ZOR				:1;
		bool ZYXOR			:1;
	};
}STATUS_M_VAL;

//--------------
//INT_CFG
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool IEN 				:1;
		bool IEL 				:1;
		bool IEA 				:1;
		uint8_t unused	:2;
		bool ZIEN	 			:1;
		bool YIEN	 			:1;
		bool XIEN				:1;
	};
}INT_CFG_M_VAL;

//--------------
//INT SRC
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool INT 				:1;
		bool MROI				:1;
		bool NTH_Z			:1;
		bool NTH_Y			:1;
		bool NTH_X			:1;
		bool PTH_Z 			:1;
		bool PTH_Y 			:1;
		bool PTH_X			:1;
	};
}INT_SRC_M_VAL;

#endif





