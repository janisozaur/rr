from rrutil import *

send_gdb('break breakpoint')
expect_gdb('Breakpoint 1')
send_gdb('c')
expect_gdb('Breakpoint 1')

send_gdb('checkpoint')
expect_gdb('= 1')
send_gdb('next')

send_gdb('restart 1')
expect_gdb('stopped')
send_gdb('c')
expect_rr('EXIT-SUCCESS')

ok()
