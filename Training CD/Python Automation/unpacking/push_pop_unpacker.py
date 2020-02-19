#!c:\\python\\python.exe

"""
Push/Pop "Unpacker" (ie: auto OEP finder)
Copyright (C) 2007 Pedram Amini <pedram.amini@gmail.com>

$Id: push_pop_unpacker.py 214 2007-08-23 05:48:44Z pedram $

Description:
    This is a quick and dirty PyDbg implementation of a known generic technique for stopping an unpacker at OEP. In
    essence the script does the following. Single step the packed executable until a PUSHA(D) is discovered. Step over
    the PUSHA(D) instruction and set a hardware breakpoint somewhere in the stack-range of the pushed data. Continue
    execution until the breakpoint is hit, usually due to a POPA(D). This is at or near the OEP. Works against UPX,
    ASPack, I believe NSPack and others.

    This script was written during Ero and I's 2007 Reverse Engineering class at BlackHat:

        http://www.blackhat.com/html/bh-usa-07/train-bh-us-07-pa.html
"""

from pydbg         import *
from pydbg.defines import *

import os
import sys
import pefile

try:
    target  = sys.argv[1]
    monitor = None
except:
    sys.stderr.write("push_pop_unpacker.py <exe to unpack>\n")
    sys.exit(1)

if not os.path.exists(target):
    sys.stderr.write("%s not found.\n" % target)
    sys.exit(1)

def end_of_packer (dbg):
    print "%08x: end of packer reached?!?" % dbg.exception_address
    dbg.terminate_process()
    return DBG_CONTINUE

def set_stack_bp (dbg):
    global monitor
    print "current ESP: %08x" % dbg.context.Esp
    print "setting hw bp at: %08x" % monitor
    dbg.bp_set_hw(monitor, 4, HW_ACCESS, handler=end_of_packer, restore=False)

    return DBG_CONTINUE

def set_stack_bp_helper (dbg):
    global monitor
    monitor = dbg.context.Esp - 4

    print "setting breakpoint to call set_stack_bp() with monitor at %08x" % monitor
    dbg.bp_set(dbg.exception_address + dbg.instruction.length, handler=set_stack_bp, restore=False)

def entry_point (dbg):
    disasm = dbg.disasm(dbg.exception_address)
    print "%08x: %s" % (dbg.exception_address, disasm)

    if not disasm.startswith("pusha"):
        dbg.single_step(True)
    else:
        set_stack_bp_helper(dbg)

    return DBG_CONTINUE

def single_step (dbg):
    disasm = dbg.disasm(dbg.exception_address)
    print "%08x: %s" % (dbg.exception_address, disasm)

    if not disasm.startswith("pusha"):
        dbg.single_step(True)
    else:
        set_stack_bp_helper(dbg)

    return DBG_CONTINUE


# find the entry point for this bad boy.
pe = pefile.PE(target)
ep = pe.OPTIONAL_HEADER.AddressOfEntryPoint + pe.OPTIONAL_HEADER.ImageBase

dbg = pydbg()
dbg.set_callback(EXCEPTION_SINGLE_STEP, single_step)
dbg.load(target)
dbg.bp_set(ep, handler=entry_point, restore=False)
dbg.run()