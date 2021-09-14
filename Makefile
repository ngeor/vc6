.PHONY:

BASH="C:\Program Files\Git\bin\bash.exe"
DOXYGEN="c:\opt\doxygen-1.9.1.windows.x64.bin\doxygen.exe"

all:
	echo "not implemented yet"
vs2019: vs2019_debug vs2019_release
vs2019_debug:
	msbuild vs2019.sln -t:Rebuild -p:Configuration=Debug
vs2019_release:
	msbuild vs2019.sln -t:Rebuild -p:Configuration=Release
vs2019_debug_build:
	msbuild vs2019.sln -p:Configuration=Debug
tidy:
	$(BASH) -c 'find . -type f -name "*.cpp" -exec clang-tidy \{\} --fix \;'
format:
	$(BASH) -c 'find . -type f -name "*.cpp" -exec clang-format -i \{\} \;'
	$(BASH) -c 'find . -type f -name "*.h" -exec clang-format -i \{\} \;'
clean:
	git clean -fdx
vc6:
	powershell -file .\ci\vm.ps1
docs:
	cd BobMarleyTheGod && $(DOXYGEN)
	cd VisiTree && $(DOXYGEN)
	cd WinObj && $(DOXYGEN)

# example for inline script (e.g. in TeamCity):
# ```
# @call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
# nmake vs2019_debug
# ```
