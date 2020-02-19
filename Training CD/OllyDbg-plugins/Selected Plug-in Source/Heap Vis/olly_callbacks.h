/*
    Olly Heap Vis - Call Back Functions
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

//
// ollydbg call-back functions.
//

BOOL WINAPI DllEntryPoint (HINSTANCE hi, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        hinst = hi;

    return TRUE;
}


int _export cdecl ODBG_Plugindata (char shortname[32])
{
    strcpy(shortname, "Heap Vis");
    return PLUGIN_VERSION;
}


int _export cdecl ODBG_Plugininit (int ollydbgversion, HWND hw, ulong *features)
{
    if (ollydbgversion < PLUGIN_VERSION)
        return -1;

    // keep a handle to the main OllyDbg window.
    hwmain = hw;

    if (olly_register_plugin_class(heap_vis_class, NULL, hinst, tw_winproc) < 0)
    {
        olly_destroy_sorted_data(&(heap_vis_table.data));

        // plugin failed to load.
        return -1;
    }

    olly_add_to_list(0, 0,  "Heap Vis Plug-in compiled on " __DATE__);
    olly_add_to_list(0, -1, "  Copyright (c) 2005 Pedram Amini <pedram.amini@gmail.com>");

    return 0;
}


void _export cdecl ODBG_Plugindestroy (void)
{
    olly_unregister_plugin_class(heap_vis_class);
    olly_destroy_sorted_data(&(heap_vis_table.data));
}


int _export cdecl ODBG_Pluginmenu (int origin, char data[4096], void *item)
{
    switch (origin)
    {
        case PM_MAIN:
            strcpy(data,
                   "0 View Heaps,"
                   "1 Search Heaps,"
                   "2 Jump to Heap Chunk,|"
                   "3 Create Heap Visualization|"
                   "9 About"
                  );
            return 1;
        case PM_DISASM:
        case PM_CPUDUMP:
            // a process must be loaded and suspended for us to display this menu.
            if (olly_get_status() != STAT_STOPPED)
                return 0;

            strcpy(data,
                   "Heap Vis {"
                       "0 View Heaps,"
                       "1 Search Heaps,"
                       "2 Jump to Heap Chunk,|"
                       "3 Create Heap Visualization"
                   "}"
                  );
            return 1;
        default:
            break;
    }

    return 0;
}


void _export cdecl ODBG_Pluginaction (int origin, int action, void *item)
{
    switch (origin)
    {
        case PM_MAIN:
        case PM_DISASM:
        case PM_CPUDUMP:
            switch (action)
            {
                // View heaps
                case 0:
                    if (olly_get_status() == STAT_STOPPED)
                        heaps_view();
                    else
                        Error("Process must be in a suspended state for Heap Vis to work.");
                    break;

                // Search heaps
                case 1:
                    if (olly_get_status() == STAT_STOPPED)
                        heaps_search();
                    else
                        Error("Process must be in a suspended state for Heap Vis to work.");
                    break;

                // Jump to heap address
                case 2:
                    if (olly_get_status() == STAT_STOPPED)
                        heaps_jump_to_chunk();
                    else
                        Error("Process must be in a suspended state for Heap Vis to work.");
                    break;

                // Create heap visualization
                case 3:
                    if (olly_get_status() == STAT_STOPPED)
                        heaps_create_visualization();
                    else
                        Error("Process must be in a suspended state for Heap Vis to work.");
                    break;

                // About
                case 9:
                    MessageBox(hwmain,
                        "Heap Vis Plug-in\n\n"
                        "Copyright (c) 2005 Pedram Amini <pedram.amini@gmail.com>\n",
                        "About Heap Vis Plug-in",
                        MB_OK | MB_ICONINFORMATION);
                    break;
            }

        default:
            break;
    }
}
