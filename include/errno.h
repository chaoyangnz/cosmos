/*
 * This header file defines a set of POSIX errno values
 * that fits consistently into the COM error code namespace -
 * i.e. these error code values can be returned from COM object methods.
 * so that programs using the oskit's minimal C library
 * can treat errno values and interface return codes interchangeably.
 *
 * One (probably the main) disadvantage of using these error codes
 * is that, since they don't start from around 0 like typical Unix errno values,
 * it's impossible to provide a Unix-style sys_errlist table for them.
 * However, they are fully compatible
 * with the POSIX-blessed strerror and perror routines,
 * and in any case the minimal C library
 * is not intended to support "legacy" applications directly -
 * for that purpose, a "real" C library would be more appropriate,
 * and such a C library would probably use more traditional errno values,
 * doing appropriate translation when interacting with COM interfaces.
 */
#ifndef _C_ERRNO_H_
#define _C_ERRNO_H_

#if !defined(errno) && !defined(ASSEMBLER)
extern int errno;			/* global error number */
#endif

/* Common errors */
#define E_UNEXPECTED	0x8000ffff	/* Unexpected error */
#define E_NOTIMPL		0x80004001	/* Not implemented */
#define E_NOINTERFACE	0x80004002	/* Interface not supported */
#define E_POINTER		0x80004003	/* Bad pointer */
#define E_ABORT		0x80004004	/* Operation aborted */
#define E_FAIL		0x80004005	/* Operation failed */
#define E_ACCESSDENIED	0x80070005	/* Access denied */
#define E_OUTOFMEMORY	0x8007000e	/* Out of memory */
#define E_INVALIDARG	0x80070057	/* Invalid argument */

/* ISO/ANSI C-1990 errors */
#define EDOM		0x8f100001	/* Argument out of domain */
#define ERANGE		0x8f100002	/* Result too large */

/* POSIX-1990 errors */
#define E2BIG		0x8f100101	/* Argument list too long */
#define EACCES		0x8f100102	/* Permission denied */
#define EAGAIN		0x8f100103	/* Rsrc temporarily unavail */
#define EBADF		0x8f100104	/* Bad file descriptor */
#define EBUSY		0x8f100105	/* Device busy */
#define ECHILD		0x8f100106	/* No child processes */
#define EDEADLK		0x8f100107	/* Resource deadlock avoided */
#define EEXIST		0x8f100108	/* File exists */
#define EFAULT		E_POINTER	/* Bad address */
#define EFBIG		0x8f100109	/* File too large */
#define EINTR		0x8f10010a	/* Interrupted system call */
#define EINVAL		E_INVALIDARG /* Invalid argument */
#define EIO		0x8f10010b	/* Input/output error */
#define EISDIR		0x8f10010c	/* Is a directory */
#define EMFILE		0x8f10010d	/* Too many open files */
#define EMLINK		0x8f10010e	/* Too many links */
#define ENAMETOOLONG	0x8f10010f	/* File name too long */
#define ENFILE		0x8f100110	/* Max files open in system */
#define ENODEV		0x8f100111	/* Op not supported by device */
#define ENOENT		0x8f100112	/* No such file or directory */
#define ENOEXEC		0x8f100113	/* Exec format error */
#define ENOLCK		0x8f100114	/* No locks available */
#define ENOMEM		E_OUTOFMEMORY /* Cannot allocate memory */
#define ENOSPC		0x8f100115	/* No space left on device */
#define ENOSYS		E_NOTIMPL	/* Function not implemented */
#define ENOTDIR		0x8f100116	/* Not a directory */
#define ENOTEMPTY		0x8f100117	/* Directory not empty */
#define ENOTTY		0x8f100118	/* Inappropriate ioctl */
#define ENXIO		0x8f100119	/* Device not configured */
#define EPERM		E_ACCESSDENIED /* Op not permitted */
#define EPIPE		0x8f10011a	/* Broken pipe */
#define EROFS		0x8f10011b	/* Read-only file system */
#define ESPIPE		0x8f10011c	/* Illegal seek */
#define ESRCH		0x8f10011d	/* No such process */
#define EXDEV		0x8f10011e	/* Cross-device link */

/* POSIX-1993 errors */
#define EBADMSG		0x8f100120	/* Bad message */
#define ECANCELED		0x8f100121	/* Operation canceled */
#define EINPROGRESS	0x8f100122	/* Operation in progress */
#define EMSGSIZE		0x8f100123	/* Bad message buffer length */
#define ENOTSUP		0x8f100124	/* Not supported */

/* POSIX-1996 errors */
#define ETIMEDOUT		0x8f100130	/* Operation timed out */

/* X/Open UNIX 1994 errors */
#define EADDRINUSE		0x8f100200	/* Address in use */
#define EADDRNOTAVAIL	0x8f100201	/* Address not available */
#define EAFNOSUPPORT	0x8f100202	/* Address family unsupported */
#define EALREADY		0x8f100203	/* Already connected */
#define ECONNABORTED	0x8f100204	/* Connection aborted */
#define ECONNREFUSED	0x8f100205	/* Connection refused */
#define ECONNRESET		0x8f100206	/* Connection reset */
#define EDESTADDRREQ	0x8f100207	/* Dest address required */
#define EDQUOT		0x8f100208	/* Reserved */
#define EHOSTUNREACH	0x8f100209	/* Host is unreachable */
#define EIDRM		0x8f10020a	/* Identifier removed */
#define EILSEQ		0x8f10020b	/* Illegal byte sequence */
#define EISCONN		0x8f10020c	/* Connection in progress */
#define ELOOP		0x8f10020d	/* Too many symbolic links */
#define EMULTIHOP		0x8f10020e	/* Reserved */
#define ENETDOWN		0x8f10020f	/* Network is down */
#define ENETUNREACH	0x8f100210	/* Network unreachable */
#define ENOBUFS		0x8f100211	/* No buffer space available */
#define ENODATA		0x8f100212	/* No message is available */
#define ENOLINK		0x8f100213	/* Reserved */
#define ENOMSG		0x8f100214	/* No message of desired type */
#define ENOPROTOOPT	0x8f100215	/* Protocol not available */
#define ENOSR		0x8f100216	/* No STREAM resources */
#define ENOSTR		0x8f100217	/* Not a STREAM */
#define ENOTCONN		0x8f100218	/* Socket not connected */
#define ENOTSOCK		0x8f100219	/* Not a socket */
#define EOPNOTSUPP		0x8f10021a	/* Op not supported on socket */
#define EOVERFLOW		0x8f10021b	/* Value too large */
#define EPROTO		0x8f10021c	/* Protocol error */
#define EPROTONOSUPPORT	0x8f10021d	/* Protocol not supported */
#define EPROTOTYPE		0x8f10021e	/* Socket type not supported */
#define ESTALE		0x8f10021f	/* Reserved */
#define ETIME		0x8f100220	/* Stream ioctl timeout */
#define ETXTBSY		0x8f100221	/* Text file busy */
#define EWOULDBLOCK	0x8f100222	/* Operation would block */

#endif /* _C_ERRNO_H_ */




