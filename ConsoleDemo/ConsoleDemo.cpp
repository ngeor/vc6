// ConsoleDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\DynamicLibraryDemo\DynamicLibraryDemo.h"

int main(int argc, char *argv[])
{
	printf("Hello World!\n");
	int x = Add(1, 3);
	printf("Add result is %d\n", x);
	return 0;
}
