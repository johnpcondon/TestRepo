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

//#define MAX_NUM_PIDS	8

class PID{
public:
  PID(const char* Name, float Kp,float Ki,float Kd);
  void init(float kP,float kI,float kD);
  
	void initOutput(float val){Iprev = val;};
  void Reset();
  void Reset_Integrator();
  float update(float error,uint32_t marker);
  
  uint8_t getIndex(){ return Index_;}
  float getKp(){ return Kp_;}
  float getKi(){ return Ki_;}
  float getKd(){ return Kd_;}
  float getOutputLimit(){ return OutputLimit_;}
  float getILimit(){ return ILimit_;}
  float getDLimit(){ return DLimit_;}
  
  void setGains(float Kp, float Ki, float Kd);
	void setGain_kP(float kP){Kp_ = kP;};
	void setGain_kI(float kI){Ki_ = kI;};
	void setGain_kD(float kD){Kd_ = kD;};
	
  void setLimits(float OLim, float ILim, float DLim);
  void setLimit_Output(float limit){OutputLimit_ = limit;};
  void setLimit_I(float limit){ILimit_ = limit;};
  void setLimit_D(float limit){DLimit_ = limit;};
  void setLimit_dT(float limit){dTLimit_ = limit;};

private:
	~PID();
  
	//Variables
	VariableGroup* VarGrp_PID;
	
	Variable* Var_kP;
	Variable* Var_kI;
	Variable* Var_kD;
	
	Variable* Var_LimitOutput;
	Variable* Var_LimitI;
	Variable* Var_LimitD;
	Variable* Var_LimitdT;
	
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
  float ILimit_; //Negative values indicate off
  float DLimit_; //Negative values indicate off
  float dTLimit_; 
  
  //Current Values
	uint32_t Marker;
	float dT;
	float Error;
  float Pval;
  float Ival;
  float Dval;
  float Outputval;
  
  //Past Values
  float errorPrev;
  float errorPrev_filt;
  float Iprev;
  
  const char* Name_;
  uint8_t Index_;
  
};


#endif

