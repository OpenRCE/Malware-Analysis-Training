Olly BP Manager
Copyright (C) 2005 Pedram Amini

OllyDBG has excellent breakpoint manipulation capabilities and can store
breakpoint information across debugging sessions for the main module
being debugged within the .udd file. However, there are some limitations
to the available functionality which this plug-in attempts to address.

To install the plugin simply copy the DLL to the OllyDBG install
directory.

The Olly Breakpoint (BP) Manager was written to provide three main
functions - breakpoint exporting, breakpoint importing and automatic
breakpoint loading. Breakpoint importing/exporting are straight forward
features and can be accessed from the main plug-in menu as well as the
right-click context menu of the breakpoints window. Olly BP Manager was
designed to support both regular and log (with expression/explanation)
breakpoints. Conditional breakpoints have not yet been implemented.
Breakpoint files for the plugin follow a simple format and use the
extension .obp (OllyDBG Break Point). The format of the file is as
follows:

    Module:Offset:Expression (1st byte = condition):Explanation

    ntdll:00001d75:#:#
    ntdll:000105d4:Edword ptr [esp+c]:size
    ntdll:0006fc94:Q:isprint
    
The name of the target DLL is stored as a string the module field (sans
the extension). The offset field represents the offset into the module
to set the breakpoint. Offsets are used in place of absolute addresses
to support setting breakpoints on modules that move around in memory.
The first byte of the expression field designates the breakpoint
condition, see the COND_XXXX defines in plugin.h. The expression and
explanation fields are optional and must be set to '#' when unused. The
explanation field does not have to be exclusively used with the "Log
value of expression" option and can be used to add a "comment", such as
the function name, to your breakpoints (See breakpoint_conditions.gif).
Breakpoint list importing/exporting can only be done when the target
process is paused. Requests to import/export are ignored if the process
is active.

The breakpoint manager also supports automatic loading of breakpoint
lists at runtime. Whenever a module is loaded by the target process, BP
Manager will check the 'breakpoints' subdirectory under the OllyDBG
install directory. If a breakpoint list matching the loaded module name
is identified, breakpoints will be loaded and inserted into the module.
For example, to automatically load a breakpoint list for kernel32.dll
copy your breakpoint list to:

    C:\Program Files\OllyDBG\Breakpoints\kernel32.dll.obp
    
The module name is case insensitive. This feature is especially useful
when working with breakpoints in modules not loaded at startup.