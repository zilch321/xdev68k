/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: signal.h,v 1.3 1993/06/06 06:02:58 mura Exp $
 */

#ifndef __signal_h__
#define __signal_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __sys_types_h__
#include <sys/types.h>
#endif

#define SIG_DFL      ((void (*) (int_))  0)
#define SIG_IGN      ((void (*) (int_))  1)
#define SIG_DOS      ((void (*) (int_))  2)
#define SIG_ERR      ((void (*) (int_)) -1)

#define SA_MODEMASK  0x03
#define SA_SIGIGN    0x00
#define SA_FORCEEXIT 0x01
#define SA_DUMPCORE  0x02
#define SA_STOPPROC  0x03
#define SA_ONSTACK   0x08
#define SA_RESETHAND 0x10

#define SIG_BLOCK    0
#define SIG_UNBLOCK  1
#define SIG_SETMASK  2

#define SIG_MAX      14
#define SIGALLMASK   ((1 << SIG_MAX) - 1)
#define NSIG         SIG_MAX

#define SIGABRT      1
#define SIGFPE       2
#define SIGILL       3
#define SIGINT       4
#define SIGSEGV      5
#define SIGTERM      6
#define SIGALRM      7
#define SIGKILL      8
#define SIGBUS       9
#define SIGSTOP     10
#define SIGEMT      11
#define SIGUSR1     12
#define SIGUSR2     13

#define SIGHUP      SIGSTOP /* only for compilation */
#define SIGQUIT     SIGSTOP /* only for compilation */

#define sigmask(x)  (1 << (x))

typedef int_ sigset_t;
typedef volatile int_ sig_atomic_t;

struct sigaction {
    void (*sa_handler) (int_);
    sigset_t sa_mask;
    int_ sa_flags;
};

extern const char *sys_siglist[];
extern int_ sys_nsig;

EXT (char *strsignal (int_));
EXT (int_ kill (pid_t, int_));
EXT (int_ raise (int_));
EXT (int_ sigaction (int_, const struct sigaction *, struct sigaction *));
EXT (int_ sigaddset (sigset_t *, int_));
EXT (int_ sigblock (int_));
EXT (int_ sigdelset (sigset_t *, int_));
EXT (int_ sigemptyset (sigset_t *));
EXT (int_ sigfillset (sigset_t *));
EXT (int_ sigismember (sigset_t *, int_));
EXT (int_ sigpending (sigset_t *));
EXT (int_ sigprocmask (int_, sigset_t *, sigset_t *));
EXT (int_ sigsetmask (int_));
EXT (int_ sigsuspend (sigset_t *));
EXT (void (*signal (int_, void (*) (int_))) (int_));

#ifndef __NO_SIGNAL_INLINE__

#define sigaddset(p,s)   ((*(sigset_t *) (p) |= (1 << (s))), 0)
#define sigdelset(p,s)   ((*(sigset_t *) (p) &= ~(1 << (s))), 0)
#define sigemptyset(p)   (*(sigset_t *) (p) = 0)
#define sigfillset(p)    (*(sigset_t *) (p) = SIGALLMASK)
#define sigismember(p,s) ((*(sigset_t *) (p) & (1 << (s))) ? 1 : 0)

#endif

#endif
