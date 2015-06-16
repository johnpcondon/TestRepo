/****************************************************************************
* File Name          : RadomNumberGenerator.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Generic interface to a random number generator
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef RND_NUM_GEN_H
#define RND_NUM_GEN_H

#include "Generic/GenericTypeDef.h"

class RndNum{
	public:
		static void Generate(uint8_t &val);
		static void Generate(uint16_t &val);
		static void Generate(uint32_t &val);
		static void Generate(uint8_t* buf,uint32_t numBytes);
	
		static void enErrCorrection(bool en);
		
	private:
		RndNum();
		~RndNum();
};
	
	
#endif

