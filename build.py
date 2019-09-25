#!usr/bin/python

import sys
import os

argNum = len(sys.argv)
cnt = 1
cmd =  "cmake"
ninja ="ninja"
make = "make"
isbuild = False

if argNum > 1:
    helper = sys.argv[1]
    if (helper == "--help")  or ( helper == "-h"):
	print """
	*********************Build.py********************

	It is a simple python script to help easily build
	and compile your project! You have to know it is
	a hobby project and now it is at the begining.
	Try to get ideas and implement to here.
	
	Usage: Add arguments for ./build.py. It can use
	more than one arguments.
	
	Possibilities:
	 -c or --cmake -> It will generate
	cmake scripts and environment for build the project.
	It will generate for ninja not for make.
	
	-b or --build -> If the CMakeLists.txt is proper 
	and the script could generate the important cmake
	files, then the python script try to compile the 
	project with ninja.
	
	-x or --purge remove....
	"""
	exit()
else:
    print """
    Use <python ./build --help> or
    <python ./build -h> to get some
    help about the building script 
    """
    exit()

print  len(sys.argv)
if argNum > 1:
    temp = sys.argv[1]
    while cnt < argNum:
        print "cmaking and maybe compiling"
        
        if temp  == "-c" or temp =="--cmake":
            cmd = cmd + " -GNinja ."
        
        elif  temp == "-b" or temp == "--build":
            isbuild = True
        
	if argNum-1 > cnt:
            cnt = cnt +1
	    temp = sys.argv[cnt]

os.system(cmd)

if isbuild :
    if cmd == "cmake .": 
        os.system(make)
    elif cmd == "cmake -GNinja .":
        os.system(ninja)
