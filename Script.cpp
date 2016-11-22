#include "stdafx.h"
#include "Script.h"

void Script::Init(char *data, int size, int entry)
{
	_data = new char[size];
	memcpy(_data, data, size);
	_entry = entry;
}
void Script::Run()
{

}