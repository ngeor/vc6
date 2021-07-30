# Microsoft Developer Studio Project File - Name="ChangeFileTimePS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ChangeFileTimePS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ChangeFileTimePS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ChangeFileTimePS.mak" CFG="ChangeFileTimePS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChangeFileTimePS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ChangeFileTimePS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ChangeFileTimePS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../i386/Release"
# PROP BASE Intermediate_Dir "i386/Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../i386/Release"
# PROP Intermediate_Dir "i386/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ChangeFileTimePS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ChangeFileTimePS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x408 /d "NDEBUG"
# ADD RSC /l 0x408 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "ChangeFileTimePS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../i386/Debug"
# PROP BASE Intermediate_Dir "i386/Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../i386/Debug"
# PROP Intermediate_Dir "i386/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ChangeFileTimePS_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ChangeFileTimePS_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x408 /d "_DEBUG"
# ADD RSC /l 0x408 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ChangeFileTimePS - Win32 Release"
# Name "ChangeFileTimePS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChangeFileTimeHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeFileTimePS.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeFileTimePS.idl
# ADD MTL /tlb ".\ChangeFileTimePS.tlb" /h "ChangeFileTimePS.h" /iid "ChangeFileTimePS_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\GlobalWinObjInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurseModeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SimplePage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChangeFileTimeHandler.h
# End Source File
# Begin Source File

SOURCE=.\GlobalWinObjInstance.h
# End Source File
# Begin Source File

SOURCE=.\RecurseModeDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SimplePage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringList.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ChangeFileTimePS.rc
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Question.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChangeFileTimePS.def
# End Source File
# Begin Source File

SOURCE=.\README.md
# End Source File
# End Target
# End Project
