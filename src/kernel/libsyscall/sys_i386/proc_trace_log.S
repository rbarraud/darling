#define __SYSCALL_32BIT_ARG_BYTES 12
#include "SYS.h"

#ifndef SYS_proc_trace_log
#error "SYS_proc_trace_log not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__i386__)
__SYSCALL2(proc_trace_log, proc_trace_log, 2, cerror_nocancel)
#endif

