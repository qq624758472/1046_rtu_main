/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_startup.S
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2023/11/21
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2023/11/21     1.0     build this module
 * Description:     This file implements the startup operation,such as pointer configuration, data segment initialization, interrupt configuration, and clock configuration are complete.
 */
    
    SECTION `.init`:CODE
    PUBLIC  _start
    
    EXTERN   main
    
    EXTERN RW_DATA$$Limit
    EXTERN CSTACK$$Limit
    EXTERN RW_DATA$$Base
    EXTERN RW_DATA$$Length
    EXTERN RW_DATA_INIT$$Base
    EXTERN RW_BSS$$Base
    EXTERN RW_BSS$$Length
    EXTERN RW_BSS$$Limit
    EXTERN HEAP$$Base
    EXTERN SystemInit
    EXTERN TrapEntry
    EXTERN  __iar_static_base$$GPREL
    
    ALIGN  2
    
_start:
        .option   norvc;
        la gp, __iar_static_base$$GPREL
        la sp, CSTACK$$Limit

	/* Load data section */
	la a0, RW_DATA_INIT$$Base
	la a1, RW_DATA$$Base
	la a2, RW_DATA$$Limit
	bgeu a1, a2, ClearBssSection
step1:
	lw t0, 0(a0)
	sw t0, 0(a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, step1
        
ClearBssSection:
	/* Clear bss section */
	la a0, RW_BSS$$Base
	la a1, RW_BSS$$Limit
	bgeu a0, a1, step3
step2:
	sw zero, 0(a0)
	addi a0, a0, 4
	bltu a0, a1, step2
step3:
    /* Enable the CPU global interrupt,[3]MIE = 1, [7]MPIE = 1, [11\12]MPP = 11 ,[13\14]FS = 01 */
	lui	a5,0x4
	addi a5,a5,-1912 //3888 
	csrw mstatus,a5
    
	/* [11]MEIE enable external interrupt PLIC */
	lui	a5,0x1
	addi a5,a5,-2048 //800 
	csrw mie,a5
    
    /* Set the exception entry function */
    la t0, TrapEntry
    csrw mtvec, t0
    
	//call SystemInit
    call main


loop:
        j loop
        
        END
