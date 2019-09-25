#!usr/bin/python

import sys
import os

argNum = len(sys.argv)
cnt = 1
cmd =  "cmake"
ninja ="ninja"
make = "make"
isbuild = False
idx = 0
print  sys.argv[argNum-1]
if argNum > 1:
    while cnt < argNum:
        print "cmaking and maybe compiling"
        
        if sys.argv[cnt] == "-cn":
            cmd = cmd + " -GNinja ."
        
        elif sys.argv[cnt] == "-c":
            cmd = cmd+" ."
        
        elif sys.argv[cnt] == "-b":
            isbuild = True
        
        cnt = cnt +1

os.system(cmd)

if isbuild :
    if cmd == "cmake .": 
        os.system(make)
    elif cmd == "cmake -GNinja .":
        os.system(ninja)
