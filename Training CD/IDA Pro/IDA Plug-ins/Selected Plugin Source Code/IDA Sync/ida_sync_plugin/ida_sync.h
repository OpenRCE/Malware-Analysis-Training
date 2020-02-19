/*
    IDA Sync Plug-in Header
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

#ifndef __IDA_SYNC_H__
#define __IDA_SYNC_H__

#define IDA_SYNC_COMMAND_JUMPTO          0x01
#define IDA_SYNC_COMMAND_NAME            0x02
#define IDA_SYNC_COMMAND_REG_COMMENT     0x04
#define IDA_SYNC_COMMAND_REP_COMMENT     0x08
#define IDA_SYNC_COMMAND_STACK_VAR_NAME  0x10

bool connector_pull         (void);
bool connector_push         (char *);
void insert_comment         (ea_t, bool);
void insert_name            (ea_t);
bool is_sub_routine         (ea_t);
long find_offset_from_name  (struc_t *, func_t *, char *);
void publish_all_func_names (void);

#endif