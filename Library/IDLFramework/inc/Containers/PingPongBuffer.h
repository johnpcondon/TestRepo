/****************************************************************************
* File Name          : pingpongbuffer.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 3/29/2013
* Description        : This module creates a interface to the ping pong buffer class
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef PINGPONG_BUFFER_H
  #define PINGPONG_BUFFER_H

#include "Generic/GenericTypeDef.h"
#include "Containers/Buffer.h"
#include "Containers/CircularBuffer.h"

//Uint_8 Implementation of PingPong Buffer
    
class PingPongBuffer{	
	public:
		PingPongBuffer(int32_t numelements); 
		virtual ~PingPongBuffer();
		void clear();
		
		int flush(CircularBuffer* dest);
		int push(uint8_t data);		
		
		int32_t getFree();
		int32_t getCount();
		inline int32_t getSize(){return buf_0->getSize();};
		
	private:
		
		Buffer* buf_0;
		Buffer* buf_1;
	
		bool Active0;
	
}; //End Class

#endif
