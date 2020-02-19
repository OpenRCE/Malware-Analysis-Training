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

/*
 *	ANSI Standard: 4.11 STRING HANDLING	<string.h>
 */

#ifndef	_STRING_H

#define	_STRING_H	1
#include <features.h>

__BEGIN_DECLS

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

#undef __P
#define	__P(a) a {}

/* `memcpy' is a built-in function for gcc 2.x. */
#if defined(__STDC__) && __GNUC__ < 2
/* Copy N bytes of SRC to DEST.  */
__ptr_t memcpy __P ((__ptr_t __dest, __const __ptr_t __src,
			    size_t __n));
#endif

/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
__ptr_t memmove __P ((__ptr_t __dest, __const __ptr_t __src,
			     size_t __n));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
__ptr_t __memccpy __P ((__ptr_t __dest, __const __ptr_t __src,
			       int __c, size_t __n));
#if defined (__USE_SVID) || defined (__USE_BSD)
__ptr_t memccpy __P ((__ptr_t __dest, __const __ptr_t __src,
			     int __c, size_t __n));
#endif /* SVID.  */


/* Set N bytes of S to C.  */
__ptr_t memset __P ((__ptr_t __s, int __c, size_t __n));

/* `memcmp' is a built-in function for gcc 2.x. */
#if defined(__STDC__) && __GNUC__ < 2
/* Compare N bytes of S1 and S2.  */
int memcmp __P ((__const __ptr_t __s1, __const __ptr_t __s2,
			size_t __n));
#endif

/* Search N bytes of S for C.  */
__ptr_t memchr __P ((__const __ptr_t __s, int __c, size_t __n));


/* Copy SRC to DEST.  */
char *strcpy __P ((char *__dest, __const char *__src));
/* Copy no more than N characters of SRC to DEST.  */
char *strncpy __P ((char *__dest, __const char *__src, size_t __n));

/* Append SRC onto DEST.  */
char *strcat __P ((char *__dest, __const char *__src));
/* Append no more than N characters from SRC onto DEST.  */
char *strncat __P ((char *__dest, __const char *__src, size_t __n));

/* Compare S1 and S2.  */
int strcmp __P ((__const char *__s1, __const char *__s2));
/* Compare N characters of S1 and S2.  */
int strncmp __P ((__const char *__s1, __const char *__s2, size_t __n));

/* Compare the collated forms of S1 and S2.  */
int strcoll __P ((__const char *__s1, __const char *__s2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
size_t strxfrm __P ((char *__dest, __const char *__src, size_t __n));

#if defined (__USE_SVID) || defined (__USE_BSD)
/* Duplicate S, returning an identical malloc'd string.  */
char *strdup __P ((__const char *__s));
#endif

/* Find the first occurrence of C in S.  */
char *strchr __P ((__const char *__s, int __c));
/* Find the last occurrence of C in S.  */
char *strrchr __P ((__const char *__s, int __c));

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
size_t strcspn __P ((__const char *__s, __const char *__reject));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
size_t strspn __P ((__const char *__s, __const char *__accept));
/* Find the first occurence in S of any character in ACCEPT.  */
char *strpbrk __P ((__const char *__s, __const char *__accept));
/* Find the first occurence of NEEDLE in HAYSTACK.  */
char *strstr __P ((__const char *__haystack, __const char *__needle));
/* Divide S into tokens separated by characters in DELIM.  */
char *strtok __P ((char *__s, __const char *__delim));

#ifdef	__USE_GNU
/* Find the first occurence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
__ptr_t memmem __P ((__const __ptr_t __haystack,
			    size_t __haystacklen,
			    __const __ptr_t __needle,
			    size_t __needlelen));
#endif

/* Return the length of S.  */
size_t strlen __P ((__const char *__s));

/* Return a string describing the meaning of the errno code in ERRNUM.  */
char *strerror __P ((int __errnum));

#ifdef	__USE_BSD
/* Find the first occurrence of C in S (same as strchr).  */
char *index __P ((__const char *__s, int __c));

/* Find the last occurrence of C in S (same as strrchr).  */
char *rindex __P ((__const char *__s, int __c));

#ifndef __linux__

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
void bcopy __P ((__const __ptr_t __src, __ptr_t __dest, size_t __n));

/* Set N bytes of S to 0.  */
void bzero __P ((__ptr_t __s, size_t __n));

/* Compare N bytes of S1 and S2 (same as memcmp).  */
int bcmp __P ((__const __ptr_t __s1, __const __ptr_t __s2, size_t __n));

#else

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
void bcopy __P ((__const __ptr_t __src, __ptr_t __dest, int __n));

/* Set N bytes of S to 0.  */
void bzero __P ((__ptr_t __s, int __n));

/* Compare N bytes of S1 and S2 (same as memcmp).  */
int bcmp __P ((__const __ptr_t __s1, __const __ptr_t __s2, int __n));

#endif

/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
int ffs __P ((int __i));

/* Compare S1 and S2, ignoring case.  */
int strcasecmp __P ((__const char *__s1, __const char *__s2));

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
char *strsep __P ((char **__stringp, __const char *__delim));
#endif

#ifdef	__USE_GNU
/* Compare no more than N chars of S1 and S2, ignoring case.  */
int strncasecmp __P ((__const char *__s1, __const char *__s2,
			     size_t __n));

/* Return a string describing the meaning of the signal number in SIG.  */
char *strsignal __P ((int __sig));

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
char *stpcpy __P ((char *__dest, __const char *__src));

/* Copy no more then N bytes from SRC to DEST, returning the address
   of the terminating '\0' in DEST.  */
char *__stpncpy __P ((char *__dest, __const char *__src, size_t __n));
char *stpncpy __P ((char *__dest, __const char *__src, size_t __n));

/* Sautee STRING briskly.  */
char *strfry __P ((char *__string));

/* Frobnicate N bytes of S.  */
__ptr_t memfrob __P ((__ptr_t __s, size_t __n));

void swab __P ((__const __ptr_t __from, __ptr_t __to,
                        size_t __nbytes));
#endif

__END_DECLS

#endif /* string.h  */
