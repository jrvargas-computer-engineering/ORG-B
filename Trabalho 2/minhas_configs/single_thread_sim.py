# -*- coding: utf-8 -*-

import m5

from m5.objects import *
from m5.util import addToPath
from optparse import OptionParser

from O3System import *

addToPath('../common/')
#import Options

############################################################
## Opções deste script
############################################################

parser = OptionParser()
parser.add_option("-c", "--cmd", default="", help="Binary file to run.")
parser.add_option("-o", "--options", default="",
                  help="""Binary input arguments. Use "" around the string.""")
parser.add_option("-e", "--env", default="",
                  help="""List of ";-separated" environment variables to be
                  set before running the binary. Ex: --env "VAR1=X;VAR2=Y""")

(options, args) = parser.parse_args()

############################################################
# System instantiation
############################################################

system = O3System()

############################################################
## Simulation
############################################################

process = Process()
if options.cmd:
    process.executable = options.cmd

    process.cmd = options.cmd
    if options.options != "": # Options.options is a string
        process.cmd += options.options.split() # That becomes a list here

    print "Program to be run: "
    print "".join([str(i)+" " for i in process.cmd])
else:
    print "Must specify the program to run (--cmd <program>)."

if options.env:
    process.env = options.env.split(";")

print ""

system.cpu.workload = process
system.cpu.createThreads()

root = Root(full_system = False, system = system)
m5.instantiate()

print ""
print "---------------- Begin Simulation ----------------"
exit_event = m5.simulate()
print ""
print 'Finishing simulation. Current tick: %i. Reason: %s' % (
    m5.curTick(), exit_event.getCause())
print "----------------- End Simulation -----------------"
