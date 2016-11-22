#pragma once
class Lexer;
class Syntaxer;
class Compiler
{
private:
	Lexer *lex;
	Syntaxer *syn;
	vector<Operator> _ops;
	set<string> _keywords;
	map<string, Type> _types;
	void AddType(const string &name, int size);
public:
	void Init();
	Operator *GetOperator(const string &val);
	Type *GetType(const string &val);
	bool IsKeyword(const string &val);
	bool IsVarName(const string &val);
	void Compile(const string &code);
};