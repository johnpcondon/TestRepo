/****************************************************************************
* File Name          : Buffer.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module creates a linear buffer class
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef BUFFER_H
  #define BUFFER_H

#include "Generic/GenericTypeDef.h"
#include "Containers/CircularBuffer.h"

class CircularBuffer;

  //Uint_8 Implementation of Linear buffer
  //This buffer is designed to accumulate data and then push out all of it at once
	
class Buffer{	
	public:
		Buffer(int32_t numelements); 
		virtual ~Buffer();
		void reset(){index_ = 0;};
		void clear(); //Resets and zeros data
		bool isFull();
		
		int flush(CircularBuffer* dest);
		void fill(uint8_t byte);
		
		template<typename T>int push(T data);		
		template<uint8_t>int push(uint8_t data);
	
		int push(uint8_t *srcData, int32_t numelements);
		int push(Buffer* buf);
		int push(const char str[]);
	
	template <typename T> int peek(T& destData,int32_t offset);
		void overwrite(int32_t index,uint8_t val);

		int32_t peekString(int32_t, char str[], int32_t maxlen);
		int32_t getCount(){return index_;};
		int32_t getSize(){return numelements_;};
		int32_t getFree(){return (numelements_- (index_));};
		uint8_t* getHead(){return data_;}; //Returns top of buffer
		RESULT periph_setIndex(int32_t new_index); //Used for low-level cases where data couple be written by DMA in the background
		
	private:
		int32_t numelements_;   //Maximum Number of elements
		int32_t index_;   		//Index to next read
		uint8_t* data_;       	//Data array
	
}; //End Class

//***************************************************************************
//Peek at byte in the buffer without modification
//Returns number of bytes in single buffer element
//***************************************************************************
template <typename T>
int Buffer::peek(T& destData, int32_t offset)
{
	__packed T* pdata = (T*)(this->data_ + offset);
  destData = *pdata;
 	return sizeof(T);
}

//***************************************************************************
//Push data into buffer
//***************************************************************************
template <typename T>
int Buffer::push(T srcData)
{
	if(sizeof(T) > 1){
		//Multi-byte push
		return push((uint8_t*)(&srcData),sizeof(T));
	}
	else{
		//Single Byte Push
		if(index_ < (numelements_)) {
			data_[index_++] = (uint8_t)srcData;
			return 1;
		}
		else{
			reset();
			//while(1); //Overrun
			return 0;
		}
	}
}

////***************************************************************************
////Push one buffer into another
////***************************************************************************
//template<uint8_t>
//int Buffer::push(uint8_t srcData)
//{		
//		if(index_ < (numelements_-1))
//		{
//				data_[index_++] = srcData;
//				return 1;
//		}
//		else{
//			clear();
//			//while(1); //Overrun
//			return 0;
//		}	
//}

////***************************************************************************
////Push one buffer into another
////***************************************************************************
//template<Buffer*>
//int Buffer::push(Buffer* srcData)
//{
//	uint8_t* data = srcData->getHead();
//	int32_t numBytes = srcData->getCount();
//	
//	if(numBytes > this->getFree()){
//		return 0; //array too large
//	}
//	else{
//		return this->push(data,numBytes);
//	}

//}


#endif


	  

