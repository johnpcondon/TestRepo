/****************************************************************************
* File Name          : FileInterface.h
* Author             : Adam Becker
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Application Interface to File System
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#include "SDHCInterface_SDIO.h"
#include "ff.h"
#include "File.h"
#include "OutputSet.h"
#include "cmsis_os.h"
#include "OutputSet.h"
#include "RTCInterface.h"
#include "IdlString.h"

#define READ_FILE_IDX 0
#define WRITE_FILE_IDX 1

class FileInterface{
      
    public:
			FileInterface(SDHCInterface* psdhc, int32_t bufSizeRx, int32_t bufSizeTx);
			File* initFile(const char* name,
										 int32_t bufSizeRx,
										 int32_t bufSizeTx,
										 uint32_t tx_timeout,
										 int32_t outputstream_bufsize,
										 uint32_t outputstream_timeout,
										 uint32_t outstream_watermark_remaining);
		
			void doTasks_mainThread();
			void doTasks_SDThread();
			
			bool isMounted(){return Mounted;};
			bool isBusy(){return Busy;};
			
			RESULT WriteHeader(File* pFile);
			FRESULT MountDrive();
			FRESULT UnmountDrive();
				
			OutputSet*	OutputSet_WriteFileStatus;
			Output* 		Output_ResOpen;
			Output* 		Output_ResWrite;
			Output* 		Output_ResTotalBytes;
			
			static void Boot(uint8_t max_num_files);
	
			static EV_ID Tx_RESP_CARD_FILENAME(Port* dest_port, PACKET_TYPE packet_type);
			
			static EV_ID Tx_RESP_CARD_INFO(Port* dest_port, PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_CARD_BLOCK(Port* dest_port, char* name, uint32_t blockNum, PACKET_TYPE packet_type);
			
			static EV_ID Tx_RESP_CARD_DIRNAME(Port* dest_port, PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_CARD_TAG(Port* dest_port, PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_CARD_FILES(Port* dest_port, PACKET_TYPE packet_type);
			static EV_ID Tx_RESP_CARD_NUMFILES(Port* dest_port, PACKET_TYPE packet_type);
		protected:

		private:
			~FileInterface();
			SDHCInterface* pSDHC;
			FATFS FatFs;
			RESULT performWrite(File* pFile);
			Timer* Timer1Hz;
			uint32_t numTxBytes;
			uint32_t WriteCount;
			uint32_t marker;
			uint32_t totalWrite;
			FRESULT res_mount;
			FRESULT res_open;
			FRESULT res_write;			
			Buffer* TxBuf_SD;
			Buffer* RxBuf_SD;
			uint8_t iFile_TxCheck;
			bool Busy;
			bool Mounted;
//			void WriteHeader();
			//static bool GenerateHeader;
			osSemaphoreId sema_TxBuf;
			volatile bool awaitingWrite;
		
			// Directory Read
			static bool readDirIsOpen;
			static DIR readDir;
			static FRESULT readDirRes;
			static FILINFO readDirFno;			
	
			static vector<File*>* Files;
			//static uint8_t iFile;
			static EV_ID Parse_CMD_GET_FILENAME(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_SET_FILENAME(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_FILES_ON_CARD(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_NUM_FILES_ON_CARD(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);			
			static EV_ID Parse_CMD_GET_CARD_BLOCK(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_DELETE_FILE(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_ERASE_CARD(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			
}; 
#endif
