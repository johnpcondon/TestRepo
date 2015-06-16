/******************************************************************************
* File Name          : SDHCInterface.h
* Author             : John Kablan
* Version            : V 1.0
* Date               : 4/20/2013
* Description        : This is the header file SD Card Hardware functions
*
*******************************************************************************/
#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

/* Includes ------------------------------------------------------------------*/
#include "SPIInterface.h"
#include "IOInterface.h"
#include "Timers.h"

#define SD_LARGE_TXRX_DMA

extern volatile unsigned int isDMARxComplete;
extern volatile unsigned int isDMATxComplete;

#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */


enum SD_Error {
/**
  * @brief  SD reponses and error flags
  */
  SD_RESPONSE_NO_ERROR      = (0x00),
  SD_IN_IDLE_STATE          = (0x01),
  SD_ERASE_RESET            = (0x02),
  SD_ILLEGAL_COMMAND        = (0x04),
  SD_COM_CRC_ERROR          = (0x08),
  SD_ERASE_SEQUENCE_ERROR   = (0x10),
  SD_ADDRESS_ERROR          = (0x20),
  SD_PARAMETER_ERROR        = (0x40),
  SD_RESPONSE_FAILURE       = (0xFF),

/**
  * @brief  Data response error
  */
  SD_DATA_OK                = (0x05),
  SD_DATA_CRC_ERROR         = (0x0B),
  SD_DATA_WRITE_ERROR       = (0x0D),
  SD_DATA_OTHER_ERROR       = (0xFF)
};

/** 
  * @brief  Card Specific Data: CSD Register   
  */ 
typedef struct
{
  __IO uint8_t  CSDStruct;            /*!< CSD structure */
  __IO uint8_t  SysSpecVersion;       /*!< System specification version */
  __IO uint8_t  Reserved1;            /*!< Reserved */
  __IO uint8_t  TAAC;                 /*!< Data read access-time 1 */
  __IO uint8_t  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
  __IO uint8_t  MaxBusClkFrec;        /*!< Max. bus clock frequency */
  __IO uint16_t CardComdClasses;      /*!< Card command classes */
  __IO uint8_t  RdBlockLen;           /*!< Max. read data block length */
  __IO uint8_t  PartBlockRead;        /*!< Partial blocks for read allowed */
  __IO uint8_t  WrBlockMisalign;      /*!< Write block misalignment */
  __IO uint8_t  RdBlockMisalign;      /*!< Read block misalignment */
  __IO uint8_t  DSRImpl;              /*!< DSR implemented */
  __IO uint8_t  Reserved2;            /*!< Reserved */
  __IO uint32_t DeviceSize;           /*!< Device Size */
  __IO uint8_t  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
  __IO uint8_t  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
  __IO uint8_t  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
  __IO uint8_t  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
  __IO uint8_t  DeviceSizeMul;        /*!< Device size multiplier */
  __IO uint8_t  EraseGrSize;          /*!< Erase group size */
  __IO uint8_t  EraseGrMul;           /*!< Erase group size multiplier */
  __IO uint8_t  WrProtectGrSize;      /*!< Write protect group size */
  __IO uint8_t  WrProtectGrEnable;    /*!< Write protect group enable */
  __IO uint8_t  ManDeflECC;           /*!< Manufacturer default ECC */
  __IO uint8_t  WrSpeedFact;          /*!< Write speed factor */
  __IO uint8_t  MaxWrBlockLen;        /*!< Max. write data block length */
  __IO uint8_t  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
  __IO uint8_t  Reserved3;            /*!< Reserded */
  __IO uint8_t  ContentProtectAppli;  /*!< Content protection application */
  __IO uint8_t  FileFormatGrouop;     /*!< File format group */
  __IO uint8_t  CopyFlag;             /*!< Copy flag (OTP) */
  __IO uint8_t  PermWrProtect;        /*!< Permanent write protection */
  __IO uint8_t  TempWrProtect;        /*!< Temporary write protection */
  __IO uint8_t  FileFormat;           /*!< File Format */
  __IO uint8_t  ECC;                  /*!< ECC code */
  __IO uint8_t  CSD_CRC;              /*!< CSD CRC */
  __IO uint8_t  Reserved4;            /*!< always 1*/
} SD_CSD;

/** 
  * @brief  Card Identification Data: CID Register   
  */
typedef struct
{
  __IO uint8_t  ManufacturerID;       /*!< ManufacturerID */
  __IO uint16_t OEM_AppliID;          /*!< OEM/Application ID */
  __IO uint32_t ProdName1;            /*!< Product Name part1 */
  __IO uint8_t  ProdName2;            /*!< Product Name part2*/
  __IO uint8_t  ProdRev;              /*!< Product Revision */
  __IO uint32_t ProdSN;               /*!< Product Serial Number */
  __IO uint8_t  Reserved1;            /*!< Reserved1 */
  __IO uint16_t ManufactDate;         /*!< Manufacturing Date */
  __IO uint8_t  CID_CRC;              /*!< CID CRC */
  __IO uint8_t  Reserved2;            /*!< always 1 */
} SD_CID;

/** 
  * @brief SD Card information 
  */
typedef struct
{
  SD_CSD SD_csd;
  SD_CID SD_cid;
  uint32_t CardCapacity;  /*!< Card Capacity */
  uint32_t CardBlockSize; /*!< Card Block Size */
} SD_CardInfo;

/**
  * @}
  */
  
/** @defgroup STM32_EVAL_SPI_SD_Exported_Constants
  * @{
  */ 
    
/**
  * @brief  Block Size
  */
#define SD_BLOCK_SIZE    0x200

/**
  * @brief  Dummy byte
  */
#define SD_DUMMY_BYTE   0xFF

/**
  * @brief  Start Data tokens:
  *         Tokens (necessary because at nop/idle (and CS active) only 0xff is 
  *         on the data/command line)  
  */
#define SD_START_DATA_SINGLE_BLOCK_READ    0xFE  /*!< Data token start byte, Start Single Block Read */
#define SD_START_DATA_MULTIPLE_BLOCK_READ  0xFE  /*!< Data token start byte, Start Multiple Block Read */
#define SD_START_DATA_SINGLE_BLOCK_WRITE   0xFE  /*!< Data token start byte, Start Single Block Write */
#define SD_START_DATA_MULTIPLE_BLOCK_WRITE 0xFC  /*!< Data token start byte, Start Multiple Block Write */
#define SD_STOP_DATA_MULTIPLE_BLOCK_WRITE  0xFD  /*!< Data toke stop byte, Stop Multiple Block Write */

/**
  * @brief  SD detection on its memory slot
  */
#define SD_PRESENT        ((uint8_t)0x01)
#define SD_NOT_PRESENT    ((uint8_t)0x00)

class SDHCInterface{
	public:
		SDHCInterface(SPIPort* spi_port, IO_Pin* pin_CS, IO_Pin* pin_card_detect);
		SD_Error Init();
	
		uint8_t sendCmd(uint8_t Cmd, uint32_t Arg);
		SD_Error CmdResp(uint8_t Cmd, uint32_t Arg, uint8_t Crc);
		uint8_t  getDataResponse();
		SD_Error getResponse(uint8_t Response);
	
		uint8_t TxRxByte(uint8_t data);
	
		SD_Error readBytes(uint8_t* pBuffer, uint8_t numBytes);
		SD_Error readBlock(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t BlockSize);
		SD_Error readBlock(uint8_t* pBuffer, uint32_t numBytes);
		SD_Error writeBlock(const uint8_t* pBuffer, uint8_t token);
		
		bool isCardPresent();
		bool isCardReady();
	
		bool WaitUntilReady();
	
		SD_Error getCardInfo(SD_CardInfo *cardinfo);
		SD_Error getCSDRegister(SD_CSD* SD_csd);
		SD_Error getCIDRegister(SD_CID* SD_cid);
	
		uint8_t getCardType(){return CardType;};
		bool Select();
		bool Deselect();
		
		uint32_t getLastTxCompleted();
		static SDHCInterface* getInstance(){return SDHCInterface::pSDHC;};
	private:
		~SDHCInterface();
		static SDHCInterface* pSDHC;
		SPIPort* pSPI;
		IO_Pin*  PinCS;
		IO_Pin*	 PinCardDetect;
		Timer*	 TimeoutTimer;
	
		uint8_t CardType;			/* Card type flags */
	
};

///**
//  * @}
//  */ 
//  
///** @defgroup STM32_EVAL_SPI_SD_Exported_Macros
//  * @{
//  */

///**
//  * @}
//  */ 

///** @defgroup STM32_EVAL_SPI_SD_Exported_Functions
//  * @{
//  */ 
//extern uint8_t CardType;			/* Card type flags */
//	
////void SPI_SetClkSpeed(uint32_t des_speed);
////void SD_DeInit(void);  
//SD_Error SD_Init(void);
//uint8_t SD_Detect(void);
//int SD_WaitReady(void);
//SD_Error SD_GetCardInfo(SD_CardInfo *cardinfo);

//int SD_ReadBlock(uint8_t* pBuffer, uint32_t numBytes);
//int SD_WriteBlock(const uint8_t* pBuffer, uint8_t token);

////SD_Error SD_ReadBlocks(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
////SD_Error SD_WriteBlocks(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);

//SD_Error SD_RxBytes(uint8_t* pBuffer, uint8_t numBytes);
//uint8_t SD_TxRxByte(uint8_t data);

//SD_Error SD_GetCSDRegister(SD_CSD* SD_csd);
//SD_Error SD_GetCIDRegister(SD_CID* SD_cid);

//uint8_t SD_SendCmd(uint8_t Cmd, uint32_t Arg);

////SD_Error SD_GetResponse(uint8_t Response);
////uint8_t SD_GetDataResponse(void);
////SD_Error SD_GoIdleState(void);
////uint16_t SD_GetStatus(void);

//void SD_Deselect(void);
//int SD_Select(void);

//unsigned int getLastTxCompleted();

////int SD_DMA_Rx(const uint8_t * buffer, unsigned int bufferSize);
////int SD_DMA_Tx(const uint8_t * buffer, unsigned int bufferSize);

//#ifdef __cplusplus
//}
// 


//#endif

#endif

