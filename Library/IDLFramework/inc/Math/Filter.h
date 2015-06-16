/******************************************************************************
* File Name          : Filter.hpp
* Author             : John Condon
* Version            : V 1.0
* Date               : 8/18/2013
* Description        : Filter Math
*
*******************************************************************************/
#ifndef FILTER_H
#define FILTER_H

#include "Generic/GenericTypeDef.h"
#include "matrix.h"

//#define num_sections 3

class Filter{
  public:
	 Filter(uint8_t num_sections, const float a[], const float b[], const float g[3]);
	 void reset();	 
	 float update(float sample);
	 
	private:
		~Filter();
	  float input;
		float output;
  	uint8_t numSections_;
		float const* A;
		float const* B;
		float const* G;
		
	   float *W;
};


#endif
