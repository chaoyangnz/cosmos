#include <unistd.h>	/* _exit */

void _run_atexits(void);

void exit(int code)
{
    _run_atexits();
    _exit(code);
}
