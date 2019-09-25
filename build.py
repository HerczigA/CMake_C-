#!usr/bin/python

import sys
import os

argNum = len(sys.argv)
cnt = 1
cmd =  "cmake -GNinja ."
ninja ="ninja"
make = "make"
isbuild = False
cleaning = False
iscompile = False
rm = "rm -rf CMakeFiles *.ninja *.cmake *Cache* Tutorial"

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
	
	-x or --purge remove all the unnecessary build 
	files, executable files  and directory(CMakeFiles)
	"""
	exit()
else:
    print """
    Use <python ./build --help> or
    <python ./build -h> to get some
    help about the building script 
    """
    exit()


if argNum > 1:
    temp = sys.argv[1]
    while cnt < argNum:

        if temp  == "-c" or temp == "--cmake":
	    isbuild = True
	    os.system(cmd)

        elif  temp == "-b" or temp == "--build":
            iscompile = True

	elif temp == "-x" or temp == "--purge":
	    cleaning = True

        cnt = cnt +1
	if (argNum-1) >= cnt:
	    temp = sys.argv[cnt]


if cleaning:
    os.system(rm)
    if isbuild :
	os.system(cmd)
    if iscompile:
	os.system(ninja)

elif isbuild :
	os.system(cmd)
	if iscompile:
	    os.system(ninja)
elif iscompile:
    os.system(ninja)    