/* Copyright (C) 1991, 1992 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

/*
 *	POSIX Standard: 2.9 Symbolic Constants		<unistd.h>
 */

#ifndef	_UNISTD_H

#define	_UNISTD_H	1
#include <features.h>

__BEGIN_DECLS

/* These may be used to determine what facilities are present at compile time.
   Their values can be obtained at run time from sysconf.  */

/* POSIX Standard approved as IEEE Std 1003.1b as of September 15, 1993.  */
#define	_POSIX_VERSION	199309L

/* These are not #ifdef __USE_POSIX2 because they are
   in the theoretically application-owned namespace.  */

#define	_POSIX2_C_VERSION	199912L	/* Invalid until 1003.2 is done.  */

/* If defined, the implementation supports the
   C Language Bindings Option.  */
#define	_POSIX2_C_BIND	1

/* If defined, the implementation supports the
   C Language Development Utilities Option.  */
#define	_POSIX2_C_DEV	1

/* If defined, the implementation supports the
   Software Development Utilities Option.  */
#define	_POSIX2_SW_DEV	1

/* If defined, the implementation supports the
   creation of locales with the localedef utility.  */
#define	_POSIX2_LOCALEDEF	1


/* Get values of POSIX options:

   If these symbols are defined, the corresponding features are
   always available.  If not, they may be available sometimes.
   The current values can be obtained with `sysconf'.

   _POSIX_JOB_CONTROL	Job control is supported.
   _POSIX_SAVED_IDS	Processes have a saved set-user-ID
   			and a saved set-group-ID.

   If any of these symbols is defined as -1, the corresponding option is not
   true for any file.  If any is defined as other than -1, the corresponding
   option is true for all files.  If a symbol is not defined at all, the value
   for a specific file can be obtained from `pathconf' and `fpathconf'.

   _POSIX_CHOWN_RESTRICTED	Only the super user can use `chown' to change
   				the owner of a file.  `chown' can only be used
				to change the group ID of a file to a group of
				which the calling process is a member.
   _POSIX_NO_TRUNC		Pathname components longer than
   				NAME_MAX generate an error.
   _POSIX_VDISABLE		If defined, if the value of an element of the
				`c_cc' member of `struct termios' is
				_POSIX_VDISABLE, no character will have the
				effect associated with that element.
   */

#include <posix_opt.h>


/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */


/* All functions that are not declared anywhere else.  */

/* Copyright (C) 1991, 1992 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the, 1992 Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#ifndef	_GNU_TYPES_H

#define	_GNU_TYPES_H	1


/* Convenience types.  */
typedef unsigned char __u_char;
typedef unsigned short __u_short;
typedef unsigned int __u_int;
typedef unsigned long __u_long;
typedef struct
{
  long val[2];
} __quad;
typedef struct
{
  __u_long val[2];
} __u_quad;

#ifdef __linux__
typedef unsigned short __dev_t;	/* Type of device numbers.  */
typedef unsigned short __gid_t;	/* Type of group identifications.  */
typedef unsigned short __uid_t;	/* Type of user identifications.  */
typedef unsigned short __mode_t;/* Type of file attribute bitmasks.  */
typedef long	__daddr_t;	/* The type of a disk address.  */
typedef long	__off_t;	/* Type of file sizes and offsets.  */
typedef long long __loff_t;	/* Type of long file sizes and offsets.  */
typedef unsigned long __ino_t;	/* Type of file serial numbers.  */
typedef unsigned short __nlink_t;	/* Type of file link counts.  */
typedef long	__time_t;
#else
typedef int __dev_t;		/* Type of device numbers.  */
typedef unsigned int __gid_t;	/* Type of group identifications.  */
typedef unsigned int __uid_t;	/* Type of user identifications.  */
typedef unsigned int __mode_t;	/* Type of file attribute bitmasks.  */
typedef long int __daddr_t;	/* The type of a disk address.  */
typedef long int __off_t;	/* Type of file sizes and offsets.  */
typedef unsigned long int __ino_t;	/* Type of file serial numbers.  */
typedef unsigned short int __nlink_t;	/* Type of file link counts.  */
typedef long int __time_t;
#endif

typedef int __pid_t;		/* Type of process identifications.  */
typedef int __ssize_t;		/* Type of a byte count, or error.  */
typedef __quad __fsid_t;	/* Type of file system IDs.  */

/* Everythin' else.  */
typedef char *__caddr_t;
typedef long int __swblk_t;	/* Type of a swap block maybe?  */


/* fd_set for select.  */

#ifdef __linux__

#ifndef __FDSET_LONGS
#define __FDSET_LONGS 8
#endif

typedef struct __fd_set {
        unsigned long fds_bits [__FDSET_LONGS];
} __fd_set;


#ifndef __NFDBITS

#define	__NFDBITS	(sizeof(unsigned long int) * 8)

#define __FD_SETSIZE	(__FDSET_LONGS*__NFDBITS)

#define __FD_SET(fd,fdsetp) \
	__asm__ __volatile__ ("btsl %1,%0": \
		"=m" (*(__fd_set *) (fdsetp)):"r" ((int) (fd)))

#define __FD_CLR(fd,fdsetp) \
	__asm__ __volatile__("btrl %1,%0": \
		"=m" (*(__fd_set *) (fdsetp)):"r" ((int) (fd)))

#define __FD_ISSET(fd,fdsetp) __extension__ ({ \
	unsigned char __result; \
	__asm__ __volatile__("btl %1,%2 ; setb %0" \
        	:"=q" (__result) :"r" ((int) (fd)), \
		"m" (*(__fd_set *) (fdsetp))); \
	__result; })

#define __FD_ZERO(fdsetp) \
	__asm__ __volatile__("cld ; rep ; stosl" \
        	:"=m" (*(__fd_set *) (fdsetp)) \
        	:"a" (0), "c" (__FDSET_LONGS), \
		"D" ((__fd_set *) (fdsetp)) :"cx","di")

#endif /* __NFDBITS */

#else /* __linux__ */

/* Number of descriptors that can fit in an `fd_set'.  */
#define	__FD_SETSIZE	256

/* It's easier to assume 8-bit bytes than to get CHAR_BIT.  */
#define	__NFDBITS	(sizeof(unsigned long int) * 8)
#define	__FDELT(d)	((d) / __NFDBITS)
#define	__FDMASK(d)	(1 << ((d) % __NFDBITS))

typedef struct
{
  unsigned long int fds_bits [(__FD_SETSIZE + (__NFDBITS - 1)) / __NFDBITS];
} __fd_set;

/* This line MUST be split!  Otherwise m4 will not change it.  */
#define	__FD_ZERO(set)	\
  ((void) memset((__ptr_t) (set), 0, sizeof(fd_set)))
#define	__FD_SET(d, set)	((set)->__bits[__FDELT(d)] |= __FDMASK(d))
#define	__FD_CLR(d, set)	((set)->__bits[__FDELT(d)] &= ~__FDMASK(d))
#define	__FD_ISSET(d, set)	((set)->__bits[__FDELT(d)] & __FDMASK(d))

#endif /* __linux__ */

#endif /* gnu/types.h */

#if !defined(ssize_t) && !defined(_SSIZE_T)
#define _SSIZE_T
#define	ssize_t	__ssize_t
#endif

#define	__need_size_t
#include <stddef.h>

/* Values for the second argument to access.
   These may be OR'd together.  */
#define	R_OK	4		/* Test for read permission.  */
#define	W_OK	2		/* Test for write permission.  */
#define	X_OK	1		/* Test for execute permission.  */
#define	F_OK	0		/* Test for existence.  */

/* Test for access to NAME.  */
int __access __P ((__const char *__name, int __type)) {}
int access __P ((__const char *__name, int __type)) {}


/* Values for the WHENCE argument to lseek.  */
#ifndef	_STDIO_H		/* <stdio.h> has the same definitions.  */
#define	SEEK_SET	0	/* Seek from beginning of file.  */
#define	SEEK_CUR	1	/* Seek from current position.  */
#define	SEEK_END	2	/* Seek from end of file.  */
#endif

/* Move FD's file position to OFFSET bytes from the
   beginning of the file (if WHENCE is SEEK_SET),
   the current position (if WHENCE is SEEK_CUR),
   or the end of the file (if WHENCE is SEEK_END).
   Return the new file position.  */
__off_t __lseek __P ((int __fd, __off_t __offset, int __whence)) {}
__off_t lseek __P ((int __fd, __off_t __offset, int __whence)) {}

#if defined(__USE_MISC) && defined(__GNUC__) && !defined(__STRICT_ANSI__)
/* This is for Linux. */
__loff_t __llseek __P ((int __fd, __loff_t __offset, int __whence)) {}
__loff_t llseek __P ((int __fd, __loff_t __offset, int __whence)) {}
#endif

/* Close the file descriptor FD.  */
int __close __P ((int __fd)) {}
int close __P ((int __fd)) {}

/* Read NBYTES into BUF from FD.  Return the
   number read, -1 for errors or 0 for EOF.  */
ssize_t __read __P ((int __fd, __ptr_t __buf, size_t __nbytes)) {}
ssize_t read __P ((int __fd, __ptr_t __buf, size_t __nbytes)) {}

/* Write N bytes of BUF to FD.  Return the number written, or -1.  */
ssize_t __write __P ((int __fd, __const __ptr_t __buf, size_t __n)) {}
ssize_t write __P ((int __fd, __const __ptr_t __buf, size_t __n)) {}


/* Create a one-way communication channel (pipe).
   If successul, two file descriptors are stored in PIPEDES;
   bytes written on PIPEDES[1] can be read from PIPEDES[0].
   Returns 0 if successful, -1 if not.  */
int __pipe __P ((int __pipedes[2])) {}
int pipe __P ((int __pipedes[2])) {}

/* Schedule an alarm.  In SECONDS seconds, the process will get a SIGALRM.
   If SECONDS is zero, any currently scheduled alarm will be cancelled.
   The function returns the number of seconds remaining until the last
   alarm scheduled would have signaled, or zero if there wasn't one.
   There is no return value to indicate an error, but you can set `errno'
   to 0 and check its value after calling `alarm', and this might tell you.
   The signal may come late due to processor scheduling.  */
unsigned int alarm __P ((unsigned int __seconds)) {}

/* Make the process sleep for SECONDS seconds, or until a signal arrives
   and is not ignored.  The function returns the number of seconds less
   than SECONDS which it actually slept (thus zero if it slept the full time).
   If a signal handler does a `longjmp' or modifies the handling of the
   SIGALRM signal while inside `sleep' call, the handling of the SIGALRM
   signal afterwards is undefined.  There is no return value to indicate
   error, but if `sleep' returns SECONDS, it probably didn't work.  */
unsigned int sleep __P ((unsigned int __seconds)) {}


/* Suspend the process until a signal arrives.
   This always returns -1 and sets `errno' to EINTR.  */
int pause __P ((void)) {}


/* Change the owner and group of FILE.  */
int __chown __P ((__const char *__file,
			 __uid_t __owner, __gid_t __group)) {}
int chown __P ((__const char *__file,
		       __uid_t __owner, __gid_t __group)) {}

#ifdef	__USE_BSD
/* Change the owner and group of the file that FD is open on.  */
int __fchown __P ((int __fd,
			  __uid_t __owner, __gid_t __group)) {}
int fchown __P ((int __fd,
			__uid_t __owner, __gid_t __group)) {}
/* Change the process's working directory to the directory
   that FD is open on.  */
int __fchdir __P ((int __fd)) {}
int fchdir __P ((int __fd)) {}
#endif /* Use BSD.  */

/* Change the process's working directory to PATH.  */
int __chdir __P ((__const char *__path)) {}
int chdir __P ((__const char *__path)) {}

/* Get the pathname of the current working directory,
   and put it in SIZE bytes of BUF.  Returns NULL if the
   directory couldn't be determined or SIZE was too small.
   If successful, returns BUF.  In GNU, if BUF is NULL,
   an array is allocated with `malloc'; the array is SIZE
   bytes long, unless SIZE <= 0, in which case it is as
   big as necessary.  */
char *getcwd __P ((char *__buf, size_t __size)) {}

#ifdef	__USE_GNU
/* Return a malloc'd string containing the current directory name.
   If the environment variable `PWD' is set, and its value is correct,
   that value is used.  */
char *get_current_dir_name __P ((void)) {}
#endif

#ifdef	__USE_BSD
/* Put the absolute pathname of the current working directory in BUF.
   If successful, return BUF.  If not, put an error message in
   BUF and return NULL.  BUF should be at least PATH_MAX bytes long.  */
char *getwd __P ((char __buf [])) {}
#endif


/* Duplicate FD, returning a new file descriptor on the same file.  */
int __dup __P ((int __fd)) {}
int dup __P ((int __fd)) {}

/* Duplicate FD to FD2, closing FD2 and making it open on the same file.  */
int __dup2 __P ((int __fd, int __fd2)) {}
int dup2 __P ((int __fd, int __fd2)) {}

/* NULL-terminated array of "NAME=VALUE" environment variables.  */
char **__environ;
char **environ;


/* Replace the current process, executing PATH with arguments ARGV and
   environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  */
int __execve __P ((__const char *__path, char *__const __argv[],
			  char *__const __envp[])) {}
int execve __P ((__const char *__path, char *__const __argv[],
			char *__const __envp[])) {}

/* Execute PATH with arguments ARGV and environment from `environ'.  */
int execv __P ((__const char *__path, char *__const __argv[])) {}

/* Execute PATH with all arguments after PATH until a NULL pointer,
   and the argument after that for environment.  */
int execle __P ((__const char *__path, __const char *__arg,...)) {}

/* Execute PATH with all arguments after PATH until
   a NULL pointer and environment from `environ'.  */
int execl __P ((__const char *__path, __const char *__arg,...)) {}

/* Execute FILE, searching in the `PATH' environment variable if it contains
   no slashes, with arguments ARGV and environment from `environ'.  */
int execvp __P ((__const char *__file, char *__const __argv[])) {}

/* Execute FILE, searching in the `PATH' environment variable if
   it contains no slashes, with all arguments after FILE until a
   NULL pointer and environment from `environ'.  */
int execlp __P ((__const char *__file, __const char *arg,...)) {}


/* Terminate program execution with the low-order 8 bits of STATUS.  */
void _exit __P ((int __status)) {}


/* Get the `_PC_*' symbols for the NAME argument to `pathconf' and
   `fpathconf'; the `_SC_*' symbols for the NAME argument to
   `sysconf'; and the `_CS_*' symbols for the NAME argument to
   `confstr'.  */
#include <confname.h>

/* Get file-specific configuration information about PATH.  */
long int __pathconf __P ((__const char *__path, int __name)) {}
long int pathconf __P ((__const char *__path, int __name)) {}

/* Get file-specific configuration about descriptor FD.  */
long int __fpathconf __P ((int __fd, int __name)) {}
long int fpathconf __P ((int __fd, int __name)) {}


/* Get the value of the system variable NAME.  */
long int __sysconf __P ((int __name)) {}
long int sysconf __P ((int __name)) {}

#ifdef	__USE_POSIX2
/* Get the value of the string-valued system variable NAME.  */
size_t confstr __P ((int __name, char *__buf, size_t __len)) {}
#endif


/* Get the process ID of the calling process.  */
__pid_t __getpid __P ((void)) {}
__pid_t getpid __P ((void)) {}

/* Get the process ID of the calling process's parent.  */
__pid_t __getppid __P ((void)) {}
__pid_t getppid __P ((void)) {}

#ifdef __linux__

/* Get the process group ID of the process matching PID.
   If PID is zero, the current process's process group ID
   is returned. */
__pid_t getpgid __P ((__pid_t __pid)) {}

/* Get the process group ID of the calling process.  */
__pid_t getpgrp __P ((void)) {}

/* Set the process group ID of the process matching PID to PGID.
   If PID is zero, the current process's process group ID is set.
   If PGID is zero, the process ID of the process is used.  */
int setpgid __P ((__pid_t __pid, __pid_t __pgid)) {}

int setpgrp __P ((void)) {}

#else

/* Get the process group ID of process PID.  */
__pid_t __getpgrp __P ((__pid_t __pid)) {}

#ifndef	__FAVOR_BSD
/* Get the process group ID of the calling process.  */
__pid_t getpgrp __P ((void)) {}
#else /* Favor BSD.  */
#define	getpgrp(pid)	__getpgrp(pid)
#endif

/* Set the process group ID of the process matching PID to PGID.
   If PID is zero, the current process's process group ID is set.
   If PGID is zero, the process ID of the process is used.  */
int __setpgrp __P ((__pid_t __pid, __pid_t __pgid)) {}
int setpgid __P ((__pid_t __pid, __pid_t __pgid)) {}

#ifdef	__USE_BSD
/* Set the process group of PID to PGRP.  */
int setpgrp __P ((__pid_t __pid, __pid_t __pgrp)) {}

#endif /* Use BSD.  */

#endif /* __linux__ */

/* Create a new session with the calling process as its leader.
   The process group IDs of the session and the calling process
   are set to the process ID of the calling process, which is returned.  */
__pid_t __setsid __P ((void)) {}
__pid_t setsid __P ((void)) {}

__pid_t __getsid __P ((__pid_t __pid)) {}
__pid_t getsid __P ((__pid_t __pid)) {}

/* Get the real user ID of the calling process.  */
__uid_t __getuid __P ((void)) {}
__uid_t getuid __P ((void)) {}

/* Get the effective user ID of the calling process.  */
__uid_t __geteuid __P ((void)) {}
__uid_t geteuid __P ((void)) {}

/* Get the real group ID of the calling process.  */
__gid_t __getgid __P ((void)) {}
__gid_t getgid __P ((void)) {}

/* Get the effective group ID of the calling process.  */
__gid_t __getegid __P ((void)) {}
__gid_t getegid __P ((void)) {}

/* If SIZE is zero, return the number of supplementary groups
   the calling process is in.  Otherwise, fill in the group IDs
   of its supplementary groups in LIST and return the number written.  */
int __getgroups __P ((int __size, __gid_t __list[])) {}
int getgroups __P ((int __size, __gid_t __list[])) {}

/* Set the user ID of the calling process to UID.
   If the calling process is the super-user, set the real
   and effective user IDs, and the saved set-user-ID to UID;
   if not, the effective user ID is set to UID.  */
int __setuid __P ((__uid_t __uid)) {}
int setuid __P ((__uid_t __uid)) {}

#ifdef	__USE_BSD
/* Set the real user ID of the calling process to RUID,
   and the effective user ID of the calling process to EUID.  */
int __setreuid __P ((__uid_t __ruid, __uid_t __euid)) {}
int setreuid __P ((__uid_t __ruid, __uid_t __euid)) {}

/* Set the effective user ID of the calling process to UID.  */
int seteuid __P ((__uid_t __uid)) {}
#endif /* Use BSD.  */

/* Set the group ID of the calling process to GID.
   If the calling process is the super-user, set the real
   and effective group IDs, and the saved set-group-ID to GID;
   if not, the effective group ID is set to GID.  */
int __setgid __P ((__gid_t __gid)) {}
int setgid __P ((__gid_t __gid)) {}

#ifdef	__USE_BSD
/* Set the real group ID of the calling process to RGID,
   and the effective group ID of the calling process to EGID.  */
int __setregid __P ((__gid_t __rgid, __gid_t __egid)) {}
int setregid __P ((__gid_t __rgid, __gid_t __egid)) {}

/* Set the effective group ID of the calling process to UID.  */
int setegid __P ((__uid_t __uid)) {}
#endif /* Use BSD.  */

/* Set the user ID used for filesystem checks.  */
int __setfsuid __P ((__uid_t __uid)) {}
int setfsuid __P ((__uid_t __uid)) {}

/* Set the group ID used for filesystem checks.  */
int __setfsgid __P ((__gid_t __gid)) {}
int setfsgid __P ((__gid_t __gid)) {}


/* Clone the calling process, creating an exact copy.
   Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
__pid_t __fork __P ((void)) {}
__pid_t fork __P ((void)) {}

#ifdef	__USE_BSD
/* Clone the calling process, but without copying the whole address space.
   The the calling process is suspended until the the new process exits or is
   replaced by a call to `execve'.  Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
__pid_t __vfork __P ((void)) {}
__pid_t vfork __P ((void)) {}

#endif /* Use BSD. */

/* get character login name of the user. */
char *cuserid __P((char * __buf)) {}

/* Return the name of the controlling terminal. */
char *ctermid __P((char *__buf)) {}

/* Return the pathname of the terminal FD is open on, or NULL on errors.
   The returned storage is good only until the next call to this function.  */
char *ttyname __P ((int __fd)) {}

/* Return 1 if FD is a valid descriptor associated
   with a terminal, zero if not.  */
int __isatty __P ((int __fd)) {}
int isatty __P ((int __fd)) {}


/* Make a link to FROM named TO.  */
int __link __P ((__const char *__from, __const char *__to)) {}
int link __P ((__const char *__from, __const char *__to)) {}

#ifdef	__USE_BSD
/* Make a symbolic link to FROM named TO.  */
int __symlink __P ((__const char *__from, __const char *__to)) {}
int symlink __P ((__const char *__from, __const char *__to)) {}

/* Read the contents of the symbolic link PATH into no more than
   LEN bytes of BUF.  The contents are not null-terminated.
   Returns the number of characters read, or -1 for errors.  */
int __readlink __P ((__const char *__path, char *__buf, size_t __len)) {}
int readlink __P ((__const char *__path, char *__buf, size_t __len)) {}

#endif /* Use BSD.  */

/* Remove the link NAME.  */
int __unlink __P ((__const char *__name)) {}
int unlink __P ((__const char *__name)) {}

/* Remove the directory PATH.  */
int __rmdir __P ((__const char *__path)) {}
int rmdir __P ((__const char *__path)) {}


/* Return the foreground process group ID of FD.  */
__pid_t tcgetpgrp __P ((int __fd)) {}

/* Set the foreground process group ID of FD set PGRP_ID.  */
int tcsetpgrp __P ((int __fd, __pid_t __pgrp_id)) {}


/* Return the login name of the user.  */
char *getlogin __P ((void)) {}

#ifdef	__USE_BSD
/* Set the login name returned by `getlogin'.  */
int setlogin __P ((__const char *__name)) {}
#endif

#ifdef	__USE_POSIX2
/* Process the arguments in ARGV (ARGC of them, minus
   the program name) for options given in OPTS.

   If `opterr' is zero, no messages are generated
   for invalid options; it defaults to 1.
   `optind' is the current index into ARGV.
   `optarg' is the argument corresponding to the current option.
   Return the option character from OPTS just read.
   Return -1 when there are no more options.
   For unrecognized options, or options missing arguments,
   `optopt' is set to the option letter, and '?' is returned.

   The OPTS string is a list of characters which are recognized option
   letters, optionally followed by colons, specifying that that letter
   takes an argument, to be placed in `optarg'.

   If a letter in OPTS is followed by two colons, its argument is optional.
   This behavior is specific to the GNU `getopt'.

   The argument `--' causes premature termination of argument scanning,
   explicitly telling `getopt' that there are no more options.

   If OPTS begins with `--', then non-option arguments
   are treated as arguments to the option '\0'.
   This behavior is specific to the GNU `getopt'.  */
int getopt __P ((int __argc, char *__const * __argv,
			__const char *__opts)) {}
int opterr;
int optind;
int optopt;
char *optarg;
#endif


#ifdef	__USE_BSD

/* Put the name of the current host in no more than LEN bytes of NAME.
   The result is null-terminated if LEN is large enough for the full
   name and the terminator.  */
int __gethostname __P ((char *__name, size_t __len)) {}
int gethostname __P ((char *__name, size_t __len)) {}

/* Set the name of the current host to NAME, which is LEN bytes long.
   This call is restricted to the super-user.  */
int sethostname __P ((__const char *__name, size_t __len)) {}

/* Return the current machine's Internet number.  */
long int gethostid __P ((void)) {}

/* Set the current machine's Internet number to ID.
   This call is restricted to the super-user.  */
int sethostid __P ((long int __id)) {}


/* Return the number of bytes in a page.  This is the system's page size,
   which is not necessarily the same as the hardware page size.  */
size_t __getpagesize __P ((void)) {}
size_t getpagesize __P ((void)) {}


/* Return the maximum number of file descriptors
   the current process could possibly have.  */
int __getdtablesize __P ((void)) {}
int getdtablesize __P ((void)) {}

/* Make all changes done to FD actually appear on disk, except changes
 * to the access times in the inode.  */
int fdatasync __P ((int __fd)) {}

/* Make all changes done to FD actually appear on disk.  */
int fsync __P ((int __fd)) {}

/* Make all changes done to all files actually appear on disk.  */
int sync __P ((void)) {}


/* Revoke access permissions to all processes currently communicating
   with the control terminal, and then send a SIGHUP signal to the process
   group of the control terminal.  */
int vhangup __P ((void)) {}


/* Turn accounting on if NAME is an existing file.  The system will then write
   a record for each process as it terminates, to this file.  If NAME is NULL,
   turn accounting off.  This call is restricted to the super-user.  */
int acct __P ((__const char *__name)) {}

/* Make PATH be the root directory (the starting point for absolute paths).
   This call is restricted to the super-user.  */
int chroot __P ((__const char *__path)) {}

/* Make the block special device PATH available to the system for swapping.
   This call is restricted to the super-user.  */
int swapon __P ((__const char *__path)) {}

/* Successive calls return the shells listed in `/etc/shells'.  */
char *getusershell __P ((void)) {}
void endusershell __P ((void)); /* Discard cached info.  */
void setusershell __P ((void)); /* Rewind and re-read the file.  */

/* Prompt with PROMPT and read a string from the terminal without echoing.
   Uses /dev/tty if possible; otherwise stderr and stdin.  */
char *getpass __P ((__const char *__prompt)) {}

#endif /* Use BSD.  */

#if defined (__USE_MISC) && !defined (F_LOCK)
/* NOTE: These declarations also appear in <fcntl.h>; be sure to keep both
   files consistent.  Some systems have them there and some here, and some
   software depends on the macros being defined without including both.  */

/* `lockf' is a simpler interface to the locking facilities of `fcntl'.
   LEN is always relative to the current file position.
   The CMD argument is one of the following.  */

#define F_ULOCK 0	/* Unlock a previously locked region.  */
#define F_LOCK  1	/* Lock a region for exclusive use.  */
#define F_TLOCK 2	/* Test and lock a region for exclusive use.  */
#define F_TEST  3	/* Test a region for other processes locks.  */

int lockf __P ((int __fd, int __cmd, __off_t __len)) {}
#endif /* Use misc and F_LOCK not already defined.  */

#ifdef __USE_MISC

/* Theses are kind of Linux specific. */
#include <sys/types.h>

int	__brk __P ((void* __end_data_segment)) {}
int	brk __P ((void* __end_data_segment)) {}
void*	__sbrk __P ((ptrdiff_t __increment)) {}
void*	sbrk __P ((ptrdiff_t __increment)) {}

char*	crypt __P((__const char *__key, __const char *__salt)) {}
void	encrypt __P((char __block[64], int __edflag)) {}
void	setkey __P((__const char *__key)) {}

int	ftruncate __P ((int __fildes, size_t __length)) {}
int	truncate __P ((__const char *__path, size_t __length)) {}

int	ioperm  __P ((unsigned long __from,
			unsigned long __num, int __turn_on)) {}
int	iopl __P((int __level)) {}

char*	mktemp __P((char *__template)) {}
int	mkstemp __P((char *__template)) {}

int	nice __P ((int __val)) {}

int	profil __P ((char *__buf, int __bufsiz, int __offset,
			int __scale)) {}

void	usleep __P((unsigned long __usec)) {}

#define LINUX_USTAT_VERSION	1	/* SVr4 */

int	_xustat __P ((int __ver, dev_t __dev, struct ustat* __ubuf)) {}
static __inline__ int
ustat (dev_t __dev, struct ustat* __ubuf)
{
  return _xustat (LINUX_USTAT_VERSION, __dev, __ubuf);
}

int	idle __P ((void)) {}
int	reboot __P ((int __magic, int __magic_too,
			int __flag)) {}

int	swapoff __P ((__const char * __specialfile)) {}

int	uselib __P ((__const char *__filename)) {}

int	getdomainname __P ((char *__name, size_t __len)) {}
int	setdomainname __P ((__const char *__name, size_t __len)) {}
char*	realpath __P ((__const char *__path,
			char __resolved_path [])) {}

#if 0
/* It is out of sync with other GNU packages. */
__const char	*basename __P((__const char *__name)) {}
#endif

#endif

#if defined(_POSIX_THREAD_SAFE_FUNCTIONS) || defined(_REENTRANT)
char *ttyname_r __P ((int __fd, char *buf, size_t len)) {}
#endif

__END_DECLS

#endif /* unistd.h  */
