#ifndef C_STDINT_H
#define C_STDINT_H

typedef unsigned char       uchar_t; // not in std c

typedef signed char		    int8_t;
typedef signed short int	int16_t;
typedef signed int		    int32_t;
//typedef signed long		int32_t;
typedef signed long long	int64_t;
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;
//typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;

typedef long long           intmax_t;
typedef unsigned long long  uintmax_t;

typedef unsigned int        addr_t;


typedef signed int           intptr_t;
typedef unsigned int         uintptr_t;
typedef signed int           ptrdiff_t;

/* Limits of integral types.  */

/* Minimum of signed integral types.  */
# define INT8_MIN                (-128)
# define INT16_MIN                (-32767-1)
# define INT32_MIN                (-2147483647-1)
# define INT64_MIN                (-9223372036854775807LL-1)
/* Maximum of signed integral types.  */
# define INT8_MAX                (127)
# define INT16_MAX                (32767)
# define INT32_MAX                (2147483647)
# define INT64_MAX                (9223372036854775807LL)

/* Maximum of unsigned integral types.  */
# define UINT8_MAX                (255)
# define UINT16_MAX                (65535)
# define UINT32_MAX                (4294967295U)
# define UINT64_MAX                (18446744073709551615ULL)

#define addr(var) ((addr_t)(&(var)))

#endif //C_STDINT_H
