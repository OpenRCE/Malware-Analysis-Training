#!c:\python\python.exe
#!/usr/bin/python

# IDA Sync Server Command Line User Management Utility
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

import getpass
import sys

sys.path.append("support")
from user_manager import *
from serverx       import *

try:
    command = sys.argv[1]
    
    if (command != "list"):
        username = sys.argv[2]
except:
    print "usage: users [add|delete|validate <username>] [list]"
    sys.exit(1)

if (command == "add"):
    password = getpass.getpass("password> ")
    realname = raw_input("realname> ")
    
    um = user_manager()

    try:
        um.add(username, password, realname)
    except serverx, x:
        print x
        sys.exit(1)

elif (command == "delete"):
    um = user_manager()
    
    try:
        um.delete(username)
    except serverx, x:
        print x
        sys.exit(1)

elif (command == "list"):
    um = user_manager()
    
    for user in um.list():
        print user.username + ", " + user.realname

elif (command == "validate"):
    password = getpass.getpass("password> ")
    
    um = user_manager()
    
    try:
        um.validate(username, password)
    except serverx, x:
        print x
        sys.exit(1)

    print "username / password combination valid."

else:
    print "usage: users [add|delete|validate <username>] <list>"
    sys.exit(1)