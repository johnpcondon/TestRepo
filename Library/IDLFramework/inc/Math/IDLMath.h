/******************************************************************************
* File Name          : IDLMath.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Basic Math Functions
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef IDL_MATH_H
#define IDL_MATH_H

#include <math.h>
#include "Math/Vect3.h"
#include "Math/Matrix.h"

const float RAD_2_DEG = 57.295779513082320876798154814105; 
const float DEG_2_RAD = 0.01745329251994329576923690768489;

//***********************************************
//Calculated a 1st order derivative
// val1 - value at t-1
// val2 - value at t
// dT   - time between t and t-1 (in seconds)
//***********************************************
 float Deriv_1stOrder(float val1,float val2,float dT);

//***********************************************
//Calculated the delta from a trapezoidal integral
//Used for PID loops or functions with an integral gain
// val1 - value at t-1
// val2 - value at t
// dT   - time between t and t-1 (in seconds)
// True integral is:
//  int_val(t) = int_val(t-1) + ((val1 + val2)*dT/2)
// This function outputs the right most term
//***********************************************
 float dIntegral_Trapezoidal(float val1,float val2,float dT);
//***********************************************
//Saturates a value
// val - referance to value to be saturated
// minVal - lower limits of saturation
// maxVal - upper limit of saturation
// Returns true if limit hit, false if no limit hit
//***********************************************
template<typename T>
 bool saturate(T& val,T minVal, T maxVal)
{
  if(val>maxVal){
	 val = maxVal;
	 return true;
  }
  else if(val<minVal){
	 val = minVal;
	 return true;
  }
  else{
	 return false;
  }
}

//***********************************************
//Creates a DeadZone
// val - referance to value to be saturated
// minVal - lower limit of deadzone
// maxVal - upper limit of deadzone
// Returns true if inside deadzone, false if outsize deadzone
//***********************************************
template<typename T>
 bool DeadZone(T& val,T minVal, T maxVal)
{
  if(val>minVal && val<maxVal){
	 val = 0;
	 return true;
  }
  return false;
}
/**********************************************************************
* Function Name   Moving Average
* Description:    Performs a moving average
* Parameters:     None
* Return Value:   None
* Notes:          None
***********************************************************************/
 float MovingAverage(float val, float pastVal,float numIterations);
/**********************************************************************
* Function Name   Euler to DCM Matrix
* Description:    Converts euler angles to a DCM attitude matrix
* Parameters:     None
* Return Value:   None
* Notes:          None
***********************************************************************/
 void eul2Cbn(Matrix<float,3,3> &DCM,float roll_rad,float pitch_rad,float yaw_rad);

/**********************************************************************
* Function Name   Euler to DCM Matrix
* Description:    Converts euler angles to a DCM attitude matrix
* Parameters:     None
* Return Value:   None
* Notes:          None
***********************************************************************/
 void eul2Cbn(Matrix<float,3,3> &DCM,Vect3<float> &eul);

/**********************************************************************
* Function Name   Euler to DCM Matrix
* Description:    Converts euler angles to a DCM attitude matrix
* Parameters:     None
* Return Value:   None
* Notes:          None
***********************************************************************/
 void Cbn2eul(Vect3<float> &eul,Matrix<float,3,3> &DCM);

template<class T>
 T abs(const T x)
{
	return (x>0?x:(-x));
}

 uint32_t isqrt(uint32_t a_nInput);
#endif
