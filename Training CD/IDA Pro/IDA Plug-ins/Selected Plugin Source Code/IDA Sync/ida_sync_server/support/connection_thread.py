# IDA Sync Server Connection Handling Class
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

import os
import socket
import sys
import threading
import time

from user_manager     import *
from serverx          import *
from server_constants import *

sys.path.append("modules")

# import any available modules.
for file in os.listdir("modules"):
    if (file.endswith(".py")):
        file = file.split(".")[0]
        exec("from " + file + " import *")

########################################################################################################################
### connection_thread
###
### an instance of this class is instantiated for each received connection to
### to register a module and handle client I/O.
###
class connection_thread(threading.Thread):
    ####################################################################################################################
    ### constructor
    ###
    ### args:    none.
    ### raises:  none.
    ### returns: none.
    ###
    def __init__(self, s, connections, log_to_console):
        threading.Thread.__init__(self)

        self.sock           = s
        self.connections    = connections
        self.log_to_console = log_to_console


    ####################################################################################################################
    ### console_log()
    ###
    ### args:    message - log message.
    ### raises:  none.
    ### returns: none.
    ###
    def console_log(self, message):
        if (self.log_to_console):
            print message


    ####################################################################################################################
    ### run() *** main thread routine ***
    ###
    ### args:    none.
    ### raises:  none.
    ### returns: none.
    ###
    def run(self):
        # read the registration request from the connected client.
        try:
            data = self.sock.recv(1024)
            data = data.rstrip("\n")
        except:
            msg = "[!] connection closed: " + self.sock.getpeername()[0]
            self.console_log(msg)
            self.sock.close()
            return

        try:
            (module, project, username, password) = data.split(":::")
        except:
            return

        msg = "[*] %s registration request for project '%s' from %s" % (module, project, username)
        self.console_log(msg)

        # validate the username and password.
        um = user_manager()
        try:
            um.validate(username, password)
        except serverx, x:
            self.console_log("[!] registration failed: " + x.msg())
            self.sock.sendall("0:::" + x.msg())
            self.sock.close()
            return

        # ensure the requested module is available..
        module_found = False

        for file in os.listdir("modules"):
            if (file.endswith(".py")):
                if (file == module + ".py"):
                    module_found = True

        if (not module_found):
            self.console_log("[!] requested module not supported")
            self.sock.sendall("0:::requested module not supported")
            self.sock.close()
            return

        # generate a connection record.
        connection = (self.sock, module, project, username, long(time.time()))

        # attempt to spawn the appropriate module handler for this connection.
        try:
            exec("module = %s()" % module)
            exec("module._init(self.sock, self.connections, connection, project, username, password)")
        except serverx, x:
            self.console_log("[!] invalid project specified: " + project)
            self.sock.sendall("0:::%s" % x.msg())
            self.sock.close()
            return

        # let the client know that registration was successful.
        try:
            self.sock.sendall("1:::successfully registered with server.")
        except:
            self.sock.close()
            return

        # register the connection record in the global data struct.
        self.connections.append(connection)

        try:
            module.run()
        except serverx, x:
            self.console_log(x.msg())

        # remove the connection record from the global data struct.
        self.connections.remove(connection)
