
	.text
	ldr r0,=0x11000c40
	ldr r1,[r0]
	bic r1, #0xf0000000
	orr r1, #0x10000000
	str r1, [r0] 
close:
	@GPX2DAT  配置为输出高电平
	ldr r0, =0x11000c44
	ldr r1, [r0]
	bic r1, #0x80
	str r1, [r0]
	bl loop

open:	
	ldr r0, =0x11000c44
	ldr r1, [r0]
	orr r1, #0x80
	str r1, [r0]
	
	bl loop
	b close

loop:
	mov r3,#0
	ldr r4,=0xfffffff
loop1:
	cmp r3,r4
	add r3,r3,#1
	blt loop1
loop_end:
	mov pc,lr


	.end
	
	
