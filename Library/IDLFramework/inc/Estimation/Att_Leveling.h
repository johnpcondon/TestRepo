/****************************************************************************
* File Name          : Att_ReducedEstimator.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 4/27/14
* Description        : This module will implements a attitude estimation
******************************************************************************/
#ifndef ATTITUDE_LEVELING_H
#define ATTITUDE_LEVELING_H

#include "pubsub.h"
#include "OutputSet.h"
#include "Vect.h"

class AttLevel : public Subscriber//,public Sensor
{

public:
  AttLevel(OutputSet* accl_eng, uint32_t accl_minPeriod_us);
  virtual void update(Publisher* who);
	
	OutputSet*	OutputSet_Tilt;
	Output* Output_Roll;
	Output* Output_Pitch;
	 
	static AttLevel* pAtt;
private:
	~AttLevel();
  OutputSet* 	Accl_pub; //Incoming Accl data pointer
	
	uint32_t* pAcclMarker;
	Vect<float,3>* pAcclVal;

	uint32_t MarkerAccl;
	float dT_Accl;

	float Roll;
	float Pitch;

	void AcclUpdate();
	void InitEst_Accl();

	void Leveling(float &roll_rad, float &pitch_rad, Vect<float,3> &accl);
	 
	//Initialization values
	bool initialized;

}; //End Class



#endif



