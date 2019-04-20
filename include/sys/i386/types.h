#ifndef	_SYS_X86_TYPES_H_
#define _SYS_X86_TYPES_H_

/*
 * On any anchitecture,
 * these types are _exactly_ as wide as indicated in their names.
 * The signed types essentially have the same meanings
 * as Java's byte, short, int, and long types, respectively.
 */
typedef signed char         uchar_t;
typedef signed char		    int8_t;
typedef signed short int	int16_t;
typedef signed int		    int32_t;
typedef signed long long	int64_t;
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;
typedef float			    float32_t;
typedef double			    float64_t;

/*
 * Just yer ordinary boolean type.
 * On the i386, bytes are fast, so we use it;
 * on other architectures this will generally be an int.
 */
typedef unsigned char		bool_t;

/*
 * Type compatible with `va_list' from <stdarg.h>.
 */
typedef char *			    va_list_t;

/*
 * A addr_t is a type-neutral pointer,
 * e.g. an offset into a virtual memory space.
 */
typedef	uint32_t		    addr_t;

/*
 * A size_t is the proper type for
 * expressing the difference between two
 * addr_t entities.
 */
#ifndef size_t
typedef	uint32_t		    size_t;
#endif
typedef int32_t		        ssize_t;

/*
 * Integer types the size of a general-purpose processor register.
 * Generally the same size as addr_t and size_t.
 */
typedef uint32_t		    reg_t;
typedef int32_t		        sreg_t;



/*
 * Types corresponding to standard POSIX types,
 * for use in the COM interfaces that export POSIX functionality.
 */
typedef uint32_t	dev_t;	/* Device number */
typedef uint32_t	f_ino_t;	/* File serial number */
typedef uint16_t	f_nlink_t;	/* Link count of a file */
typedef int32_t	    pid_t;	/* Process ID */
typedef uint32_t	uid_t;	/* User ID */
typedef uint32_t	gid_t;	/* Group ID */
typedef uint16_t	f_mode_t;	/* File type and access permissions */
typedef int64_t	    f_offset_t;	/* File offset */
#ifndef wchar_t
typedef uint16_t	wchar_t;	/* Unicode wide character */
#endif

#endif	/* _SYS_X86_TYPES_H_ */
