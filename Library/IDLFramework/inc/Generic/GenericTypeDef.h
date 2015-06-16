/*******************************************************************************
* File Name          : genericTypeDef.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Defines generic data types
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef GENERIC_TYPE_DEF_H
#define GENERIC_TYPE_DEF_H

#include <limits.h>
#include <stdint.h>
#include <stddef.h>

#pragma anon_unions //Allows anoynmous unions

//#ifndef NULL
//	#define NULL		0
//#endif


typedef decltype(nullptr) nullptr_t;


#define FAIL    0
#define PASS	  1
//#define BUSY    2

enum RESULT{
	RESULT_FAILURE = 0,
	RESULT_SUCCESS,
	RESULT_BUSY
};

const float RAD2DEG = 57.295779513082320876798154814105;
const float DEG2RAD = 0.01745329251994329576923690768489;

const uint32_t PERIOD_5sec	= 5000000;
const uint32_t PERIOD_3sec	= 3000000;
const uint32_t PERIOD_2sec	= 2000000;
const uint32_t PERIOD_1Hz 	= 1000000;
const uint32_t PERIOD_2Hz 	= 500000;
const uint32_t PERIOD_3Hz 	= 333333;
const uint32_t PERIOD_4Hz 	= 250000;
const uint32_t PERIOD_5Hz 	= 200000;
const uint32_t PERIOD_10Hz 	= 100000;
const uint32_t PERIOD_20Hz 	= 50000;
const uint32_t PERIOD_50Hz 	= 20000;
const uint32_t PERIOD_100Hz = 10000;
const uint32_t PERIOD_200Hz = 5000;
const uint32_t PERIOD_400Hz = 2500;
const uint32_t PERIOD_500Hz = 2000;
const uint32_t PERIOD_1kHz 	= 1000;
const uint32_t PERIOD_2kHz 	= 500;
const uint32_t PERIOD_4kHz 	= 250;
const uint32_t PERIOD_8kHz 	= 125;
const uint32_t PERIOD_10kHz = 100;
const uint32_t PERIOD_20kHz = 50;

const uint32_t FREQ_1Hz				= 1;
const uint32_t FREQ_10Hz			= 10;
const uint32_t FREQ_20Hz			= 20;
const uint32_t FREQ_25Hz			= 25;
const uint32_t FREQ_50Hz			= 50;
const uint32_t FREQ_100Hz			= 100;
const uint32_t FREQ_200Hz			= 200;
const uint32_t FREQ_400Hz			= 400;
const uint32_t FREQ_500Hz			= 500;
const uint32_t FREQ_1kHz			= 1000;
const uint32_t FREQ_2kHz			= 2000;
const uint32_t FREQ_4kHz			= 4000;
const uint32_t FREQ_5kHz			= 5000;
const uint32_t FREQ_8kHz			= 8000;
const uint32_t FREQ_10kHz			= 10000;
const uint32_t FREQ_20kHz			= 20000;
const uint32_t FREQ_40kHz			= 20000;
const uint32_t FREQ_80kHz			= 80000;
const uint32_t FREQ_100kHz		= 100000;
const uint32_t FREQ_125kHz		= 125000;
const uint32_t FREQ_200kHz		= 200000;
const uint32_t FREQ_250kHz		= 250000;
const uint32_t FREQ_400kHz		= 400000;
const uint32_t FREQ_500kHz		= 500000;
const uint32_t FREQ_800kHz		= 800000;
const uint32_t FREQ_1MHz			= 1000000;
const uint32_t FREQ_2MHz			= 2000000;
const uint32_t FREQ_4MHz			= 4000000;
const uint32_t FREQ_8MHz			= 8000000;
const uint32_t FREQ_10MHz			= 10000000;

//#define NULL 0
#define RETURN_SUCCESS  1
#define RETURN_FAILURE  -1
#define RETURN_BUSY     0

#ifdef __INT8_T_MAX__
	#define INT8_MAX __INT8_T_MAX__
#else
	#define INT8_MAX 127
#endif

#ifdef __INT8_T_MIN__
	#define INT8_MIN __INT8_T_MIN__
#else
	#define INT8_MIN -127
#endif

#ifdef __UINT8_T_MAX__
	#define UINT8_MAX __UINT8_T_MAX__
#else
	#define UINT8_MAX 255
#endif


#ifdef __UINT8_T_MIN__
	#define UINT8_MIN __UINT8_T_MIN__
#else
	#define UINT8_MIN 0
#endif

//#define INT16_MAX __INT16_T_MAX__
//#define UINT16_MAX __UINT16_T_MAX__
//#define INT32_MAX __INT32_T_MAX__
#define UINT32_MAX 0xFFFFFFFF

#ifndef float32_t
  #define float32_t float
#endif
//ON/OFFBool"ish" Type
typedef enum _ONOFF
{
  OFF = 0,
  ON  = 1
}ONOFF;

typedef enum {
  FALSE = 0,
  TRUE = 1
}BOOL;

enum ENABLE_DISABLE{
	DIS = 0,
	EN
};

//8-bit Unsigned Struct
typedef union {
    uint8_t  val;
    struct {
      uint8_t bit0 :1;
      uint8_t bit1 :1;
      uint8_t bit2 :1;
      uint8_t bit3 :1;
      uint8_t bit4 :1;
      uint8_t bit5 :1;
      uint8_t bit6 :1;
      uint8_t bit7 :1;
    };
}UINT8_VAL;

//16-bit Unsigned Struct
typedef union {
    uint16_t  	val;
    uint8_t	array[2];
    struct {
      uint8_t LB;
      uint8_t HB;
    };
    struct {
      uint16_t bit0  :1;
      uint16_t bit1  :1;
      uint16_t bit2  :1;
      uint16_t bit3  :1;
      uint16_t bit4  :1;
      uint16_t bit5  :1;
      uint16_t bit6  :1;
      uint16_t bit7  :1;
      uint16_t bit8  :1;
      uint16_t bit9  :1;
      uint16_t bit10 :1;
      uint16_t bit11 :1;
      uint16_t bit12 :1;
      uint16_t bit13 :1;
      uint16_t bit14 :1;
      uint16_t bit15 :1;
    };
}UINT16_VAL;

//16-bit Signed Struct
typedef union {
    int16_t  val;
    struct {
      uint8_t LB;
      uint8_t HB;
    };
}INT16_VAL;

//32-bit Unsigned Struct
typedef union {
    uint32_t  val;
    struct {
      uint8_t LB;
      uint8_t HB;
      uint8_t MB;
      uint8_t UB;
    };
    struct {
      uint32_t bit0  :1;
      uint32_t bit1  :1;
      uint32_t bit2  :1;
      uint32_t bit3  :1;
      uint32_t bit4  :1;
      uint32_t bit5  :1;
      uint32_t bit6  :1;
      uint32_t bit7  :1;
      uint32_t bit8  :1;
      uint32_t bit9  :1;
      uint32_t bit10 :1;
      uint32_t bit11 :1;
      uint32_t bit12 :1;
      uint32_t bit13 :1;
      uint32_t bit14 :1;
      uint32_t bit15 :1;
      uint32_t bit16 :1;
      uint32_t bit17 :1;
      uint32_t bit18 :1;
      uint32_t bit19 :1;
      uint32_t bit20 :1;
      uint32_t bit21 :1;
      uint32_t bit22 :1;
      uint32_t bit23 :1;
      uint32_t bit24 :1;
      uint32_t bit25 :1;
      uint32_t bit26 :1;
      uint32_t bit27 :1;
      uint32_t bit28 :1;
      uint32_t bit29 :1;
      uint32_t bit30 :1;
      uint32_t bit31 :1;
    };
}UINT32_VAL;

//32-bit signed Struct
typedef union {
    int32_t  val;
    struct {
      int8_t LB;
      int8_t HB;
      int8_t MB;
      int8_t UB;
    };
}INT32_VAL;

//32-bit Single Float
typedef union {
    float  val;
    uint32_t wordVal;
    struct {
      uint8_t LB;
      uint8_t HB;
      uint8_t MB;
      uint8_t UB;
    };
}FLOAT_VAL;

//64-bit Unsigned Struct
typedef union {
    uint64_t  val;
    struct {
      uint8_t B8;
      uint8_t B16;
      uint8_t B24;
      uint8_t B32;
      uint8_t B40;
      uint8_t B48;
      uint8_t B56;
      uint8_t B64;      
    };
    struct{
      uint16_t HW16;
      uint16_t HW32;
      uint16_t HW48;
      uint16_t HW64;
      };
    struct{
      uint16_t W32;
      uint16_t W64;
      };
    }UINT64_VAL;

//enum PERIPH_STATUS{
//  PERIPH_OK,
//  PERIPH_ERROR,
//  PERIPH_ISBUSY,
//	PERIPH_IDLE,
//	PERIPH_FINISHED,
//	PERIPH_TIMEOUT,
//};

enum POWER_STATE{
	POWER_UNKNOWN = 0,
	POWER_CHARGING,
	POWER_NORMAL,
	POWER_WIRED,
	POWER_LOWWARN,
	POWER_CRITICAL,
	POWER_SHUTDOWN
};

//These values are returned after a function
enum PERIPH_STATUS{
	PERIPH_DEFAULT,
	PERIPH_AOK,
	PERIPH_ERROR,
	PERIPH_DEVNOTFOUND,
	PERIPH_TIMEOUT,
	PERIPH_BUSY
};

//These values are the current state of a periph
enum PERIPH_TRANSACTION_STATE{
	PERIPH_TRANSACTION_IDLE,
	PERIPH_TRANSACTION_INPROGRESS,
	PERIPH_TRANSACTION_FINISHED,
	PERIPH_TRANSACTION_ERROR
};

#endif		

