* NO_APP
RUNS_HUMAN_VERSION	equ	3
	.cpu 68000
	.include doscall.inc
	.include iocscall.inc
* X68 GCC Develop
	.file	"main.c"				*	.file	"main.c"
							*| GNU C17 (GCC) version 10.2.0 (m68k-elf)
							*|	compiled by GNU C version 12.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP
							*
							*| GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
							*| options passed:  -I C:/msys64/home/gespe/xdev68k/include/xc
							*| -I C:/msys64/home/gespe/xdev68k/include/xdev68k
							*| -iprefix c:\msys64\home\gespe\xdev68k\m68k-toolchain\bin\../lib/gcc/m68k-elf/10.2.0/
							*| -MD _build/m68000/main.m68k-gas.d -MF _build/m68000/main.d -MP
							*| -MT _build/m68000/main.o main.c -mcpu=68000
							*| -auxbase-strip _build/m68000/main.m68k-gas.s -Os
							*| -Wno-builtin-declaration-mismatch -fcall-used-d2 -fcall-used-a2
							*| -finput-charset=cp932 -fexec-charset=cp932 -fverbose-asm
							*| options enabled:  -faggressive-loop-optimizations -fallocation-dce
							*| -fauto-inc-dec -fbranch-count-reg -fcaller-saves -fcode-hoisting
							*| -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
							*| -fcrossjumping -fcse-follow-jumps -fdefer-pop
							*| -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
							*| -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
							*| -feliminate-unused-debug-types -fexpensive-optimizations
							*| -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
							*| -fgcse-lm -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads
							*| -fident -fif-conversion -fif-conversion2 -findirect-inlining -finline
							*| -finline-atomics -finline-functions -finline-functions-called-once
							*| -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-icf
							*| -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
							*| -fipa-ra -fipa-reference -fipa-reference-addressable -fipa-sra
							*| -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
							*| -fira-share-save-slots -fira-share-spill-slots
							*| -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
							*| -fleading-underscore -flifetime-dse -flra-remat -fmath-errno
							*| -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
							*| -fomit-frame-pointer -foptimize-sibling-calls -fpartial-inlining
							*| -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays -freg-struct-return
							*| -freorder-blocks -freorder-functions -frerun-cse-after-loop
							*| -fsched-critical-path-heuristic -fsched-dep-count-heuristic
							*| -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
							*| -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
							*| -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
							*| -fshow-column -fshrink-wrap -fshrink-wrap-separate -fsigned-zeros
							*| -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop -fssa-phiopt
							*| -fstdarg-opt -fstore-merging -fstrict-aliasing
							*| -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
							*| -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
							*| -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-dce
							*| -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
							*| -ftree-loop-distribute-patterns -ftree-loop-if-convert -ftree-loop-im
							*| -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
							*| -ftree-phiprop -ftree-pre -ftree-pta -ftree-reassoc -ftree-scev-cprop
							*| -ftree-sink -ftree-slsr -ftree-sra -ftree-switch-conversion
							*| -ftree-tail-merge -ftree-ter -ftree-vrp -funit-at-a-time -fverbose-asm
							*| -fzero-initialized-in-bss -mstrict-align
							*
	.text						*	.text
	.data						*	.section	.rodata.str1.1,"aMS",@progbits,1
_?LC0:							*.LC0:
	.dc.b $64,$75,$6d,$70,$2e,$78,$20,$56
	.dc.b $65,$72,$73,$69,$6f,$6e,$20,$30
	.dc.b $2e,$35,$30,$0a
	.dc.b $00					*	.string	"dump.x Version 0.50\n"
_?LC1:							*.LC1:
	.dc.b $44,$75,$6d,$70,$20,$46,$69,$6c
	.dc.b $65,$3a,$20,$5b,$20,$25,$73,$20
	.dc.b $5d,$0a
	.dc.b $00					*	.string	"Dump File: [ %s ]\n"
_?LC2:							*.LC2:
	.dc.b $72,$62
	.dc.b $00					*	.string	"rb"
_?LC3:							*.LC3:
	.dc.b $43,$61,$6e,$6e,$6f,$74,$20,$6f
	.dc.b $70,$65,$6e,$20,$74,$68,$65,$20
	.dc.b $66,$69,$6c,$65,$2e,$2e,$2e
	.dc.b $00					*	.string	"Cannot open the file..."
_?LC4:							*.LC4:
	.dc.b $41,$44,$44,$52,$45,$53,$53,$20
	.dc.b $20,$20,$2b,$30,$20,$2b,$31,$20
	.dc.b $2b,$32,$20,$2b,$33,$20,$2b,$34
	.dc.b $20,$2b,$35,$20,$2b,$36,$20,$2b
	.dc.b $37,$20,$2b,$38,$20,$2b,$39,$20
	.dc.b $2b,$41,$20,$2b,$42,$20,$2b,$43
	.dc.b $20,$2b,$44,$20,$2b,$45,$20,$2b
	.dc.b $46,$20,$20,$20,$30,$31,$32,$33
	.dc.b $34,$35,$36,$37,$38,$39,$41,$42
	.dc.b $43,$44,$45,$46
	.dc.b $00					*	.string	"ADDRESS   +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F   0123456789ABCDEF"
_?LC5:							*.LC5:
	.dc.b $25,$30,$38,$58,$3a,$20
	.dc.b $00					*	.string	"%08X: "
_?LC6:							*.LC6:
	.dc.b $25,$30,$32,$58,$20
	.dc.b $00					*	.string	"%02X "
_?LC7:							*.LC7:
	.dc.b $20,$20,$20
	.dc.b $00					*	.string	"   "
_?LC8:							*.LC8:
	.dc.b $20,$20
	.dc.b $00					*	.string	"  "
	.text						*	.section	.text.startup,"ax",@progbits
	.align	2					*	.align	2
	.xref __main	* workaround for libc.
	.globl	_main					*	.globl	main
							*	.type	main, @function
_main:							*main:
	lea (-544,sp),sp				*	lea (-544,%sp),%sp	|,
	movem.l d3/d4/d5/d6/a3/a4/a5/a6,-(sp)		*	movem.l #7710,-(%sp)	|,
							*| main.c:14: 	printf("dump.x Version 0.50\n\n");
	pea _?LC0					*	pea .LC0		|
	lea _puts,a4					*	lea puts,%a4	|, tmp54
	jbsr (a4)					*	jsr (%a4)		| tmp54
	move.l 588(sp),a3				*	move.l 588(%sp),%a3	| argv, ivtmp.31
	addq.l #4,a3					*	addq.l #4,%a3	|, ivtmp.31
							*| main.c:16: 	for (i = 1; i < argc; i++)
	addq.l #4,sp					*	addq.l #4,%sp	|,
							*| main.c:16: 	for (i = 1; i < argc; i++)
	moveq #1,d3					*	moveq #1,%d3	|, i
							*| main.c:20: 			strcpy(sName, argv[i]);
	moveq #64,d4					*	moveq #64,%d4	|, tmp85
	add.l sp,d4					*	add.l %sp,%d4	|, tmp85
	lea _strcpy,a5					*	lea strcpy,%a5	|, tmp86
_?L2:							*.L2:
							*| main.c:16: 	for (i = 1; i < argc; i++)
	cmp.l 580(sp),d3				*	cmp.l 580(%sp),%d3	| argc, i
	jblt _?L4					*	jlt .L4		|
							*| main.c:26: 		printf("Dump File: [ %s ]\n", sName);
	moveq #64,d3					*	moveq #64,%d3	|, tmp57
	add.l sp,d3					*	add.l %sp,%d3	|, tmp57
	move.l d3,-(sp)					*	move.l %d3,-(%sp)	| tmp57,
	pea _?LC1					*	pea .LC1		|
	lea _printf,a3					*	lea printf,%a3	|, tmp58
	jbsr (a3)					*	jsr (%a3)		| tmp58
							*| main.c:27: 		if (sName[0] == 0) break;
	addq.l #8,sp					*	addq.l #8,%sp	|,
	tst.b 64(sp)					*	tst.b 64(%sp)	| sName[0]
	jbeq _?L1					*	jeq .L1		|
							*| main.c:28: 		fp = fopen(sName, "rb");
	pea _?LC2					*	pea .LC2		|
	move.l d3,-(sp)					*	move.l %d3,-(%sp)	| tmp57,
	jbsr _fopen					*	jsr fopen		|
	move.l d0,d4					*	move.l %d0,%d4	| tmp87, fp
							*| main.c:29: 		if (fp == 0)
	addq.l #8,sp					*	addq.l #8,%sp	|,
	jbne _?L6					*	jne .L6		|
							*| main.c:31: 			printf("Cannot open the file...\n");
	pea _?LC3					*	pea .LC3		|
	jbsr (a4)					*	jsr (%a4)		| tmp78
_?L19:							*.L19:
							*| main.c:61: 		fclose(fp);
	addq.l #4,sp					*	addq.l #4,%sp	|,
_?L1:							*.L1:
							*| main.c:65: }
	movem.l (sp)+,d3/d4/d5/d6/a3/a4/a5/a6		*	movem.l (%sp)+,#30840	|,
	lea (544,sp),sp					*	lea (544,%sp),%sp	|,
	rts						*	rts
_?L4:							*.L4:
							*| main.c:18: 		if (argv[i][0] != '-')
	move.l (a3)+,a0					*	move.l (%a3)+,%a0	| MEM[base: _61, offset: 0B], _4
							*| main.c:18: 		if (argv[i][0] != '-')
	cmp.b #45,(a0)					*	cmp.b #45,(%a0)	|, *_4
	jbeq _?L3					*	jeq .L3		|
							*| main.c:20: 			strcpy(sName, argv[i]);
	move.l a0,-(sp)					*	move.l %a0,-(%sp)	| _4,
	move.l d4,-(sp)					*	move.l %d4,-(%sp)	| tmp85,
	jbsr (a5)					*	jsr (%a5)		| tmp86
	addq.l #8,sp					*	addq.l #8,%sp	|,
_?L3:							*.L3:
							*| main.c:16: 	for (i = 1; i < argc; i++)
	addq.l #1,d3					*	addq.l #1,%d3	|, i
	jbra _?L2					*	jra .L2		|
_?L6:							*.L6:
							*| main.c:35: 		printf("ADDRESS   +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F   0123456789ABCDEF\n");
	pea _?LC4					*	pea .LC4		|
	jbsr (a4)					*	jsr (%a4)		| tmp78
	addq.l #4,sp					*	addq.l #4,%sp	|,
							*| main.c:13: 	iPage = 0;
	sub.l a5,a5					*	sub.l %a5,%a5	| iPage
							*| main.c:38: 			p = fread(buf, 1, 16, fp);
	moveq #32,d5					*	moveq #32,%d5	|, tmp63
	add.l sp,d5					*	add.l %sp,%d5	|, tmp63
	move.l #_fread,d6				*	move.l #fread,%d6	|, tmp64
	lea _putchar,a6					*	lea putchar,%a6	|, tmp84
_?L17:							*.L17:
	move.l d4,-(sp)					*	move.l %d4,-(%sp)	| fp,
	pea 16.w					*	pea 16.w		|
	pea 1.w						*	pea 1.w		|
	move.l d5,-(sp)					*	move.l %d5,-(%sp)	| tmp63,
	move.l d6,a0					*	move.l %d6,%a0	| tmp64,
	jbsr (a0)					*	jsr (%a0)		|
	move.l d0,d3					*	move.l %d0,%d3	| tmp88, p
							*| main.c:39: 			if (p == 0) break;
	lea (16,sp),sp					*	lea (16,%sp),%sp	|,
	jbeq _?L7					*	jeq .L7		|
							*| main.c:40: 			printf("%08X: ",iPage);
	move.l a5,-(sp)					*	move.l %a5,-(%sp)	| iPage,
	pea _?LC5					*	pea .LC5		|
	jbsr (a3)					*	jsr (%a3)		| tmp79
							*| main.c:41: 			for(i = 0; i < p ; i++)
	addq.l #8,sp					*	addq.l #8,%sp	|,
							*| main.c:41: 			for(i = 0; i < p ; i++)
	sub.l a4,a4					*	sub.l %a4,%a4	| i
_?L8:							*.L8:
							*| main.c:41: 			for(i = 0; i < p ; i++)
	cmp.l a4,d3					*	cmp.l %a4,%d3	| i, p
	jbgt _?L9					*	jgt .L9		|
	move.l d3,a4					*	move.l %d3,%a4	| p, i
	tst.l d3					*	tst.l %d3	| p
	jbge _?L11					*	jge .L11		|
	sub.l a4,a4					*	sub.l %a4,%a4	| i
_?L11:							*.L11:
							*| main.c:45: 			for(; i < 16 ; i++)
	moveq #15,d0					*	moveq #15,%d0	|,
	cmp.l a4,d0					*	cmp.l %a4,%d0	| i,
	jbge _?L12					*	jge .L12		|
							*| main.c:50: 			printf("  ");
	pea _?LC8					*	pea .LC8		|
	jbsr (a3)					*	jsr (%a3)		| tmp79
							*| main.c:52: 			for(i = 0; i < p ; i++)
	addq.l #4,sp					*	addq.l #4,%sp	|,
							*| main.c:52: 			for(i = 0; i < p ; i++)
	sub.l a4,a4					*	sub.l %a4,%a4	| i
_?L13:							*.L13:
							*| main.c:52: 			for(i = 0; i < p ; i++)
	cmp.l a4,d3					*	cmp.l %a4,%d3	| i, p
	jbgt _?L16					*	jgt .L16		|
							*| main.c:57: 			printf("\n");
	pea 10.w					*	pea 10.w		|
	jbsr (a6)					*	jsr (%a6)		| tmp84
							*| main.c:58: 			iPage += 16;
	lea (16,a5),a5					*	lea (16,%a5),%a5	|, iPage
							*| main.c:38: 			p = fread(buf, 1, 16, fp);
	addq.l #4,sp					*	addq.l #4,%sp	|,
	jbra _?L17					*	jra .L17		|
_?L9:							*.L9:
							*| main.c:43: 				printf("%02X ", buf[i]);
	moveq #0,d0					*	moveq #0,%d0	| MEM[symbol: buf, index: _59, offset: 0B]
	move.b (a4,d5.l),d0				*	move.b (%a4,%d5.l),%d0	| MEM[symbol: buf, index: _59, offset: 0B], MEM[symbol: buf, index: _59, offset: 0B]
	move.l d0,-(sp)					*	move.l %d0,-(%sp)	| MEM[symbol: buf, index: _59, offset: 0B],
	pea _?LC6					*	pea .LC6		|
	jbsr (a3)					*	jsr (%a3)		| tmp79
							*| main.c:41: 			for(i = 0; i < p ; i++)
	addq.l #1,a4					*	addq.l #1,%a4	|, i
	addq.l #8,sp					*	addq.l #8,%sp	|,
	jbra _?L8					*	jra .L8		|
_?L12:							*.L12:
							*| main.c:47: 				printf("   ");
	pea _?LC7					*	pea .LC7		|
	jbsr (a3)					*	jsr (%a3)		| tmp79
							*| main.c:45: 			for(; i < 16 ; i++)
	addq.l #1,a4					*	addq.l #1,%a4	|, i
	addq.l #4,sp					*	addq.l #4,%sp	|,
	jbra _?L11					*	jra .L11		|
_?L16:							*.L16:
							*| main.c:54: 				if ((buf[i] >= 0x20) && (buf[i] <= 'z')) printf("%c", buf[i]);
	move.b (a4,d5.l),d0				*	move.b (%a4,%d5.l),%d0	| MEM[symbol: buf, index: _60, offset: 0B], _10
							*| main.c:54: 				if ((buf[i] >= 0x20) && (buf[i] <= 'z')) printf("%c", buf[i]);
	move.b d0,d1					*	move.b %d0,%d1	| _10, tmp72
	add.b #-32,d1					*	add.b #-32,%d1	|, tmp72
							*| main.c:54: 				if ((buf[i] >= 0x20) && (buf[i] <= 'z')) printf("%c", buf[i]);
	cmp.b #90,d1					*	cmp.b #90,%d1	|, tmp72
	jbhi _?L14					*	jhi .L14		|
							*| main.c:54: 				if ((buf[i] >= 0x20) && (buf[i] <= 'z')) printf("%c", buf[i]);
	and.l #255,d0					*	and.l #255,%d0	|, _10
	move.l d0,-(sp)					*	move.l %d0,-(%sp)	| _10,
_?L18:							*.L18:
							*| main.c:55: 				else printf(".");
	jbsr (a6)					*	jsr (%a6)		| tmp84
	addq.l #4,sp					*	addq.l #4,%sp	|,
							*| main.c:52: 			for(i = 0; i < p ; i++)
	addq.l #1,a4					*	addq.l #1,%a4	|, i
	jbra _?L13					*	jra .L13		|
_?L14:							*.L14:
							*| main.c:55: 				else printf(".");
	pea 46.w					*	pea 46.w		|
	jbra _?L18					*	jra .L18		|
_?L7:							*.L7:
							*| main.c:61: 		fclose(fp);
	move.l d4,-(sp)					*	move.l %d4,-(%sp)	| fp,
	jbsr _fclose					*	jsr fclose		|
	jbra _?L19					*	jra .L19		|
							*	.size	main, .-main
							*	.ident	"GCC: (GNU) 10.2.0"
