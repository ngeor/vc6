// ConsoleDemo.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include "..\DynamicLibraryDemo\DynamicLibraryDemo.h"
#include "..\StaticLibraryDemo\StaticLibraryDemo.h"

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	int x = Add(1, 3);
	printf("Add result is %d\n", x);
	int y = Subtract(9, 1);
	printf("Subtract result is %d\n", y);
	return 0;
}
