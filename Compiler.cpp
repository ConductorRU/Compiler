#include "stdafx.h"
#include "Struct.h"
#include "Lexer.h"
#include "Syntaxer.h"
#include "Semantyc.h"
#include "Compiler.h"

void Compiler::AddType(const string &name, int size)
{
	_types[name] = {name, (int)_types.size(), size};
}
void Compiler::Init()
{
	lex = new Lexer;
	syn = new Syntaxer;
	_ops.push_back({";", OPERATOR_DELIM, 20});
	_ops.push_back({",", OPERATOR_DELIM, 17, ASSOC_LEFT_TO_RIGHT});
	_ops.push_back({"=", OPERATOR_BINARY, 15, ASSOC_RIGHT_TO_LEFT});
	_ops.push_back({"+", OPERATOR_BINARY, 6, ASSOC_LEFT_TO_RIGHT});
	_ops.push_back({"-", OPERATOR_BINARY, 6, ASSOC_LEFT_TO_RIGHT});
	_ops.push_back({"/", OPERATOR_BINARY, 5, ASSOC_LEFT_TO_RIGHT});
	_ops.push_back({"*", OPERATOR_BINARY, 5, ASSOC_LEFT_TO_RIGHT});
	AddType("bool", sizeof(bool));
	AddType("char", sizeof(char));
	AddType("uchar", sizeof(unsigned char));
	AddType("short", sizeof(short));
	AddType("ushort", sizeof(unsigned short));
	AddType("int", sizeof(int));
	AddType("uint", sizeof(unsigned int));
	AddType("long", sizeof(long long));
	AddType("ulong", sizeof(unsigned long long));
	AddType("float", sizeof(float));
	AddType("double", sizeof(double));
}
Operator *Compiler::GetOperator(const string &val)
{
	for(Operator &op : _ops)
		if(op.name == val)
			return &op;
	return nullptr;
}
Type *Compiler::GetType(const string &val)
{
	auto it = _types.find(val);
	if(it == _types.end())
		return nullptr;
	return &it->second;
}
bool Compiler::IsKeyword(const string &val)
{
	auto it = _keywords.find(val);
	if(it == _keywords.end())
		return false;
	return true;
}
bool Compiler::IsVarName(const string &val)
{
	if(IsKeyword(val) || GetType(val) || GetOperator(val))
		return false;
	return true;
}
void Compiler::Compile(const string &code)
{
	lex->Compile(code, this);
	lex->Print();
	cout << endl << "Syntax Tree:" << endl;
	syn->Compile(lex, this);
	syn->Print();
}