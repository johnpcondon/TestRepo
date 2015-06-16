/****************************************************************************
* File Name          : ComplementaryAhrs.h
* Author             : Adam Becker
* Version            : V 2.0
* Date               : 12/10/14
* Description        : IDL's implementation and optimization of a 
* 										 Classical Complementary Filter using Accls and Gyros
******************************************************************************/
#ifndef COMPLEMENTARYAHRS_H
#define COMPLEMENTARYAHRS_H

#include "Vect3.h"
#include "RunningStat.h"
#include "marker.h"
#include "SensorFuser.h"

class ComplementaryAhrs : public SensorFuser
{
	public:
		ComplementaryAhrs(float kp, float ki, float acclThres, float maxAcclDt, float maxGyroDt, int32_t gyroInitMinIter, float gyroInitMaxVar);
	
		// These are the filter's configuration variables
		float 					Kp;
		float 					Ki;
		float32_t 			AcclThres;
	  float 					MaxAcclDt;
	  float 					MaxGyroDt;
	  int32_t  				GyroInitMinIter;
		float 				  GyroInitMaxVar;
	
		// These are the filter's output and status variables
	  uint32_t        SolutionMarker;
		Vect3<float> 	Quat;
		Vect3<float> 	GyroBias;
		Vect3<float> 	CorrectedBodyRates;
		Vect3<float> 	ErrAccum;
		Vect3<float> 	AcclKp;
		Vect3<float> 	AcclKi;
		Vect3<float> 	LinearAccel_body;
		Vect3<float> 	LinearAccel_nav;
		Vect3<float> 	MagsTiltComp;
		Vect3<float> 	Euler;
		uint32_t 				InitAttempts;
		uint32_t 				AcclLastMarker;
		float 					AcclDt;
		uint32_t 				GyroLastMarker;
		float 					GyroDt;
		uint32_t 				MagsLastMarker;
		float 					MagsDt;

		virtual void AcclUpdate(uint32_t marker, Vect3<float> &acclVals);
		virtual void GyroUpdate(uint32_t marker, Vect3<float> &gyroVals);
		virtual void MagsUpdate(uint32_t marker, Vect3<float> &magsVals);
		virtual void Reset();
	protected:
		virtual ~ComplementaryAhrs(){};
	private:
		RunningStat 		_acclInitRsX;
		RunningStat 		_acclInitRsY;
		RunningStat 		_acclInitRsZ;
		RunningStat 	 	_gyroInitRsX;
		RunningStat 		_gyroInitRsY;
		RunningStat 		_gyroInitRsZ;
		float 					_gyroInitVarX;
		float 					_gyroInitVarY;
		float 					_gyroInitVarZ;
	  Vect3<float> 	_acclInit;
	
		void AcclInit(Vect3<float> &acclVals);
		void GyroInit(Vect3<float> &gyroVals);
		void MagsInit(Vect3<float> &magsVals);
	
		//Debug only
		uint32_t markerHigh;
		uint32_t markerLow;
};

#endif
