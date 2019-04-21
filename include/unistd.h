#ifndef _C_UNISTD_H_
#define _C_UNISTD_H_

#include <stddef.h>
#include <kernel/i386/types.h>
#include "compiler.h"

#ifndef _SIZE_T
#define _SIZE_T
typedef size_t size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef ssize_t ssize_t;
#endif

#ifndef NULL
#define NULL		0
#endif

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

/* access function */
#define F_OK            0       /* test for existence of file */
#define X_OK            0x01    /* test for execute or search permission */
#define W_OK            0x02    /* test for write permission */
#define R_OK            0x04    /* test for read permission */



/* POSIX unistd.h prototypes implemented in the OSKit */
void _exit(int __rc) NORETURN;
                     int access(const char *__name, f_mode_t __mode);
                     int chdir(const char *__path);
                     int chown(const char *__path, uid_t __owner, gid_t __group);
                     int close(int __fd);
                     int dup(int __fd);
                     int dup2(int __oldfd, int __newfd);
                     int link(const char *__path1, const char *__path2);
                     f_offset_t lseek(int __fd, f_offset_t __offset, int __whence);
                     ssize_t read(int __fd, void *__buf, size_t __n);
                     int rmdir(const char *__path);
                     int unlink(const char *__path);
                     ssize_t write(int __fd, const void *__buf, size_t __n);

/* POSIX unistd.h prototypes not implemented in the OSKit */
                     unsigned int alarm(unsigned int);
                     int execl(const char *, const char *, ...);
                     int execle(const char *, const char *, ...);
                     int execlp(const char *, const char *, ...);
                     int execv(const char *, char * const *);
                     int execve(const char *, char * const *, char * const *);
                     int execvp(const char *, char * const *);
                     int fdatasync(int);
                     pid_t fork(void);
                     long fpathconf(int, int);
                     int fsync(int);
                     int ftruncate(int, f_offset_t);
                     char *getcwd(char *, size_t);
                     gid_t getegid(void);
                     uid_t geteuid(void);
                     gid_t getgid(void);
                     int getgroups(int, gid_t[]);
                     char *getlogin(void);
                     int gethostname(char *, int);
                     pid_t getpgrp(void);
                     pid_t getpid(void);
                     pid_t getppid(void);
                     uid_t getuid(void);
                     int isatty(int);
                     long pathconf(const char *, int);
                     int pause(void);
                     int pipe(int *);
                     int setgid(gid_t);
                     int setpgid(pid_t, pid_t);
                     pid_t setsid(void);
                     int setuid(uid_t);
                     unsigned int sleep(unsigned int);
                     int usleep(unsigned int);
                     long sysconf(int);
                     pid_t tcgetpgrp(int);
                     int tcsetpgrp(int, pid_t);
                     char *ttyname(int);

/* CAE BASE Issue 4, Version 2 unistd.h prototypes implemented in the OSKit */
                     extern char *optarg;
                     extern int optind, optopt, opterr, optreset;

                     int fchdir(int __fd);
                     int fchown(int __fd, uid_t __owner, gid_t __group);
                     int getopt(int argc, char * const argv[], const char *optstring);
                     int lchown(const char *__path, uid_t __owner, gid_t __group);
                     int readlink(const char  *__path, void *__buf, size_t __n);
                     int symlink(const char *__path1, const char *__path2);

/* ``Traditional'' BSD unistd.h prototypes implemented in the OSKit */
                     int mknod(const char *__name, f_mode_t __mode, dev_t __dev);
                     int swapon(const char *path);
                     int swapoff(const char *path);

/* OSKit specific prototypes */
                     extern void (*sys_libc_exit)(int);
                     extern void sys_init_libc(void);



#endif /* _C_UNISTD_H_ */
