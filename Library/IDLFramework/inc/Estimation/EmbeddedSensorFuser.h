/****************************************************************************
* File Name          : EmbeddedSensorFuser.h
* Author             : Adam Becker
* Version            : V 1.0
* Date               : 12/11/14
* Description        : This is essentially a wrapper and manager class for 
* 										 sensor fusion objects. The design philosophy is that 
* 										 this class is derived from Subscriber and thus handles
* 										 the IO of outputsets and settings for the sensor fusion 
*											 objects. It enables less dependacies and portablity of 
*											 sensor fusion object code.
******************************************************************************/
#ifndef EMBEDDEDSENSORFUSER_H
#define EMBEDDEDSENSORFUSER_H

#include "pubsub.h"
#include "OutputSet.h"
#include "Vect3.h"
#include "Matrix.h"
#include "RunningStat.h"
#include "SettingTypes.h"
#include "VariableAccess.h"
#include "ComplementaryAhrs.h"

enum FUSION_TYPE{
  COMPLEMENTARY_AHRS	= 0x00,
  EKF_AHRS 						= 0x01,
  ZUPT_DETECTOR  		  = 0x02,
};

class EmbeddedSensorFuser : public Subscriber
{
	public:
		EmbeddedSensorFuser(const char* name, FUSION_TYPE type, OutputSet* acclOutputSet, OutputSet* gyroOutputSet, OutputSet* magsOutputSet);

		OutputSet*  		outputSets[FUSER_MAX_OUTPUTSETS];
		Output* 	  		outputs[FUSER_MAX_OUTPUTS];
	
		//SensorFuser* 		Fuser;
	ComplementaryAhrs* 		Fuser;
		FUSION_TYPE  		Type;
	
		virtual void update(Publisher* who);
	private:
		~EmbeddedSensorFuser();
  
		OutputSet* 			pAcclPub; 
		uint32_t* 			pAcclMarker;
		Vect3<float>* 	pAcclVal;
	
		OutputSet* 			pGyroPub;
		uint32_t* 			pGyroMarker;
		Vect3<float>* 	pGyroVal;
	
		OutputSet* 			pMagsPub;
		uint32_t* 			pMagsMarker;
		Vect3<float>* 	pMagsVal;
	
		Variable*       vars[MAX_NUM_VARS_PER_GROUP];
		VariableGroup* 	varGrp;
	
};

#endif
