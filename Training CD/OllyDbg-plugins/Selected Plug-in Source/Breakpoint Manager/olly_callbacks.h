/*
    Olly BP Man - Call Back Functions
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
    strcpy(shortname, "Breakpoint Manager");

    return PLUGIN_VERSION;
}


int _export cdecl ODBG_Plugininit (int ollydbgversion, HWND hw, ulong *features)
{
    HMODULE h_psapi;

    if (ollydbgversion < PLUGIN_VERSION)
        return -1;

    // keep a handle to the main OllyDbg window.
    hwmain = hw;

    // resolve function pointers.
    if ((h_psapi = LoadLibrary("psapi.dll")) != NULL)
        pGetMappedFileName = (lpfGetMappedFileName)  GetProcAddress(h_psapi, "GetMappedFileNameA");

    // initialize global variables.
    module_list = NULL;
    num_modules = 0;

    olly_add_to_list(0, 0,  "Breakpoint Manager Plug-in compiled on " __DATE__);
    olly_add_to_list(0, -1, "  Copyright (c) 2005 Pedram Amini <pamini@idefense.com> <pedram.amini@gmail.com>");

    return 0;
}


void _export cdecl ODBG_Plugindestroy (void)
{
    // free the modules linked list.
    node_free_list(&module_list, &num_modules);
}


// as new modules are loaded, the plugin will look in a directory for a breakpoint list matching the
// loaded module's name. if found, the module / breakpoint list will be added to a processing queue.
// we use a queue here because the module is not memory mapped at the time of the LOAD_DLL_DEBUG_EVENT event.
void _export cdecl ODBG_Pluginmainloop (DEBUG_EVENT *dbg)
{
    t_module *module;
    t_table  *mod_table;
    FILE     *bpl;
    BOOL     module_loaded = FALSE;
    node     *module_node;
    node     *cursor;
    char     bpl_path[1024];
    char     filename[256];
    char     just_name[SHORTLEN];
    char     *dot;
    int      i;

    // if the modules list is not empty. attempt to resolve and process them.
    if (num_modules)
    {
        // get a pointer to the modules table.
        if ((mod_table = (t_table *) olly_plugin_get_value(VAL_MODULES)) == NULL)
            return;

        // for each module in the linked list.
        for (cursor = module_list; cursor != NULL; cursor = cursor->next)
        {
            // determine if this module has been mapped into memory.
            for (i = 0; i < mod_table->data.n; i++)
            {
                // grab the module at index 'i'.
                if ((module = (t_module *) olly_get_sorted_by_selection(&(mod_table->data), i)) == NULL)
                    continue;

                // create the temporary variable just name.
                memset(just_name, 0, sizeof(just_name));
                strncpy(just_name, module->name, SHORTLEN);

                // truncate the string at the first 'dot'.
                if ((dot = strchr(just_name, '.')) != NULL)
                    *dot = 0;

                // module found. load the breakpoints.
                if (strnicmp(just_name, module->name, SHORTLEN) == 0)
                {
                    // import the breakpoints for this module.
                    // if 'true' is returned then we remove the module from the list to prevent future attempts at re-processing.
                    if (import_breakpoints(cursor->path))
                    {
                        olly_add_to_list(0, 0, "BP Manager> Breakpoint list for module %s loaded.", cursor->name);

                        // remove this module from the linked list.
                        node_remove(cursor->name, &module_list, &num_modules);
                        break;
                    }
                    else
                    {
                        olly_add_to_list(0, 0, "BP Manager> Failed to load breakpoint list, will try again later.");
                        break;
                    }
                }
            }
        }
    }

    // if no debug event was passed to us, return.
    if (dbg == NULL)
        return;

    // only interested in load dll events.
    if (dbg->dwDebugEventCode != LOAD_DLL_DEBUG_EVENT)
        return;

    memset(filename, 0, sizeof(filename));

    // determine the filename of the recently loaded module.
    if (get_filename_from_handle(dbg->u.LoadDll.hFile, filename))
    {
        memset(bpl_path, 0, sizeof(bpl_path));
        _snprintf(bpl_path, sizeof(bpl_path), "breakpoints\\%s.obp", filename);

        // determine if a breakpoint list for this module exists..
        if ((bpl = fopen(bpl_path, "r")) != NULL)
        {
            fclose(bpl);

            // if we already have this module in the modules list, return.
            if (node_find_by_name(filename, module_list) != NULL)
                return;

            // add this module to the modules list.
            module_node = (node *) malloc(sizeof(node));
            memset(module_node, 0, sizeof(module_node));
            strncpy(module_node->name, filename, SHORTLEN);
            strncpy(module_node->path, bpl_path, 1024);
            node_add(module_node, &module_list, &num_modules);

            #ifdef DEBUG
                olly_add_to_list(0, 1, "BP Manager> Added %s to linked list.", module_node->name);
            #endif
        }
    }
}


int _export cdecl ODBG_Pluginmenu (int origin, char data[4096], void *item)
{
    switch (origin)
    {
        case PM_MAIN:
            strcpy(data,
                   "0 Import Breakpoints,"
                   "1 Export Breakpoints|"
                   "9 About"
                  );
            return 1;
        case PM_BREAKPOINTS:
            // a process must be loaded and suspended for us to display this menu.
            if (olly_get_status() != STAT_STOPPED)
                return 0;

            strcpy(data,
                   "Breakpoint Manager {"
                   "0 Import Breakpoints,"
                   "1 Export Breakpoints"
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
    char *filename;

    switch (origin)
    {
        case PM_MAIN:
        case PM_BREAKPOINTS:
            switch (action)
            {
                // import breakpoints.
                case 0:
                    if (olly_get_status() != STAT_STOPPED)
                        return;

                    // prompt the user for the file to import from.
                    if ((filename = dialog_get_filename(DIALOG_OPEN)) == NULL)
                    {
                        olly_add_to_list(0, 1, "BP Manager> Import cancelled.");
                        return;
                    }

                    import_breakpoints(filename);
                    break;
                // export breakpoints.
                case 1:
                    if (olly_get_status() != STAT_STOPPED)
                        return;

                    // prompt the user for the file to export to.
                    if ((filename = dialog_get_filename(DIALOG_SAVE)) == NULL)
                    {
                        olly_add_to_list(0, 1, "BP Manager> Export cancelled.");
                        return;
                    }

                    export_breakpoints(filename);
                    break;

                // about
                case 9:
                    MessageBox(hwmain,
                        "Breakpoint Manager Plug-in\n\n"
                        "Copyright (c) 2005 Pedram Amini <pamini@idefense.com> <pedram.amini@gmail.com>\n",
                        "About Breakpoint Manager Plug-in",
                        MB_OK | MB_ICONINFORMATION);
                    break;
            }

        default:
            break;
    }
}
