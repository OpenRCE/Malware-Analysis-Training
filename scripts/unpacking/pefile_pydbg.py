import pefile
import os
import time
import pydbg

pe_kernel32 = ('kernel32', pefile.PE('c:/windows/system32/kernel32.dll'))
pe_user32 = ('user32', pefile.PE('c:/windows/system32/user32.dll'))

export_names = dict()
export_addr = set()

for name, pe in (pe_kernel32, pe_user32):
    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        addr = pe.OPTIONAL_HEADER.ImageBase + exp.address
        #print hex(addr), exp.name
        export_addr.add(addr)
        export_names[addr] = '%s.%s' % (name, exp.name)
    
print '> Loaded %d exported symbols' % len(export_addr)


# If we want to be clever about dumping the right stuff...
#
# import pefile

exe_path = "calc-aspack.exe"

print '> starting process...'
process_handle = os.spawnl(os.P_NOWAIT, exe_path, exe_path)
print '> process started. Process Handle %d' % process_handle

time.sleep(3)

dbg = pydbg.pydbg()

print dbg.enumerate_processes()

process_pid = None
for pid, name in dbg.enumerate_processes():
    if exe_path in name:
        process_pid = pid
        
if process_pid is None:
    print 'Could not attach, process not found'
    os.sys.exit(1)
    
print '> found proces with PID %d' % process_pid

print '> attaching'
dbg.attach(process_pid)


range_start = None
range_end = None
valid_range = None
data = list()

for addr in range(0x00000000, 0x02000000, 0x1000):
    
    try:
        data.append( dbg.read(addr, 0x1000) )
        if range_start is None:
            range_start = addr
        range_end = addr+0xfff
    except Exception, pydbg.pdx:
        if range_start:
            valid_range = (range_start, range_end)
        range_start, range_end = None, None
        
    if valid_range:
        print 'Valid pages at %x->%x %d %f' % (
            valid_range[0], valid_range[1], 
            valid_range[1] - valid_range[0], len(''.join(data)) )
        f = file('dump_%08x-%08x.bin' % (valid_range[0], valid_range[1]), 'w+b')
        data = ''.join(data)
        f.write(data)
        f.close()
        for idx in range(len(data)-4):
            dword = (ord(data[idx])) | (ord(data[idx+1])<<8) | (ord(data[idx+2])<<16) | (ord(data[idx+3])<<24)
            if dword in export_addr:
                print '>   Possible PTR to [0x%08x:%s] found at 0x%08x' % (dword, export_names[dword], valid_range[0]+idx)
        valid_range = None
        data = list()
        

print '> detaching'
dbg.detach()

os.waitpid(process_handle, 0)
