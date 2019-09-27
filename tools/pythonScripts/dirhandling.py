#!/usr/bin/python3

import os
import sys

def MakeDir_And_Mv_binary(dirname, binary):
    if not os.path.exists(dirname):
        os.mkdir(dirname)
    Movecmd ="mv "
    Movecmd = Movecmd + binary
    Movecmd = Movecmd + " build/"
    os.system( Movecmd )