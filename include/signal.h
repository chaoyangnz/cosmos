#ifndef _SYS_X86_C_SIGNAL_H_
#define	_SYS_X86_C_SIGNAL_H_

/*
 * Machine-dependent signal definitions
 */

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to restore state properly if
 * a non-standard exit is performed.
 */
struct	sigcontext {
	int	sc_onstack;		/* sigstack state to restore */
	int	sc_mask;		/* signal mask to restore */
	int	sc_esp;			/* machine state */
	int	sc_ebp;
	int	sc_isp;
	int	sc_eip;
	int	sc_efl;
	int	sc_es;
	int	sc_ds;
	int	sc_cs;
	int	sc_ss;
	int	sc_edi;
	int	sc_esi;
	int	sc_ebx;
	int	sc_edx;
	int	sc_ecx;
	int	sc_eax;
	int	sc_gs;
	int	sc_fs;
#  define sc_sp sc_esp
#  define sc_fp sc_ebp
#  define sc_pc sc_eip
#  define sc_ps sc_efl
	int	sc_trapno;
	int	sc_err;
};

typedef struct sigcontext sigcontext_t;

void sigcontext_dump(struct sigcontext *scp);

#endif /* _SYS_X86_C_SIGNAL_H_ */
