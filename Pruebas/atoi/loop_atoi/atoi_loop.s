	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
$Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.globl	atoi_loop
$LFB0 = .
	.file 1 "atoi_loop.c"
	.loc 1 3 0
	.cfi_startproc
	.set	nomips16
	.set	nomicromips
	.ent	atoi_loop
	.type	atoi_loop, @function
atoi_loop:
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$fp,20($sp)
	.cfi_offset 30, -4
	move	$fp,$sp
	.cfi_def_cfa_register 30
	sw	$4,24($fp)
	.loc 1 4 0
	sw	$0,8($fp)
	.loc 1 6 0
	b	$L2
	nop

$L3:
	.loc 1 8 0
	lw	$3,8($fp)
	move	$2,$3
	sll	$2,$2,2
	addu	$2,$2,$3
	sll	$2,$2,1
	move	$3,$2
	lw	$2,24($fp)
	lb	$2,0($2)
	addiu	$2,$2,-48
	addu	$2,$3,$2
	sw	$2,8($fp)
	.loc 1 9 0
	lw	$2,24($fp)
	addiu	$2,$2,1
	sw	$2,24($fp)
$L2:
	.loc 1 6 0
	lw	$2,24($fp)
	lb	$2,0($2)
	bne	$2,$0,$L3
	nop

	.loc 1 12 0
	lw	$2,8($fp)
	.loc 1 13 0
	move	$sp,$fp
	.cfi_def_cfa_register 29
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	.cfi_restore 30
	.cfi_def_cfa_offset 0
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	atoi_loop
	.cfi_endproc
$LFE0:
	.size	atoi_loop, .-atoi_loop
$Letext0:
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.4byte	0x6a
	.2byte	0x4
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$LASF1
	.byte	0xc
	.4byte	$LASF2
	.4byte	$LASF3
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	$Ldebug_line0
	.uleb128 0x2
	.4byte	$LASF4
	.byte	0x1
	.byte	0x2
	.4byte	0x59
	.4byte	$LFB0
	.4byte	$LFE0-$LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x59
	.uleb128 0x3
	.ascii	"p\000"
	.byte	0x1
	.byte	0x2
	.4byte	0x60
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x4
	.ascii	"num\000"
	.byte	0x1
	.byte	0x4
	.4byte	0x59
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x6
	.byte	0x4
	.4byte	0x66
	.uleb128 0x7
	.byte	0x1
	.byte	0x6
	.4byte	$LASF0
	.byte	0
	.section	.debug_abbrev,"",@progbits
$Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
$LASF2:
	.ascii	"atoi_loop.c\000"
$LASF1:
	.ascii	"GNU C11 6.3.0 20170516 -meb -march=mips32r2 -mfpxx -mlls"
	.ascii	"c -mno-lxc1-sxc1 -mips32r2 -mabi=32 -g -O0\000"
$LASF3:
	.ascii	"/home/tomas/atoi/loop_atoi\000"
$LASF0:
	.ascii	"char\000"
$LASF4:
	.ascii	"atoi_loop\000"
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
