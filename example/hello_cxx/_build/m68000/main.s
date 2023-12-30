* NO_APP
RUNS_HUMAN_VERSION	equ	3
	.cpu 68000
	.include doscall.inc
	.include iocscall.inc
* X68 GCC Develop
	.file	"main.cpp"				*	.file	"main.cpp"
							*| GNU C++17 (GCC) version 10.2.0 (m68k-elf)
							*|	compiled by GNU C version 12.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP
							*
							*| GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
							*| options passed:  -I C:/msys64/home/gespe/xdev68k/include/xc
							*| -I C:/msys64/home/gespe/xdev68k/include/xdev68k
							*| -iprefix c:\msys64\home\gespe\xdev68k\m68k-toolchain\bin\../lib/gcc/m68k-elf/10.2.0/
							*| -MD _build/m68000/main.m68k-gas.d -MF _build/m68000/main.d -MP
							*| -MT _build/m68000/main.o main.cpp -mcpu=68000
							*| -auxbase-strip _build/m68000/main.m68k-gas.s -Os
							*| -Wno-builtin-declaration-mismatch -std=gnu++17 -fcall-used-d2
							*| -fcall-used-a2 -finput-charset=cp932 -fexec-charset=cp932 -fverbose-asm
							*| -fno-rtti -fno-exceptions
							*| options enabled:  -faggressive-loop-optimizations -fallocation-dce
							*| -fauto-inc-dec -fbranch-count-reg -fcaller-saves -fcode-hoisting
							*| -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
							*| -fcrossjumping -fcse-follow-jumps -fdefer-pop
							*| -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
							*| -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
							*| -feliminate-unused-debug-types -fexpensive-optimizations -ffinite-loops
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
	.data						*	.section	.rodata._ZN17StaticCtorExampleD2Ev.str1.1,"aMS",@progbits,1
_?LC0:							*.LC0:
	.dc.b $53,$74,$61,$74,$69,$63,$43,$74
	.dc.b $6f,$72,$45,$78,$61,$6d,$70,$6c
	.dc.b $65,$3a,$20,$64,$74,$6f,$72,$2e
	.dc.b $00					*	.string	"StaticCtorExample: dtor."
	.text						*	.section	.text._ZN17StaticCtorExampleD2Ev,"axG",@progbits,_ZN17StaticCtorExampleD5Ev,comdat
	.align	2					*	.align	2
	.globl	__ZN17StaticCtorExampleD2Ev		*	.weak	_ZN17StaticCtorExampleD2Ev
							*	.type	_ZN17StaticCtorExampleD2Ev, @function
__ZN17StaticCtorExampleD2Ev:				*_ZN17StaticCtorExampleD2Ev:
							*| main.cpp:91: 		printf("StaticCtorExample: dtor.\n");
	move.l #_?LC0,4(sp)				*	move.l #.LC0,4(%sp)	|,
							*| main.cpp:92: 	}
							*| main.cpp:91: 		printf("StaticCtorExample: dtor.\n");
	jbra _puts					*	jra puts		|
							*	.size	_ZN17StaticCtorExampleD2Ev, .-_ZN17StaticCtorExampleD2Ev
	.globl	__ZN17StaticCtorExampleD1Ev		*	.weak	_ZN17StaticCtorExampleD1Ev
__ZN17StaticCtorExampleD1Ev=__ZN17StaticCtorExampleD2Ev	*	.set	_ZN17StaticCtorExampleD1Ev,_ZN17StaticCtorExampleD2Ev
	.data						*	.section	.rodata.str1.1,"aMS",@progbits,1
_?LC1:							*.LC1:
	.dc.b $45,$78,$61,$6d,$70,$6c,$65,$3a
	.dc.b $20,$63,$74,$6f,$72,$2e
	.dc.b $00					*	.string	"Example: ctor."
_?LC2:							*.LC2:
	.dc.b $45,$78,$61,$6d,$70,$6c,$65,$3a
	.dc.b $20,$68,$65,$6c,$6c,$6f,$20,$63
	.dc.b $2b,$2b,$20,$77,$6f,$72,$6c,$64
	.dc.b $2e
	.dc.b $00					*	.string	"Example: hello c++ world."
_?LC3:							*.LC3:
	.dc.b $45,$78,$61,$6d,$70,$6c,$65,$3a
	.dc.b $20,$64,$74,$6f,$72,$2e
	.dc.b $00					*	.string	"Example: dtor."
	.text						*	.section	.text.startup,"ax",@progbits
	.align	2					*	.align	2
	.xref __main	* workaround for libc.
	.globl	_main					*	.globl	main
							*	.type	main, @function
_main:							*main:
	move.l a3,-(sp)					*	move.l %a3,-(%sp)	|,
							*| main.cpp:105: 	execute_static_ctors();
	jbsr _execute_static_ctors			*	jsr execute_static_ctors		|
							*| main.cpp:76: 		printf("Example: ctor.\n");
	pea _?LC1					*	pea .LC1		|
	lea _puts,a3					*	lea puts,%a3	|, tmp35
	jbsr (a3)					*	jsr (%a3)		| tmp35
							*| main.cpp:73: 		printf("Example: hello c++ world.\n");
	pea _?LC2					*	pea .LC2		|
	jbsr (a3)					*	jsr (%a3)		| tmp35
							*| main.cpp:79: 		printf("Example: dtor.\n");
	pea _?LC3					*	pea .LC3		|
	jbsr (a3)					*	jsr (%a3)		| tmp35
							*| main.cpp:110: }
	lea (12,sp),sp					*	lea (12,%sp),%sp	|,
	moveq #0,d0					*	moveq #0,%d0	|
	move.l (sp)+,a3					*	move.l (%sp)+,%a3	|,
	rts						*	rts
							*	.size	main, .-main
	.data						*	.section	.rodata.str1.1
_?LC4:							*.LC4:
	.dc.b $53,$74,$61,$74,$69,$63,$43,$74
	.dc.b $6f,$72,$45,$78,$61,$6d,$70,$6c
	.dc.b $65,$3a,$20,$63,$74,$6f,$72,$2e
	.dc.b $00					*	.string	"StaticCtorExample: ctor."
	.text						*	.section	.text.startup
	.align	2					*	.align	2
							*	.type	_GLOBAL__sub_I_main, @function
__GLOBAL__sub_I_main:					*_GLOBAL__sub_I_main:
							*| main.cpp:88: 		printf("StaticCtorExample: ctor.\n");
	pea _?LC4					*	pea .LC4		|
	jbsr _puts					*	jsr puts		|
							*| main.cpp:94: static StaticCtorExample s_staticCtorExample;
	pea ___dso_handle				*	pea __dso_handle		|
	pea __ZL19s_staticCtorExample			*	pea _ZL19s_staticCtorExample		|
	pea __ZN17StaticCtorExampleD1Ev			*	pea _ZN17StaticCtorExampleD1Ev		|
	jbsr ___cxa_atexit				*	jsr __cxa_atexit		|
							*| main.cpp:110: }
	lea (16,sp),sp					*	lea (16,%sp),%sp	|,
	rts						*	rts
							*	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
							*	.section	.ctors,"aw",@progbits
	.align	4					*	.align	4
	.ctor	__GLOBAL__sub_I_main			*	.long	_GLOBAL__sub_I_main
							*	.local	_ZL19s_staticCtorExample
	.comm	__ZL19s_staticCtorExample,1		*	.comm	_ZL19s_staticCtorExample,1,1
							*	.hidden	__dso_handle
							*	.ident	"GCC: (GNU) 10.2.0"
