#include <string.h>
#include <stdio.h>
#include <errno.h>

/*
 * Note that we don't support str_errlist here
 */
static struct errdef {
	int	num;
	char 	*str;
} errlist[] = {
/*
 * I created this using the following, some manual cleanup required.
 */

#if 0
egrep '^#define' ../../oskit/error.h | fgrep ' E' | sed 's;/\* ;\";g' | sed 's; \*/;\" },;g' | sed 's/#define /{ /g' | sed 's;0x[0-9a-f]*;,;g' >! tmp
#endif

{ E_UNEXPECTED	,	"Unexpected error" },
{ E_NOTIMPL	,	"Not implemented" },
{ E_NOINTERFACE	,	"Interface not supported" },
{ E_POINTER	,	"Bad pointer" },
{ E_ABORT		,	"Operation aborted" },
{ E_FAIL		,	"Operation failed" },
{ E_ACCESSDENIED	,	"Access denied" },
{ E_OUTOFMEMORY	,	"Out of memory" },
{ E_INVALIDARG	,	"Invalid argument" },
{ EDOM		,	"Argument out of domain" },
{ ERANGE		,	"Result too large" },
{ E2BIG		,	"Argument list too long" },
{ EACCES		,	"Permission denied" },
{ EAGAIN		,	"Rsrc temporarily unavail" },
{ EBADF		,	"Bad file descriptor" },
{ EBUSY		,	"Device busy" },
{ ECHILD		,	"No child processes" },
{ EDEADLK		,	"Resource deadlock avoided" },
{ EEXIST		,	"File exists" },
{ EFAULT		,	"Bad address" },
{ EFBIG		,	"File too large" },
{ EINTR		,	"Interrupted system call" },
{ EINVAL		, 	"Invalid argument" },
{ EIO		,	"Input/output error" },
{ EISDIR		,	"Is a directory" },
{ EMFILE		,	"Too many open files" },
{ EMLINK		,	"Too many links" },
{ ENAMETOOLONG	,	"File name too long" },
{ ENFILE		,	"Max files open in system" },
{ ENODEV		,	"Op not supported by device" },
{ ENOENT		,	"No such file or directory" },
{ ENOEXEC		,	"Exec format error" },
{ ENOLCK		,	"No locks available" },
{ ENOMEM		, 	"Cannot allocate memory" },
{ ENOSPC		,	"No space left on device" },
{ ENOSYS		,	"Function not implemented" },
{ ENOTDIR		,	"Not a directory" },
{ ENOTEMPTY	,	"Directory not empty" },
{ ENOTTY		,	"Inappropriate ioctl" },
{ ENXIO		,	"Device not configured" },
{ EPERM		, 	"Op not permitted" },
{ EPIPE		,	"Broken pipe" },
{ EROFS		,	"Read-only file system" },
{ ESPIPE		,	"Illegal seek" },
{ ESRCH		,	"No such process" },
{ EXDEV		,	"Cross-device link" },
{ EBADMSG		,	"Bad message" },
{ ECANCELED	,	"Operation canceled" },
{ EINPROGRESS	,	"Operation in progress" },
{ EMSGSIZE		,	"Bad message buffer length" },
{ ENOTSUP		,	"Not supported" },
{ ETIMEDOUT	,	"Operation timed out" },
{ EADDRINUSE	,	"Address in use" },
{ EADDRNOTAVAIL	,	"Address not available" },
{ EAFNOSUPPORT	,	"Address family unsupported" },
{ EALREADY		,	"Already connected" },
{ ECONNABORTED	,	"Connection aborted" },
{ ECONNREFUSED	,	"Connection refused" },
{ ECONNRESET	,	"Connection reset" },
{ EDESTADDRREQ	,	"Dest address required" },
{ EDQUOT		,	"Reserved" },
{ EHOSTUNREACH	,	"Host is unreachable" },
{ EIDRM		,	"Identifier removed" },
{ EILSEQ		,	"Illegal byte sequence" },
{ EISCONN		,	"Connection in progress" },
{ ELOOP		,	"Too many symbolic links" },
{ EMULTIHOP	,	"Reserved" },
{ ENETDOWN		,	"Network is down" },
{ ENETUNREACH	,	"Network unreachable" },
{ ENOBUFS		,	"No buffer space available" },
{ ENODATA		,	"No message is available" },
{ ENOLINK		,	"Reserved" },
{ ENOMSG		,	"No message of desired type" },
{ ENOPROTOOPT	,	"Protocol not available" },
{ ENOSR		,	"No STREAM resources" },
{ ENOSTR		,	"Not a STREAM" },
{ ENOTCONN		,	"Socket not connected" },
{ ENOTSOCK		,	"Not a socket" },
{ EOPNOTSUPP	,	"Op not supported on socket" },
{ EOVERFLOW	,	"Value too large" },
{ EPROTO		,	"Protocol error" },
{ EPROTONOSUPPORT	,	"Protocol not supported" },
{ EPROTOTYPE	,	"Socket type not supported" },
{ ESTALE		,	"Reserved" },
{ ETIME		,	"Stream ioctl timeout" },
{ ETXTBSY		,	"Text file busy" },
{ EWOULDBLOCK	,	"Operation would block" },
};

#define NERROR	(sizeof(errlist)/sizeof(errlist[0]))

char *
strerror(int num)
{
	#define PREFIX "Unknown error: 0x"

	static char tmp[sizeof PREFIX + 20];
	int	i = 0;

	for (i = 0; i < NERROR; i++)
		if (errlist[i].num == num)
			return errlist[i].str;

	/* 
	 * Note: we shouldn't be doing this, as this creates a 
	 * rather unnecessary link-time dependency
	 */
	sprintf(tmp, PREFIX"%x", num);
	return tmp;
}
