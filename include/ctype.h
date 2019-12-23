#ifndef C_CTYPE_H
#define C_CTYPE_H

#include "compiler.h"

extern int isascii(int c);
extern int iscntrl(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int islower(int c);
extern int isprint(int c);
extern int isspace(int c);
extern int isupper(int c);
extern int isxdigit(int c);
extern int isalpha(int c);
extern int isalnum(int c);
extern int ispunct(int c);
extern int toascii(int c);
extern int toupper(int c);
extern int tolower(int c);


#endif //C_CTYPE_H
