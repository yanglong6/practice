.text
.global _start
.global delayls
_start:
		b		reset
		ldr		pc,_undefined_instruction
		ldr		pc,_software_interrupt
		ldr		pc,_prefetch_abort
		ldr		pc,_data_abort
		ldr		pc,_not_used
		ldr		pc,_irq
		ldr		pc,_fiq

_undefined_instruction: .word  _undefined_instruction
_software_interrupt:	.word  _software_interrupt
_prefetch_abort:		.word  _prefetch_abort
_data_abort:			.word  _data_abort
_not_used:				.word  _not_used
_irq:					.word  _irq 
_fiq:					.word  _fiq


reset:
	ldr	r0,=0x43E00000
	mcr	p15,0,r0,c12,c0,0		@ Vector Base Address Register

init_stack:
	ldr		r0,stacktop         /*get stack top pointer*/

	/********svc mode stack********/
		mov		sp,r0
		sub		r0,#128*4          /*512 byte  for irq mode of stack*/
	/****irq mode stack**/
		msr		cpsr,#0xd2
		mov		sp,r0
		sub		r0,#128*4          /*512 byte  for irq mode of stack*/
	/***fiq mode stack***/
		msr 	cpsr,#0xd1
		mov		sp,r0
		sub		r0,#0
	/***abort mode stack***/
		msr		cpsr,#0xd7
		mov		sp,r0
		sub		r0,#0
	/***undefine mode stack***/
		msr		cpsr,#0xdb
		mov		sp,r0
		sub		r0,#0
   /*** sys mode and usr mode stack ***/
		msr		cpsr,#0x10
		mov		sp,r0             /*1024 byte  for user mode of stack*/

		b		main

	.align	4

	/****  swi_interrupt handler  ****/

delayls:
	mov r0, #1
	ldr r1, =0x3ffffff
delayls_loop:
	cmp r0, r1
	add r0, r0, #1
	blt delayls_loop
delayls_end:
	mov pc, lr

stacktop:    .word 		stack+4*512

.data

stack:	 .space  4*512
.end
