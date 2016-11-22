#pragma once
enum OPERATOR_TYPE
{
	OPERATOR_DELIM = 0,
	OPERATOR_UNARY = 1,
	OPERATOR_BINARY = 2,
	OPERATOR_TERNARY = 3
};
enum ASSOC_TYPE
{
	ASSOC_NONE = 0,
	ASSOC_LEFT_TO_RIGHT = 1,
	ASSOC_RIGHT_TO_LEFT = 2,
};
enum SYNTAX_TYPE
{
	SYNTAX_NONE = 0,
	SYNTAX_KEYWORD = 1,
	SYNTAX_OPERATOR = 2,
	SYNTAX_VARIABLE = 3,
	SYNTAX_BLOCK = 4,
	SYNTAX_TYPENAME = 5,
	SYNTAX_CONST = 6,
};
struct Lexem
{

};
struct Operator
{
	string name;
	OPERATOR_TYPE type;
	int prior;
	ASSOC_TYPE assoc;
};
struct Type
{
	string name;
	int id;
	int size;
};
struct Syntax
{
	Syntax *root = nullptr;
	vector<Syntax *> childs;
	SYNTAX_TYPE type = SYNTAX_NONE;
	string value;
};
struct CodeVar
{
	int id;
	string name;
};
struct CodeBlock
{
	vector<CodeVar*> vars;
	CodeVar *AddVar(const string &name);
};
struct Semantix
{
	Semantix *root = nullptr;
	vector<Semantix *> childs;
	SYNTAX_TYPE type = SYNTAX_NONE;
	union Data
	{
		Operator *op;
		Type *type;
		CodeVar *var;
		CodeBlock *block;
	};
	Data data = {0};
	string cData;
};