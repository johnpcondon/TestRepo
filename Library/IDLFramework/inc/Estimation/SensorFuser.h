/****************************************************************************
* File Name          : SensorFuser.h
* Author             : Adam Becker
* Version            : V 2.0
* Date               : 12/11/14
* Description        : Abstract base class for sensor fusion objects
******************************************************************************/
#ifndef SENSORFUSER_H
#define SENSORFUSER_H

#include "Vect3.h"
#include "RunningStat.h"
#include "marker.h"

class SensorFuser
{
	public:		
		uint8_t Initialized;
	
		virtual void AcclUpdate(uint32_t marker, Vect3<float> &acclVals)=0;
		virtual void GyroUpdate(uint32_t marker, Vect3<float> &gyroVals)=0;
	  virtual void MagsUpdate(uint32_t marker, Vect3<float> &magsVals)=0;
		virtual void Reset()=0;
	protected:
		virtual ~SensorFuser(){};
	private:
		
		
};

#endif
