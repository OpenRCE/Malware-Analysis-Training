Olly Heap Vis
Copyright (C) 2005 Pedram Amini

You may have noticed the ghosted 'Heap' option under the 'View' menu in
OllyDBG. The feature is available only under Windows 95 based OSes and
is supposed to display a list of allocated memory blocks. The Olly Heap
Vis plug-in was written to provide this functionality and more on all
modern Windows OSes such as Windows 2000, XP and 2003.

The plug-in can only be run when the process is in a suspended state. It
can be launched from the plug-in menu as well as the CPU and dump
right-click context menus. The following menu options are available:

    - View Heaps
    - Search Heaps
    - Jump to Heap Chunk
    - Create Heap Visualization

'View Heaps' will generate a native OllyDBG window table listing the
allocated heap blocks for the debuggee. Individual blocks can be double-
clicked to view the relevant memory. Eventually, I would like to write a
custom SPECDUMP routine to display the actual heap chunk structure
information in a pleasant manner.

The 'Search Heaps' option can be accessed from the specified menus or
alternatively, by pressing the hotkey 's' from within the heap list. A
dialog prompting for a search sequence is presented allowing for ASCII,
Unicode or hex byte sequences to be specified. The search is conducted
over all listed heaps, matching blocks are listed in the log window.
This capability is only accessible after 'View Heaps' has generated a
list.

The 'Jump to Heap Chunk' option can be accessed from the specified menus
or alternatively, by pressing the hotkey 'j' from within the heap list.
A dialog prompting for an address is presented allowing for hexadecimal,
signed or unsigned values to be specified. The search is conducted
over all listed heaps. If a heap chunk exists at the specified address,
the entire heap chunk will be displayed.

The 'Create Heap Visualization' feature will generate a Graphviz graph
description suitable for rendering in DOT layout. A sample graph
generated from the startup heap state of Internet Explorer is available
in the 'Documentation' directory as 'iexplore_start_state.png'. Graphs
show the free lists and the heap chunks by size.

A screenshot excerpt of Heap Vis in action is also available in the
'Documentation' directory as 'skylined_ie_heap_fill.gif'. The screenshot
demonstrates the interesting method Berend-Jan Wever (SkyLined) uses in
the exploitation of heap-based Internet Explorer vulnerability. Details
regarding the vulnerability can be found in MS05-020 or:

    www.idefense.com/application/poi/display?id=228&type=vulnerabilities

Currently, the plug-in can not handle the listing or visualizing of
"broken" heaps. This is due to the reliance on the Heap32xxx() API. In
the future support for this may be added. Also on the todo list is
adding a 'cancel' feature to heap listing as some applications with
numerous heaps can take a long time to enumerate.

If you have any questions, comments or feature requests feel free to
drop me a line.