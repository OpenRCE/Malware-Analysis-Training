/* 
   windows.h

   Include this file if you wish to use the Windows32 API Library

   Copyright (C) 1996 Free Software Foundation

   Author:  Scott Christley <scottc@net-community.com>
   Date: 1996
   
   This file is part of the Windows32 API Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   If you are interested in a warranty or support for this source code,
   contact Scott Christley <scottc@net-community.com> for more information.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation, 
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/ 

#ifndef _GNU_H_WINDOWS_H
#define _GNU_H_WINDOWS_H

#ifndef RC_INVOKED
#include <limits.h>
#include <stdarg.h>
#endif

/* Base definitions */
#include <Windows32/Base.h>

/* WIN32 messages */
#include <Windows32/Messages.h>

/* WIN32 definitions */
#include <Windows32/Defines.h>

#ifndef RC_INVOKED

/* WIN32 structures */
#include <Windows32/Structures.h>

/* WIN32 functions */
#include <Windows32/Functions.h>

#endif /* ! defined (RC_INVOKED) */

/* WIN32 error codes */
#include <Windows32/Errors.h>

#ifndef RC_INVOKED

/* Windows sockets specification version 1.1 */
#ifdef Win32_Winsock
#include <Windows32/Sockets.h>
#endif

/* How do we get the VM page size on NT? */
#ifndef vm_page_size
#define vm_page_size 4096
#endif

#endif /* ! defined (RC_INVOKED) */

#endif /* _GNU_H_WINDOWS_H */
