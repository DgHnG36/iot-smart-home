Import("env")

import os

if os.name == "nt":
    msys_bin = r"C:\msys64\ucrt64\bin"
    gcc = os.path.join(msys_bin, "gcc.exe")
    gxx = os.path.join(msys_bin, "g++.exe")

    if os.path.exists(gcc) and os.path.exists(gxx):
        os.environ["CC"] = gcc
        os.environ["CXX"] = gxx
        os.environ["PATH"] = msys_bin + os.pathsep + os.environ.get("PATH", "")

        env.Replace(CC=gcc, CXX=gxx)
        env.Replace(LINK=gxx)
        env.PrependENVPath("PATH", msys_bin)
