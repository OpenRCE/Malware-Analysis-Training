# IDA Sync Server User Management Class
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

import Mk4py as mk
from serverx import *

################################################################################
### user_manager
###
### this class provides an interface for the general management of users.
###
class user_manager:
    ############################################################################
    ### constructor
    ###
    ### args:    none.
    ### raises:  none.
    ### returns: none.
    ###
    def __init__(self):
        # open the users database, creating it if it doesn't exist.
        self.db = mk.storage("databases/users.db", 1)

        # define the user table (view) if it doesn't already exist.
        self.view = self.db.getas("users[username:S,password:S,realname:S]")


    ############################################################################
    ### add()
    ###
    ### args:    username - unique username to add.
    ###          password - password.
    ###          realname - real name.
    ### raises:  exception on error.
    ### returns: none.
    ###
    def add(self, username, password, realname):
        # ensure the user doesn't already exist.
        if (self.view.find(username=username) != -1):
            raise serverx("username already exists")

        # add the user and commit the changes.
        self.view.append(username=username,
                         password=password,
                         realname=realname)

        self.db.commit()


    ############################################################################
    ### delete()
    ###
    ### args:    username - user to delete.
    ### raises:  exception on error.
    ### returns: none.
    ###
    def delete(self, username):
        # ensure the user exists.
        index = self.view.find(username=username)

        if (index == -1):
            raise serverx("username not found")

        # remove the user and commit the changes.
        self.view.delete(index)

        self.db.commit()


    ############################################################################
    ### list()
    ###
    ### args:    none.
    ### raises:  none.
    ### returns: none.
    ###
    def list(self):
        return self.view.sort(self.view.username)


    ############################################################################
    ### update()
    ###
    ### args:    username - user to update.
    ###          password - new password.
    ###          realname - new value for real name.
    ### raises:  exception on error.
    ### returns: none.
    ###
    def update(self, username, password, realname):
        # ensure the user exists.
        index = self.view.find(username=username)

        if (index == -1):
            raise serverx("username not found")

        # remove the user.
        self.view.delete(index)

        # insert the updated user in it's place.
        self.view.insert(index, username=username,
                                password=password,
                                realname=realname)

        # commit the changes.
        self.db.commit()


    ############################################################################
    ### validate()
    ###
    ### args:    username - user to validate as.
    ###          password - username's password.
    ### raises:  exception on error.
    ### returns: none.
    ###
    def validate(self, username, password):
        # ensure the user exists.
        index = self.view.find(username=username, password=password)

        if (index == -1):
            raise serverx("invalid username or password")

        # see if the passwords match.
        user = self.view[index]

        if (user.password != password):
            raise serverx("invalid username or password")
