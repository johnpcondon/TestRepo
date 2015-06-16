/****************************************************************************
* File Name          : PID.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 7/9/2013
* Description        : This module will implements a PID control loop
******************************************************************************/
#ifndef PID_H
#define PID_H

#include "genericTypeDef.h"
#include "JCVect.h"
#include <string>
#include "Filter.h"
#include "VariableAccess.h"
#include "OutputSet.h"

class PID{
public:
  PID(const char* name, uint32_t period_us, float Kp,float Ki,float Kd,float Tf,float Ti);
  
	//void initOutput(float val){Iprev = val;};
  void Reset();
  //void Reset_Integrator();
  float update(float desired, float actual ,uint32_t marker);
  
  uint8_t getIndex(){ return Index_;}
  float getKp(){ return Kp_;}
  float getKi(){ return Ki_;}
  float getKd(){ return Kd_;}
  float getOutputLimit(){ return OutputLimit_;}
  
  void setGains(float Kp, float Ki, float Kd,float Tf, float Ti); //Use to set all gains at once
	void setGain_kP(float kP){Kp_ = kP; ApplyNewGains();}; //Use for single gain change
	void setGain_kI(float kI){Ki_ = kI; ApplyNewGains();}; //Use for single gain change
	void setGain_kD(float kD){Kd_ = kD; ApplyNewGains();}; //Use for single gain change
	void setGain_Tf(float Tf){Kd_ = Tf; ApplyNewGains();}; //Use for single gain change
	void setGain_Ti(float Ti){Kd_ = Ti; ApplyNewGains();}; //Use for single gain change

  void setLimit(float limit){OutputLimit_ = limit;};
	void setRefWeighting(float weight){RefWeighting = weight;}
	void initOutput(float initVal);
	
	static EV_ID ApplyNewGains(Variable* var);
	static vector<PID*,MAX_NUM_PIDS> PIDs;
private:
	~PID();
  EV_ID ApplyNewGains();

	//Variables
	VariableGroup* VarGrp_PID;
	
	Variable* Var_kP;
	Variable* Var_kI;
	Variable* Var_kD;
	Variable* Var_Tf;		//Derivitive Filtering Time Constant
	Variable* Var_Ti;		//Integral Time Constant
	Variable* Var_RefWeight;		//Reference/SetPoint Weighting (0-1)

	Variable* Var_LimitOutput;
	
	//Output Sets
	OutputSet*	OutputSet_PID;
	Output* Out_Err;	
	Output* Out_P;
	Output* Out_I;
	Output* Out_D;
	Output* Out_Total;

	//Parameters
  float Kp_;
  float Ki_;
  float Kd_;
  float OutputLimit_; //Negative values indicate off
  float Tf_;
	float Ti_;
  float RefWeighting;
	
	float bi_;
	float ad_;
	float bd_;
	float br_;
	
	float dT;
	
  //Current Values
	uint32_t Marker;
	float Error;
  float Pval;
  float Ival;
  float Dval;
  float OutputVal;
  
  //Past Values
  float ActualPrev;
  uint32_t MarkerOld;
	
  const char* Name_;
  uint8_t Index_;
  
};


#endif

