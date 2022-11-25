#!/usr/bin/python

import sys
import os

argNum = len(sys.argv)
arg_counter = 1
cmd =  "cmake -DENABLE_CROSS_COMPILE=1 -GNinja "
debug = "-DCMAKE_BUILD_TYPE=Debug ."
# cmake -Bbuild -GNinja -DENABLE_CROSS_COMPILE=1 .
ninja ="ninja"
isbuild = False
cleaning = False
iscompile = False
isdebug = False
dirBuild = "build"
dirDebug = "build_debug"
directory = dirBuild

target = " mv RPI_IOT "
rm = "rm -r build*"

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
    """)
    exit()

else:
	while arg_counter < argNum:
		argument = sys.argv[arg_counter]
		if argument  == "-c" or argument == "--cmake":
			iscompile = True
		
		elif  argument == "-b" or argument == "--build":
			isbuild = True

		elif argument == "-x" or argument == "--purge":
			cleaning = True

		# elif argument == "-r" or argument == "--Rb":
		# 	os.system(rm_withoutBinary)

		elif argument == "-d" or argument == "--Debug":
			isdebug = True
			directory = dirDebug

		arg_counter = arg_counter +1


if cleaning:
	os.system(rm)
	if isdebug:
		directory = dirDebug
		cmd = cmd + "-B" + directory
	if iscompile:
		cmd = cmd + " ."
		os.system(cmd)
	if isbuild:
		print("Building")
		os.system("cd " + directory)
		os.system(ninja)
		
elif iscompile :
	if isdebug:
		directory = dirDebug	
	cmd = cmd + "-B" + directory + " ."
	os.system(cmd)
	if isbuild:
		print("Building")
		os.system("cd " + directory)
		os.system(ninja)
		

elif isbuild:
	print("Building")
	os.system("cd " + directory)
	os.system(ninja)    
	

