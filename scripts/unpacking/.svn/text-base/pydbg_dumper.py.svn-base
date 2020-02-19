import os
import pydbg

# If we want to be clever about dumping the right stuff...
#
# import pefile

exe_path = "calc-aspack.exe"

print '> starting process...'
process_handle = os.spawnl(os.P_NOWAIT, exe_path, exe_path)
print '> process started. Process Handle %d' % process_handle

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
        f.write(''.join(data))
        f.close()
        valid_range = None
        data = list()
        

print '> detaching'
dbg.detach()

os.waitpid(process_handle, 0)
