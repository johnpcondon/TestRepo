/* ========================================================================== */
/*                                                                            */
/*   scheduler.h                                                          */
/*   (c) 2013 John Kablan                                                     */
/*                                                                            */
/*   Contains the IDL specific SD card interface                              */
/*                                                                            */
/* ========================================================================== */
/*------------------------------------------------------------------------------
 *PUBLIC FUNCTIONS
 *------------------------------------------------------------------------------*/

#

/*
 *
 *
 */
 
#ifndef __scheduler_h__
#define __scheduler_h__



	void del_process(void);
	//Initialize Tasks
void initTasks(void * (* tasks[])(void *), void * args[], void * stackTopAddr, uint32_t stackSizes[], int numTasks);

#ifdef __cplusplus
extern "C" 
{
#endif
   
//This defines the stack frame that is saved  by the hardware
typedef struct {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t psr;
} hw_stack_frame_t;
 
//This defines the stack frame that must be saved by the software
typedef struct {
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8;
  uint32_t r9;
  uint32_t r10;
  uint32_t r11;
} sw_stack_frame_t;

typedef struct
{
  unsigned int isValidTask 	: 1;
  unsigned int status 		: 2;
} task_flags_t;

typedef struct {
     void * sp; //The task's current stack pointer
     task_flags_t flags; //Status flags includes activity status, parent task, etc
} task_table_t;

#define MAX_TASKS 	  		2
#define EXEC_FLAG 	  		0x01
#define IN_USE_FLAG 	  	0x02
#define TOP_OF_STACK		((uint32_t)__Vectors) 
#define SCHEDULER_RUN() 	*((volatile uint32_t *)0xE000ED04) = 0x10000000; /* trigger PendSV, forces scheduler to run */

//note that stack frames must be aligned on 4 byte boundries
#define SDCARD_STACK_SIZE   	0x600
#define MAIN_STACK_SIZE				0x400
//external const unsigned int ISR_RET_ADDR;


//get the stack pointer of the next task
void * getNextTaskSP(void * cProcStack);

//get end of CSTACK location
extern void * __Vectors;

/*
//Reads the main stack pointer
static inline void * rd_stack_ptr(void){
  void * result=0;
  asm volatile ("MRS %0, msp\n\t"
      //"MOV r0, %0 \n\t"
      : "=r" (result) );
  return result;
}

//Writes stack pionter
static inline void wr_stack_ptr(void * ptr){
    asm volatile ("MSR msp, %0\n\t" : : "r" (ptr) );
}


//This saves the context on the PSP, the Cortex-M3 pushes the other registers using hardware
//"STMDB %0!, {r4-r11}\n\t"
inline void save_context(void){
  uint32_t scratch;
  asm volatile ("MRS r0, msp\n\t"
      "STMDB r0!, {r4-r11}\n\t"
      "MSR msp, r0\n\t"  : "=r" (scratch) );
}
 
//This loads the context from the PSP, the Cortex-M3 loads the other registers using hardware
inline void load_context(void){
  uint32_t scratch;
  asm volatile ("MRS r0, msp\n\t"
      "LDMFD r0!, {r4-r11}\n\t"
      "MSR msp, r0\n\t"  : "=r" (scratch) );
}
*/

#ifdef __cplusplus
}
#endif

#endif //__scheduler.h__


