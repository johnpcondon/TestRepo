/****************************************************************************
* File Name          : File.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Port Interface to Files
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef FILE_H
#define FILE_H

#include "port.h"
#include "circular_buffer.h"
#include "SDHCInterface_SDIO.h"
#include "ff.h"

//This class should only be access via FileInterface
class File: public Port{
	public:
		friend class FileInterface;
		
	protected:
		File( const char* name,
					int32_t bufSizeRx,
					int32_t bufSizeTx,
					uint32_t tx_timeout,
					int32_t bufSizeOutputStream,
					uint32_t outputstream_timeout,
					uint32_t outstream_watermark_remaining);
		void doTasks_mainThread();
		int32_t transferTxData(Buffer* pTxBuf);
	
		File* Open(const char* name, uint8_t mode);
		FRESULT Close();
		uint32_t Read(uint32_t index, uint8_t bytes);
		void TriggerHeaderWrite(){GenerateHeader = true;};
		int getSize();
		bool isOpen();
		FILINFO Fno;
	FIL Fil;
	private:
		~File();
		void Init();
		
		uint8_t Mode;
		FRESULT res_openfile;
		FRESULT res_filesize;
		FRESULT res_writedata;
		const char* Name;
		bool FileOpen;
		bool GenerateHeader;
		uint32_t TxThreshold;
};

#endif




