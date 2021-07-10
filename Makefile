.PHONY:

BASH="C:\Program Files\Git\bin\bash.exe"

all:
	msbuild vs2019.sln -t:Rebuild -p:Configuration=Debug
	msbuild vs2019.sln -t:Rebuild -p:Configuration=Release
format:
	$(BASH) -c 'find . -type f -name "*.cpp" -exec clang-format -i \{\} \;'
	$(BASH) -c 'find . -type f -name "*.h" -exec clang-format -i \{\} \;'
clean:
	git clean -fdx
