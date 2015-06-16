/******************************************************************************
* File Name          : DMAInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 10/22/14
* Description        : This defines functions for the DMA Interface
* This is a thin interface and most of the functions are defined in the hardware file
*******************************************************************************/
#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

#include "Peripherals/IOInterface.h"
#include "Peripherals/InterruptsInterface.h"

enum DMA_DIR{
	DMA_PERIPH_TO_MEMORY,
	DMA_MEMORY_TO_PERIPH,
	DMA_MEMORY_TO_MEMORY,
};

enum DMA_MODE{
	DMA_MODE_NORMAL,
	DMA_MODE_CIRCULAR,
};
enum DMA_PRIORITY{
	DMA_PRIOR_VERYHIGH,
	DMA_PRIOR_HIGH,
	DMA_PRIOR_MED,
	DMA_PRIOR_LOW,
};

enum DMA_TRANSFER_SIZE{
	DMA_TRANSFER_BYTE 		= 1,
	DMA_TRANSFER_HALFWORD = 2,
	DMA_TRANSFER_WORD 		= 4,
};

class DMAInterface{
	public:
		//Periph2Mem or Mem2Periph
		DMAInterface(AF_Periph periph,
								uint32_t periph_data_reg,
								uint8_t stream_num,
								DMA_DIR direction,
								DMA_MODE mode,
								DMA_TRANSFER_SIZE txsize);
		//Mem2Mem
		DMAInterface(uint8_t stream_num);
	
		uint32_t getNumBytesToTransfer(){return numTransfers*DMATXSize;};
		uint32_t getMemoryEndAddr(){return MemoryBaseAddr + getNumBytesToTransfer();};
		
		//Defined in Hardware Def
		void setPriority(DMA_PRIORITY dma_priority);
		int setIncrement_DestAddr(bool val);
		int setIncrement_SrcAddr(bool val);
		
		int startTransfer(volatile uint8_t* mem_base_addr,uint16_t numTransfers);
		int startTransfer(volatile uint16_t* mem_base_addr,uint16_t numTransfers);
		int startTransfer(volatile uint32_t* mem_base_addr,uint16_t numTransfers);
		int startMemTransfer(uint8_t* srcAddr,uint8_t* destAddr,uint16_t numTransfers);
		int startMemTransfer(uint16_t* srcAddr,uint16_t* destAddr,uint16_t numTransfers);
		int startMemTransfer(uint32_t* srcAddr,uint32_t* destAddr,uint16_t numTransfers);
		void Enable();
		void Disable();
		bool isEnabled(){return Enabled;};
		bool isBusy(){return TransferInProgress;}
		void* getChPointer(){return DMAx_y;};
		uint16_t getCount();
		
		volatile bool TransferInProgress; //Only public for IRQ use...
	private:
		~DMAInterface();
	
		bool Enabled;
		
		//Defined in Hardware Def
		void init(INTERRUPT_PRIORITY priority);
	
		AF_Periph Periph;
		uint8_t DMAStreamNum;
		DMA_DIR DMADir;
		DMA_MODE DMAMode;
		DMA_PRIORITY DMAPriority;
		DMA_TRANSFER_SIZE DMATXSize;
	
		//Set in Hardware def
		//uint8_t DMANum;
		//uint8_t DMAChNum;
		void* DMAx_y; //Pointer to DMA Stream/Channel
		
		uint32_t PeriphBaseAddr;		
		uint32_t MemoryBaseAddr;		 
		uint16_t numTransfers;
	
		int startTransfer(void* mem_base_addr,uint16_t numTransfers,DMA_TRANSFER_SIZE txsize);
		int startMemTransfer(void* srcAddr,void* destAddr,uint16_t numTransfers,DMA_TRANSFER_SIZE txsize);
};

#endif
