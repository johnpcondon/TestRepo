/******************************************************************************
* File Name          : DataTypes.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 4/12/2013
* Description        : Used to get the enum value of the data type
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef DATATYPES_H
#define DATATYPES_H


#include "Generic/GenericTypedef.h"
#include "Math/Vect3.h"
#include "Math/Vect4.h"
#include "Math/Matrix.h"

typedef enum DATA_TYPE{
	UNKNOWN			 	= 0x00,
	UINT8_T			 	= 0x01,
	INT8_T				= 0x02,
	UINT16_T			= 0x03,
	INT16_T				= 0x04,
	UINT32_T			= 0x05,
	INT32_T				= 0x06,
	UINT64_T			= 0x07,
	INT64_T				= 0x08,
	FLOAT_32			= 0x09,
	FLOAT_64			= 0x0A,
	VECT3_INT16		= 0x0B,
	VECT3_FLOAT32	= 0x0C,
	VECT4_FLOAT32	= 0x0D,
	MAT33_FLOAT32	= 0x0E,

}DATA_TYPE;

//***********************************
//Get DataType Size
//***********************************

//Access individual element
//template <class T>
//int32_t getDataTypeSize(T &a){return sizeof(a);}

//template <class T>
//int32_t getDataTypeSize(T *a){return sizeof(*a);}

inline uint8_t getDataTypeSize(uint8_t *val)						{return 1;}
inline uint8_t getDataTypeSize(int8_t *val)							{return 1;}
inline uint8_t getDataTypeSize(uint16_t *val)						{return 2;}
inline uint8_t getDataTypeSize(int16_t *val)						{return 2;}
inline uint8_t getDataTypeSize(uint32_t *val)						{return 4;}
inline uint8_t getDataTypeSize(int32_t *val)						{return 4;}
inline uint8_t getDataTypeSize(uint64_t *val)						{return 8;}
inline uint8_t getDataTypeSize(int64_t *val)						{return 8;}
inline uint8_t getDataTypeSize(float *val)							{return 4;}
inline uint8_t getDataTypeSize(double *val)							{return 8;}
inline uint8_t getDataTypeSize(Vect3<int16_t> *val)			{return 6;}
inline uint8_t getDataTypeSize(Vect3<float> *val)				{return 12;}
inline uint8_t getDataTypeSize(Vect4<float> *val)				{return 16;}
inline uint8_t getDataTypeSize(Matrix<float,3,3> *val)	{return 36;}

inline DATA_TYPE getDataType(uint8_t *val)						{return UINT8_T;}
inline DATA_TYPE getDataType(int8_t *val)							{return INT8_T;}
inline DATA_TYPE getDataType(uint16_t *val)						{return UINT16_T;}
inline DATA_TYPE getDataType(int16_t *val)						{return INT16_T;}
inline DATA_TYPE getDataType(uint32_t *val)						{return UINT32_T;}
inline DATA_TYPE getDataType(int32_t *val)						{return INT32_T;}
inline DATA_TYPE getDataType(uint64_t *val)						{return UINT64_T;}
inline DATA_TYPE getDataType(int64_t *val)						{return INT64_T;}
inline DATA_TYPE getDataType(float *val)							{return FLOAT_32;}
inline DATA_TYPE getDataType(double *val)							{return FLOAT_64;}
inline DATA_TYPE getDataType(Vect3<int16_t> *val)			{return VECT3_INT16;}
inline DATA_TYPE getDataType(Vect3<float> *val)				{return VECT3_FLOAT32;}
inline DATA_TYPE getDataType(Vect4<float> *val)			{return VECT4_FLOAT32;}
inline DATA_TYPE getDataType(Matrix<float,3,3> *val)	{return MAT33_FLOAT32;}

#endif

