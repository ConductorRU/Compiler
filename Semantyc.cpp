#include "stdafx.h"
#include "Struct.h"
#include "Syntaxer.h"
#include "Semantyc.h"
#include "Compiler.h"

CodeVar *CodeBlock::AddVar(const string &name)
{
	CodeVar *v = new CodeVar;
	v->name = name;
	v->id = vars.size();
	vars.push_back(v);
	return v;
}

void Semantyc::Compile(Syntaxer *syn, Compiler *comp)
{
	block = new CodeBlock;
	_root = new Semantix;
	_root->type = SYNTAX_BLOCK;
	_root->data.block = block;
	vector<Syntax*> ls = syn->GetList();
	for(Syntax *s : ls)
	{
		if(s->type == SYNTAX_TYPENAME)//объ€влени€ переменных
		{
			Semantix *sem = new Semantix;
			sem->type = s->type;
			sem->data.type = comp->GetType(s->value);
			for(Syntax *vName : s->childs)
			{
				Semantix *vSem = new Semantix;
				vSem->type = vName->type;
				CodeVar *var = block->AddVar(vName->value);
				if(var)
				{
					vSem->data.var = var;
					vSem->root = sem;
					sem->childs.push_back(vSem);
				}
			}
			_root->childs.push_back(sem);
		}
	}
}

void Semantyc::Print()
{

}