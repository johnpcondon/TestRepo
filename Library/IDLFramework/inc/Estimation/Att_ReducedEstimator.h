/****************************************************************************
* File Name          : Att_ReducedEstimator.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 4/27/14
* Description        : This module will implements a attitude estimation
******************************************************************************/
#ifndef ATTITUDE_H
#define ATTITUDE_H

#include "pubsub.h"
#include "OutputSet.h"

#include "Vect.h"
#include "Matrix.h"
#include "PID2.h"
#include "Gyro_LSM330DLC.h"
#include "Accl_LSM330DLC.h"
#include "RunningStat.h"
#include "VariableAccess.h"

class AttitudeEst : public Subscriber//,public Sensor
{

public:
	 AttitudeEst(Accl* accl, uint32_t accl_minPeriod_us, Gyro* gyro, uint32_t gyro_minPeriod_us);

	//Output Abstractions
	 OutputSet*	OutputSet_DCM;
	 Output* Output_DCM;
	 
	 OutputSet*	OutputSet_Euler;
	 Output* Output_Euler;
	
	 virtual void update(Publisher* who);

	 static void Reset();
	 static AttitudeEst* pAtt;
	 static Matrix<float,3,3>* getDCMPointer(){return &((AttitudeEst::pAtt)->DCM);};
	 
private:
	~AttitudeEst();
  
	Gyro* pGyro;
	Accl* pAccl;
	OutputSet* 	pAcclPub; //Incoming Accl data pointer
	OutputSet* 	pGyroPub; //Incoming Gyro data pointer

	uint32_t* pAcclMarker;
	Vect<float,3>* pAcclVal;

	uint32_t* pGyroMarker;
	Vect<float,3>* pGyroVal;

	Matrix<float,3,3> R;
	Vect<float,3> v;
	Matrix<float,3,3> Cbn_Norm;

	//Initialization variables
	RunningStat rs_accl_x;
	RunningStat rs_accl_y;
	RunningStat rs_accl_z;

	RunningStat rs_gyro_x;
	RunningStat rs_gyro_y;
	RunningStat rs_gyro_z;

	float Gyro_Init_VarX;
	float Gyro_Init_VarY;
	float Gyro_Init_VarZ;
	uint32_t numInitAttempts;
	
	//PID* GyroBiasAcclX;
	//PID* GyroBiasAcclY;
	float GyroBiasGain;
	float DCMCorrectionGain;
	

	Vect<float,3> GyroBias;//Gyro Bias
	uint32_t MarkerAccl;
	float dT_Accl;
	
	uint32_t MarkerGyro;
	float_t dT_Gyro;
	
	Vect<float,3> Euler;//Data is in radians  
	Matrix<float,3,3> DCM;

	void AcclUpdate();
	void GyroUpdate();
	void InitEst_Accl();
	void InitEst_Gyro();
	
	void DCMCorrection_Accl(float error_x, float error_y);
	void gyroIntegration();
	void DCMOrthonormalize(Matrix<float,3,3>& DCM);
	void DCMGramSchmidtOrthonorm(Matrix<float,3,3>& Cbn);
	void Leveling(float &roll_rad, float &pitch_rad, Vect<float,3> &accl);
	 
	 //Variable Abstractions
	 //Variable* Var_GBias_kP;
	 //Variable* Var_GBias_kI;
	 //Variable* Var_GBias_kD;
	 
	Variable* Var_GyroBiasGain;
	Variable* Var_DCMCorrGain;
	Variable* Var_Initialized;
	VariableGroup* VarGrp_AttEst;
	//Initialization values
	uint8_t initialized;
	bool gyro_init;

}; //End Class



#endif



