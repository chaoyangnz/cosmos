#include <ctype.h>
#include <string.h>

long strtol(const char *p, char **out_p, int base)
{
	long v = 0;
	int is_neg = 0;

	while (isspace(*p))
		p++;
	if (*p == '-')
		is_neg = 1, p++;
	else if (*p == '+')
		is_neg = 0;
	if (((base == 16) || (base == 0)) &&
	    ((*p == '0') && ((p[1] == 'x') || (p[1] == 'X'))))
	{
		p += 2;
		base = 16;
	}
	if (base == 0)
	{
		if (*p == '0')
			base = 8;
		else
			base = 10;
	}
	while (1)
	{
		char c = *p;
		if ((c >= '0') && (c <= '9') && (c - '0' < base))
			v = (v * base) + (c - '0');
		else if ((c >= 'a') && (c <= 'z') && (c - 'a' + 10 < base))
			v = (v * base) + (c - 'a' + 10);
		else if ((c >= 'A') && (c <= 'Z') && (c - 'A' + 10 < base))
			v = (v * base) + (c - 'A' + 10);
		else
			break;
		p++;
	}
	if (is_neg)
		v = -v;
	if (out_p) *out_p = (char*)p;
	return v;
}

