.PHONY:

BASH="C:\Program Files\Git\bin\bash.exe"

all:
	echo "not implemented yet"
vs2019:
	msbuild vs2019.sln -t:Rebuild -p:Configuration=Debug
	msbuild vs2019.sln -t:Rebuild -p:Configuration=Release
format:
	$(BASH) -c 'find . -type f -name "*.cpp" -exec clang-format -i \{\} \;'
	$(BASH) -c 'find . -type f -name "*.h" -exec clang-format -i \{\} \;'
clean:
	git clean -fdx
vs6:
	echo "not implemented yet"
# "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
