#include <stdio.h>
#include <signal.h>

void
sigcontext_dump_stack_trace(struct sigcontext *scp)
{
	unsigned int *fp, i;

	fp = (unsigned int *)scp->sc_ebp;

	printf("Backtrace:");
	for (i = 0; i < 16; i++) {
		if ((i % 8) == 0)
			printf("\n");

		fp = (int *)(*fp);
		if (!(*(fp + 1) && *fp))
			break;

		printf(" %08x", *(fp + 1));
	}
	printf("\n");
}

void
sigcontext_dump(struct sigcontext *scp)
{
	printf("EAX %08x EBX %08x ECX %08x EDX %08x\n",
		scp->sc_eax, scp->sc_ebx, scp->sc_ecx, scp->sc_edx);
	printf("ESI %08x EDI %08x EBP %08x ESP %08x\n",
		scp->sc_esi, scp->sc_edi, scp->sc_ebp, scp->sc_esp);
	printf("EIP %08x EFLAGS %08x\n", scp->sc_eip, scp->sc_efl);
	printf("CS %04x SS %04x DS %04x ES %04x\n",
		scp->sc_cs & 0xffff, scp->sc_ss & 0xffff,
		scp->sc_ds & 0xffff, scp->sc_es & 0xffff);
	sigcontext_dump_stack_trace(scp);
}
