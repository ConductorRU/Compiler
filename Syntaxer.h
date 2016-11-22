#pragma once
class Lexer;
class Compiler;
class Syntaxer
{
private:
	vector<Syntax*> _root;
	Syntax *SplitOp(const vector<string> &block, Compiler *comp, int start, int end, int &cur);
	Syntax *TypeBlock(const vector<string> &block, Compiler *comp);
	Syntax *CompileBlock(const vector<string> &block, Compiler *comp);
	void Print(Syntax *el, int depth);
public:
	vector<Syntax*> &GetList() { return _root; };
	void Compile(Lexer *lexer, Compiler *comp);
	void Print();
};