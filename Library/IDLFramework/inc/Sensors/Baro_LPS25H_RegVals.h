/*******************************************************************************
* File Name          : Baro_LPS25H_RegVals.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 12/12/14
* Description        : Register Values for the ST Micro LPS25H Barometer
*******************************************************************************/
#ifndef BARO_LPS25H_REGVALS_H
#define BARO_LPS25H_REGVALS_H

#include "Generic/GenericTypeDef.h"

//--------------
//Constants
//--------------

const float LPS25H_PRESS_SCALEFACTOR = 0.0244140625; 
const float LPS25H_TEMP_SCALEFACTOR  = 0.0020833333;

const float LPS25H_TEMP_BIAS = 42.5;

const uint8_t WHO_AM_I_B_VAL = 0x3D;

const uint8_t READ_B_REG  = 0xC0; //Auto increment
const uint8_t WRITE_B_REG = 0x40; //Auto increment

const uint32_t MAX_BARO_SPI_SLACK = 600; //uS
//--------------
//Register Addresses
//--------------
enum LPS25H_ADDR{
	BARO_NONE						= 0x00,
	BARO_REF_P_XL				= 0x08,
	BARO_REF_P_L				= 0x09,
	BARO_REF_P_H				= 0x0A,
	BARO_WHO_AM_I				= 0x0F,
	BARO_RES_CONF				= 0x10,
	BARO_CNTRL1					= 0x20,
	BARO_CNTRL2					= 0x21,
	BARO_CNTRL3					= 0x22,
	BARO_CNTRL4					= 0x23,
	BARO_INT_CFG				= 0x24,
	BARO_INT_SOURCE			= 0x25,
	BARO_STATUS					= 0x27,
	BARO_PRESS_POUT_XL	= 0x28,
	BARO_PRESS_POUT_L		= 0x29,
	BARO_PRESS_POUT_H		= 0x2A,
	BARO_PRESS_TEMP_L		= 0x2B,
	BARO_PRESS_TEMP_H		= 0x2C,
	BARO_FIFO_CTRL 			= 0x2E,
	BARO_FIFO_STATUS 		= 0x2F,
	BARO_THS_P_L 				= 0x30,
	BARO_THS_P_H 				= 0x31,
	BARO_RPDS_L 				= 0x39,
	BARO_RPDS_H 				= 0x3A,

};

//--------------
//RES_CONF
//--------------
enum AVGT_VAL{
	AVGT_8 		= 0,
	AVGT_16 	= 1,
	AVGT_32 	= 2,
	AVGT_64 	= 3,
};

enum AVGP_VAL{
	AVGP_8 		= 0,
	AVGP_32 	= 1,
	AVGP_128 	= 2,
	AVGP_512 	= 3,
};

typedef union{
	uint8_t  val;
  struct {
		uint8_t				reserved 	:4;
		AVGT_VAL			AVGT			:2;
		AVGP_VAL			AVGP			:2;
	};
}RES_CONF_VAL;


//--------------
//CNTRL_REG1
//--------------
enum SIM_B_VAL{
	SIM_B_4WIRE = 0,
	SIM_B_3WIRE = 1,
};

enum BDU_B_VAL{
	BDU_B_CONT 	= 0,
	BDU_B_BLOCK = 1,
};

enum ODR_B_VAL{
	ODR_B_OneShot = 0,
	ODR_B_1P0			= 1,
	ODR_B_7P0			= 2,
	ODR_B_12P5		= 3,
	ODR_B_25P0		= 4,
};

typedef union{
	uint8_t  val;
  struct {
		SIM_B_VAL			SIM				:1;
		bool					RESET_AZ	:1;
		BDU_B_VAL			BDU				:1;
		bool					INT_EN		:1;
		ODR_B_VAL			ODR				:3;
		bool					ACTIVE_EN	:1;
	};
}CTRL_REG1_B_VAL;

//--------------
//CNTRL_REG2
//--------------

typedef union{
	uint8_t  val;
  struct {
		bool ONE_SHOT_START 	:1;
		bool AUTOZERO_EN 			:1;
		bool SW_RESET 				:1;
		bool I2C_DISABLE 			:1;
		bool FIFO_MEAN_DEC_EN :1;
		bool WTM_EN 					:1;
		bool FIFO_EN 					:1;
		bool BOOT 						:1;
	};
}CTRL_REG2_B_VAL;

//--------------
//CNTRL_REG3
//--------------

enum INT_H_L_VAL{
	INT_ACTIVE_HIGH = 0,
	INT_ACTIVE_LOW	= 1,
};

enum PP_OD_B_VAL{
	PUSHPULL 	= 0,
	OPENDRAIN = 1,
};

enum INT1_VAL{
	INT1_DATASIGNAL			= 0,
	INT1_PRESS_HIGH			= 1,
	INT1_PRESS_LOW			= 2,
	INT1_PRESS_LOWHIGH	= 3,
};

typedef union{
	uint8_t  val;
  struct {
		INT1_VAL INT1 					:2;
		uint8_t reserved 				:4;
		PP_OD_B_VAL PP_OD				:1;
		INT_H_L_VAL INT_H_L			:1;
	};
}CTRL_REG3_B_VAL;

//--------------
//CNTRL_REG4
//--------------

typedef union{
	uint8_t  val;
  struct {
		bool P1_DRDY 			:1;
		bool P1_OVERRUN 	:1;
		bool P1_WTM 			:1;
		bool P1_EMPTY 		:1;
		uint8_t reserved 	:4;		
	};
}CTRL_REG4_B_VAL;

//--------------
//INTERRUPT_CFG
//--------------

typedef union{
	uint8_t  val;
  struct {
		bool PH_INT_EN		:1;
		bool PL_INT_EN		:1;
		bool LATCH_INT_EN	:1;
		uint8_t reserved 	:5;
	};
}INT_CFG_B_VAL;

//--------------
//INTERRUPT_SOURCE
//--------------

typedef union{
	uint8_t  val;
  struct {
		bool PH_INT_FLAG		:1;
		bool PL_INT_FLAG		:1;
		bool INT_FLAG				:1;
		uint8_t reserved 		:5;
	};
}INT_SRC_B_VAL;

//--------------
//STATUS_REG
//--------------

typedef union{
	uint8_t  val;
  struct {
		bool T_DATAREADY		:1;
		bool P_DATAREADY		:1;
		uint8_t reserved2 	:2;
		bool T_OVERRUN			:1;
		bool P_OVERRUN			:1;
		uint8_t reserved 		:2;
	};
}STATUS_B_VAL;


//--------------
//FIFO_CTRL
//--------------
enum F_MODE_VAL{
	F_MODE_BYPASS0	= 0,
	F_MODE_FIFO			= 1,
	F_MODE_STREAM1	= 2,
	F_MODE_STREAM2	= 3,
	F_MODE_BYPASS1	= 4,
	F_MODE_reserved = 5,
	F_MODE_MEAN 		= 6,
	F_MODE_BYPASS2 	= 7,
};

enum WTM_POINT_VAL{
	WTM_POINT_2			= 1,
	WTM_POINT_4			= 3,
	WTM_POINT_8			= 7,
	WTM_POINT_16		= 15,
	WTM_POINT_32		= 31,
};

typedef union{
	uint8_t  val;
  struct {
		WTM_POINT_VAL WTM_POINT :5;
		F_MODE_VAL F_MODE 			:3;
	};
}FIFO_CNTRL_B_VAL;

//--------------
//FIFO_CTRL
//--------------

typedef union{
	uint8_t  val;
  struct {
		uint8_t FIFO_DATA_LVL :5;
		bool FIFO_EMPTY			:1;
		bool FIFO_FULL			:1;
		bool FIFO_WTM_LVL		:1;
	};
}FIFO_STATUS_B_VAL;

#endif





