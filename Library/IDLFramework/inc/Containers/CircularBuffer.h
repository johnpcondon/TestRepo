/****************************************************************************
* File Name          : circular_buffer.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module creates a interface to the ring buffer class
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef CIRCULAR_BUFFER_H
  #define CIRCULAR_BUFFER_H

#include "Generic/GenericTypeDef.h"
#include "Containers/Buffer.h"

class Buffer;
  //Uint_8 Implementation of Circular Buffer
    
class CircularBuffer{	
	public:
		CircularBuffer(int32_t numelements); 
		CircularBuffer(int32_t numelements,bool enable); 
		virtual ~CircularBuffer();
		void reset();
		void fill(uint8_t byte);
		void clear(); //resets and fills with 0
		int setWriteIndex(int32_t new_index);
		int setReadIndex(int32_t new_index);
					
		int pop(uint8_t *destData);
		int pop(uint8_t *destData, int32_t numelements);

		int push(uint8_t data);		
		template<typename T>int push(T& data);		
		int push(uint8_t *srcData, int32_t numelements);
		int push(Buffer* buf);
		int push(const char str[]);

		bool isLocked(){return lock;}
		
		template<typename T>int peek(T* data,int32_t baseindex, int32_t offset);

		int overwrite(int32_t index, uint8_t val);

		int32_t getFree();
		inline int32_t getCount(){return count_;};
		inline int32_t getSize(){return numelements_;};
		inline uint8_t* getHead(){return pData;};
		inline int32_t getReadFromIndex(){return iReadFrom_;};
		inline int32_t getWriteToIndex(){return iWriteTo_;};
		
	private:
		bool enOverwrites;
		bool lock; //Locks buffer during read and write operations (makes this interrupt safe)
		void init(int32_t numelements, bool enableOver);
		bool getLock();		
		void setLock(){lock = true;}
		void clearLock(){lock = false;}
		int32_t numelements_;        //Maximum Number of elements
		uint8_t* pData;       //Data array
	
		volatile int32_t iReadFrom_;   //Index to next read
		volatile int32_t iWriteTo_;    //Index to next write
		volatile int32_t count_;       //Number of bytes in buffer
		
}; //End Class

//*******************************************************************************
// Returns value from buffer without modifying pointers or count
// Handles wrap of offset if needed
//*******************************************************************************
template<typename T>int CircularBuffer::peek(T* destData, int32_t baseindex, int32_t offset) {

  int32_t i;
  int32_t index;
  
  int32_t numBytes = sizeof(destData);
	
	if(numBytes == 1){
			index = (baseindex + offset) % numelements_;      
			*destData = pData[index];
	}
	else{
		//*destData = 0; //clear destData
		
		for(i=0; i<numBytes; i++){
		 index = (baseindex + offset) % numelements_;   
		 *destData = (*destData << 8) + pData[index];
		}
	}
  
  return numBytes;
}

/*******************************************************************************
Pushes data into the circular buffer and returns the number of bytes pushed
*******************************************************************************/
template <typename T>
int CircularBuffer::push(T& srcData)
{
	if(sizeof(T) > 1){
		//Multi-byte push
		return push((uint8_t*)(&srcData),sizeof(T));
	}
	else{
		//Single Byte Push
		return push((uint8_t)srcData);
	}
}


#endif
