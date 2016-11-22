#pragma once
class Syntaxer;
class Compiler;
class Semantyc
{
private:
	CodeBlock *block;
	Semantix* _root;
public:
	void Compile(Syntaxer *syn, Compiler *comp);
	void Print();
};