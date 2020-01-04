#!/usr/bin/python

import sys
import os
sys.path.append("tools/pythonScripts/")
import  dirhandling

argNum = len(sys.argv)
cnt = 1
cmd =  "cmake -GNinja ."
debug = "-DCMAKE_BUILD_TYPE=Debug ."
ninja ="ninja"
make = "make"
isbuild = False
cleaning = False
iscompile = False
isdebug = False
dirBuild = "build"
dirDebug = "debug"
target = " mv RPI_IOT "
rm = "rm -rf CMakeFiles *.ninja *.cmake *Cache* build/RPI_IOT .ninja*"
rm_withoutBinary = "rm -rf CMakeFiles *.ninja *.cmake *Cache* .ninja*"

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

	-r or --Rb is similar to -x . Removes every unnecessary
	files except binary

	-d or --Debug you can build debug version software
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
	temp = sys.argv[cnt]
	while cnt < argNum:
		if temp  == "-c" or temp == "--cmake":
			iscompile = True
		
		elif  temp == "-b" or temp == "--build":
			isbuild = True

		elif temp == "-x" or temp == "--purge":
			cleaning = True

		elif temp == "-r" or temp == "--Rb":
			os.system(rm_withoutBinary)

		elif temp == "-d" or temp == "--Debug":
			isdebug = True

		cnt = cnt +1
		if (argNum-1) >= cnt:
			temp = sys.argv[cnt]

if cleaning:
	os.system(rm)
	if isdebug:
		cmd = cmd[:-1]
		cmd = cmd + debug
	if iscompile:
		os.system(cmd)
	if isbuild:
		print "Building"
		os.system(ninja)
		dirhandling.MakeDir_And_Mv_binary(dirBuild,target)


elif iscompile :
	if isdebug:
		cmd = cmd[:-1]
		cmd = cmd + debug
	os.system(cmd)
	if isbuild:
		print "Building"
		os.system(ninja)
		dirhandling.MakeDir_And_Mv_binary(dirBuild,target)

elif isbuild:
	print "Building"
	os.system(ninja)    
	dirhandling.MakeDir_And_Mv_binary(dirBuild,target)

