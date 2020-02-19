/*
    Olly BP Man
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

#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>

#include "olly_redefines.h"
#include "plugin.h"
#include "olly_bp_man.h"
#include "olly_callbacks.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dialog_get_filename()
//
// display a sexy little dialog asking the user for a filename.
//
// arguments: dialog type - DIALOG_SAVE or DIALOG_OPEN.
// returns:   file path on success or NULL on error.
//

char *dialog_get_filename (int dialog_type)
{
    static TCHAR filename[MAX_PATH];
    OPENFILENAME FileName;

    memset(filename, 0, MAX_PATH - 1);

    FileName.lStructSize       = sizeof(OPENFILENAME);
    FileName.hwndOwner         = hwmain;
    FileName.hInstance         = GetModuleHandle(NULL);
    FileName.lpstrFilter       = "Breakpoint List (.obp)\0*.obp\0\0";
    FileName.lpstrCustomFilter = NULL;
    FileName.nMaxCustFilter    = 0;
    FileName.nFilterIndex      = 1;
    FileName.lpstrFile         = filename;
    FileName.nMaxFile          = MAX_PATH - 1;
    FileName.lpstrFileTitle    = NULL;
    FileName.nMaxFileTitle     = 0;
    FileName.lpstrInitialDir   = "C:\\Program Files\\OllyDBG\\";
    FileName.nFileOffset       = 0;
    FileName.nFileExtension    = 0;
    FileName.lpstrDefExt       = "bpl";
    FileName.lCustData         = 0;
    FileName.lpfnHook          = NULL;
    FileName.lpTemplateName    = NULL;
    FileName.Flags             = OFN_EXPLORER | OFN_NOCHANGEDIR;

    switch (dialog_type)
    {
        case DIALOG_OPEN:
            FileName.lpstrTitle = "Select File For Import";

            if (GetOpenFileName(&FileName))
                return filename;

            break;
        case DIALOG_SAVE:
            FileName.lpstrTitle = "Select File For Export";

            if (GetSaveFileName(&FileName))
                return filename;

            break;
    }

    return NULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

void export_breakpoints (char *filename)
{
    t_bpoint *bp;
    t_module *module;
    t_table  *bp_table;
    FILE     *fp;
    char     expression [TEXTLEN];
    char     explanation[TEXTLEN];
    char     saved;
    int      i;

    // attempt to open the target file for writing.
    if ((fp = fopen(filename, "w+")) == NULL)
    {
        olly_add_to_list(0, 1, "BP Manager> Unable to open %s for writing.", filename);
        return;
    }

    // get a pointer to the breakpoint table.
    bp_table = (t_table *) olly_plugin_get_value(VAL_BREAKPOINTS);

    if (bp_table == NULL)
    {
        olly_add_to_list(0, 1, "BP Manager> No breakpoint table found.");
        fclose(fp);
        return;
    }

    // enumerate breakpoints.
    for (i = 0; i < bp_table->data.n; i++)
    {
        memset(expression,  0, sizeof(expression));
        memset(explanation, 0, sizeof(explanation));

        // grab the breakpoint at index 'i'.
        if ((bp = (t_bpoint *) olly_get_sorted_by_selection(&(bp_table->data), i)) == NULL)
        {
            olly_add_to_list(0, 1, "BP Manager> Unable to resolve breakpoint at index %d.", i);
            continue;
        }

        if ((module = olly_find_module(bp->addr)) == NULL)
        {
            olly_add_to_list(bp->addr, 1, "BP Manager> Module for breakpoint at 0x%08x could not be located.");
            continue;
        }

        // name is not null terminated causing it and path to converge together.
        // this fixes what i need but munges the first char of path (which we restore later).
        saved = module->name[SHORTLEN];
        module->name[SHORTLEN] = 0;

        #ifdef DEBUG
            olly_add_to_list(bp->addr, 1, "Breakpoint in %s at %08x", module->name, bp->addr);

            if (olly_find_name(bp->addr, NM_BREAKEXPR, expression) != 0)
                olly_add_to_list(0, 0, "    NM_BREAKEXPR: %s", expression);

            if (olly_find_name(bp->addr, NM_BREAKEXPL, explanation) != 0)
                olly_add_to_list(0, 0, "    NM_BREAKEXPL: %s", explanation);
        #endif

        // breakpoint conditions are stored in the first byte of the NM_BREAKEXPR name.
        // if no expression is found, set to '#'.
        if (olly_find_name(bp->addr, NM_BREAKEXPR, expression) == 0)
            expression[0] = '#';

        // write this breakpoint entry to the breakpoint list file. the format is:
        // module name:breakpoint offset address:expression:explanation (optional, '#' if empty)
        if (olly_find_name(bp->addr, NM_BREAKEXPL, explanation) != 0)
            fprintf(fp, "%s:%08x:%s:%s\n", module->name, bp->addr - module->base, expression, explanation);
        else
            fprintf(fp, "%s:%08x:%s:#\n", module->name, bp->addr - module->base, expression);
    }

    // close the export file.
    fclose(fp);

    // restore the truncated character in name/path.
    module->name[SHORTLEN] = saved;

    olly_add_to_list(0, 0, "BP Manager> Export complete.");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

BOOL get_filename_from_handle (HANDLE h_file, char *target_filename)
{
    HANDLE h_filemap;
    DWORD  file_size_hi = 0;
    char   filename[MAX_PATH + 1];
    char   *stripped;
    void   *mem;

    // ensure our dynamically resolved function pointer is resolved before continuing.
    if (!pGetMappedFileName)
        return FALSE;

    // initialize the filename variable.
    memset(filename, 0, sizeof(filename));

    // get the file size and ensure it's not zero.
    if (GetFileSize(h_file, &file_size_hi) == 0)
        return FALSE;

    // create a file mapping object.
    if ((h_filemap = CreateFileMapping(h_file, NULL, PAGE_READONLY, 0, 1, NULL)) == NULL)
        return FALSE;

    // create a file mapping to get the file name.
    if ((mem = MapViewOfFile(h_filemap, FILE_MAP_READ, 0, 0, 1)) == NULL)
        return FALSE;

    // get the mapped file's name.
    if (!pGetMappedFileName (GetCurrentProcess(), mem, filename, MAX_PATH))
        return FALSE;

    // strip the device path and copy the name to the target buffer.
    stripped = strrchr(filename, '\\');
    strncpy(target_filename, stripped + 1, 256);

    // cleanup.
    UnmapViewOfFile(mem);
    CloseHandle(h_filemap);

    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

BOOL import_breakpoints (char *filename)
{
    t_module *module;
    t_table  *mod_table;
    DWORD    base_address;
    DWORD    address;
    FILE     *fp;
    char     name[16];
    char     expression [TEXTLEN];
    char     explanation[TEXTLEN];
    int      i, ret;

    // attempt to open the target file for reading.
    if ((fp = fopen(filename, "r")) == NULL)
    {
        olly_add_to_list(0, 1, "BP Manager> Unable to open %s for reading.", filename);
        
        // don't try processing this breakpoint list later.
        return TRUE;
    }

    // get a pointer to the modules table.
    mod_table = (t_table *) olly_plugin_get_value(VAL_MODULES);

    if (mod_table == NULL)
    {
        olly_add_to_list(0, 1, "BP Manager> No module table found.");
        fclose(fp);

        // try processing this breakpoint list later.
        return FALSE;
    }

    // parse the input file.
    for (;;)
    {
        memset(name,        0, sizeof(name));
        memset(expression,  0, sizeof(expression));
        memset(explanation, 0, sizeof(explanation));

        // read a line from the file.
        ret = fscanf(fp, "%15[^:]:%08x:%255[^:]:%255[^\n]\n", name, &address, expression, explanation);

        // end of file reached, break loop.
        if (ret == EOF)
            break;

        // if 4 fields weren't read from the line then move on to the next line.
        // this is a cheap hack that allows us to create arbitrary style comments in the file.
        if (ret != 4)
            continue;

        #ifdef DEBUG
            olly_add_to_list(0, 0, "BP Manager> Read BP: %s.%08x expression:%s explanation:%s",
                name, address, expression, explanation);
        #endif

        base_address = 0;

        // enumerate modules looking for a match to determine this breakpoints base address.
        for (i = 0; i < mod_table->data.n; i++)
        {
            // grab the module at index 'i'.
            if ((module = (t_module *) olly_get_sorted_by_selection(&(mod_table->data), i)) == NULL)
            {
                olly_add_to_list(0, 1, "BP Manager> Unable to resolve module at index %d.", i);
                continue;
            }

            // if a match was found, update the base address.
            if (strnicmp(module->name, name, SHORTLEN) == 0)
            {
                base_address = module->base;
                break;
            }
        }

        // ensure a base address was found.
        if (base_address == 0)
        {
            olly_add_to_list(0, 1, "BP Manager> Unable to determine base address for %s.%08x", name, address);
            
            // try processing this breakpoint list later.
            return FALSE;
        }

        // set the breakpoint
        olly_set_breakpoint(base_address + address, TY_ACTIVE, 0);

        // if the breakpoint expression does not start with a '#', set that too.
        if (expression[0] != '#')
            olly_insert_name(base_address + address, NM_BREAKEXPR, expression);

        // if the breakpoint explanation does not start with a '#', set that too.
        if (explanation[0] != '#')
            olly_insert_name(base_address + address, NM_BREAKEXPL, explanation);
    }

    // close the import file.
    fclose(fp);

    olly_add_to_list(0, 0, "BP Manager> Import complete.");
    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// node_add()
//
// add a node to the ordered (by address) list.
//
// arguments: to_add    - pointer to node structure to add.
//            head      - pointer to the head of the list to add to.
//            num_nodes - pointer to the variable storing the node count for this list.
// returns:   none.
//

void node_add (node *to_add, node **head, int *num_nodes)
{
    node *cursor;
    node *last;

    // ensure we have a node to add.
    if (to_add == NULL)
        return;

    // this is the first node.
    if ((*head) == NULL)
    {
        (*head)       = to_add;
        (*head)->next = NULL;

        (*num_nodes)++;
        return;
    }

    // locate the last node in the list.
    for (cursor = (*head)->next, last = (*head); cursor != NULL; cursor = cursor->next)
        last = cursor;

    // add this node to the end of the list.
    to_add->next = NULL;
    last->next   = to_add;

    (*num_nodes)++;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// node_find_by_name()
//
// given a function name searches through the linked list returning a pointer to a node
// if the name is matched.
//
// arguments: module_name - name of the module to find.
//            head        - pointer to the head of the list to search through.
// returns:   pointer to the found node or NULL if not found.
//

node * node_find_by_name (char *module_name, node *head)
{
    node *cursor;

    for (cursor = head; cursor != NULL; cursor = cursor->next)
        if (strnicmp(module_name, cursor->name, SHORTLEN) == 0)
            return cursor;

    return NULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// node_free_list()
//
// traverse through the desired list and free each node.
//
// arguments: head      - pointer to the head of the list to free.
//            num_nodes - pointer to the variable storing the node count for this list.
// returns:   none.
//

void node_free_list (node **head, int *num_nodes)
{
    node *cursor;
    node *tmp;

    // step through the list.
    for (cursor = (*head); cursor != NULL; cursor = tmp)
    {
        tmp = cursor->next;
        free(cursor);
    }

    (*head)      = NULL;
    (*num_nodes) = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// node_remove()
//
// search through the specified list for the node specified by the function id. remove it
// from the ordered (by address) list and return a pointer to it.
//
// note: if you wish to release the memory for the removed node you must free() it
//       manually.
//
// arguments: module_name - name of the module to remove.
//            head        - pointer to the head of the list to remove from.
//            num_nodes   - pointer to the variable storing the node count for this list.
// returns:   none.
//

void node_remove (char *module_name, node **head, int *num_nodes)
{
    node *cursor = NULL;
    node *prev   = NULL;

    // locate the node we wish to remove from the specified list.
    for (cursor = (*head); cursor != NULL; cursor = cursor->next)
    {
        if (strnicmp(module_name, cursor->name, SHORTLEN) == 0)
            break;

        prev = cursor;
    }

    // if the node was found detach it from the list.
    if (cursor)
    {
        // the first node was removed.
        if (prev == NULL)
            (*head) = cursor->next;

        // another node was removed.
        else
            prev->next = cursor->next;

        (*num_nodes)--;

        // the removed cursor shouldn't be pointing to another node anymore.
        cursor->next = NULL;
    }

    // free the memory for the removed node.
    free(cursor);
}