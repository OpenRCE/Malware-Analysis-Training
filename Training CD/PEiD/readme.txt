PE iDentifier v0.94 by snaker, Qwerton, Jibz & xineohP
------------------------------------------------------

PEiD detects most common packers, cryptors and compilers for PE files. It can currently detect more than 600 different signatures in PE files.

PEiD is special in some aspects when compared to other identifiers already out there!

1. It has a superb GUI and the interface is really intuitive and simple.
2. Detection rates are amongst the best given by any other identifier.
3. Special scanning modes for *advanced* detections of modified and unknown files.
4. Shell integration, Command line support, Always on top and Drag'n'Drop capabilities.
5. Multiple file and directory scanning with recursion.
6. Task viewer and controller.
7. Plugin Interface with plugins like Generic OEP Finder and Krypto ANALyzer.
8. Extra scanning techniques used for even better detections.
9. Heuristic Scanning options.
10. New PE details, Imports, Exports and TLS viewers
11. New built in quick disassembler.
12. New built in hex viewer.
13. External signature interface which can be updated by the user.


There are 3 different and unique scanning modes in PEiD.

The *Normal Mode* scans the PE files at their Entry Point for all documented signatures. This is what all other identifiers also do.

The *Deep Mode* scans the PE file's Entry Point containing section for all the documented signatures. This ensures detection of around 80% of modified and scrambled files.

The *Hardcore Mode* does a complete scan of the entire PE file for the documented signatures. You should use this mode as a last option as the small signatures often tend to occur a lot in many files and so erroneous outputs may result.

The scanner's inbuilt scanning techniques have error control methods which generally ensure correct outputs even if the last mode is chosen. The first two methods produce almost instantaneous outputs but the last method is a bit slow due to obvious reasons!


Command line Options
--------------------

PEiD now fully supports commandline parameters.

peid -time	// Show statistics before quitting
peid -r		// Recurse through subdirectories
peid -nr	// Don't scan subdirectories even if its set
peid -hard	// Scan files in Hardcore Mode
peid -deep	// Scan files in Deep Mode
peid -norm	// Scan files in Normal Mode

peid <file1> <file2> <dir1> <dir2>

You can combine one or more of the parameters.


For example.

peid -hard -time -r c:\windows\system32
peid -time -deep c:\windows\system32\*.dll


Task Viewing / Control Module
-----------------------------

You can scan currently running tasks with PEiD. The files are scanned from memory. Processes can also be terminated. You can also optionally dump a module and scan the dumped image. You can also view all dependant modules of the processes.


Multiple File Scan Module
-------------------------

You can scan multiple files at one go with PEiD. Just drag and drop the files on the PEiD main dialog and the Multiple File Scan Dialog will popup displaying the results. You can keep dragging and dropping files onto this dialog as well. It also offers you to choose from the different scanning modes and optionally load a single file in PEiD. It allows you to skip the non PE files so that the list looks clean. You can also scan the contents of a directory choosing files of custom extension if required. MFS v0.02 now supports recursive directory scanning.


Disassembler Module
-------------------

You can have a quick disassembly of the file loaded in PEiD. Double click to follow JMPs and CALLs and use the Back button to trace back to the original positions. You can copy disassembled output to the clipboard. A new CADT core with custom String Reference Finder has been cooked up.
CADT is coded by Ms-Rem.


Hex Viewer Module
-------------------

You can have a quick hex view of the file loaded in PEiD. A modified version of 16Edit by y0da is used for this purpose.


We intend to update the signatures quite often to keep pace with this ever evolving scene :)


Please report bugs, ideas, new signatures or packer info to: 
snaker	-> snaker(at)myrealbox(dot)com
Jibz	-> peid(at)ibsensoftware(dot)com
Qwerton -> qwaci(at)gmx(dot)net

ALL SUGGESTIONS, IDEAS, BUG REPORTS AND CRITICS ARE WELCOME.


History
-------

0.7 Beta 	-> 	First public release.

0.8 Public	->	Added support for 40 more packers. OEP finding module. Task viewing/control module.
			GUI changes. General signature bug fixes. Multiple File and Directory Scanning module.

0.9 Recode	->	Completely recoded from scratch.  New Plugin Interface which lets you use extra features.
			Added more than 130 new signatures. Fixed many detections and general bugs.

0.91 Reborn	-> 	Recoded everything again. New faster and better scanning engine. New internal signature system.
 			MFS v0.02 now supports Recursive Scanning. Commandline Parser now updated and more powerful.
			Detections fine tuned and newer detections added. Very basic Heuristic scanning.

0.92 Classic	->	Added support for external database, independent of internal signatures. Added PE details lister.
			Added Import, Export, TLS and Section viewers. Added Disassembler. Added Hex Viewer.
			Added ability to use plugins from Multiscan window. Added exporting of Multiscan results.
			Added ability to abort MultiScan without loosing results.
			Added ability to show process icons in Task Viewer.
			Added ability to show modules under a process in Task Viewer. Added some more detections.

0.93 Elixir	->	Added sorting of Plugin menu items. Submenus are created based on subfolders in the directory.
			Added Brizo disassembler core. Added some more detections.
			Fixed documented and undocumented vulnerability issues.
			Fixed some general bugs.
			Removed mismatch mode scanner which needs further improvements.

0.94 Flux	->	Too much is new to remember.
			MFS, Task Viewer and Disassembler windows maximizable.
			New smaller and lighter disassembler core CADT.
			New KANAL 2.90 with much more detections and export features.
			Added loads of new signatures. Thanks to all the external signature collections online.
			String References integrated into disassembler.
			Fixed documented and undocumented crashes.
			Fixed some general bugs.

Greets
------

Qwerton, Jibz, CHRiST0PH, uno, DAEMON, MackT, VAG, SAC, Gamumba, SnowP and all the rest at uG, Michael Hering, tE!, pusher, {igNo}, Maxx, CoDE, BaND, Snacker, skamer, HypnZ, ParaBytes, Clansman, BuLLeT, Devine9, innuendo, Corby, cokine, AiRW0lF, fxfighter, GodsJiva, Carpathia, _death, artik, r!sc, NoodleSPA, SiR_dReaM, CHoRDLeSS, NeOXQuiCk, un4Giv3n, RZX, 7xS, LibX and all who helped with PEiD :)

snaker, Jibz, cokine, Iczelion, Clansman, Z-Wing, Unknown One/TMG, PeeWee, DnNuke, sinny/BAFH, all the other nice people in CiA, uG and all of you who helped us develope PEiD. Thanks.

snaker, Qwerton, DAEMON, VaG, Parabytes, bse, f0dder, Stone, Michael Hering, Iczelion, Steve Hutchesson, Eugene Suslikov, and everybody in #unpacking and #compression.


Qwerton		- Hope you get time someday again, was nice working with you :)
Jibz		- You rock evil friend. Thanks for all your help. It's a pleasure working with you. Hope things work out!
Michael Hering	- FILE INFO is still the absolute best. Your suggestions rock :)
uG2oo6		- Delicious Slumber!
MackT		- Thanks for all your help and for ImpREC of course ;)
Unknown One	- Spend more time with us :)
BaND		- Thanks for all your testing and help.
pusher		- Thanks for your help and all the testing and the constant encouragment ;)
Maxx		- Thanks for the encouragment, your code and suggestions should be added next time :)
Kaparo & Aaron	- Thanks for your sites :)


We would also like to thank the *few* people who sent us their comments and feedback about PEiD. 
Also greetings to everyone who has supported PEiD till date. Without you this new release would never be possible.


You can check out the PEiD homepage at http://peid.has.it and the PEiD Forums at http://peidforums.has.it


snaker, Qwerton, Jibz & xineohP Productions
	     -2006-
