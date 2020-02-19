/*
    Olly BP Man - Header File
    Copyright (C) 2005 Pedram Amini <pamini@idefense.com,pedram.amini@gmail.com>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __OLLY_BP_MAN_H__
#define __OLLY_BP_MAN_H__

#define DIALOG_SAVE 0
#define DIALOG_OPEN 1

#undef DEBUG

//
// dynamically resolved function pointers.
//

typedef DWORD (WINAPI *lpfGetMappedFileName) (HANDLE, LPVOID, LPTSTR, DWORD);

static lpfGetMappedFileName pGetMappedFileName = NULL;

//
// linked list data struct.
//

typedef struct __node
{
    char name[SHORTLEN + 1];
    char path[1024];
    struct __node *next;
} node;

//
// global variables.
//

HINSTANCE hinst;                    // DLL instance/
HWND      hwmain;                   // handle of main OllyDbg window.
node      *module_list;             // linked list of module breakpoint lists to load.
int       num_modules;              // number of modules in linked list.

//
// function prototypes.
//

char * dialog_get_filename      (int);
void   export_breakpoints       (char *);
BOOL   get_filename_from_handle (HANDLE, char *);
BOOL   import_breakpoints       (char *);
void   node_add                 (node *, node **, int *);
node * node_find_by_name        (char *, node *);
void   node_free_list           (node **, int *);
void   node_remove              (char *, node **, int *);

#endif