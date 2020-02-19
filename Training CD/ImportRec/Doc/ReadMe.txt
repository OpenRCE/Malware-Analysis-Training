=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
~            Import REConstructor v1.6 FINAL by MackT/uCF2000 in 2001-2003            ~
=                                                                                     =
~                       - *for Windows 9x, ME, NT, 2K and XP* -                       ~
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

Disclaimer:
-----------
This program may crash, or in a worse case it may even reboot your computer, so please use
it with caution. (Do not run it 3 hours into an unsaved coding session for example)

I am *NOT* responsible for any damage caused by the use of it.


Purpose:
--------
This tool is designed to rebuild imports for protected/packed Win32 executables. It
reconstructs a new Image Import Descriptor (IID), Import Array Table (IAT) and all ASCII
module and function names. It can also inject into your output executable, a loader which
is able to fill the IAT with real pointers to API or a ripped code from the protector/packer
(very useful against emulated API in a thunk).

Sorry but this tool is not designed for newbies, you should be familiar a bit with manual
unpacking first (some tutorials are easy to find on internet).


Features:
---------
- Imports
	- An original tree view
	- 2 different methods to find original imports (by IAT and/or API calls)
	- A *FULL* complete rebuilder (including a new fresh IAT)

- Loader
	- An analyzer and ripper of redirected API code
	- An injected loader code to support mix of imports + ripped code in a thunk
	- A heuristic relocator

- Tracers
	- 3 default tracers (disasm, hook & ring3) to find APIs in redirected code
	- A plugin interface to develop your own tracers

- Misc
	- Support ALL 32bits Windows (9x, ME, NT, 2k and XP)
	- An export renormalizer for Win9x/ME (ala Icedump)
	- A built-in coloured disasm/hex-viewer to analyze the redirected code
	- A built-in dumper
		- Support almost all known antidump tricks


What does it need?
------------------
- A full dump of the target (RAW and VIRTUAL infos of sections DO NOT NEED to be equal)

- A running process of your target

- You have to find the Original Entry Point (OEP) manually (or with /tracex command of
  Icedump) for using the 'IAT AutoSearch' command


How does it work?
-----------------
1  - Select the target in the "Attach to an Active Process" combobox.
     (Its Entry Point (EP) will be automatically put in the OEP editbox)

	* If the target is a dll, choose the process which uses it and click on "Pick DLL"
	  to select it.

	* IF AND ONLY IF you have suspended your target at OEP (with a "jmp eip" at OEP for
	  example), you can dump it with the "Full Dump" button on the dialogbox of the
	  "Select Code Section(s)" command (right click on the tree).

	  NOTE:
	  -----
	  The "Full Dump" button does not take care of the selected sections near it so you
	  do not need to select all sections.

2  - If you have the OEP:
         - Enter it (IN Relative Virtual Address (RVA)) in the appropriate editbox and
	   press "IAT AutoSearch" button to get a possible rva address and size values
	   which can contain the original IAT
     Else:
         - Enter the RVA and size of IAT

3  - Press "Get Imports" button if the "IAT AutoSearch" has found something. For Borland
     targets (for example), you will notice you will not have the complete IAT. It is
     because these targets do not have a contigous IAT. For this case, enter the RVA and
     Size of the whole section which contains that IAT (that information is ALWAYS written
     in the messagebox and the Log window just after clicking on "Get Imports").

     NOTE:
     -----
     The IAT could be completely (or partially) removed by the packer/protector so the
     "IAT AutoSearch" will fail. In this case, use the "Get API Call" command (right click
     on the tree). It will add to your imports, all pointers <XXX> of all <CALL [XXX]> and
     <JMP [XXX]> directly in the code. Do not forget to precise all sections which contain
     or are supposed to contain code (usually it is only the first section so you have
     nothing to do because it is the default configuration). To precise these sections,
     right click on the tree for a "Select Code Section(s)". This method is based on
     heuristics so you might have to analyze and remove by hand all invalid slots.

4  - Use the "Show Invalid" button to see all unresolved slots. You will need to trace into
     them to find the real API. Always try the Tracer Level1 first because it does not
     execute any code of the target. The Tracer Level2 is to be used in the last resort
     because it is the less stable one (it uses a global hook).

     * If you need to retrace into an already traced slot, you have to invalidate it (right
       click on it and use "Invalidate function(s)" command.

     * Use "Cut thunk(s)" to remove individually each function

     * Use "Delete thunk(s)" to remove individually each module

     * Double click on a slot to edit it manually if you know the real API

5  - Use the "Show Suspect" button to check 'supposed' wrong traced slot. This is possible
     because of the Tracer Level1 for example.

     * A suspect slot is an alone valid function in a thunk or an API which already exists
       in the same thunk (ie several same apis in the same module)

     * A suspect slot is not necessary invalid. It only needs a quick analyze of your part.

6  - After playing with all tracers, if you still have some unresolved slots, you can
     try to use the "Loader". This feature will allow you to rip the redirected code to
     be used directly in your dump. To use the loader, select your invalid slots and right
     click on the tree for a "*Switch Loader*". A tag "*LOADER*" will appear near the
     module which contains your slots. If you want to disable it, just "*Switch Loader*"
     again. You are allowed to have invalid functions in all modules which have a tag
     "*LOADER*".

     * The loader is to be used only for rebuilding executable (not dll)

     * The loader analyzer is based on "Max Recursion" and "Buffer Size" options to find
       all needed regions from the invalid slots

7  - If you do not want to add a new section and know where you can put the new rebuilt
     import (in the last section for example), uncheck "Add new section" and enter the
     wanted RVA. (the easiest way is to add a new section though (by default))

     * If the "Loader" is enabled, a new section will be added necessary

8  - Press "Fix Dump" to fix your DUMPED file. You do not need to make a backup. If your
     filename is "Dump.exe", it will create "Dump_.exe". Moreover the EP of your dump will
     be fixed to the value you have entered if you turned "Fix EP to OEP" on, in Options.

     * If you have some modules with a tag "*LOADER*" and some unresolved functions in
       them, a dialogbox will appear and allow you to customize the rip processing.
       You will see all regions which will be ripped of the target. You can add, remove
       and modify them if needed (for advanced users only).

       You will also have these options:

       * "Auto reloc"      : Normal mode for relocations. It will reloc only the ripped
                             region by tracing instruction per instruction (with the disasm
                             engine)

       * "Hardcore reloc"  : Hardcore mode for relocations. It will reloc the whole region
                             in addition to the "Auto reloc"

       * "Rebuild Imports" : All imports in the regions will be rebuilt. It means ImportREC
                             will stick to the current imports, the imports needed by the
                             ripped code.

9  - Pheeeww, your fixed dump should work...


Options:
--------
- "Import all by ordinal" : It needs less size than the usual import (by name and ordinal)
  but it will not be portable. Use it ** IF AND ONLY IF ** you want to rebuild the exe
  ONLY for your system and want a smaller file.

- The "Max Recursion" is the number of conditionnal jumps or calls it's allowed to follow
  when the tracer level1 is in action. More this number is big and more you have to wait,
  use it CAREFULLY. (But you can stop its progression by pressing "CONTROL+F12")

- The "Buffer Size" is the size of the allocated memory block for tracing for EACH
  recursion. (still for the tracer level1)

- "Fix EP to OEP" : Turn on this option if you want to set the EP of your dump file to
  the OEP you have given in ImportREC.

- "Time Out" : Time out for stopping tracers level2 and 3 in their progression. The value
  is in 50 milliseconds and in decimal.

- "Enable Debug Privilege (NT/2K/XP)" : Enable this if your target is not listed in the
  process combobox selector. You will need to restart ImportREC to activate it.

- "Fix Damaged PDB (Win9X/ME Only)" : Enable this if the target has hacked its PDB (ugly)
  against process opening. You will need to restart ImportREC to activate it.

- "Use PE Header From Disk" : Use the PE Header of the disk rather than the dump.

- "Renormalize Exports (W9X/ME)" : Use this to get a better portable executable. You must
  run ImportREC at least once before running your target with this option enabled. You will
  need to restart ImportREC to activate it.

- "Exact Call" : Enable this option to rebuild schemes that use a unique pointer for
                 several (or all) API redirections.

  * Q: What is an "Exact Call"?

    A: An "Exact Call" is a reference in the code of a call to an API. Usually a call to an
       API is done throuh the IAT but some packers/protectors can modify directly the code
       to redirect to a unique pointer (this is also called "mangled scheme"). To fix an
       "Exact Call", ImportREC will need to fix the code to redirect it back to the IAT.

- "Skip Main Slot" : Enable this if you want to trace only on all "Exact Call"s letting
                     the main slot remained.

- "TL3 Dumb Mode"  : It has the behaviour of the Tracer Level1 but it will execute each
                     instruction. Almost done for wrapped api which copies the start of
                     the API and jump "later".

- "TL3 Log"        : Enable this to log all EIP traced by the Tracer Level3. The max
                     logged EIP can be set in the editbox near the checkbox. This will
                     help you to debug where the tracer failed/stopped.

- "Rebuild
   Original FT"    :  Enable this to also rebuild the original first thunks.
                      This could help your disassembler to recognize imports, better.

- "Create New IAT" : Enable this to create a new IAT.

  * This feature is needed when an "Exact Call" has no entry in the current IAT. You will
    be notified anyway if you did not enable it and try to fix your dump.

  * Do not forget to precise all sections which contains the code to be modified by this
    function, by right clicking on the tree for a "Select Code Section(s)"

- "Mode Cloak"     : Mainly for Anti-Imprec methods, it could be used to all technics
                     which tries to prevent ReadProcessMemory from another process.
                     This option will change the name of the window and the API
                     RPM will not be used anymore.

  * The "Full Dump" button will benefit of this option.

  * You can rename <ImportREC.exe> if the target tries to search ImportREC by process
    listing.


Commands:
---------
- "IAT AutoSearch"        : Give it an OEP and it will try to find the IAT RVA and its size
                            for you.

  * Do not forget to read the text written on the MessageBox, erm...

- "Get Imports"           : Build the IAT described by a RVA and a size into a tree.

- "Show Invalid"          : Select all pointers in the IAT which are still invalid
                            (redirected)

- "Show Suspect"          : Select all valid functions which need a manual check of your
                            part. It will select all same functions in the same thunk and
                            all thunk which has only one function.

- "Auto Trace"            : An automatic tracer which will use the tracer level1 on all
                            invalid pointers. It will apply the tracer level3 on suspect
                            entries. Do not expect so much on it because it will never be
                            able to replace some manual actions of your part. It is here
                            for showing how to rebuild "Notepad_asp.exe".

- "Clear Imports"         : Clear all current imports

- "Clear Log"             : Clear the log window

- "Load Tree"             : Load a tree. (You still can load old ".rec" files)

- "Save Tree"             : Save your current tree in a file. (text format)

- "Fix Dump"              : Add your current imports into a dumped file of your target

- "Invalidate function(s)": Invalidate a valid function. Use it if you know the current
                            API is not valid and want to retrace it.

- "Cut thunk(s)"          : Remove all selected functions

- "Delete thunk(s)"       : Remove the modules of all selected functions which they belond
                            to.

- "Get API Calls"         : This feature will get all call[] and jmp[] from the target to
                            your imports. Its first purpose is to find internal calls to
                            the protector which does not belong to the IAT. After getting
                            them, switch them to the loader which will rip the code of the
                            protector to your dump file.

- "Load PE Header"        : To force ImportREC to use a specific PE Header. It will be
                            useful in a particular case.

                            Note: This command WILL NOT PASTE the PE Header to your
                                  dump.

- "Select Code Section(s)": To use for "Get API Calls", "Create New IAT" and "Exact Call".
                            It will precise to them which sections contains code (for
                            redirect all calls to the new IAT or to get all calls).

- "Show Exact Call Window": Show a window to see all the current "Exact Call"s found. You
                            can remove them if needed (right click on the window).

- "Switch *Loader*"       : This command allows you to fix your dump even if you still have
                            some invalid functions (unresolved or different modulenames in
                            the same thunk). It will switch the modules of all selected
                            functions which they belond to, into the loader. It means the
                            IAT of these modules will be resolved by the loader of ImportREC
                            and not by Windows.

- "Get Imports Filter"    : This command will set the range of the "valid" addresses to
                            take care about. All the rest will be removed.

- "Disassemble / HexView" : This new feature will allow you to directly disasm/hexview the
                            redirected code. Use right click to see possible functions
                            on the disassembled code (address, imports...)


Limitations
-----------
- The "IAT AutoSearch" will not work if the IAT is not contigous (ie: cutted in different
  parts of the exe for each thunks) so you will have to put each RVA and SIZE manually or
  use "Get API Calls" command

- The loader cannot actually reloc datas

- The loader does not manage 'Exact Calls' and relative (R) imports

- The loader code cannot be injected in dll (because the current code cannot be reloc'ed)

- Tracers are always to be improved but you can code yours!


Personal greetings:
-------------------
Ab4ds, Analyst, Athol, Band, Christoph/UG, Cluesurf, Cronos, Daemon, Duelist, EOD, EliCZ,
Eternal Bliss, Fodder, FLWright, Gamumba, GanJaMaN, G-RoM, Grugq, Hackwizz, Hasher,
Ivanopulo, __Ice, JB007, [k], Kahel, LaBBa, LightDruid, LordByte, LutinNoir, mac, MAK,
Minothaur, Muffin, Necrotoad, NchantA, NeoXQuick, Night, Nihil, NikDH, Nitrus, NoodleSpa,
Noos, Nukem, Ousir, Pain, Pal, Pedro, Predator, Quantico, R2-C2, Reeb, SAC, ScareByte,
Seifer, shandi, Snacker, Snaker, Spath, StatMan, Syntax, TaMaMBoLo, tE!, The Owl, tHeRaiN,
Thigo, Thrawn, +Tired, Titi, TomCraft, Toonie, ToyBomB, Unf4rgiv3n, Unknown One, VAG,
WarezPop, X-Lock, Yoda, Zack, ZigD and all i forgot!!!
