#!/usr/bin/python
import os

def MakeDir_And_Mv_binary(dirname, binary):
    if not os.path.exists(dirname):
        os.mkdir(dirname)
    os.system("mv" binary "build/")  
