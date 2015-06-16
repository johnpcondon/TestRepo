/****************************************************************************
* File Name          : IOInterface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 7/3/2013
* Description        : This module implements GPIO Functions
******************************************************************************/
#ifndef IO_Hardware_H
#define IO_Hardware_H

#include "nrf.h"
#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"

enum IO_PORT_NUM;
enum IO_PIN_NUM;


//Nordic Specific Functions for IO Pin
//These functions should only be called by other ***_Hardware.h files
//uint32_t IO_getPinNum(IO_PIN_NUM pin_num);

#endif

