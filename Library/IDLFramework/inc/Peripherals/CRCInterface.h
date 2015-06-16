/****************************************************************************
* File Name          : CRCInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/5/2015
* Description        : This module implements CRC functionality
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef CRCINTERFACE_H_
  #define CRCINTERFACE_H_

#include "Generic/GenericTypeDef.h"
#include "Containers/Buffer.h"
#include "DMAInterface.h"

class CRCCalc{
	 public:
		static void useDMA(uint8_t dma_stream);
	  static int Process(Buffer* buf, uint32_t& result);
		static int Process(uint8_t* pBuf, uint32_t numBytes, uint32_t& result);
	 protected:
		 
	 
	 private:  
		static bool isInitialized;
		static bool usingDMA;
	  static bool isBusy;
		static DMAInterface* DMAPort;
};//End Class

#endif


