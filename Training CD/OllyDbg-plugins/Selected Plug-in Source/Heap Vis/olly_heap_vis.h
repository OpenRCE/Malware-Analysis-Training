/*
    Olly Heap Vis - Header File
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

#ifndef __OLLY_HEAP_VIS_H__
#define __OLLY_HEAP_VIS_H__

#undef DEBUG

//
// heap_vis table entry structure.
//

typedef struct t_heap_vis
{
    ulong index;
    ulong size;
    ulong type;
    DWORD base;
    DWORD block;
    DWORD block_size;
    char  desc[12];
} t_heap_vis;

//
// global variables.
//

HINSTANCE hinst;                    // DLL instance
HWND      hwmain;                   // handle of main OllyDbg window
t_table   heap_vis_table;           // plugin's output table
char      heap_vis_class[32];       // name of the plugin's window class

//
// function prototypes.
//

DWORD            get_process_id             (void);
void             heaps_create_visualization (void);
void             heaps_jump_to_chunk        (void);
void             heaps_search               (void);
void             heaps_view                 (void);
void             tw_add_element             (ulong, DWORD, DWORD, DWORD, char *);
void             tw_create_window           (void);
int              tw_get_line                (char *, char *, int *, t_sortheader *, int);
int              tw_sort_func               (t_heap_vis *, t_heap_vis *, int);
LRESULT CALLBACK tw_winproc                 (HWND, UINT, WPARAM, LPARAM);

#endif