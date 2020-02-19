/*
    IDA Sync Plug-in
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

// we must define _WINSOCKAPI_ prior to including windows.h, otherwise compilation
// will fail on a number of redefinition errors in winsock structures.
#define _WINSOCKAPI_

#include <windows.h>
#include <winsock2.h>

#include <ida.hpp>
#include <idp.hpp>
#include <bytes.hpp>
#include <expr.hpp>
#include <frame.hpp>
#include <kernwin.hpp>
#include <loader.hpp>
#include <name.hpp>
#include <struct.hpp>

#pragma warning (disable:4273)

#include "ida_sync.h"
#include "IDAconnector.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
// _ida_init()
//
// IDA will call this function only once.
// If this function returns PLUGIN_SKIP, IDA will never load it again.
// If this function returns PLUGIN_OK, IDA will unload the plugin but
// remember that the plugin agreed to work with the database.
// The plugin will be loaded again if the user invokes it by
// pressing the hot key or by selecting it from the menu.
// After the second load, the plugin will stay in memory.
// If this function returns PLUGIN_KEEP, IDA will keep the plugin
// in memory.
//
// arguments: none.
// returns:   plugin status.
//

int _ida_init (void)
{
    msg("\n[*] ida_sync initialized. Compiled on " __DATE__ "\n");
    msg("[*] Pedram Amini <pedram.amini@gmail.com>\n\n");

    return PLUGIN_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////
// _ida_run()
//
// the run function is called when the user activates the plugin. this is the main
// function of the plugin.
//
// arguments: arg - the input argument. it can be specified in the
//                  plugins.cfg file. the default is zero.
// returns:   none.
//

void _ida_run (int arg)
{
    // parse the argument.
    switch (arg)
    {
        // default plug-in run.
        // connect to the server.
        case 0:
            connector->server_connect();

            if (!connector->is_connected())
                return;

            msg("[*] IDA Sync> Connection to server established.\n");
            break;

        // regular indented comment hook.
        case 1:
            if (connector->is_connected())
                insert_comment(get_screen_ea(), false);
            break;

        // repeatable comment hook.
        case 2:
            if (connector->is_connected())
                insert_comment(get_screen_ea(), true);
            break;

        // name hook.
        case 3:
            if (connector->is_connected())
                insert_name(get_screen_ea());
            break;

        // publish all function names hook
        case 4:
            if (connector->is_connected())
                publish_all_func_names();
            break;

        default:
            break;
    }

    // force a refresh.
    refresh_idaview_anyway();
}


/////////////////////////////////////////////////////////////////////////////////////////
// _ida_term()
//
// IDA will call this function when the user asks to exit. this function will not be
// called in the case of emergency exists. usually this callback is empty.
//
// arguments: none.
// returns:   none.
//

void _ida_term (void)
{
    connector->cleanup();
}


/////////////////////////////////////////////////////////////////////////////////////////
// connector_pull()
//
// this routine is called by the socket_proc notification hook to handle inbound data
// from the server.
//
// arguments: none.
// returns:   false if socket connection was severed, true otherwise.
//

bool connector_pull (void)
{
    int   len;
    char  buf  [1024];
    char  data [1024];
    char  name [1024];
    int   command;
    int   name_flags;

    ea_t   address;
    ea_t   offset;
    SOCKET connection;

    struc_t *stk_frame;

    memset(buf,     0, sizeof(buf));
    memset(data,    0, sizeof(data));

    // grab the socket we wil be reading from.
    connection = connector->get_connection();

    len = recv(connection, buf, sizeof(buf) - 1, 0);

    // connection closed.
    if (len == 0 || len == SOCKET_ERROR)
    {
        connector->cleanup();
        msg("[!] IDA Sync> Socket read failed. Connection closed.\n");
        return false;
    }

    // null terminate the string.
    buf[len] = 0;

    // parse the inbound request. if we can't extract the correct fields, return.
    if (sscanf(buf, "%d:::%08x:::%1023[^\0]", &command, &address, data) != 3)
        return true;

    //
    // handle the received command appropriately.
    //

    switch(command)
    {
        case IDA_SYNC_COMMAND_JUMPTO:
            jumpto(address);
            break;

        case IDA_SYNC_COMMAND_NAME:
            if (sscanf(data,"%08x*%1023[^0]", &name_flags, name) != 2)
            {
                msg("[!] IDA Sync> Received invalid name command.\n");
                break;
            }

            msg("[*] IDA Sync> Received new name @%08x: %s\n", address, name);
            set_name(address, name, name_flags);
            break;

        case IDA_SYNC_COMMAND_REG_COMMENT:
            msg("[*] IDA Sync> Received regular comment @%08x: %s\n", address, data);
            set_cmt(address, data, false);
            break;

        case IDA_SYNC_COMMAND_REP_COMMENT:
            msg("[*] IDA Sync> Received repeatable comment @%08x: %s\n", address, data);
            set_cmt(address, data, true);
            break;

        case IDA_SYNC_COMMAND_STACK_VAR_NAME:
            if (sscanf(data,"%08x*%1023[^0]", &offset, name) != 2)
            {
                msg("[!] IDA Sync> Received invalid stack name command.\n");
                break;
            }

            msg("[*] IDA Sync> Received new stack variable name @%08x: %s\n", address, name);
            stk_frame = get_frame(address);
            set_member_name(stk_frame, offset, name);
            break;

        default:
            msg("[*] IDA Sync> Received unknown command code: %d, ignoring.\n", command);
    }

    // force a refresh.
    refresh_idaview_anyway();

    // ping pong.
    send(connection, "1", 1, 0);

    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////
// connector_push()
//
// this routine is utilized to transmit data to the server.
//
// arguments: buf - buffer containing data to send to server.
// returns:   boolean value representing success.
//

bool connector_push (char *buf)
{
    int    len;
    SOCKET connection;

    // grab the socket we wil be writing to.
    connection = connector->get_connection();

    len = strlen(buf);

    if (send(connection, buf, len, 0) != len)
    {
        connector->cleanup();
        msg("[!] IDA Sync> Socket write failed. Connection closed.\n");
        return false;
    }

    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////
// insert_comment()
//
// prompt the user for a comment and insert it at the specified address. push the
// comment/address pair to the server.
//
// arguments: ea         - effective address to add comment.
//            repeatable - boolean flag for whether or not this comment is repeatable.
// returns:   none.
//

void insert_comment (ea_t ea, bool repeatable)
{
    char buf     [MAXSTR+128];
    char comment [MAXSTR];
    char title   [128];

    memset(buf,     0, sizeof(buf));
    memset(comment, 0, sizeof(comment));
    memset(title,   0, sizeof(title));

    if (repeatable)
        qstrncpy(title, "IDA Sync> Enter repeatable comment.", sizeof(title));
    else
        qstrncpy(title, "IDA Sync> Enter comment.", sizeof(title));

    // present the user with a multi-line form to enter a comment.
    get_cmt(ea, repeatable, comment, sizeof(comment) - 1);

    if (asktext(MAXSTR - 1, comment, comment, title) == NULL)
        return;

    // update the comment in the local IDA database.
    set_cmt(ea, comment, repeatable);

    // push the entered comment to the server.
    if (repeatable)
        qsnprintf(buf, sizeof(buf) - 1, "%d:::%08x:::%s", IDA_SYNC_COMMAND_REP_COMMENT, ea, comment);
    else
        qsnprintf(buf, sizeof(buf) - 1, "%d:::%08x:::%s", IDA_SYNC_COMMAND_REG_COMMENT, ea, comment);

    if (connector_push(buf))
        msg("[*] IDA Sync> Successfully pushed comment at address 0x%08x to server.\n", ea);
}


/////////////////////////////////////////////////////////////////////////////////////////
// insert_name()
//
// prompt the user for a name and insert it at the specified address. push the
// name/address pair to the server.
//
// arguments: ea - effective address to add name.
// returns:   none.
//

void insert_name (ea_t ea)
{
    char buf      [MAXSTR+128];
    char old_name [MAXSTR];
    char new_name [MAXSTR];
    char sel_name [MAXSTR];

    ea_t  name_address = BADADDR;
    ea_t  fcref_from   = get_first_fcref_from(ea);
    ea_t  dref_from    = get_first_dref_from (ea);
    ea_t  fcref_to     = get_first_fcref_to  (ea);
    ea_t  dref_to      = get_first_dref_to   (ea);
    short check_boxes  = 0;
    int   name_flags   = 0;
    int   x, y;

    struc_t  *stk_frame;
    ea_t      stk_offset;
    func_t   *pfn;
    member_t *stk_item;
    char     *line;
    char     *selection;

    const short IB_LOCAL    = 0x1;
    const short IB_INCLUDE  = 0x2;
    const short IB_PUBLIC   = 0x4;
    const short IB_AUTO     = 0x8;

    const char dialog_format [] =
        "STARTITEM 0\n"
        "IDA Sync Rename Address\n"
        "Address: %$\n"
        "<~N~ame:A:255:32::>\n"
        "         <Local name:C>\n"
        "         <Include in names list:C>\n"
        "         <Public name:C>\n"
        "         <Autogenerated name:C>>\n\n";

    const char dialog_stk_var [] =
        "STARTITEM 0\n"
        "IDA Sync Rename Stack Variable\n"
        "<Enter stack variable name:A:255:64::>\n";

    memset(buf,      0, sizeof(buf));
    memset(old_name, 0, sizeof(old_name));
    memset(new_name, 0, sizeof(new_name));
    memset(sel_name, 0, sizeof(sel_name));

    // default flags:
    //
    //      offset names are default "include in names list" and "autogenerated name".
    //      sub names are default "include in names list"
    //      location names are default "local name"

    //
    // stack variable names.
    //

    // get x/y coordinates of cursor.
    get_cursor(&x, &y);

    // retrieve the current line.
    line = get_curline();
    tag_remove(line, buf, sizeof(buf));
    extract_name(buf, x, sel_name, sizeof(sel_name));

    // the stack variable name is the last item.
    selection = sel_name;

    while (strstr(selection, "+") != NULL)
        selection = strstr(selection, "+") + 1;

    while (strstr(selection, "-") != NULL)
        selection = strstr(selection, "-") + 1;

    // retrieve the stack frame pointer.
    stk_frame = get_frame(ea);

    // retrieve a pointer pointer to the current function.
    pfn = get_func(ea);

    stk_offset = find_offset_from_name( stk_frame, pfn, selection );

    // rename the stack variable.
    if (stk_offset != -1)
    {
        // calculate the stack offset based on the current function, the address, and the operand
        // XXX - need to figure out how to know which operand we have selected.

        // retrieve the stack frame member.
        stk_item = get_member(stk_frame, stk_offset);

        // retrieve the item name and copy it as the default value.
        get_member_name(stk_item->id, new_name, sizeof(new_name) - 1);

        // present the user with a dialog asking for the new name.
        // if cancel was selected then simply return.
        if (!AskUsingForm_c(dialog_stk_var, new_name))
            return;

        // set the stack_frame member name based on the stack frame pointer and the offset.
        set_member_name(stk_frame, stk_offset, new_name);

        // push the entered name to the server.
        qsnprintf(buf, sizeof(buf) - 1, "%d:::%08x:::%08x*%s", IDA_SYNC_COMMAND_STACK_VAR_NAME, ea, stk_offset, new_name);

        if (connector_push(buf))
            msg("[*] IDA Sync> Successfully pushed stack variable name at offset 0x%08x:0x%08x to server.\n", ea, stk_offset);

        return;
    }

    //
    // offset names.
    //

    if (dref_to != BADADDR)                 // current ea is an offset name.
    {
        check_boxes = IB_INCLUDE | IB_AUTO;
        get_name(BADADDR, ea, old_name, MAXSTR - 1);
        name_address = get_name_ea(ea, old_name);
    }

    else if (dref_from != BADADDR)          // current ea references an offset name.
    {
        check_boxes = IB_INCLUDE | IB_AUTO;
        get_name(ea, dref_from, old_name, MAXSTR - 1);
        name_address = get_name_ea(dref_from, old_name);
    }

    //
    // sub-routine names.
    //

    else if (is_sub_routine(ea))            // current ea is the start of a sub-routine.
    {
        check_boxes = IB_INCLUDE;
        get_name(BADADDR, ea, old_name, MAXSTR - 1);
        name_address = get_name_ea(ea, old_name);
    }

    else if (is_sub_routine(fcref_from))    // current ea calls a sub-routine.
    {
        check_boxes = IB_INCLUDE;
        get_name(ea, fcref_from, old_name, MAXSTR - 1);
        name_address = get_name_ea(fcref_from, old_name);
    }

    //
    // location names.
    //

    else if (fcref_to != BADADDR)           // current ea is the start of a location.
    {
        check_boxes = IB_LOCAL;
        get_name(BADADDR, ea, old_name, MAXSTR - 1);
        name_address = get_name_ea(ea, old_name);
    }

    else if (fcref_from != BADADDR)         // current ea references a location.
    {
        check_boxes = IB_LOCAL;
        get_name(ea, fcref_from, old_name, MAXSTR - 1);
        name_address = get_name_ea(fcref_from, old_name);
    }
    else                                    // there is no name at this location.
    {
        return;
    }

    // ensure we have a name.
    if (name_address == BADADDR)
        return;

    qstrncpy(new_name, old_name, sizeof(new_name));

    // present the user with a dialog asking for the new name.
    // if cancel was selected then simply return.
    if (!AskUsingForm_c(dialog_format, &name_address, new_name, &check_boxes))
        return;

    // parse the radio button value and set the appropriate name flags.
    if (check_boxes & IB_LOCAL)      name_flags |= SN_LOCAL;
    if (check_boxes & IB_PUBLIC)     name_flags |= SN_PUBLIC;
    if (check_boxes & IB_AUTO)       name_flags |= SN_AUTO;
    if (!(check_boxes & IB_INCLUDE)) name_flags |= SN_NOLIST;

    // update the name in the local IDA database.
    set_name(name_address, new_name, name_flags);

    // push the entered name to the server.
    qsnprintf(buf, sizeof(buf) - 1, "%d:::%08x:::%08x*%s", IDA_SYNC_COMMAND_NAME, name_address, name_flags, new_name);

    if (connector_push(buf))
        msg("[*] IDA Sync> Successfully pushed name at address 0x%08x to server.\n", name_address);
}


/////////////////////////////////////////////////////////////////////////////////////////
// is_sub_routine()
//
// determine if the supplied address is the start of a sub-routine.
//
// arguments: ea - effective address to examine.
// returns:   boolean value.
//

bool is_sub_routine (ea_t ea)
{
    func_t *fptr;
    size_t i;

    // step through all functions.
    for (i = 0; i < get_func_qty(); i++)
    {
        // get a pointer to the current function.
        if ((fptr = getn_func(i)) == NULL)
            continue;

        // see if we have a match.
        if (fptr->startEA == ea)
            return true;
    }

    return false;
}



/////////////////////////////////////////////////////////////////////////////////////////
// publish_all_func_names()
//
// push all function names to the server.
//
// arguments: none.
// returns:   none.
//

void publish_all_func_names ()
{
    func_t *fptr;
    size_t i;
    char func_name[MAXSTR];
    char buf      [MAXSTR + 128];

    memset(func_name, 0, sizeof(func_name));
    memset(buf,       0, sizeof(buf));

    // step through all functions.
    for (i = 0; i < get_func_qty(); i++)
    {
        // get a pointer to the current function.
        if ((fptr = getn_func(i)) == NULL)
            continue;

        if (get_name(BADADDR, fptr->startEA, func_name, MAXSTR - 1) == NULL)
            continue;

		// we don't want to push the generic IDA generated names to the sync server.
		if (strnicmp(func_name, "sub_", 4) == 0)
			continue;

        // push the entered comment to the server.
        qsnprintf(buf, sizeof(buf) - 1, "%d:::%08x:::%08x*%s", IDA_SYNC_COMMAND_NAME, fptr->startEA, fptr->flags, func_name);

        if (connector_push(buf))
            msg("[*] IDA Sync> Successfully pushed function '%s' @0x%08x to server.\n", func_name, fptr->startEA);
    }
}



//////////////////////////////////////////////////////////////////////////////////////
// find_offset_from_name()
//
// walk the stack structure and find the offset for a given name.
//
// arguments: stk_frame - stack struct_t
//            pfn       - function pfn
//            name      - name to find
// returns:   unsigned

long find_offset_from_name (struc_t *stk_frame, func_t *pfn, char *name)
{
    unsigned i;
    char item_name [MAXSTR];
    member_t *stk_item;

    for (i = 0; i <= get_frame_size(pfn); i++)
    {
        stk_item = get_member(stk_frame, i);

        if (stk_item != NULL)
        {
            get_member_name(stk_item->id, item_name, sizeof(item_name) - 1);

            if (strcmp(item_name, name) == 0)
                return i;
        }
    }

    return -1;
}

// include the data structures that describe the plugin to IDA.
#include "plugin_info.h"
