/*
    Olly Heap Vis
    Copyright (C) 2005 Pedram Amini <pamini@idefense.com,pedram.amini@gmail.com>

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

#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>

#include "olly_redefines.h"
#include "plugin.h"
#include "olly_heap_vis.h"
#include "olly_callbacks.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// determine the process id of the debuggee.

DWORD get_process_id (void)
{
    HANDLE        h_snapshot;
    t_thread      *pthread;
    BOOL          thread_exists;
    THREADENTRY32 thread_entry;
    char          *error;

    // determine the current thread id.
    pthread = olly_find_thread(olly_get_cpu_thread_id());

    h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (h_snapshot == INVALID_HANDLE_VALUE)
    {
        olly_add_to_list(0, 1, "Heap Vis> CreateToolhelp32Snapshot() failed");
        return 0;
    }

    // initialize the dwSize member and get the first thread.
    // according to MSDN Thread32...() calls will fail if this is not done.
    thread_entry.dwSize = sizeof(THREADENTRY32);
    thread_exists      = Thread32First(h_snapshot, &thread_entry);

    if (!thread_exists)
    {
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &error,
            0,
            NULL);

        olly_add_to_list(0, 1, "Heap Vis> Thread32First: %s", error);
    }

    // step through the threads looking for our thread id.
    while (thread_exists)
    {
        if (thread_entry.th32ThreadID == pthread->threadid)
            return thread_entry.th32OwnerProcessID;

        thread_entry.dwSize = sizeof(THREADENTRY32);
        thread_exists      = Thread32Next(h_snapshot, &thread_entry);
    }

    // matching thread not found.
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// retrieve the list of heaps and heap blocks for the debuggee and create a graphviz dot visualization description.

void heaps_create_visualization (void)
{
    DWORD       pid;
    HANDLE      h_snapshot;
	HANDLE      process;
    HEAPLIST32  heap_list;
    HEAPENTRY32 heap_entry;
    BOOL        heap_exists;
    BOOL        block_exists;
    char        *error;
    char        desc[12];
	FILE        *fp;
	int         node;
	int         top_node;
	int         block;
	void        *start;
	void        *this;
	void        *next;
	int         index;
    char        filename[MAX_PATH];

    // initialize the filename buffer.
    memset(filename, 0, sizeof(filename));

    // prompt the user for the filename to save the DOT file to.
    // 0x80 specifies that we open a "save" dialog, instead of the default "open" dialog.
    if (!olly_browse_filename("Generate Graphviz DOT Visualization", filename, ".dot", 0x80))
    {
        olly_add_to_list(0, 1, "Heap Vis> Heap dump cancelled");
        return;
    }

	// create / open graph file.
	if ((fp = fopen(filename, "w")) == NULL)
	{
		olly_add_to_list(0, 1, "Heap Vis> Failed opening %s for writing.", "c:\\test.dot");
		return;
	}

	// determine process id of debugee.
    if ((pid = get_process_id()) == 0)
    {
        olly_add_to_list(0, 1, "Heap Vis> get_process_id() failed.");
        return;
    }

	// attempt to obtain a handle to the target process.
	if ((process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid)) == NULL)
	{
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &error,
            0,
            NULL);

        olly_add_to_list(0, 1, "Heap Vis> OpenProcess: %s", error);
		return;
	}

    olly_add_to_list(0, 0, "Heap Vis> Taking process snapshot of pid %d and beginning heap dump.", pid);

    // take a snapshot of the target process.
    h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, pid);

    if (h_snapshot == INVALID_HANDLE_VALUE)
    {
        olly_add_to_list(0, 1, "Heap Vis> CreateToolhelp32Snapshot() failed");
        return;
    }

	//
	// write the graph header.
	//

	fprintf(fp, "digraph heap_vis\n"
				"{\n"
				"  graph\n"
				"  [\n"
				"    label    = \"Heap Vis\",\n"
				"    fontname = \"courier\",\n"
				"    ratio    = \"compress\",\n"
				//"    size     = \"16,20\"\n"
				"  ];\n\n");

    // initialize the dwSize member and get the first heap.
    // according to MSDN Heap32...() calls will fail if this is not done.
    heap_list.dwSize = sizeof(HEAPLIST32);
    heap_exists      = Heap32ListFirst(h_snapshot, &heap_list);

    if (!heap_exists)
    {
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &error,
            0,
            NULL);

        olly_add_to_list(0, 1, "Heap Vis> Heap32ListFirst: %s", error);
    }

	// enumerate process heaps.
    for (node = 0; heap_exists; node++)
    {
		//
		// draw the nodes for the free list.
		//

		for (index = 0; index < 128; index++)
		{
			next     = 0;
			start    = (void *)(heap_list.th32HeapID + 0x178 + (index * 8));
			this     = start;
			top_node = node;

			for (node; next != start; node++)
			{
				ReadProcessMemory(process, this, &next, 4, NULL);

				// if there are any elements in this free list entry, then create the nodes for it.
				if (next != start || this != start)
				{
					fprintf(fp, "  n%d\n"
								"  [\n"
								"    shape     = \"record\",\n"
								"    fillcolor = \"#EEEEEE\",\n"
								"    fontname  = \"courier\",\n"
								"    fontcolor = \"#333333\",\n"
								"    fontsize  = \"8\",\n"
								"    style     = \"filled\",\n",
								node);

					// first node?
					if (this == start)
						fprintf(fp, "    label     = \"{%d}\"\n  ];\n\n", index);
					else
						fprintf(fp, "    label     = \"{%p}\"\n  ];\n\n", this);
				}

				// create forward / back edge pairs for the added nodes (ignore the first one).
				if (this != start)
				{
					fprintf(fp, "  n%d -> n%d [color=\"#FF0000\"];\n",   node - 1, node);
					fprintf(fp, "  n%d -> n%d [color=\"#0000FF\"];\n\n", node, node - 1);
				}
				
				#ifdef DEBUG
					olly_add_to_list((long)(heap_list.th32HeapID + 0x178 + (index * 8)), 1, "%08x", this);
				#endif

				this = next;
			}

			#ifdef DEBUG
				olly_add_to_list(0, 0, "");
			#endif

			// complete the doubly linked list.
			// XXX - disabled as it makes the graph look ugly.
			/*
			if (node - 1 != top_node)
			{			
				fprintf(fp, "  n%d -> n%d [color=\"#FF0000\"];\n\n", node - 1, top_node);
				fprintf(fp, "  n%d -> n%d [color=\"#0000FF\"];\n\n", top_node, node - 1);
			}
			*/
		}

		// initialize the dwSize member and get the first heap block
        // according to MSDN Heap32...() calls will fail if this is not done.
        heap_entry.dwSize = sizeof(HEAPENTRY32);
        block_exists      = Heap32First(&heap_entry, pid, heap_list.th32HeapID);

		// ignore the very first block (the look-aside table).
        heap_list.dwSize = sizeof(HEAPLIST32);
        heap_exists      = Heap32ListNext(h_snapshot, &heap_list);

		//
		// create the node for this heap.
		//

		fprintf(fp, "  n%d\n"
			        "  [\n"
					"    shape     = \"record\",\n"
					"    fillcolor = \"#EEEEEE\",\n"
					"    fontname  = \"courier\",\n"
					"    fontcolor = \"#333333\",\n"
					"    fontsize  = \"8\",\n"
					"    style     = \"filled\",\n"
					"    label     = \"{heap base %08X|{",
					node,
					heap_list.th32HeapID);

        if (!block_exists)
        {
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &error,
                0,
                NULL);

            olly_add_to_list(0, 1, "Heap Vis> Heap32First: %s", error);
        }

        // enumerate heap blocks.
        for (block = 1; block_exists; block++)
        {
            // determine the description column value for this heap block.
            if (heap_entry.dwAddress - heap_list.th32HeapID == 0x688)
                strcpy(desc, "Look-aside");
            else if (heap_entry.dwFlags == LF32_FREE)
                strcpy(desc, "Free");
            else
                strcpy(desc, "Used");

			//
            // add the heap block to the node.
			//

			fprintf(fp, "%6d", heap_entry.dwBlockSize);

			if (block % 16 == 0)
				fprintf(fp, "}|{");
			else
				fprintf(fp, "|");

            heap_entry.dwSize = sizeof(HEAPENTRY32);
            block_exists      = Heap32Next(&heap_entry);
        }

		//
		// close this heap node.
		//

		fprintf(fp, "}}\"\n  ];\n\n");

        heap_list.dwSize = sizeof(HEAPLIST32);
        heap_exists      = Heap32ListNext(h_snapshot, &heap_list);
    }

    CloseHandle(h_snapshot);
	CloseHandle(process);

	//
	// print graph footer and close graph file.
	//

	fprintf(fp, "}");
	fclose(fp);

    olly_add_to_list(0, 0, "Heap Vis> Heap dump complete.");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// quick jump to the specified heap block.

void heaps_jump_to_chunk (void)
{
    t_heap_vis *hvis;
    ulong      jump_address;
    int        chunk_index;

    // ensure we have a heap list to jump to.
    if (!heap_vis_table.data.n)
    {
        Error("No heap list to jump to. Try 'View Heaps' first.");
        return;
    }

    // prompt the user for the address to jump to.
    if (olly_get_long("Jump to ...", &jump_address, 4, 0, 0) == -1)
        return;

    // step through each heap chunk.
    for (chunk_index = 0; chunk_index < heap_vis_table.data.n; chunk_index++)
    {
        hvis = (t_heap_vis *)olly_get_sorted_by_selection(&(heap_vis_table.data), chunk_index);

        if (jump_address >= hvis->block && jump_address <= hvis->block + hvis->block_size)
            break;
        else
            hvis = NULL;
    }

    if (hvis == NULL)
        olly_add_to_list(0, 1, "Heap Vis> Address not found in available heap chunks");
    else
        olly_create_dump_window("Heap Block",
            hvis->block,
            (ulong)hvis->block_size,
            hvis->block,
            DU_ESCAPABLE | 0x01101,
            NULL);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// search the debuggee's heaps space for the specified bytes.

void heaps_search (void)
{
    t_hexstr      search_for;
    t_heap_vis    *hvis;
    int           chunk_index;
    DWORD         offset;
    unsigned char *memory;

    memset(&search_for, 0, sizeof(t_hexstr));

    // ensure we have data to search through.
    if (!heap_vis_table.data.n)
    {
        Error("No heap list to search through. Try 'View Heaps' first.");
        return;
    }

    // prompt the user for a search sequence.
    if (olly_get_hex_string("Search for ...", &search_for, DIA_DEFASCII|DIA_ASKGLOBAL, FIXEDFONT, 0) == -1)
        return;

    // step through each heap chunk.
    for (chunk_index = 0; chunk_index < heap_vis_table.data.n; chunk_index++)
    {
        hvis = (t_heap_vis *)olly_get_sorted_by_selection(&(heap_vis_table.data), chunk_index);

        // allocate some memory to copy the heap chunk into, continue to the next heap chunk on error.
        if ((memory = (unsigned char *)malloc(hvis->block_size)) == NULL)
            continue;

        // grab the heap chunk from the debuggee, continue to the next heap chunk on error.
        if (olly_read_memory((void *)memory, hvis->block, hvis->block_size, MM_RESTORE | MM_SILENT) == 0)
        {
            olly_add_to_list(hvis->block, 1, "Heap Vis> Error when attempting to read chunk of %d bytes.", hvis->block_size);
            free(memory);
            continue;
        }

        // search the chunk for the specified contents.
        for (offset = 0; offset < hvis->block_size - search_for.n; offset++)
        {
            // match found.
            if (memcmp((void *)(memory + offset), search_for.data, search_for.n) == 0)
            {
                olly_add_to_list(hvis->block, 0, "Heap Vis> Heap chunk of size %d contains search sequence.", hvis->block_size);
                
                // once a match has been found, move on.
                break;
            }
        }

        // free the memory we allocated for this heap chunk.
        free(memory);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// retrieve the list of heaps and heap blocks for the debuggee and display them in a native olly table.

void heaps_view (void)
{
    DWORD       pid;
    HANDLE      h_snapshot;
    HEAPLIST32  heap_list;
    HEAPENTRY32 heap_entry;
    BOOL        heap_exists;
    BOOL        block_exists;
    char        *error;
    char        desc[12];
    ulong       index = 0;

    // destroy any existing sorted data.
    olly_destroy_sorted_data(&(heap_vis_table.data));

    // create a fresh sorted data store.
    if (olly_create_sorted_data(&(heap_vis_table.data),
        "Heap Vis",
        sizeof(t_heap_vis),
        10,
        (SORTFUNC *)tw_sort_func,
        NULL) != 0)
    {
        return;
    }

    // create a new window or restore an existing one.
    tw_create_window();

    // determine process id of debugee.
    if ((pid = get_process_id()) == 0)
    {
        olly_add_to_list(0, 1, "Heap Vis> get_process_id() failed.");
        return;
    }

    olly_add_to_list(0, 0, "Heap Vis> Taking process snapshot of pid %d and beginning heap enumeration.", pid);

    // take a snapshot of the target process.
    h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, pid);

    if (h_snapshot == INVALID_HANDLE_VALUE)
    {
        olly_add_to_list(0, 1, "Heap Vis> CreateToolhelp32Snapshot() failed");
        return;
    }

    // initialize the dwSize member and get the first heap.
    // according to MSDN Heap32...() calls will fail if this is not done.
    heap_list.dwSize = sizeof(HEAPLIST32);
    heap_exists      = Heap32ListFirst(h_snapshot, &heap_list);

    if (!heap_exists)
    {
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &error,
            0,
            NULL);

        olly_add_to_list(0, 1, "Heap Vis> Heap32ListFirst: %s", error);
    }

    // enumerate process heaps.
    while (heap_exists)
    {
        // initialize the dwSize member and get the first heap block
        // according to MSDN Heap32...() calls will fail if this is not done.
        heap_entry.dwSize = sizeof(HEAPENTRY32);
        block_exists      = Heap32First(&heap_entry, pid, heap_list.th32HeapID);

        if (!block_exists)
        {
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &error,
                0,
                NULL);

            olly_add_to_list(0, 1, "Heap Vis> Heap32First: %s", error);
        }

        // enumerate heap blocks.
        while (block_exists)
        {
            // determine the description column value for this heap block.
            if (heap_entry.dwAddress - heap_list.th32HeapID == 0x688)
                strcpy(desc, "Look-aside");
            else if (heap_entry.dwFlags == LF32_FREE)
                strcpy(desc, "Free");
            else
                strcpy(desc, "Used");

            // add the heap block to the sorted list.
            tw_add_element(index++,
                (DWORD)heap_list.th32HeapID,
                (DWORD)heap_entry.dwAddress,
                (DWORD)heap_entry.dwBlockSize,
                desc);

            heap_entry.dwSize = sizeof(HEAPENTRY32);
            block_exists      = Heap32Next(&heap_entry);
        }

        heap_list.dwSize = sizeof(HEAPLIST32);
        heap_exists      = Heap32ListNext(h_snapshot, &heap_list);
    }

    CloseHandle(h_snapshot);

    olly_add_to_list(0, 0, "Heap Vis> Heap enumeration complete. Found %d blocks.", index);

    if (heap_vis_table.hw != NULL)
        InvalidateRect(heap_vis_table.hw, NULL, FALSE);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// table add element handler.

void tw_add_element (ulong index, DWORD base, DWORD block, DWORD block_size, char *desc)
{
    t_heap_vis hvis;

    memset(&hvis, 0, sizeof(hvis));

    hvis.index       = index;
    hvis.size        = 1;
    hvis.type        = 0;
    hvis.base        = base;
    hvis.block       = block;
    hvis.block_size  = block_size;

    strncpy(hvis.desc, desc, sizeof(hvis.desc) - 1);

    if (olly_add_sorted_data(&(heap_vis_table.data), &hvis) == NULL)
        olly_add_to_list(0, 1,"Heap Vis> Failed adding heap block: %08x", hvis.block);

    #ifdef DEBUG
        olly_add_to_list(0, -1, "%08x %08x %d %s", hvis.block, hvis.base, hvis.size, hvis.desc);
    #endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// table create window handler.

void tw_create_window (void)
{
    // describe the table columns if the bar is uninitialized.
    if (heap_vis_table.bar.nbar == 0)
    {
        heap_vis_table.bar.name [0] = "Base";
        heap_vis_table.bar.defdx[0] = 10;
        heap_vis_table.bar.mode [0] = 0;

        heap_vis_table.bar.name [1] = "Block";
        heap_vis_table.bar.defdx[1] = 10;
        heap_vis_table.bar.mode [1] = 0;

        heap_vis_table.bar.name [2] = "Size";
        heap_vis_table.bar.defdx[2] = 15;
        heap_vis_table.bar.mode [2] = 0;

        heap_vis_table.bar.name [3] = "Description";
        heap_vis_table.bar.defdx[3] = 32;
        heap_vis_table.bar.mode [3] = BAR_NOSORT;

        heap_vis_table.bar.nbar = 4;
        heap_vis_table.mode     = TABLE_COPYMENU | TABLE_SORTMENU | TABLE_APPMENU | TABLE_SAVEPOS | TABLE_ONTOP;
        heap_vis_table.drawfunc = tw_get_line;
    }

    // if the window already exists, Quicktablewindow() will not create a new one but rather restore the current one.
    olly_quick_table_window(&heap_vis_table, 15, 4, heap_vis_class, "Heap Vis");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// table display line handler.

int tw_get_line (char *s, char *mask, int *select, t_sortheader *ph, int column)
{
    int ret = 0;
    t_heap_vis *hvis = (t_heap_vis *)ph;

    switch (column)
    {
        // base column.
        case 0:
            ret = sprintf(s, "%08X", hvis->base);
            break;

        // block column.
        case 1:
            ret = sprintf(s, "%08X", hvis->block);
            break;

        // size column.
        case 2:
            ret = sprintf(s, "%d", hvis->block_size);
            break;

        // description column.
        case 3:
            ret = sprintf(s, "%s", hvis->desc);
            break;
    }

    return ret;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// table sort handler.

int tw_sort_func (t_heap_vis *a, t_heap_vis *b, int sort)
{
    int ret = 0;

    switch (sort)
    {
        // sort by first column, heap base address.
        case 0:
            if (a->base < b->base)
                ret = -1;
            else
                ret = 1;
            break;

        // sort by second column, heap block address.
        case 1:
            if (a->block < b->block)
                ret = -1;
            else
                ret = 1;
            break;

        // sort by third column, heap block size.
        case 2:
            if (a->block_size < b->block_size)
                ret = -1;
            else
                ret = 1;
            break;
    }

    return ret;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// window procedure for the heap vis window class.

LRESULT CALLBACK tw_winproc (HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
    t_heap_vis *hvis;

    switch (msg)
    {
        case WM_DESTROY:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_HSCROLL:
        case WM_VSCROLL:
        case WM_TIMER:
        case WM_SYSKEYDOWN:
        case WM_USER_SCR:
        case WM_USER_VABS:
        case WM_USER_VREL:
        case WM_USER_VBYTE:
        case WM_USER_STS:
        case WM_USER_CNTS:
        case WM_USER_CHGS:
        case WM_WINDOWPOSCHANGED:
            return olly_table_function(&heap_vis_table, hw, msg, wp, lp);
        case WM_KEYDOWN:
            switch (wp)
            {
                // 'j' - jump
                case 74:
                    heaps_jump_to_chunk();
                    break;

                // 's' - search
                case 83:
                    heaps_search();
                    break;
            }

            return 1;
        case WM_USER_DBLCLK:
            hvis = (t_heap_vis *)olly_get_sorted_by_selection(&(heap_vis_table.data), heap_vis_table.data.selected);

            if (hvis != NULL)
                olly_create_dump_window("Heap Block",
                    hvis->block,
                    (ulong)hvis->block_size,
                    hvis->block,
                    DU_ESCAPABLE | 0x01101,
                    NULL);

            return 1;
        case WM_USER_CHALL:
        case WM_USER_CHMEM:
            // redraw the window.
            InvalidateRect(hw, NULL, FALSE);
            return 0;
        case WM_USER_MENU:
            return 0;
        case WM_PAINT:
            olly_paint_table(hw, &heap_vis_table, tw_get_line);
            return 0;
        default:
            break;
    }

    return DefMDIChildProc(hw, msg, wp, lp);
}