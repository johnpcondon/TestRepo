/****************************************************************************
* File Name          : FlashSettings.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Provides the ability to save settings to flash memory
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef FLASH_SETTINGS_H
#define FLASH_SETTINGS_H

#include "Generic/GenericTypeDef.h"
#include "Containers/Buffer.h"

class FlashSettings{
	public:
		FlashSettings(uint8_t* base_addr);
		static FlashSettings* getInstance();
		static bool Erase();
	
		template<typename T> static bool Save(T& val);
		static bool Save(Buffer* buf);
	
		template <typename T>static uint32_t Read(T* val, uint32_t offset);

		static bool Unlock();
		static bool Lock();
		static uint8_t* getAddress(uint8_t page);
		static bool isLocked(){return pFlash->Locked;};
		static uint8_t* getBaseAddress(){return pFlash->BaseAddress;};
	
	private:
		static FlashSettings* pFlash;
		uint8_t* BaseAddress;
		uint32_t Offset;
		bool Locked;
	
};

/*******************************************************************************
* Save a value to the next location in memory
*******************************************************************************/
template<typename T>
bool FlashSettings::Save(T& val)
{
	uint8_t num_bytes 	= getDataTypeSize(&val);
	return Save(val,num_bytes);
}

/*******************************************************************************
* Read a value from memory
*******************************************************************************/
template <typename T>
uint32_t FlashSettings::Read(T* val, uint32_t offset)
{
	*val = *(T*)(pFlash->BaseAddress + offset);
	
	return getDataTypeSize(val);
}


#endif
