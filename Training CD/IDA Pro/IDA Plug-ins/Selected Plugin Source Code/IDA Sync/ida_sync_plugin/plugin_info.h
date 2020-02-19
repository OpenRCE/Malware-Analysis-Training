/*
    IDA Sync Plug-in Info
    Copyright (C) 2005 Pedram Amini <pedram.amini@gmail.com>

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

#ifndef __PLUGIN_INFO_H__
#define __PLUGIN_INFO_H__

//
// These global data items are used by IDA to display information about
// the plugin.
//

char _ida_comment[] = "Pedram Amini IDA Sync";

char _ida_help[] =
    "[ Pedram Amini IDA Sync ]\n"
    "\n"
    "\n"
    "\n";


// This is the preferred name of the plugin module in the menu system.
// The preferred name may be overridden in the plugins.cfg file.

char _ida_wanted_name[] = "ida_sync";


// This is the preferred hot key for the plugin module.
// The preferred hot key may be overridden in the plugins.cfg file.
// Note: IDA won't tell you if the hot key is not correct.
// It will just disable the hot key.

char _ida_wanted_hotkey[] = "Alt-Shift-C";


//
// PLUGIN DESCRIPTION BLOCK
//

extern "C" plugin_t PLUGIN =
{
    IDP_INTERFACE_VERSION,
    0,                  // plugin flags.
    _ida_init,          // initialize callback.
    _ida_term,          // terminate callback. this pointer may be NULL.
    _ida_run,           // invoke plugin routine.
    _ida_comment,       // long comment about the plugin.
                        // it could appear in the status line
                        // or as a hint.
    _ida_help,          // multiline help about the plugin.
    _ida_wanted_name,   // the preferred short name of the plugin.
    _ida_wanted_hotkey  // the preferred hot key to run the plugin.
};

#endif