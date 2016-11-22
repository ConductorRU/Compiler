#include "stdafx.h"
#include "Class.h"
int main()
{
	string code = "int i = 5, v = 6 + 2; i = 8;";
	Compiler comp;
	comp.Init();
	comp.Compile(code);
	int i;
	cin >> i;
	return 0;
}