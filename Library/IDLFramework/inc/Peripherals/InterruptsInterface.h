/****************************************************************************
* File Name          : ExtTrigger_Interface.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module implements External Interrupts on GPIO Pins
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "Generic/GenericTypeDef.h"
#include "Interrupts_Hardware.h"
#include "Peripherals/IOInterface.h"

typedef void (*IntCallback)(IRQ_TYPE irqsrc); //Interrupt callback function.  Return if to clear flag
extern IntCallback Interrupt_Fcns[MAX_NUM_INTERRUPTS];

enum INTERRUPT_PRIORITY{
	IRQ_PRIOR_0,
	IRQ_PRIOR_1,
	IRQ_PRIOR_2,
	IRQ_PRIOR_3,
	
	IRQ_PREEMPT_0_SUB_0,
	IRQ_PREEMPT_0_SUB_1,
	IRQ_PREEMPT_0_SUB_2,
	IRQ_PREEMPT_0_SUB_3,
	
	IRQ_PREEMPT_1_SUB_0,
	IRQ_PREEMPT_1_SUB_1,
	IRQ_PREEMPT_1_SUB_2,
	IRQ_PREEMPT_1_SUB_3,
	
	IRQ_PREEMPT_2_SUB_0,
	IRQ_PREEMPT_2_SUB_1,
	IRQ_PREEMPT_2_SUB_2,
	IRQ_PREEMPT_2_SUB_3,
	
	IRQ_PREEMPT_3_SUB_0,
	IRQ_PREEMPT_3_SUB_1,
	IRQ_PREEMPT_3_SUB_2,
	IRQ_PREEMPT_3_SUB_3
};

class IRQInterface{
	public:
		static void Init(IRQ_TYPE int_type, IntCallback fcn, INTERRUPT_PRIORITY priority);
		static void InitHardware(IRQ_TYPE irq_type);
		static void GenerateSWInterrupt(IRQ_TYPE irq_type);
	
		static void SetIRQ_EnableFlag(IRQ_TYPE irq_type, uint32_t flag, bool new_state);
		static void ClearIRQ_PendFlag(IRQ_TYPE irq_type, uint32_t flag);
		static bool isEnabled(IRQ_TYPE irq_type, uint32_t flag);
			
		//Functions implemented in hardware file
		static void SetPriority(IRQ_TYPE irq_type, INTERRUPT_PRIORITY priority);
		static void* getPeriph(IRQ_TYPE irq_type);
		//Called from interrupt functions
		static IntCallback Fcns[MAX_NUM_INTERRUPTS];
		static IRQn_Type getIRQn(AF_Periph periph);
	protected:
	
	private:
		IRQInterface();
		~IRQInterface();
	
		
}; //End Class


#endif
