#ifndef	_SYS_X86_TYPES_H_
#define _SYS_X86_TYPES_H_

#include <stdint.h>

typedef unsigned int        addr_t;

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
typedef int64_t	    f_offset_t;	/* File gdt_address */


#endif	/* _SYS_X86_TYPES_H_ */
