#pragma once
class Compiler;
class Lexer
{
private:
	vector<string> _list;
	void AddWord(string &word);
public:
	vector<string> &GetList() { return _list; };
	void Compile(const string &code, class Compiler *comp);
	void Print();
};
