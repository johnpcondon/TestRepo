/*******************************************************************************
* File Name          : AcclGyro_LSM9DS1_RegVals.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Register Definitions to ST Micro LSM9DS1 Accel and Gyro
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef LSM9DS1_ACCLGYRO_REGVALS_H
#define LSM9DS1_ACCLGYRO_REGVALS_H

#include "Generic/GenericTypeDef.h"

//--------------
//Constants
//--------------
const float ACCL_SENS_2G 	= 0.000061; 	
const float ACCL_SENS_4G 	= 0.000122;	
const float ACCL_SENS_8G 	= 0.000244;	
const float ACCL_SENS_16G = 0.000732;	

const float GYRO_SENS_245	 = 0.000152716309549504; //Rad
const float GYRO_SENS_500	 = 0.000305432619099008; //Rad
const float GYRO_SENS_2000 = 0.001221730476396031; //Rad

const uint8_t WHO_AM_I_AG_VAL = 0x68;

const uint8_t READ_AG_REG  = 0x80;
const uint8_t WRITE_AG_REG = 0x00;

const uint32_t MAX_AG_SPI_SLACK = 500; //uS

const uint8_t ACCLGYRO_MAX_FIFO_SAMP = 32; //Max num FIFO samples possible
const uint8_t ACCLGYRO_MAX_SAMPLE_SIZE = 12; //Num bytes per sample (accl/gyro, only... not temp)

//This uses the SPI's Tx buffer for data transfers.
const int32_t ACCLGYRO_TX_MAXSIZE = 10; 
//const int32_t ACCLGYRO_RX_MAXSIZE = ACCLGYRO_MAX_SAMPLE_SIZE*ACCLGYRO_NUMSAMPLES_BUFF+5;

//--------------
//Register Addresses
//--------------
enum LSM9DS1_AG_ADDR{
	AG_NONE							= 0x00,
	AG_ACT_THS 					= 0x04,
	AG_ACT_DUR 					= 0x05,
	AG_INT_GEN_CFG_XL		= 0x06,
	AG_INT_GEN_THS_X_XL	= 0x07,
	AG_INT_GEN_THS_Y_XL	= 0x08,
	AG_INT_GEN_THS_Z_XL	= 0x09,
	AG_INT_GEN_DUR_XL		= 0x0A,
	AG_REFERENCE_G			= 0x0B,
	AG_INT1_CNTRL				= 0x0C,
	AG_INT2_CNTRL				= 0x0D,
	AG_WHO_AM_I					= 0x0F,
	AG_CTRL_REG1_G			= 0x10,
	AG_CTRL_REG2_G			= 0x11,
	AG_CTRL_REG3_G			= 0x12,
	AG_ORIENT_CFG_G			= 0x13,
	AG_INT_GEN_SRC_G		= 0x14,
	AG_OUT_TEMP_L				= 0x15,
	AG_OUT_TEMP_H				= 0x16,
	AG_STATUS_REG_G			= 0x17,
	AG_OUT_X_L_G				= 0x18,
	AG_OUT_X_H_G				= 0x19,
	AG_OUT_Y_L_G				= 0x1A,
	AG_OUT_Y_H_G				= 0x1B,
	AG_OUT_Z_L_G				= 0x1C,
	AG_OUT_Z_H_G				= 0x1D,
	AG_CTRL_REG4				= 0x1E,
	AG_CTRL_REG5_XL			= 0x1F,
	AG_CTRL_REG6_XL			= 0x20,
	AG_CTRL_REG7_XL			= 0x21,
	AG_CTRL_REG8				= 0x22,
	AG_CTRL_REG9				= 0x23,
	AG_CTRL_REG10				= 0x24,
	AG_INT_GEN_SRC_XL		= 0x26,
	AG_STATUS_REG_XL		= 0x27,	
	AG_OUT_X_L_XL				= 0x28,
	AG_OUT_X_H_XL				= 0x29,
	AG_OUT_Y_L_XL				= 0x2A,
	AG_OUT_Y_H_XL				= 0x2B,
	AG_OUT_Z_L_XL				= 0x2C,
	AG_OUT_Z_H_XL				= 0x2D,
	AG_FIFO_CTRL				= 0x2E,
	AG_FIFO_SRC					= 0x2F,
	AG_INT_GEN_CFG_G		= 0x30,
	AG_INT_GEN_THS_XH_G	= 0x31,
	AG_INT_GEN_THS_XL_G	= 0x32,
	AG_INT_GEN_THS_YH_G	= 0x33,
	AG_INT_GEN_THS_YL_G	= 0x34,
	AG_INT_GEN_THS_ZH_G	= 0x35,
	AG_INT_GEN_THS_ZL_G	= 0x36,
	AG_INT_GEN_DUR_G		= 0x37,
};
//--------------
//ACT_THS
//--------------
enum GYRO_INACTIVEMODE{
  GYRO_INACTIVEMODE_PWRDOWN = 0,
	GYRO_INACTIVEMODE_SLEEP		= 1,
};

typedef union{
	uint8_t inactive_thres 					:7;
	GYRO_INACTIVEMODE inactive_mode :1;
}ACT_THS_VAL;

//--------------
//INT_GEN_CFG_XL
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool XLIE_XL 					:1;
		bool XHIE_XL 					:1;
		bool YLIE_XL 					:1;
		bool YHIE_XL 					:1;
		bool ZLIE_XL 					:1;
		bool ZHIE_XL 					:1;
		bool XL_6D						:1;
		bool AOI_XL						:1;
	};
}INT_GEN_CFG_XL_VAL;

//--------------
//INT1_CTRL
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool DRDY_XL 					:1;
		bool DRDY_G 					:1;
		bool BOOT		 					:1;
		bool FTH		 					:1;
		bool OVR		 					:1;
		bool FSS5 						:1;
		bool IG_XL						:1;
		bool IG_G							:1;
	};
}INT1_CTRL_AG_VAL;

//--------------
//INT2_CTRL
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool DRDY_XL 					:1;
		bool DRDY_G 					:1;
		bool DRDY_TEMP				:1;
		bool FTH		 					:1;
		bool OVR		 					:1;
		bool FSS5 						:1;
		bool unused						:1;
		bool INACT						:1;
	};
}INT2_CTRL_AG_VAL;

//--------------
//CNTRL_REG1_G
//--------------
enum BW_G_VAL{
	BW_G_LOW 		= 0,
	BW_G_MED 		= 1,
	BW_G_HIGH  	= 2,
	BW_G_VHIGH 	= 3,
};

enum FS_G_VAL{
	FS_G_245 	= 0,
	FS_G_500 	= 1,
	FS_G_NA 	= 2,
	FS_G_2000 = 3,
};

enum ODR_G_VAL{
	ODR_G_PWRDWN 	= 0,
	ODR_G_14P9		= 1,
	ODR_G_59P5 		= 2,
	ODR_G_119 		= 3,
	ODR_G_238 		= 4,
	ODR_G_476 		= 5,
	ODR_G_952 		= 6,
	ODR_G_NA  		= 7,
};

typedef union{
	uint8_t  val;
  struct {
		BW_G_VAL 		BW_G		:2;
		bool 				unused	:1;
		FS_G_VAL		FS_G		:2;
		ODR_G_VAL		ODR_G		:3;
	};
}CTRL_REG1_G_VAL;

//--------------
//CNTRL_REG2_G
//--------------
enum OUTSEL_G_VAL{
	OUTSEL_G_LPF1 = 0,
	OUTSEL_G_HPF 	= 1,
	OUTSEL_G_LPF2 = 2,	
};

enum INSEL_G_VAL{
	INSEL_G_LPF1 	= 0,
	INSEL_G_HPF 	= 1,
	INSEL_G_LPF2 	= 2,	
};

typedef union{
	uint8_t  val;
  struct {
		OUTSEL_G_VAL 	OUT_SEL	:2;
		INSEL_G_VAL 	IN_SEL	:2;
		uint8_t unused				:4;
	};
}CTRL_REG2_G_VAL;
 
//--------------
//CNTRL_REG3_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t HPCF		:4;
		uint8_t unused 	:2;
		bool		HP_EN		:1;
		bool LWPWR_EN 	:1;
	};
}CTRL_REG3_G_VAL;

//--------------
//ORIENT_CFG_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t Orient 	:3;
		bool	SignX_G 	:1;
		bool	SignY_G 	:1;
		bool	SignZ_G 	:1;
		uint8_t unused 	:2;
	};
}ORIENT_CFG_G_VAL;

//--------------
//INT_GEN_SRC_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool 	XL_G		 	:1;
		bool 	XH_G		 	:1;
		bool 	YL_G		 	:1;
		bool 	YH_G		 	:1;
		bool 	ZL_G		 	:1;
		bool 	ZH_G		 	:1;
		uint8_t unused 	:1;
	};
}INT_GEN_SRC_G_VAL;

//--------------
//STATUS_REG
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool XLDA 	:1;
		bool GDA 		:1;
		bool TDA 		:1;
		bool BOOT 	:1;
		bool INACT 	:1;
		bool IG_G 	:1;
		bool IG_XL 	:1;
		bool unused :1;
	};
}STATUS_REG1_AG_VAL;

//--------------
//CTRL_REG4
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool INT4D_XL	:1;
		bool LIR_XL		:1;
		bool unused		:1;
		bool XEN_G	 	:1;
		bool YEN_G	 	:1;
		bool ZEN_G	 	:1;
		uint8_t unused2 :2;
	};
}CTRL_REG4_AG_VAL;

//--------------
//CTRL_REG5
//--------------
enum DEC_XL_VAL{
	DEC_XL_NONE = 0,
	DEC_XL_2 		= 1,
	DEC_XL_4 		= 2,
	DEC_XL_8 		= 3,
};

typedef union{
	uint8_t  val;
  struct {
		uint8_t unused	:3;
		bool 		XEN_XL	:1;
		bool 		YEN_XL	:1;
		bool 		ZEN_XL	:1;
		DEC_XL_VAL 	DEC	:2;
	};
}CTRL_REG5_XL_VAL;

//--------------
//CTRL_REG6
//--------------
enum BW_XL_VAL{
	BW_XL_408 	= 0,
	BW_XL_211 	= 1,
	BW_XL_105 	= 2,
	BW_XL_50 		= 3,
};

enum FS_XL_VAL{
	FS_XL_2G = 0,
	FS_XL_16G = 1,
	FS_XL_4G = 2,
	FS_XL_8G = 3,
};

enum ODR_XL_VAL{
	ODR_XL_PWRDWN = 0,
	ODR_XL_10 		= 1,
	ODR_XL_50 		= 2,
	ODR_XL_119 		= 3,
	ODR_XL_238 		= 4,
	ODR_XL_476 		= 5,
	ODR_XL_952 		= 6,
	ODR_XL_NA 		= 7,
};

typedef union{
	uint8_t  val;
  struct {
		BW_XL_VAL BW_XL				:2;
		bool 			BW_SCAL_ODR	:1;
		FS_XL_VAL FS_XL				:2;
		ODR_XL_VAL ODR_XL			:3;
	};
}CTRL_REG6_XL_VAL;

//--------------
//CTRL_REG7
//--------------
enum DCF_XL_VAL{
	DCF_XL_MED 		= 0,
	DCF_XL_HIGH 	= 1,
	DCF_XL_LOW 		= 2,
	DCF_XL_VHIGH 	= 3,
};

typedef union{
	uint8_t  val;
  struct {
		bool HPIS1 			:1;
		bool unused1 		:1;
		bool FDS				:1;
		bool unused2 		:1;
		bool unused3		:1;
		DCF_XL_VAL DCF	:2;
		bool HR					:1;
	};
}CTRL_REG7_XL_VAL;

//--------------
//CTRL_REG8
//--------------
enum BDU_AG_VAL{
	BDU_AG_CONT 	= 0,
	BDU_AG_BLOCK = 1,
};

enum H_LACTIVE_VAL{
	HL_ACTIVE_HIGH 	= 0,
	HL_ACTIVE_LOW		= 1,
};

enum PP_OD_VAL{
	INT_PP = 0,
	INT_OD = 1,
};

enum SIM_VAL{
	SIM_AG_4WIRE = 0,
	SIM_AG_3WIRE = 1,
};

typedef union{
	uint8_t  val;
  struct {
		bool SW_RESET 			:1;
		bool BLE 						:1;
		bool IF_ADD_IC 			:1;
		SIM_VAL SIM 				:1;
		PP_OD_VAL PP_OD 		:1;
		H_LACTIVE_VAL HL_ACTIVE	:1;
		BDU_AG_VAL BDU 			:1;
		bool BOOT 					:1;
	};
}CTRL_REG8_AG_VAL;

//--------------
//CTRL_REG9
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool STOP_ON_FTH 	:1;
		bool FIFO_EN 			:1;
		bool I2C_DISABLE 	:1;
		bool DRDY_TMR_EN 	:1;
		bool FIFO_TEMP_EN	:1;
		bool unused 			:1;
		bool SLEEP_G 			:1;
		bool unused2 			:1;	
	};
}CTRL_REG9_AG_VAL;

//--------------
//CTRL_REG10
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool ST_XL 			:1;
		bool unused 		:1;
		bool ST_G 			:1;
		uint8_t unused2 :5;
	};
}CTRL_REG10_AG_VAL;

//--------------
//INT_GEN_SRC_XL
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool XL 		:1;
		bool XH			:1;
		bool YL			:1;
		bool YH			:1;
		bool ZL			:1;
		bool ZH			:1;
		bool IA			:1;
		bool unused	:1;
	};
}INT_GEN_SRC_XL_VAL;

//--------------
//STATUS_REG
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool XLDA 			:1;
		bool GDA 				:1;
		bool TDA 				:1;
		bool BOOT 			:1;
		bool INACT 			:1;
		bool IG_G 			:1;
		bool IG_XL			:1;
		bool unused			:1;
	};
}STATUS_REG2_AG_VAL;

//--------------
//FIFO_CTRL
//--------------
enum FMODE_VAL{
	FIFO_MODE_BYPASS			= 0, //Skip the FIFO, resets FIFO
	FIFO_MODE_FIFO 				= 1, //Fills FIFO, then stops collecting (use for burst data collect)
	FIFO_MODE_NA 					= 2, //Reserved, don't use
	FIFO_MODE_CONT2FIFO		= 3, //Continous until trigger released, then FIFO mode
	FIFO_MODE_BYPASS2CONT = 4, //Bypass mode until trigger released, then Continous mode
	FIFO_MODE_CONT		 		= 6, //Continuous mode, overwrites old FIFO samples on overflow
};

typedef union{
	uint8_t  val;
  struct {
		uint8_t FTH 			:5;
		FMODE_VAL FMODE		:3;
	};
}FIFO_CTRL_AG_VAL;

//--------------
//FIFO_SRC
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t FSS :6;
		bool OVRN		:1;
		bool FTH		:1;
	};
}FIFO_SRC_AG_VAL;

//--------------
//INT_GEN_CFG_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		bool XLIE :1;
		bool XHIE :1;
		bool YLIE :1;
		bool YHIE :1;
		bool ZLIE :1;
		bool ZHIE :1;
		bool LIR	:1;
		bool AOI	:1;
	};
}INT_GEN_CFG_G_VAL;

//--------------
//INT_GEN_THS_X_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t THS 	:7;
		bool 		DCRM 	:1;
	};
}INT_GEN_THS_G_X_VAL;

//--------------
//INT_GEN_THS_Y_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t THS 	:7;
		bool 		unused 	:1;
	};
}INT_GEN_THS_G_Y_VAL;

//--------------
//INT_GEN_THS_Z_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t THS 	:7;
		bool 		unused 	:1;
	};
}INT_GEN_THS_G_Z_VAL;

//--------------
//INT_GEN_DUR_G
//--------------
typedef union{
	uint8_t  val;
  struct {
		uint8_t DUR 	:7;
		bool 		WAIT 	:1;
	};
}INT_GEN_DUR_G_VAL;

#endif




