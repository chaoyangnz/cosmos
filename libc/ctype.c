#include <ctype.h>

int isascii(int c)
{
    return ((c & ~0x7f) == 0);
}

int iscntrl(int c)
{
    return ((c) < ' ') || ((c) > 126);
}

int isdigit(int c)
{
    return ((c) >= '0') && ((c) <= '9');
}

int isgraph(int c)
{
    return ((c) > ' ') && ((c) <= 126);
}

int islower(int c)
{
    return (c >= 'a') && (c <= 'z');
}

int isprint(int c)
{
    return ((c) >= ' ') && ((c) <= 126);
}

int isspace(int c)
{
    return ((c) == ' ') || ((c) == '\f')
           || ((c) == '\n') || ((c) == '\r')
           || ((c) == '\t') || ((c) == '\v');
}

int isupper(int c)
{
    return (c >= 'A') && (c <= 'Z');
}

int isxdigit(int c)
{
    return isdigit(c) ||
           ((c >= 'A') && (c <= 'F')) ||
           ((c >= 'a') && (c <= 'f'));
}

int isalpha(int c)
{
    return islower(c) || isupper(c);
}

int isalnum(int c)
{
    return isalpha(c) || isdigit(c);
}

int ispunct(int c)
{
    return isgraph(c) && !isalnum(c);
}

int toascii(int c)
{
    return ((c) & 0x7f);
}

int toupper(int c)
{
    return ((c >= 'a') && (c <= 'z')) ? (c - 'a' + 'A') : c;
}

int tolower(int c)
{
    return ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 'a') : c;
}