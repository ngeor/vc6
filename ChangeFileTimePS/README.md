# ChangeFileTimePS
A property page shell extension that allows modifying the file timestamps (legacy project)

![screenshot](/scrnshot.png?raw=true "Screenshot")

## Known issues

In Visual Studio C++ 6, the `ChangeFileTimePS.tlb` will be generated inside the `Debug`
folder and needs to be copied back to the project folder.

## Installation

Register with `regsvr32 ChangeFileTimePS.dll`,
unregister with `regsvr32 /u ChangeFileTimePS.dll`
