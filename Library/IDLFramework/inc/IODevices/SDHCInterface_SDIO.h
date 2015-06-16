/******************************************************************************
* File Name          : SDHCInterface_SDIO.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 4/20/2013
* Description        : This is the header file SD Card Hardware functions
*
*******************************************************************************/
#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

/* Includes ------------------------------------------------------------------*/
#include "Peripherals/IOInterface.h"
#include "Peripherals/TimerInterface.h"
#include "SDCardDefines.h"
#include "InterruptsInterface.h"
//#include "diskio.h"
//#include "ff.h"

//STM32F4 has 48MHz SDIO Clock
  /*!< SDIO_CK = SDIOCLK / (SDIO_TRANSFER_CLK_DIV + 2) */
const uint8_t SDIO_TRANSFER_CLK_DIV_400kHz = 118;
const uint8_t SDIO_TRANSFER_CLK_DIV_HIGHSPEED = 0;

const uint32_t SDIO_CMD0TIMEOUT = 0x00010000; //Clock cycles
const uint32_t SDIO_CMD7TIMEOUT = 0x00010000; //Clock cycles

//typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

class SDHCInterface{
	public:
		SDHCInterface(IO_Pin* pin_sdio_ck,
									IO_Pin* pin_sdio_dat0,
									IO_Pin* pin_sdio_dat1,
									IO_Pin* pin_sdio_dat2,
									IO_Pin* pin_sdio_dat3,
									IO_Pin* pin_sdio_cmd);
	
		void UseEnablePin(IO_Pin* pin_EN, IO_ACTIVE_LEVEL active_lvl);
		void UseCardDetectPin(IO_Pin* pin_CD,IO_ACTIVE_LEVEL active_lvl);
		void UseDMA();
	
		//Functions called directly by FatFs
		SD_Error SD_Init();
		//SD_Error SD_Status();
		//SD_Error SD_IOCtl(uint8_t cmd, char *buff);
		SD_Error SD_Read(uint8_t *buff, uint32_t sector, uint32_t count);
		SD_Error SD_Write(uint8_t *buff, uint32_t sector, uint32_t count);

		//Card Management
		bool isCardPresent();
		bool isWriteProtected(){return false;};
		bool isInitialized(){return isInit;};
		
		SD_Error EnablePower();
		SD_Error DisablePower();
		//FRESULT getDriveSize(uint32_t* total, uint32_t* free);
		
		//IRQ Callback Functions
		void ProcessIRQSrc(IRQ_TYPE irqsrc);
		void ProcessDMAIRQ(IRQ_TYPE irqsrc);
		static SDHCInterface* getSDHCPointer(){return pSDHC;};
		
	protected:
		~SDHCInterface();
	private:
		static SDHCInterface* pSDHC;
	
		//Functions defined at hardware levevl
		void LowLevelInit();
		void LowLevel_DMATxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
		void LowLevel_DMARxConfig(uint32_t *BufferDST, uint32_t BufferSize);
	
		SD_Error SD_CheckCard();
		SD_Error SD_Initialization();
		SD_Error SD_SelectDesect(uint64_t addr);
		SD_Error SD_IsProgramming();
		SD_Error SD_WideBusOperation(bool enable); //Only called by SDIO function
	
		SD_Error SD_GetSCR(uint16_t rca, uint32_t *pscr);
	
		SDTransferState SD_GetStatus(void);
		SDCardState SD_GetState(void);
		SD_Error SD_SendStatus(uint32_t *pcardstatus);
		
		SD_Error SD_ReadBlock(uint8_t* readbuf, uint64_t ReadAddr, uint16_t BlockSize);
		SD_Error SD_ReadMultiBlocks (uint8_t *readbuff, uint64_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
		SD_Error SD_WaitReadOperation();
		
		SD_Error SD_WriteBlock (uint8_t *writebuff, uint64_t WriteAddr, uint16_t BlockSize);
		SD_Error SD_WriteMultiBlocks (uint8_t *writebuff, uint64_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
		SD_Error SD_WaitWriteOperation();
		
		SD_Error SD_Erase(uint64_t startaddr, uint64_t endaddr);
		SD_Error IsCardProgramming(uint8_t *pstatus);
		SD_Error SD_StopTransfer();
		
		SD_Error SDIO_EnableWideBusOperation(uint32_t WideWode);
		SD_Error EnableHighSpeedMode();
		
		SD_Error SD_ErrChk_Cmd();
		SD_Error SD_ErrChk_CmdResp1(uint8_t cmd);
		SD_Error SD_ErrChk_CmdResp2();
		SD_Error SD_ErrChk_CmdResp3();
		SD_Error SD_ErrChk_CmdResp6(uint8_t cmd, uint16_t *prca);
		SD_Error SD_ErrChk_CmdResp7();
		
		SD_Error SD_FindSCR(uint16_t rca, uint32_t *pscr);
		
		SD_Error SD_GetCardInfo();
		
		//Card Information Variables
		__IO SD_Error ErrorStatus;
		__IO SDTransferState TransferState;
		SD_CardInfo CardInfo;
		uint32_t CardType;
		uint32_t CSD_Tab[4];
		uint32_t CID_Tab[4];
		uint32_t RCA;
		//uint8_t SDSTATUS_Tab[16];
		__IO uint32_t StopCondition;
		__IO SD_Error TransferError;
		__IO uint32_t TransferEnd;
		__IO uint32_t DMAEndOfTransfer;
		uint32_t SDType;
		
		//Hardware Variables
		IO_Pin*	 Pin_SDIO_CK;
		IO_Pin*	 Pin_SDIO_DAT0;
		IO_Pin*	 Pin_SDIO_DAT1;
		IO_Pin*	 Pin_SDIO_DAT2;
		IO_Pin*	 Pin_SDIO_DAT3;
		IO_Pin*	 Pin_SDIO_CMD;
		IO_Pin*  PinEN;
		IO_Pin*	 PinCD;
		Timer*	 TimeoutTimer;
		bool 		 usingDMA;
		bool		 isInit;
		
		//volatile DSTATUS FATFS_SD_Status;	/* Physical drive status */
	
};

//#endif

#endif

