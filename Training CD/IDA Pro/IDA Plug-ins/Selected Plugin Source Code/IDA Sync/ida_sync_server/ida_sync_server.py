#!c:\python\python.exe
#!/usr/bin/python

# IDA Sync Server
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
#
# ***** NOTES *****
#
# This app creates the main server socket and spawns a connection handling
# thread for each connected peer. The connection thread is then responsible
# for validating the user and determining what module to instantiate to handle
# the connection. The module handler registers the connection in the global
# 'connections' list and processes all client requests from that point on.

import socket
import sys

sys.path.append("support")
from connection_thread import *

def console_log(message):
    if (log_to_console):
        print message

if len(sys.argv) == 3:
    host = sys.argv[1]
    port = int(sys.argv[2])
else:
    host = "0.0.0.0"
    port = 5041

################################################################################

connections    = []
log_to_console = True

try:
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(1)
except:
    sys.stderr.write("Unable to bind to %s:%d\n" % (host, port))
    sys.exit(1)

console_log("Server v1.0 ready.\n")

while (1):
    (client, client_address) = server.accept()

    console_log("[*] connection received from: %s:%d" \
             % (client_address[0], client_address[1]))

    connection = connection_thread(client, connections, log_to_console)
    connection.start()
