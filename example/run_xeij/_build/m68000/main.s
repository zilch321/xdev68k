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
							*| 渡されたオプション:  -I C:/msys64/home/gespe/xdev68k/include/xc
							*| -I C:/msys64/home/gespe/xdev68k/include/xdev68k
							*| -iprefix c:\msys64\home\gespe\xdev68k\m68k-toolchain\bin\../lib/gcc/m68k-elf/10.2.0/
							*| -MD _build/m68000/main.m68k-gas.d -MF _build/m68000/main.d -MP
							*| -MT _build/m68000/main.o main.c -mcpu=68000
							*| -auxbase-strip _build/m68000/main.m68k-gas.s -Os
							*| -Wno-builtin-declaration-mismatch -fcall-used-d2 -fcall-used-a2
							*| -finput-charset=cp932 -fexec-charset=cp932 -fverbose-asm
							*| 有効オプション:  -faggressive-loop-optimizations -fallocation-dce
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
	.dc.b $83,$4f,$83,$89,$83,$74,$83,$42
	.dc.b $83,$4e,$83,$58,$82,$f0,$88,$b5
	.dc.b $82,$a4,$83				*	.ascii	"\203O\203\211\203t\203B\203N\203X\202\360\210\265\202\244\203"
	.dc.b $76,$83,$8d,$83,$4f,$83,$89,$83
	.dc.b $80,$93,$99,$82,$c5,$58,$36,$38
	.dc.b $4b,$82,$cc,$89				*	.ascii	"v\203\215\203O\203\211\203\200\223\231\202\305X68K\202\314\211"
	.dc.b $e6,$96,$ca,$82,$c9,$92,$bc,$90
	.dc.b $da,$83,$66,$83,$6f,$83,$62,$83
	.dc.b $4f,$83					*	.ascii	"\346\226\312\202\311\222\274\220\332\203f\203o\203b\203O\203"
	.dc.b $8d,$83,$4f,$82,$f0,$8f,$6f,$97
	.dc.b $cd,$82,$b7,$82,$e9,$82,$c6,$81
	.dc.b $41,$82					*	.ascii	"\215\203O\202\360\217o\227\315\202\267\202\351\202\306\201A\202"
	.dc.b $b1,$82,$cc,$82,$e6,$82,$a4,$82
	.dc.b $c9,$91,$e5,$82,$ab,$82,$c8		*	.ascii	"\261\202\314\202\346\202\244\202\311\221\345\202\253\202\310"
	.dc.b $95,$b6,$8e,$9a,$82,$c5,$95,$5c
	.dc.b $8e,$a6,$82,$b3,$82,$ea,$82,$bd		*	.ascii	"\225\266\216\232\202\305\225\\\216\246\202\263\202\352\202\275"
	.dc.b $82,$e8,$81,$41,$83,$65,$83,$4c
	.dc.b $83,$58,$83,$67,$83			*	.ascii	"\202\350\201A\203e\203L\203X\203g\203"
	.dc.b $70,$83,$8c,$83,$62,$83,$67,$82
	.dc.b $cc,$90,$dd,$92,$e8,$8e,$9f,$91
	.dc.b $e6,$82,$c5,$82,$cd,$93,$c7,$82
	.dc.b $dd,$82,$c3,$82,$e7,$82,$ad,$82
	.dc.b $c8,$82,$e9,$82,$c8,$82,$c7,$81
	.dc.b $41,$97,$6c,$81,$58,$82,$c8,$96
	.dc.b $e2,$91,$e8,$82,$aa,$82,$a0,$82
	.dc.b $e8,$82,$dc,$82,$b7,$81,$42,$0a
	.dc.b $0a,$83,$66,$83,$6f,$83,$62,$83
	.dc.b $4f,$83,$8d,$83,$4f,$82,$cd,$58
	.dc.b $36,$38,$4b,$82,$cc,$89,$e6,$96
	.dc.b $ca,$82,$c9,$92,$bc,$90,$da,$8f
	.dc.b $6f,$97,$cd,$82,$b9,$82,$b8,$81
	.dc.b $41,$73,$74,$64,$61,$75,$78,$82
	.dc.b $c9,$8f,$6f,$97,$cd,$82,$b5,$81
	.dc.b $41,$83,$7a,$83,$58,$83,$67,$91
	.dc.b $a4,$82,$cc,$83,$5e,$81,$5b,$83
	.dc.b $7e,$83,$69,$83,$8b,$83,$45,$83
	.dc.b $42,$83,$93,$83,$68,$83,$45,$8f
	.dc.b $e3,$82,$c5,$8a,$6d,$94,$46,$82
	.dc.b $b7,$82,$e9,$82,$b1,$82,$c6,$82
	.dc.b $f0,$83,$49,$83,$58,$83,$58,$83
	.dc.b $81,$82,$b5,$82,$dc,$82,$b7,$81
	.dc.b $42,$0a,$0a,$88,$c8,$89,$ba,$81
	.dc.b $41,$73,$74,$64,$61,$75,$78,$82
	.dc.b $c9,$8f,$6f,$97,$cd,$82,$b5,$82
	.dc.b $dc,$82,$b7,$82,$cc,$82,$c5,$83
	.dc.b $5e,$81,$5b,$83,$7e,$83,$69,$83
	.dc.b $8b,$8f,$6f,$97,$cd,$91,$a4,$82
	.dc.b $f0,$82,$b2,$8a,$6d,$94,$46,$82
	.dc.b $ad,$82,$be,$82,$b3,$82,$a2,$81
	.dc.b $42,$0a,$28,$91,$b1,$82,$ad,$29
	.dc.b $00					*	.string	"p\203\214\203b\203g\202\314\220\335\222\350\216\237\221\346\202\305\202\315\223\307\202\335\202\303\202\347\202\255\202
							*		\310\202\351\202\310\202\307\201A\227l\201X\202\310\226\342\221\350\202\252\202\240\202\350\202\334\202\267\201B\n\n\203f\203o\20
							*		3b\203O\203\215\203O\202\315X68K\202\314\211\346\226\312\202\311\222\274\220\332\217o\227\315\202\271\202\270\201Astdaux\202\311\
							*		217o\227\315\202\265\201A\203z\203X\203g\221\244\202\314\203^\201[\203~\203i\203\213\203E\203B\203\223\203h\203E\217\343\202\305\
							*		212m\224F\202\267\202\351\202\261\202\306\202\360\203I\203X\203X\203\201\202\265\202\334\202\267\201B\n\n\210\310\211\272\201Astd
							*		aux\202\311\217o\227\315\202\265\202\334\202\267\202\314\202\305\203^\201[\203~\203i\203\213\217o\227\315\221\244\202\360\202\262
							*		\212m\224F\202\255\202\276\202\263\202\242\201B\n(\221\261\202\255)"
_?LC1:							*.LC1:
	.dc.b $0a,$28,$91,$b1,$82,$ab,$29,$0a
	.dc.b $73,$74,$64,$61,$75,$78,$82,$d6
	.dc.b $82,$cc,$83,$8d,$83,$4f,$8f		*	.ascii	"\n(\221\261\202\253)\nstdaux\202\326\202\314\203\215\203O\217"
	.dc.b $6f,$97,$cd,$82,$cd,$81,$41,$66
	.dc.b $70,$72,$69,$6e,$74,$66,$82,$cc
	.dc.b $91,$e6,$88,$ea,$88,$f8			*	.ascii	"o\227\315\202\315\201Afprintf\202\314\221\346\210\352\210\370"
	.dc.b $90,$94,$82,$c9,$73,$74,$64,$61
	.dc.b $75,$78,$82,$f0,$8e,$77,$92,$e8
	.dc.b $82,$b7,$82,$e9,$82			*	.ascii	"\220\224\202\311stdaux\202\360\216w\222\350\202\267\202\351\202"
	.dc.b $be,$82,$af,$82,$c5,$89,$c2,$94
	.dc.b $5c,$82,$c5,$82,$b7,$81,$42,$73
	.dc.b $74,$64,$61,$75				*	.ascii	"\276\202\257\202\305\211\302\224\\\202\305\202\267\201Bstdau"
	.dc.b $78,$82,$cd,$96,$7b,$97,$88,$81
	.dc.b $41					*	.ascii	"x\202\315\226{\227\210\201A"
	.dc.b $52,$53,$2d,$32,$33,$32,$43,$8c
	.dc.b $6f,$97,$52,$82,$c5,$58,$36,$38
	.dc.b $4b,$82,$f0,$83,$8a,$83,$82,$81
	.dc.b $5b,$83,$67,$91,$80,$8d,$ec,$82
	.dc.b $b7,$82,$e9,$97,$70,$93,$72,$82
	.dc.b $c5,$97,$98,$97,$70,$82,$b3,$82
	.dc.b $ea,$82,$e9,$83,$58,$83,$67,$83
	.dc.b $8a,$81,$5b,$83,$80,$82,$c5,$82
	.dc.b $b7,$81,$42,$58,$36,$38,$4b,$91
	.dc.b $53,$90,$b7,$8a,$fa,$82,$cc,$93
	.dc.b $96,$8e,$9e,$81,$41,$52,$53,$2d
	.dc.b $32,$33,$32,$43,$82,$aa,$8d,$4c
	.dc.b $82,$ad,$8a,$88,$97,$70,$82,$b3
	.dc.b $82,$ea,$82,$bd,$82,$b1,$82,$c6
	.dc.b $82,$e0,$82,$a0,$82,$e8,$81,$41
	.dc.b $48,$75,$6d,$61,$6e,$36,$38,$6b
	.dc.b $82,$c9,$82,$cd,$73,$74,$64,$61
	.dc.b $75,$78,$82,$f0,$83,$54,$83,$7c
	.dc.b $81,$5b,$83,$67,$82,$b7,$82,$e9
	.dc.b $91,$bd,$82,$ad,$82,$cc,$8b,$40
	.dc.b $94,$5c,$82,$aa,$94,$f5,$82,$ed
	.dc.b $82,$c1,$82,$c4,$82,$a2,$82,$dc
	.dc.b $82,$b7,$81,$42,$82,$ba,$82,$d0
	.dc.b $82,$bb,$82,$ea,$82,$e7,$82,$f0
	.dc.b $8a,$88,$97,$70,$82,$b5,$82,$c4
	.dc.b $8c,$f8,$97,$a6,$93,$49,$82,$c8
	.dc.b $83,$66,$83,$6f,$83,$62,$83,$4f
	.dc.b $8a,$c2,$8b,$ab,$8d,$5c,$92,$7a
	.dc.b $82,$c9,$83,$60,$83,$83,$83,$8c
	.dc.b $83,$93,$83,$57,$82,$b5,$82,$c4
	.dc.b $82,$dd,$82,$c4,$82,$ad,$82,$be
	.dc.b $82,$b3,$82,$a2,$81,$42,$0a,$0a
	.dc.b $00					*	.string	"RS-232C\214o\227R\202\305X68K\202\360\203\212\203\202\201[\203g\221\200\215\354\202\267\202\351\227p\223r\202\305\227\2
							*		30\227p\202\263\202\352\202\351\203X\203g\203\212\201[\203\200\202\305\202\267\201BX68K\221S\220\267\212\372\202\314\223\226\216\
							*		236\201ARS-232C\202\252\215L\202\255\212\210\227p\202\263\202\352\202\275\202\261\202\306\202\340\202\240\202\350\201AHuman68k\20
							*		2\311\202\315stdaux\202\360\203T\203|\201[\203g\202\267\202\351\221\275\202\255\202\314\213@\224\\\202\252\224\365\202\355\202\30
							*		1\202\304\202\242\202\334\202\267\201B\202\272\202\320\202\273\202\352\202\347\202\360\212\210\227p\202\265\202\304\214\370\227\2
							*		46\223I\202\310\203f\203o\203b\203O\212\302\213\253\215\\\222z\202\311\203`\203\203\203\214\203\223\203W\202\265\202\304\202\335\
							*		202\304\202\255\202\276\202\263\202\242\201B\n\n"
	.text						*	.section	.text.startup,"ax",@progbits
	.align	2					*	.align	2
	.xref __main	* workaround for libc.
	.globl	_main					*	.globl	main
							*	.type	main, @function
_main:							*main:
	move.l a4,-(sp)					*	move.l %a4,-(%sp)	|,
	move.l a3,-(sp)					*	move.l %a3,-(%sp)	|,
							*| main.c:39: 	CRTMOD(6);
	pea 6.w						*	pea 6.w		|
	lea _CRTMOD,a3					*	lea CRTMOD,%a3	|, tmp35
	jbsr (a3)					*	jsr (%a3)		| tmp35
							*| main.c:42: 	TPALET(3, 0x5555);
	pea 21845.w					*	pea 21845.w		|
	pea 3.w						*	pea 3.w		|
	jbsr _TPALET					*	jsr TPALET		|
							*| main.c:48: 	printf(
	pea _?LC0					*	pea .LC0		|
	jbsr _puts					*	jsr puts		|
							*| main.c:68: 	fprintf(
	pea __iob+78					*	pea _iob+78		|
	pea _?LC1					*	pea .LC1		|
	jbsr _fputs					*	jsr fputs		|
							*| main.c:81: 	while (INPOUT(0xFF) == 0) {}
	lea (24,sp),sp					*	lea (24,%sp),%sp	|,
							*| main.c:81: 	while (INPOUT(0xFF) == 0) {}
	lea _INPOUT,a4					*	lea INPOUT,%a4	|, tmp39
_?L2:							*.L2:
							*| main.c:81: 	while (INPOUT(0xFF) == 0) {}
	pea 255.w					*	pea 255.w		|
	jbsr (a4)					*	jsr (%a4)		| tmp39
							*| main.c:81: 	while (INPOUT(0xFF) == 0) {}
	addq.l #4,sp					*	addq.l #4,%sp	|,
	tst.l d0					*	tst.l %d0	| tmp43
	jbeq _?L2					*	jeq .L2		|
							*| main.c:84: 	CRTMOD(0x10);
	pea 16.w					*	pea 16.w		|
	jbsr (a3)					*	jsr (%a3)		| tmp42
							*| main.c:87: }
	addq.l #4,sp					*	addq.l #4,%sp	|,
	moveq #0,d0					*	moveq #0,%d0	|
	move.l (sp)+,a3					*	move.l (%sp)+,%a3	|,
	move.l (sp)+,a4					*	move.l (%sp)+,%a4	|,
	rts						*	rts
							*	.size	main, .-main
							*	.ident	"GCC: (GNU) 10.2.0"
