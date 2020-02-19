/*
    Olly BP Man - PDK Redefines
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

// I'm not a fan of the PDK's naming conventions so I redefine them here to my liking.

#ifndef __OLLY_REDEFINES_H__
#define __OLLY_REDEFINES_H__

#define olly_add_sorted_data            Addsorteddata
#define olly_add_to_list                Addtolist
#define olly_create_dump_window         Createdumpwindow
#define olly_create_sorted_data         Createsorteddata
#define olly_destroy_sorted_data        Destroysorteddata
#define olly_find_module                Findmodule
#define olly_find_name                  Findname
#define olly_find_thread                Findthread
#define olly_get_cpu_thread_id          Getcputhreadid
#define olly_get_sorted_by_selection    Getsortedbyselection
#define olly_get_status                 Getstatus
#define olly_insert_name                Insertname
#define olly_message                    Message
#define olly_paint_table                Painttable
#define olly_plugin_get_value           Plugingetvalue
#define olly_quick_table_window         Quicktablewindow
#define olly_register_plugin_class      Registerpluginclass
#define olly_set_breakpoint             Setbreakpoint
#define olly_set_breakpoint_ext         Setbreakpointext
#define olly_table_function             Tablefunction
#define olly_unregister_plugin_class    Unregisterpluginclass

#endif