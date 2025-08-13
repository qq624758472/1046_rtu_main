/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_trap_entry.S
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2023/12/14
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2023/12/14     1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the PLIC module.
 */
#define REGBYTES  4
#define STORE     sw
#define LOAD      lw
#define FSTORE    fsw
#define FLOAD     flw

    SECTION      `.text.entry`:CODE
    
    ALIGN       2
    
    PUBLIC      TrapEntry                      
    PUBLIC      SetMstatusMie   
    PUBLIC      ResetMstatusMie                     
    PUBLIC      Default_Int_Handler  
    EXTERN      PLIC_TrapHandler


/*
 * @brief Macro definition to save context when entering interrupt
 */
SAVE_CONTEXT MACRO

     addi sp, sp, -64*REGBYTES
 
     STORE x1, 0*REGBYTES(sp)
     STORE x2, 1*REGBYTES(sp)
     STORE x3, 2*REGBYTES(sp)
     STORE x4, 3*REGBYTES(sp)
     STORE x5, 4*REGBYTES(sp)
     STORE x6, 5*REGBYTES(sp)
     STORE x7, 6*REGBYTES(sp)
     STORE x8, 7*REGBYTES(sp)
     STORE x9, 8*REGBYTES(sp)
     
     STORE x10, 9*REGBYTES(sp)
     
     STORE x11, 10*REGBYTES(sp)
     STORE x12, 11*REGBYTES(sp)
     STORE x13, 12*REGBYTES(sp)
     STORE x14, 13*REGBYTES(sp)
     STORE x15, 14*REGBYTES(sp)
     STORE x16, 15*REGBYTES(sp)
     STORE x17, 16*REGBYTES(sp)
     STORE x18, 17*REGBYTES(sp)
     STORE x19, 18*REGBYTES(sp)
     STORE x20, 19*REGBYTES(sp)
     STORE x21, 20*REGBYTES(sp)
     STORE x22, 21*REGBYTES(sp)
     STORE x23, 22*REGBYTES(sp)
     STORE x24, 23*REGBYTES(sp)
     STORE x25, 24*REGBYTES(sp)
     STORE x26, 25*REGBYTES(sp)
     STORE x27, 26*REGBYTES(sp)
     STORE x28, 27*REGBYTES(sp)
     STORE x29, 28*REGBYTES(sp)
     STORE x30, 29*REGBYTES(sp)
     STORE x31, 30*REGBYTES(sp)

    FSTORE f0, 31*REGBYTES(sp)
    FSTORE f1, 32*REGBYTES(sp)
    FSTORE f2, 33*REGBYTES(sp)
    FSTORE f3, 34*REGBYTES(sp)
    FSTORE f4, 35*REGBYTES(sp)
    FSTORE f5, 36*REGBYTES(sp)
    FSTORE f6, 37*REGBYTES(sp)
    FSTORE f7, 38*REGBYTES(sp)
    FSTORE f8, 39*REGBYTES(sp)
    FSTORE f9, 40*REGBYTES(sp)
    FSTORE f10, 41*REGBYTES(sp)
    FSTORE f11, 42*REGBYTES(sp)
    FSTORE f12, 43*REGBYTES(sp)
    FSTORE f13, 44*REGBYTES(sp)
    FSTORE f14, 45*REGBYTES(sp)
    FSTORE f15, 46*REGBYTES(sp)
    FSTORE f16, 47*REGBYTES(sp)
    FSTORE f17, 48*REGBYTES(sp)
    FSTORE f18, 49*REGBYTES(sp)
    FSTORE f19, 50*REGBYTES(sp)
    FSTORE f20, 51*REGBYTES(sp)
    FSTORE f21, 52*REGBYTES(sp)
    FSTORE f22, 53*REGBYTES(sp)
    FSTORE f23, 54*REGBYTES(sp)
    FSTORE f24, 55*REGBYTES(sp)
    FSTORE f25, 56*REGBYTES(sp)
    FSTORE f26, 57*REGBYTES(sp)
    FSTORE f27, 58*REGBYTES(sp)
    FSTORE f28, 59*REGBYTES(sp)
    FSTORE f29, 60*REGBYTES(sp)
    FSTORE f30, 61*REGBYTES(sp)
    FSTORE f31, 62*REGBYTES(sp)
 
     csrr	a0, mcause
     csrr	t0, mepc
     STORE	t0, 63*REGBYTES(sp)
 ENDM

/*
 * @brief Macro definition to restore context when exiting interrupt
 */
RESTORE_CONTEXT MACRO
    LOAD	 t0, 63*REGBYTES(sp)
    csrw	 mepc,t0
    LOAD x1, 0*REGBYTES(sp)
    LOAD x2, 1*REGBYTES(sp)
    LOAD x3, 2*REGBYTES(sp)
    LOAD x4, 3*REGBYTES(sp)
    LOAD x5, 4*REGBYTES(sp)
    LOAD x6, 5*REGBYTES(sp)
    LOAD x7, 6*REGBYTES(sp)
    LOAD x8, 7*REGBYTES(sp)
    LOAD x9, 8*REGBYTES(sp)
    LOAD x10, 9*REGBYTES(sp)
    LOAD x11, 10*REGBYTES(sp)
    LOAD x12, 11*REGBYTES(sp)
    LOAD x13, 12*REGBYTES(sp)
    LOAD x14, 13*REGBYTES(sp)
    LOAD x15, 14*REGBYTES(sp)
    LOAD x16, 15*REGBYTES(sp)
    LOAD x17, 16*REGBYTES(sp)
    LOAD x18, 17*REGBYTES(sp)
    LOAD x19, 18*REGBYTES(sp)
    LOAD x20, 19*REGBYTES(sp)
    LOAD x21, 20*REGBYTES(sp)
    LOAD x22, 21*REGBYTES(sp)
    LOAD x23, 22*REGBYTES(sp)
    LOAD x24, 23*REGBYTES(sp)
    LOAD x25, 24*REGBYTES(sp)
    LOAD x26, 25*REGBYTES(sp)
    LOAD x27, 26*REGBYTES(sp)
    LOAD x28, 27*REGBYTES(sp)
    LOAD x29, 28*REGBYTES(sp)
    LOAD x30, 29*REGBYTES(sp)
    LOAD x31, 30*REGBYTES(sp)

    FLOAD f0, 31*REGBYTES(sp)
    FLOAD f1, 32*REGBYTES(sp)
    FLOAD f2, 33*REGBYTES(sp)
    FLOAD f3, 34*REGBYTES(sp)
    FLOAD f4, 35*REGBYTES(sp)
    FLOAD f5, 36*REGBYTES(sp)
    FLOAD f6, 37*REGBYTES(sp)
    FLOAD f7, 38*REGBYTES(sp)
    FLOAD f8, 39*REGBYTES(sp)
    FLOAD f9, 40*REGBYTES(sp)
    FLOAD f10, 41*REGBYTES(sp)
    FLOAD f11, 42*REGBYTES(sp)
    FLOAD f12, 43*REGBYTES(sp)
    FLOAD f13, 44*REGBYTES(sp)
    FLOAD f14, 45*REGBYTES(sp)
    FLOAD f15, 46*REGBYTES(sp)
    FLOAD f16, 47*REGBYTES(sp)
    FLOAD f17, 48*REGBYTES(sp)
    FLOAD f18, 49*REGBYTES(sp)
    FLOAD f19, 50*REGBYTES(sp)
    FLOAD f20, 51*REGBYTES(sp)
    FLOAD f21, 52*REGBYTES(sp)
    FLOAD f22, 53*REGBYTES(sp)
    FLOAD f23, 54*REGBYTES(sp)
    FLOAD f24, 55*REGBYTES(sp)
    FLOAD f25, 56*REGBYTES(sp)
    FLOAD f26, 57*REGBYTES(sp)
    FLOAD f27, 58*REGBYTES(sp)
    FLOAD f28, 59*REGBYTES(sp)
    FLOAD f29, 60*REGBYTES(sp)
    FLOAD f30, 61*REGBYTES(sp)
    FLOAD f31, 62*REGBYTES(sp)

    addi sp, sp, 64*REGBYTES
    mret
 ENDM

/*
 * @brief Interrupt entry function
 */
TrapEntry:
    /* save context and the value of mepc register,and transfer function parameter to PLIC_TrapHandler,the parameter is the value of mcause register. */
	 SAVE_CONTEXT

    /* Call the interrupt handler */
     call PLIC_TrapHandler
     
    /* Restore mepc values and restore context */
     RESTORE_CONTEXT

/*
 * @brief Global interrupt enable
 */
SetMstatusMie:
    csrsi mstatus, 0x08
    ret

/*
 * @brief Global interrupt disable
 */
ResetMstatusMie:
    csrci mstatus, 0x08
    ret

/*
 * @brief Default interrupt handler virtual function definition
 */
Default_Int_Handler:
Undef_Handler:
    j Undef_Handler


	