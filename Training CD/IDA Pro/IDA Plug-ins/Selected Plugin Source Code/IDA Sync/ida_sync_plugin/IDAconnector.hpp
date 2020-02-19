/*
    IDA Connector Class
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

    *** NOTES ***

    This class / wrapper function provides server connectivity via the global
    instantiation 'connector'. All server I/O is accomplished in an abstracted
    asynchronous environment.

    - The socket receive notification routine requires that the following
      external routine be defined for handling received data:
          bool connector_pull (void);
    - PLUGIN_NAME must be updated.
    - connector->cleanup() should be called prior to plug-in/program exit.
*/

#ifndef __IDACONNECTOR_H__
#define __IDACONNECTOR_H__

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

#define SOCKET_MSG    WM_USER + 100
#define PLUGIN_NAME   "ida_sync"

//
// class definition.
//

class IDAconnector
{
    public:
         IDAconnector();
        ~IDAconnector();

        // getters.
        bool   is_connected   (void) { return connected;  }
        SOCKET get_connection (void) { return connection; }
        char * get_project    (void) { return project;    }
        char * get_username   (void) { return username;   }

        // exposed member routines.
        void cleanup               (void);
        void server_connect        (void);
        BOOL CALLBACK socket_proc  (HWND, UINT, WPARAM, LPARAM);

    private:
        bool    connected;
        SOCKET  connection;
        char    project [64];
        HWND    socket_hwnd;
        char    username[64];

};

//
// global class pointer.
//

IDAconnector *connector = new IDAconnector();

/////////////////////////////////////////////////////////////////////////////////////////
// socket_proc_wrapper()
//
// we register this proc handler from SetWindowLong() which wraps our class proc handler.
//
// arguments: h_dialog -
//            msg      -
//            w_param  -
//            l_param  -
// returns:   boolean value representing success or failure.
//

BOOL CALLBACK socket_proc_wrapper (HWND h_dialog, UINT u_message, WPARAM w_param, LPARAM l_param)
{
    return connector->socket_proc(h_dialog, u_message, w_param, l_param);
}


/////////////////////////////////////////////////////////////////////////////////////////
// constructor
//

IDAconnector::IDAconnector()
{
    connected   = false;
    connection  = NULL;
    socket_hwnd = NULL;

    memset(project,  0, sizeof(project));
    memset(username, 0, sizeof(username));
}


/////////////////////////////////////////////////////////////////////////////////////////
// destructor
//

IDAconnector::~IDAconnector()
{
    // cancel all notifications. if we don't do this ida will crash on exit.
    WSAAsyncSelect(connection, socket_hwnd, 0, 0);

    if (connected)
    {
        closesocket(connection);
        WSACleanup();
        DestroyWindow(socket_hwnd);
    }

    connected = false;
}


/////////////////////////////////////////////////////////////////////////////////////////
// cleanup()
//
// cancel all notifications, close the socket and destroy the hook notification window.
//
// arguments: none.
// returns:   none.
//
void IDAconnector::cleanup (void)
{
    // cancel all notifications. if we don't do this ida will crash on exit.
    WSAAsyncSelect(connection, socket_hwnd, 0, 0);

    if (connected)
    {
        closesocket(connection);
        WSACleanup();
        DestroyWindow(socket_hwnd);
    }

    connected = false;
}


/////////////////////////////////////////////////////////////////////////////////////////
// server_connect()
//
// present the user with an IDA generated dialog and connect to the server.
//
// arguments: none.
// returns:   none.
//

void IDAconnector::server_connect (void)
{
    hostent      *he;
    sockaddr_in  sin;
    in_addr      addr;
    WSADATA      wsa_data;

    char buf         [512];
    char message     [128];
    char password    [64];
    char project     [64];
    char server_addr [128];
    char username    [64];
    int  code;
    int  len;
    int  port = 5041;

    const char dialog_format[] =
        "STARTITEM 0\n"
        PLUGIN_NAME"\n"
        "Connect to IDA Sync server.\n\n"
        "Server / Port: \n<:A:512:30::> <:D:5:5::>\n"
        "Username:      \n<:A:128:40::>\n"
        "Password:      \n<:A:128:40::>\n"
        "Project Name:  \n<:A:128:40::>\n\n";

    memset(buf,         0, sizeof(buf));
    memset(message,     0, sizeof(message));
    memset(password,    0, sizeof(password));
    memset(project,     0, sizeof(project));
    memset(server_addr, 0, sizeof(server_addr));
    memset(username,    0, sizeof(username));

    // if we are already connected then do nothing.
    if (connected)
        return;

    // prompt the user for server connection information..
    if (!AskUsingForm_c(dialog_format, server_addr, &port, username, password, project))
    {
        msg("[!] "PLUGIN_NAME"> Connection cancelled.\n");
        return;
    }

    // initialize winsock.
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        msg("[!] "PLUGIN_NAME"> WSAStartup() failed.\n");
        return;
    }

    // confirm that the requested winsock version is supported.
    if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
    {
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Winsock version 2.2 not found.\n");
        return;
    }

    // check if a valid IP address was provided, if not try to do gethostbyname().
    addr.s_addr = inet_addr(server_addr);

    if( addr.s_addr == INADDR_NONE )
    {
        if ((he = gethostbyname(server_addr)) == NULL)
        {
            msg("[!] "PLUGIN_NAME"> Unable to resolve name: %s\n", server_addr);
            return;
        }
    }
    // otherwise, use the numeric IP address with gethostbyaddr()
    else
    {
        if ((he = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET)) == NULL)
        {
            msg("[!] "PLUGIN_NAME"> Unable to resolve address\n");
            return;
        }
    }

    // create a socket.
    if ((connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Failed to create socket.\n");
        return;
    }

    // connect to the server.
    sin.sin_family = AF_INET;
    sin.sin_addr   = *((LPIN_ADDR)*he->h_addr_list);
    sin.sin_port   = htons(port);

    if (connect(connection, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
    {
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Failed to connect to server.\n");
        return;
    }

    // connection to server successful.

    // register the plugin with the console.
    qsnprintf(buf, sizeof(buf) - 1, PLUGIN_NAME":::%s:::%s:::%s", project, username, password);

    len = strlen(buf);

    // send the registration request.
    if (send(connection, buf, len, 0) != len)
    {
        closesocket(connection);
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Failed to register with server.\n");
        return;
    }

    // receive the registration confirmation.
    len = recv(connection, buf, sizeof(buf) - 1, 0);

    // connection closed.
    if (len == 0 || len == SOCKET_ERROR)
    {
        closesocket(connection);
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Failed to read registration response from server.\n");
        return;
    }

    // null terminate the received buffer.
    buf[len] = 0;

    // parse the server message. format: code:::message.
    // if we can't understand the response, then quit.
    if (sscanf(buf, "%d:::%127[^\0]", &code, message) != 2)
    {
        closesocket(connection);
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Registration failed.\n");
        return;
    }

    // registration failed. print why.
    if (code == 0)
    {
        closesocket(connection);
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> Registration failed: %s\n", message);
        return;
    }

    // create an invisble window for hooking messages received by our socket.
    if ((socket_hwnd = CreateWindowEx(0, "STATIC", PLUGIN_NAME, 0, 0, 0, 0, 0, 0, 0, 0, 0)) == NULL)
    {
        closesocket(connection);
        WSACleanup();
        msg("[!] "PLUGIN_NAME"> CreateWindowEx() failed.\n");
        return;
    }

    // register the callback function for our invisible window.
    if (SetWindowLong(socket_hwnd, GWL_WNDPROC, (long) socket_proc_wrapper) == 0)
    {
        closesocket(connection);
        WSACleanup();
        DestroyWindow(socket_hwnd);
        msg("[!] "PLUGIN_NAME"> SetWindowLong() failed.\n");
        return;
    }

    // make the socket a non-blocking asynchronous socket hooked with our socket_proc handler.
    if (WSAAsyncSelect(connection, socket_hwnd, SOCKET_MSG, FD_READ | FD_CLOSE) == SOCKET_ERROR)
    {
        closesocket(connection);
        WSACleanup();
        DestroyWindow(socket_hwnd);
        msg("[!] "PLUGIN_NAME"> Failed to create asynchronous connection to server.\n");
        return;
    }

    // asynchronous connection to server established. raise the connected flag.
    msg("[*] "PLUGIN_NAME"> Successfully registered project '%s' with server as '%s'\n", project, username);
    connected = true;
}


/////////////////////////////////////////////////////////////////////////////////////////
// socket_proc()
//
// this is the proc handler we register with our invisible window for hooking the
// socket notification messages.
//
// arguments: h_dialog -
//            msg      -
//            w_param  -
//            l_param  -
// returns:   boolean value representing success or failure.
//

BOOL CALLBACK IDAconnector::socket_proc (HWND h_dialog, UINT u_message, WPARAM w_param, LPARAM l_param)
{
    // we are only interested in our socket callback.
    if (u_message == SOCKET_MSG)
    {
        if (WSAGETSELECTERROR(l_param))
        {
            cleanup();
            msg("[!] "PLUGIN_NAME"> Connection to server severed.\n");
            return FALSE;
        }

        switch(WSAGETSELECTEVENT(l_param))
        {
            // receiving data.
            case FD_READ:
                if (!connector_pull())
                {
                    cleanup();
                    msg("[!] "PLUGIN_NAME"> Connection to server severed.\n");
                }
                break;

            // sending data.
            case FD_WRITE:
                break;

            // server connection closed.
            case FD_CLOSE:
                cleanup();
                msg("[!] "PLUGIN_NAME"> Connection to server severed.\n");
                break;
        }
    }

    return FALSE;
}

#endif