/****************************************************************************
* File Name          : VariableAccess.h
* Author             : John Condon / Adam Becker
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This creates access to variables via port packets
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef VARIABLEACCESS_H
#define VARIABLEACCESS_H

#include "Generic/GenericTypeDef.h"
#include "Containers/JCVect.h"
#include "Generic/DataTypes.h"
#include "Comms/PacketBuilder.h"
#include "Comms/PacketParser.h"
#include "Peripherals/FlashInterface.h"

const uint32_t SETTINGS_SYNC 			= 0x12345678;
const uint8_t	VAR_MASK_READABLE 	= 1;
const uint8_t	VAR_MASK_SETTABLE 	= 2;
const uint8_t VAR_MASK_SAVEABLE 	= 4;
const uint8_t	VAR_MASK_STREAMABLE = 8;
const uint8_t MAX_SETTING_SIZE		= 8; //Max size of a single setting including overhead
class Variable;
typedef EV_ID (*SettingFcn)(Variable* var); //Define setting callback function
//typedef void (*SettingFcn_void)(void); 			//Define setting callback function

class Variable{
	public:
			template <typename T> Variable(const char* name, const char* units, T* pval);
			void makeSettable();
			void makeSettable(SettingFcn callback_fcn);
			//void makeSaveable(uint8_t setting_class,uint8_t sub_class);
	
			uint8_t getIndex()			{return Index;};
			
			DATA_TYPE getType()			{return DataType;};
			uint8_t getNumBytes()		{return NumBytes;};
			uint8_t	getPermissions(){return Permissions;};
			const char* getUnits()	{return Units;};
			uint16_t getSettingID()	{return SettingID;};
			void*	getVal_RAMAddr()	{return pVal_RAM;};
			void*	getVal_FlashAddr() {return pVal_Flash;};
			
			//template <typename T> EV_ID setVar(T* pval);
			EV_ID setVal_RAM(void* pval,uint8_t num_bytes);
			
			bool isReadable()		{return (Permissions & VAR_MASK_READABLE);};
			bool isSettable()		{return (Permissions & VAR_MASK_SETTABLE);};
			bool isSaveable()		{return (Permissions & VAR_MASK_SAVEABLE);};
			bool isStreamable()	{return (Permissions & VAR_MASK_STREAMABLE);};
			
			static void initVariableStorage(uint8_t* pSettingsHead);
			static Variable* getVariable(uint8_t index);
			static void* getVal_RAMAddr(uint8_t index);
			static void* getVal_FlashAddr(uint8_t index);
			static uint8_t getNumVars()    {return Variables->getCnt();};
			static const char* getName(uint8_t index);
			static Variable* findSetting(uint16_t setting_id);
			
			static bool EraseAll();
			//static bool Restore(uint16_t setting_id);
			static bool RestoreAll();
			static bool SaveAll(uint32_t date);
			
			//Packet Transmission
			static EV_ID TX_RESP_ALL_VARIABLE_INFO(Port* destPort,PACKET_TYPE packet_type);
			static EV_ID TX_RESP_VARIABLE_INFO(Port* destPort, uint8_t var_index,PACKET_TYPE packet_type);
			static EV_ID TX_RESP_VARIABLE_UNITS(Port* destPort, uint8_t var_index,PACKET_TYPE packet_type);
			static EV_ID TX_RESP_VARIABLE_VAL(Port* destPort,uint8_t var_index,PACKET_TYPE packet_type);
			
			static void Boot(uint16_t max_num_variables,uint8_t max_num_variable_groups, uint8_t flash_settings_page);
	private:
			~Variable();

			const char* Name;
			const char* Units;
			void*				pVal_RAM;
			void*				pVal_Flash;
			DATA_TYPE 	DataType;
			uint8_t 		NumBytes;
			uint8_t 		Index;
			uint8_t 		Permissions;
			uint16_t 		SettingID;
			SettingFcn 	SettingCallback;
			//SettingFcn_void SettingCallback_void;
			
			static FlashSettings* 	pFlash;
			//static bool VariablesInitialized;
			static Buffer* SettingsBuf;
			//static vector<Variable*> Variables;
			static Variable* Var_SaveDate;
			static uint32_t SaveDate;
	
			void	addPermissions(uint8_t permissions){Permissions |= permissions;};
			
			//Packet Parsing
			static EV_ID Parse_CMD_GET_ALL_VAR_INFO(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_VAR_INFO(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_VAR_UNITS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_GET_VARIABLE(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_SET_VARIABLE(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_SAVE_SETTINGS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_RESTORE_SETTINGS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			static EV_ID Parse_CMD_ERASE_SETTINGS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
			
			static vector<Variable*>* Variables;
};

template <typename T> Variable::Variable(const char* name, const char* units, T* pval)
{
	if(Variable::Variables == nullptr){
		while(1); //Call Boot First
	}
	
	Name = name;
	Units = units;
	pVal_RAM = pval;
	pVal_Flash = nullptr;
	DataType 		= getDataType(pval);
	NumBytes 		= getDataTypeSize(pval);
	SaveDate = 0;
	addPermissions(VAR_MASK_READABLE);
	
	Index = Variables->getCnt();
	Variables->push_back(this);
	
}

class VariableGroup
{
	public:
	 VariableGroup(const char* name,uint8_t num_variables_in_group);
	 void makeStreamable();
	 void add(Variable* var);
	 uint8_t getVarIndex(uint8_t iVar);
	 uint8_t getNumVars(){return Group.getCnt();};
	 static uint8_t getNumGroups() { return VariableGroups->getCnt(); };
	 static VariableGroup* getVariableGroup(uint8_t index);
	 static const char* getName(uint8_t index);
	 
	 static EV_ID TX_RESP_GET_ALL_VARGROUPS(Port* resp_port, PACKET_TYPE packet_type);
	 static void Boot(uint8_t max_num_variableGroups);
	private:
		~VariableGroup();
		const char* Name;
		vector<uint8_t> Group;
	
		static EV_ID Parse_CMD_GET_ALL_VARGROUPS(Port* resp_port, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);		
	
		static vector<VariableGroup*>* VariableGroups;
	
};

#endif


