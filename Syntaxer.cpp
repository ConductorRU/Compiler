#include "stdafx.h"
#include "Struct.h"
#include "Lexer.h"
#include "Syntaxer.h"
#include "Compiler.h"

Syntax *Syntaxer::SplitOp(const vector<string> &block, Compiler *comp, int start, int end, int &cur)
{
	int maxPrior = 1000;
	Operator *rootOp = nullptr;
	int split = 0;
	for(int i = start; i < end; ++i)
	{
		Operator *op = comp->GetOperator(block[i]);
		if(op)
		{
			if(op->name == ",")
			{
				end = i;
				cur = i;
				break;
			}
			if(!rootOp || maxPrior < op->prior)
			{
				rootOp = op;
				maxPrior = op->prior;
				split = i;
			}
		}
	}
	if(start == end - 1)
	{
		Syntax *par = new Syntax;
		par->value = block[start];
		par->type = SYNTAX_CONST;
		cur = start;
		return par;
	}
	if(rootOp)
	{
		Syntax *par = new Syntax;
		par->value = rootOp->name;
		par->type = SYNTAX_OPERATOR;
		Syntax *c1 = SplitOp(block, comp, start, split, cur);
		Syntax *c2 = SplitOp(block, comp, split + 1, end, cur);
		if(c1)
		{
			c1->root = par;
			par->childs.push_back(c1);
		}
		if(c2)
		{
			c2->root = par;
			par->childs.push_back(c2);
		}
		return par;
	}
	return nullptr;
}

Syntax *Syntaxer::TypeBlock(const vector<string> &block, Compiler *comp)
{
	int size = block.size();
	Syntax *parent = new Syntax;
	parent->type = SYNTAX_TYPENAME;
	parent->value = block[0];
	bool isComa = false;
	Syntax *var = nullptr;
	for(int i = 1; i < size; ++i)
	{
		if(comp->IsVarName(block[i]))//if typename
		{
			var = new Syntax;
			var->value = block[i];
			var->type = SYNTAX_VARIABLE;
			var->root = parent;
			if(var->root)
				var->root->childs.push_back(var);
			isComa = false;
		}
		else if(!isComa && block[i] == ",")//if comma
		{
			isComa = true;
		}
		else if(!isComa && var && block[i] == "=")//if setter
		{
			++i;
			Syntax *val = SplitOp(block, comp, i, block.size(), i);
			if(val)
			{
				var->childs.push_back(val);
				val->root = var;
			}
		}
		else
		{
			cout << "Error" << endl;
		}
	}
	return parent;
}
Syntax *Syntaxer::CompileBlock(const vector<string> &block, Compiler *comp)
{
	int size = block.size();
	if(!size)
		return nullptr;
	Syntax *parent = nullptr;
	Type *type = comp->GetType(block[0]);
	if(type)
		parent = TypeBlock(block, comp);
	else
	{
		int i = 0;
		parent = SplitOp(block, comp, 0, block.size(), i);
	}
	return parent;
}
void Syntaxer::Compile(Lexer *lexer, class Compiler *comp)
{
	vector<string> list = lexer->GetList();
	int size = list.size();
	string s;
	vector<string> block;
	for(int i = 0; i < size; ++i)
	{
		s = list[i];
		if(s != ";")
			block.push_back(list[i]);
		else
		{
			Syntax *par = CompileBlock(block, comp);
			if(par)
				_root.push_back(par);
			block.clear();
		}
	}
}
void Syntaxer::Print(Syntax *el, int depth)
{
	for(int i = 0; i < depth; ++i)
		cout << "  ";
	cout << el->value << endl;
	for(Syntax *s : el->childs)
		Print(s, depth + 1);
}
void Syntaxer::Print()
{
	for(Syntax *s : _root)
		Print(s, 0);
}