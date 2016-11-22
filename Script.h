#pragma once
class Script
{
	char *_data;
	int _entry;
public:
	void Init(char *data, int size, int entry);
	void Run();
};