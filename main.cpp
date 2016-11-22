#include "stdafx.h"
#include "Class.h"

struct Int
{
	int i = 0;
	void Add(int a, int b)
	{
		i = a + b;
	}
};
int main()
{
	//void *v = Int::Add;
	string code = "int i = 5, v = 6 + 2; i = 8;";
	Compiler comp;
	comp.Init();
	comp.Compile(code);
	int i;
	cin >> i;
	return 0;
}