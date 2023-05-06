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
							*| options passed:  -I H:/Emulator/X68k/xeij/xeij_boot/xdev68k/include/xc
							*| -I H:/Emulator/X68k/xeij/xeij_boot/xdev68k/include/xdev68k
							*| -iprefix h:\emulator\x68k\xeij\xeij_boot\xdev68k\m68k-toolchain\bin\../lib/gcc/m68k-elf/10.2.0/
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
	.text						*	.section	.text.startup,"ax",@progbits
	.align	2					*	.align	2
	.xref __main	* workaround for libc.
	.globl	_main					*	.globl	main
							*	.type	main, @function
_main:							*main:
							*| main.c:51: 		asm volatile (
* APP ON (APP) asm_mode=has				*#APP
							*| 51 "main.c" 1
		move.l	#_s_string?1,-(sp)		*		move.l	#s_string.1,-(sp)	|
	jbsr	_puts					*	jbsr	_puts
	addq.l	#4,sp					*	addq.l	#4,sp
							*
							*| 0 "" 2
							*| main.c:64: 		asm volatile (
							*| 64 "main.c" 1
		move.l	#_s_string?0,-(sp)		*		move.l	#s_string.0,-(sp)	|
	dc.w	__PRINT					*	dc.w	__PRINT
	addq.l	#4,sp					*	addq.l	#4,sp
							*
							*| 0 "" 2
							*| main.c:75: }
* APP OFF (NO_APP) asm_mode=gas				*#NO_APP
	moveq #0,d0					*	moveq #0,%d0	|
	rts						*	rts
							*	.size	main, .-main
	.data						*	.data
							*	.type	s_string.0, @object
							*	.size	s_string.0, 28
_s_string?0:						*s_string.0:
	.dc.b $68,$65,$6c,$6c,$6f,$20,$77,$6f
	.dc.b $72,$6c,$64,$2e,$20,$28,$62,$79
	.dc.b $20,$64,$6f,$73,$63,$61,$6c,$6c
	.dc.b $29,$0d,$0a
	.dc.b $00					*	.string	"hello world. (by doscall)\r\n"
							*	.type	s_string.1, @object
							*	.size	s_string.1, 25
_s_string?1:						*s_string.1:
	.dc.b $68,$65,$6c,$6c,$6f,$20,$77,$6f
	.dc.b $72,$6c,$64,$2e,$20,$28,$62,$79
	.dc.b $20,$70,$75,$74,$73,$28,$29,$29
	.dc.b $00					*	.string	"hello world. (by puts())"
							*	.ident	"GCC: (GNU) 10.2.0"
