# IDA Sync Server Module
# Copyright (C) 2005 Pedram Amini <pedram.amini@gmail.com>
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
# 
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA 02111-1307 USA

import time
import Mk4py as mk

from serverx          import *
from server_constants import *

class ida_sync:
    ############################################################################
    ### constructor
    ###
    ### args:    none.
    ### raises:  none.
    ### returns: none.
    ###
    def __init__(self):
        # open the IDA Sync database, creating it if it doesn't exist.
        self.db = mk.storage("databases/ida_sync.db", 1)

        # if it doesn't already exist, define a view to track user updates.
        description = "__last__[username:S,project:S,timestamp:L]"
        self.last_view = self.db.getas(description)


    ############################################################################
    ### _init()
    ###
    ### args:    s           - connected socket.
    ###          connections - global list of connection records.
    ###          connection  - current connection record.
    ###          project     - requested project.
    ###          username    -
    ###          password    -
    ### raises:  exception on error.
    ### returns: none.
    ### notes:   generated exceptions should not close the socket. the calling
    ###          thread handler will relay the error message back to the client
    ###          and then close the socket.
    ###
    def _init(self, s, connections, connection, project, username, password):
        self.sock        = s
        self.connections = connections
        self.connection  = connection
        self.project     = project
        self.username    = username
        self.password    = password

        # retrieve the project view.
        self.proj_view = self.db.view(project)

        # create an exception if the view doesn't exist.
        if (str(self.proj_view.structure()) == "[]"):
            raise serverx("requested project not found.")

        self.db.commit()

        # determine the user's last update.
        index = self.last_view.find(username=username, project=project)

        if (index != -1):
            last = self.last_view[index].timestamp

            # refresh the last update record.
            self.update_last(username, project)
        else:
            last = 0

        print ">>DEBUG %08x" % last

         # locate all changes made since the user's last update.
        index   = self.proj_view.filter(lambda row: row.timestamp >= last)
        subview = self.proj_view.remapwith(index)

        # XXX - this is a cheap hack because the IDA plugin doesn't seem to
        # process the first message.
        self.sock.sendall("31337:::deadbeef:::sync")

        for record in subview:
            msg = "%d:::%08x:::%s" % (record.type, record.address, record.data)
            try:
                self.sock.sendall(msg)
                self.sock.recv(1)
            except:
                break

        # reset the last update time.
        self.update_last(username, project)


    ############################################################################
    ### create()
    ###
    ### args:    project - table (view) to create.
    ### raises:  none.
    ### returns: none.
    ###
    def create(self, project):
        self.db.getas(project + "[type:I,address:L,data:S,timestamp:L,user:S]")
        self.db.commit()


    ############################################################################
    ### delete_row()
    ###
    ### args:    address - address of data to erase.
    ###          type    - type of data to erase at address.
    ### raises:  none.
    ### returns: none.
    ###
    def delete_row(self, address, type):
        # we can't just search for an exact address/type match because a regular
        # comment and a repeatable comment are considered overlapping.
        start = 0
        while (1):
            index = self.proj_view.find(address=address, start=start)
            start = start + 1

            if (index == -1):
                break

            row  = self.proj_view[index]

            # data types are the same.
            if (type == row.type):
                self.proj_view.delete(index)

            # data types are both comments.
            if ((type     == server_constants.REG_COMMENT or type     == server_constants.REP_COMMENT) and
                (row.type == server_constants.REG_COMMENT or row.type == server_constants.REP_COMMENT)):
                    self.proj_view.delete(index)

        # commit changes to database.
        self.db.commit()


    ############################################################################
    ### drop()
    ###
    ### args:    project - table (view) to drop.
    ### raises:  none.
    ### returns: none.
    ###
    def drop(self, project):
        # drop the project table (view).
        self.db.getas(project)

        # erase all last update records associated with the project to remove.
        subview = self.last_view.filter(lambda row: row.project == project)
        self.last_view.remove(subview)

        # commit changes to database.
        self.db.commit()


    ############################################################################
    ### list_projects()
    ###
    ### args:    none.
    ### raises:  none.
    ### returns: none.
    ###
    def list_projects(self):
        project_list = []
        projects     = self.db.contents().properties()

        for project in projects:
            # ignore the internal databases.
            if (project != "__last__"):
                project_list.append(project)

        project_list.sort()
        return project_list


    ############################################################################
    ### list_rows()
    ###
    ### args:    project - list rows for this project.
    ### raises:  none.
    ### returns: none.
    ###
    def list_rows(self, project):
        return self.db.view(project)


    ############################################################################
    ### reset_last()
    ###
    ### args:    username -
    ###          project  -
    ### raises:  none.
    ### returns: none.
    ###
    def reset_last(self, username, project):
        index = self.last_view.find(username=username, project=project)

        # if a last update entry already exists for this user, remove it.
        if (index != -1):
            self.last_view.delete(index)

        # commit the changes.
        self.db.commit()


    ############################################################################
    ### run() *** main handler routine ***
    ###
    ### args:    none.
    ### raises:  exception on failure.
    ### returns: none.
    ###
    def run(self):
        # enter an infinite read loop to process all inbound requests.
        while 1:
            try:
                buf = self.sock.recv(1024)
                buf = buf.rstrip("\n")

                if (not buf):
                    raise Exception
            except:
                msg = "[!] connection from %s for ida_sync::%s closed." % (self.sock.getpeername()[0], self.project)
                self.sock.close()
                raise serverx(msg)

            # parse out the fields, ignore and continue on error.
            try:
                (type, address, data) = buf.split(":::")

                type    = int(type)
                address = long(address, 16)
            except:
                continue

            # print to console.
            if type == server_constants.NAME or type == server_constants.STACK_NAME:
                print_data = data.split("*")[1]
            else:
                print_data = data

            print "[*] data from %s. type %d. @%08x. %s" % (self.username, type, address, print_data)

            # erase any previous overlapping data at this address.
            self.delete_row(address, type)

            # append the received data to the database.
            self.proj_view.append(type      = type,
                                  address   = address,
                                  data      = data,
                                  timestamp = long(time.time()),
                                  user      = self.username)

            # commit changes to database.
            self.db.commit()

            # walk through all active connections and relay the received data
            # to all equivalent module/project combinations.
            for conn in self.connections:
                # ignore the current connection.
                if (conn == self.connection):
                    continue

                if (conn[server_constants.MODULE] == "ida_sync" and conn[server_constants.PROJECT] == self.project):
                    conn[server_constants.SOCK].sendall(buf)
                    self.update_last(conn[server_constants.USERNAME], conn[server_constants.PROJECT])


    ############################################################################
    ### update_last()
    ###
    ### args:    username -
    ###          project  -
    ### raises:  none.
    ### returns: none.
    ###
    def update_last(self, username, project):
        index = self.last_view.find(username=username, project=project)

        # if a last update entry already exists for this user, remove it.
        if (index != -1):
            self.last_view.delete(index)

        # create the last update entry.
        self.last_view.append(username  = username,
                              project   = project,
                              timestamp = long(time.time()))

        # commit the changes.
        self.db.commit()
