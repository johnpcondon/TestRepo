/****************************************************************************
* File Name          : Protocol.h
* Author             : John Condon & Adam Becker
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This file defines the general protocol
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "Generic/GenericTypeDef.h"

const uint8_t START_SYNC 			= 0xCC;
const uint8_t END_SYNC 				= 0xDD;

const uint8_t PI_PARSELOCAL 	= 0x0F;
const uint8_t PI_RESPCONSOLE	= 0x0E;
const uint8_t OPCODE_TYPEMASK	= 0xF0;
const uint8_t OPCODE_SRCMASK	= 0x0F;

const uint8_t HEADER_LEN_1bytelen = 3;
const int32_t 	MAX_PAYLOAD_LEN 	= 254;

enum class DEV_TYPE : uint8_t
{
	NONE							= 0x00,
	
	//Primary Type
  IMU								= 0x01,
  USBDONGLE	 				= 0x02,
  CRAFT		  				= 0x03,
	CONTROLLER				= 0x04,
  TARGETPUCK				= 0x05,
	TENNIS						= 0x06,
	nRF51DEV					= 0x07,
	
	// Secondary
	GENERICRADIO			= 0xA0, 
	CRAFTRADIO  			= 0xA1,	
	
	UNKNOWN					= 0xFF,
};

//enum class APP_CMD : uint8_t;
//enum class APP_RESP : uint8_t;

enum class PACKET_TYPE : uint8_t
{
	NONE					= 0x00,	// Invalid Packet
	STATUS				= 0x10,	// Periodic Status message
	COMMAND				= 0x20,	// Command unit 
	RESPONSE			= 0x30,	// Response to Command
	OUTPUTDATA		= 0x40,	// Output Data Set
	DATABLOCK			= 0x50,	// Data block from Memory
	FORWARDDATA		= 0x60,	// Data to be forwarded to another port
	APP_CMD				= 0x70,	// Application Specific Command
	APP_RESP			= 0x80,	// Application Specific Response
	RDOOUTPUTDATA	= 0xD0,	// Output Data Set
	RADIOCMD			= 0xE0,	// Command to radio
	RADIORESP			= 0xF0,	// Response to radio
};


enum class EV_ID : uint8_t
{
	NONE									= 0x00, // No event to tx
	NOTIMPLEMENTED				= 0x10,	// Command not yet implemented
	ERR										= 0x11,	// General Parsing Error
	AOK										= 0x12,	// Command Received Correctly
	BADPARAM							= 0x13,	// Bad Parameter Received
	CMDFAILED							= 0x14,	// Failure to act on command
	INVALIDCMD						= 0x15,	// Invalid Command ID Given
	BADCHECKSUM						= 0x16,	// Invalid Checksum
	FORWARDED							= 0x17, // Packet Forwarded 
	WRITEPROTECTED				= 0x18,
};

enum class CMD_ID : uint8_t 
{
	// **** Core Commands 			**** 
	INVALID								= 0x00, // Invalid Command
	GET_NAME							= 0x01, // Returns string names of objects
	GET_UNIT							= 0x02,	// Gets the unit of a variable
	GET_DEVINFO 					= 0x03, // Gets the device information
	GET_PORTS 	 					= 0x04, // Gets which ports are available on this device
	SELF_CAL							= 0x05, // Starts an internal calibration routine
	REQ_SELFTEST					= 0x06, // Requests the self test results
	RUN_SELFTEST					= 0x07, // Runs a self-test for all available components
	SHUTDOWN							= 0x08, // Shuts down the unit into off mode
	LOWPOWER							= 0x09, // Shuts down the unit into low power mode
	GET_STATUS						= 0x0A, // Requests Device Status
	PING_PORT							= 0x0B, // Pings a port
	GET_TESTPACKET				= 0x0F, // Requests A Test Packet
	
	// **** Outputsets Commands	**** 
	GET_OUTPUTSETS				= 0x10, // Request the output sets available on this device
	SUB_OUTPUTSETS				= 0x11, // Subscribe a port to output sets
	STOP_OUTPUTSETS				= 0x12, // Stop all outputs to a port
	GET_OUTPUTSETRATE			= 0x13, // Get current outputset rates
	
	// **** Variable Commands 	****
	GET_ALL_VARGROUPS			= 0x20,	// Requests all variable groups
	GET_ALL_VAR_INFO			= 0x21,	// Requests all variable information
	GET_VAR_INFO					= 0x22,	// Requests all variable information
	GET_VAR_UNITS					= 0x23,	// Requests all variable information
	GET_VARIABLE					= 0x24,	// Requests a single variable value
	SET_VARIABLE					= 0x25,	// Sets a single variable value
	SAVE_SETTINGS					= 0x41, // Saves current settings to flash (change this SAVE_ALL_VARIABLES)
	RESTORE_SETTINGS			= 0x42, // Restores settings from flash (change this RESTORE_ALL_VARIABLES)
	ERASE_SETTINGS				= 0x43, // Restores settings to factory default (change ERASE_ALL_VARIABLES)
	RESTORE_VARIABLE			= 0x44,	// Restores a single variable from flash (not implemented yet)
	
	// **** Time Commands 			****
	GET_MARKER						= 0x30, // Requests the current marker value and time offset
	SET_MARKER						= 0x31, // Sets the internal marker value
	GET_DATETIME					= 0x32, // Returns both the time and marker value
	SET_DATETIME					= 0x33, // Sets internal real time clock
	
	// **** Flash Commands			****
	//GET_SYSCONFIG				= 0x40, // Requests the current system configuration
	
	// **** SdCard Commands			****
	GET_CARD_INFO					= 0x50, // Requests Storage Information
	GET_CARD_BLOCK				= 0x51, // Requests a block of data from Storage
	ERASE_CARD						= 0x52, // Erases a block (or entire) of data from storage
	GET_FILENAME					= 0x53, // Requests the active filename for data storage
	SET_FILENAME					= 0x54, // Sets the active filename for data storage
	GET_FILES_ON_CARD			= 0x55, // Scans for files on the sdcard. 
	GET_NUM_FILES_ON_CARD	= 0x56, // Returns number of files on the sdcard 
	DELETE_FILE			  		= 0x57, // Delets a file on the SD card
	
	// **** Radio Commands 			**** 
	PAIR_REQ							= 0xF0, // Request from Device to Host to Pair
	PAIR_CMD							= 0xF1, // Command to Device from Host to pair
	UNPAIR								= 0xF2,	// Command to unpair
	PAIR_VERIFY						= 0xF3,	// Verification that pairing has occured
	GET_TESTMODE					= 0xF4, // Request Radio Test Mode
	SET_TESTMODE					= 0xF5, // Set Radio Test Mode
	GET_PIPES							= 0xF6, // Get Pipe Information
};

enum class RESP_ID : uint8_t
{	
	// **** Core Responses 			**** 
	INVALID							= 0x00,
	NAME								= 0x01, 
	UNIT 								= 0x02,
	DEVINFO							= 0x03, // Device information
	PORTS								= 0x04, // A listing of the port available on the unit
	SELF_CAL						= 0x05, // Starts an internal calibration routine
	REQ_SELFTEST				= 0x06, // Requests the self test results
	RUN_SELFTEST				= 0x07, // Runs a self-test for all available components
	SHUTDOWN						= 0x08, // Shuts down the unit into low power mode 
	GET_STATUS					= 0x0A, 
	PING								= 0x0B,
	TESTPACKET			    = 0x0F,
	
	// **** OutputSet Responses ****
	OUTPUTSETS					= 0x10, // Returns the available output sets and their current rates
	OUTPUTSETRATE      	= 0x13, // Returns the output set rate for an output set
	
	// **** Variable Responses 	****
	ALL_VARGROUPS				= 0x20, // All variable groups in the system
	ALL_VARIABLE_INFO		= 0x21, // All variables in the system
	VARIABLE_INFO				= 0x22, // Specific Variable information
	VARIABLE_UNITS			= 0x23, // Units of a specific variable
	VARIABLE_VAL				= 0x24, // Requested variable values
	
	// **** Time Responses 			****
	MARKER							= 0x30, //The current marker value
	DATETIME						= 0x32, //The current real-time clock value
	
	// **** Flash Responses			****
	// TBD - 0x40
	
	// **** SdCard Responses		****
	CARD_INFO						= 0x50, 
	CARD_BLOCK					= 0x51,
	CARD_FILENAME				= 0x53, 
	CARD_FILES					= 0x55,
	CARD_NUMFILES				= 0x56,
	
	// **** Radio Responses 		****
	RDO_TESTMODE				= 0xF4, // Radio Test Mode 
	RDO_PIPES						= 0xF6, // Radio Pipe Status

	// **** Other Responses 		****		
	RDO_STATUS					= 0xA4, // Radio Status	
	EVENT								= 0xEE, // Generic Event Responses
};

enum class STATUS_KEY : uint8_t
{
	INVALID 			= 0x00,
	MARKER  			= 0x01,
	VOLTAGE 			= 0x02,
	SDCARD  			= 0x03,
	RSSI    			= 0x04,
	TXRX    			= 0x05,
	PIPEINFO 			= 0x06,
	RDOADDR				= 0x07,
};

enum class OBJECT_TYPE : uint8_t 
{
	DEVICE 	 					= 0,
	PORT			 				= 1,
	OUTPUTSET 				= 2,
	OUTPUT		 				= 3,
	VARIABLE	 				= 4,
	VARGROUP	 				= 5,
};

#endif

