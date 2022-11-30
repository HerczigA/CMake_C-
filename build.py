#!/usr/bin/python

import sys
import os

def runCmake(cmd, directory, isCrossCompiled):
	debug = " -DCMAKE_BUILD_TYPE=Debug "
	platform = "1" if isCrossCompiled else "0"
	if "debug" in directory:
		cmd = cmd + debug
	cmd = cmd + " -B" + directory +" -DENABLE_CROSS_COMPILE=" + platform +" ."
	os.system(cmd)

def building(cmd):
	dirBuild = "build"
	dirDebug = "build_debug"
	if os.path.exists(dirBuild):
		print("Building in", dirBuild)
		os.chdir(dirBuild)
		os.system(cmd)
	elif os.path.exists(dirDebug):
		print("Building in", dirDebug)
		os.chdir(dirDebug)
		os.system(cmd)
	else:
		print("There is no build directory")

argNum = len(sys.argv)
arg_counter = 1
cmd = "cmake -GNinja "
ninja ="ninja"
switches = {
			"-c": False,
			"-b": False,
			"-r" : False,
			"-d" : False,
			"-C" : False
			}

dirBuild = "build"
dirDebug = "build_debug"
directory = dirBuild

rm = "rm -r " + dirBuild + " " + dirDebug

if argNum == arg_counter:
	print("""\n
	Use <python ./build --help> or
    <python ./build -h> to get some
    help about the building script 
	""")
	exit()
elif sys.argv[arg_counter] =="--help" or sys.argv[arg_counter] =="-h":
    print("""
    *********************Build.py********************

	It is a simple python script to help easily build
	and compile your project! You have to know it is
	a hobby project and now it is at the begining.
	Try to get ideas and implement to here.
	
	Usage: Add arguments for ./build.py. It can use
	more than one arguments.
	
	Possibilities:
	-c -> It will generate
	cmake scripts and environment for build the project.
	It will generate for ninja not for make.
	
	-b -> If the CMakeLists.txt is proper 
	and the script could generate the important cmake
	files, then the python script try to compile the 
	project with ninja.
	
	-r remove all the unnecessary build 
	files, executable files  and directory(CMakeFiles)

	-d you can build debug version of the software.

	-C -> choose to cross-compile 
    """)
    exit()

else:
	while arg_counter < argNum:
		argument = sys.argv[arg_counter]
		if argument in switches:
			switches[argument] = True
		
		if argument == "-d":
			directory = dirDebug

		arg_counter = arg_counter +1


if switches["-r"]:
	os.system(rm)
	if switches["-c"]:
		runCmake(cmd, directory, switches["-C"])
	if switches["-b"]:
		building(ninja)
		
elif switches["-c"]:
	runCmake(cmd, directory, switches["-C"])
	
	if switches["-b"]:
		building(ninja)
		
elif switches["-b"]:
	building(ninja)
	

