/*****************************************************************************
* File Name          : Device.h
* Date               : 05/13/2015
* Description        : Processes standard IDL Protocol packets for the device
*******************************************************************************/
#ifndef DEVICE_H
#define DEVICE_H
// General Includes
#include "Generic/GenericTypeDef.h"
#include "Comms/Protocol.h"
#include "Comms/VariableAccess.h"

//typedef struct{
//  	DEV_TYPE DevType;
//		uint16_t HardwareVer;
//  	uint16_t SoftwareVer;
//		uint16_t RadioSoftwareVer;
//	union{
//		uint32_t word[2];
//		uint8_t  byte[8];
//	}MySN;
//	const char* Name;
//	
//}DEV_INFO;

//Temp Struct until we find a better spot for this
//typedef struct{
//	uint32_t Marker;
//	int16_t  RSSI;
//	uint16_t NumChSwitches;
//	uint16_t NumTxAttempts;
//	uint32_t ByteRate_Rx;
//	uint32_t ByteRate_Tx;
//}RDO_STATUS;

class Device{
	public:
		static Device* getInstance();
		//static void init();
		static const char* getName(){return getInstance()->Name;};
		static DEV_TYPE getDevType(){return getInstance()->DevType;};
		static uint64_t getSN(){return getInstance()->SN;};
		static uint16_t getHWVer(){return getInstance()->HardwareVer;};
		static uint16_t getSWVer(){return getInstance()->SoftwareVer;};
		//Functions Defined by application (hardware specific)
		static RESULT startShutdown();
		static RESULT startLowPower();
		static uint16_t getVBat_mV();
		static uint16_t getVcc_mV();
		static uint16_t getTemp();
	
		static uint32_t getTotalHeapUsage();
		static uint32_t getSysClk();
		
		//Packet Transmission Functions
		static EV_ID Tx_STATUS(Port* dest_port);
		static EV_ID Tx_RESP_DEVINFO(Port* dest_port,PACKET_TYPE packet_type);
		static EV_ID Tx_RESP_NAME(Port* dest_port, OBJECT_TYPE obj_type, uint8_t obj_index, uint8_t obj_subIndex,PACKET_TYPE packet_type);
		
		static void Boot(DEV_TYPE dev_type, uint16_t hardware_ver, uint16_t software_ver,const char* name, uint64_t serial_num);
	private:
		static Device* pDevice;
		Device(DEV_TYPE dev_type, uint16_t hardware_ver, uint16_t software_ver,const char* name, uint64_t serial_num);
		~Device();

	 	DEV_TYPE DevType;
		uint16_t HardwareVer;
  	uint16_t SoftwareVer;
		uint16_t RadioSoftwareVer;
		uint64_t SN;
		const char* Name;
	
		//Packet Parsing Functions
		static EV_ID Parse_CMD_GET_NAME(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_GET_DEVINFO(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_GET_STATUS(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_SHUTDOWN(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_CMD_LOWPOWER(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
		static EV_ID Parse_RESP_RDOSTATUS(Port* RespPort, Buffer* buf, uint8_t DataLen,PACKET_TYPE packet_type);
	
		//static DEV_INFO DevInfo;
		//static RDO_STATUS RdoStatus; //Todo, Move this out of here
};


#endif
