#include "stdafx.h"
#include "Class.h"

#include <assert.h>

//   онтейнер дл€ хранени€ до 2-х аргументов.
struct NIL {};
class IArguments { public: virtual ~IArguments() {} };
template< class T1 = NIL, class T2 = NIL >
class Arguments: public IArguments
{
public:
	Arguments() {}
	Arguments(T1 i_arg1): arg1(i_arg1) {}
	Arguments(T1 i_arg1, T2 i_arg2): arg1(i_arg1), arg2(i_arg2) {}
	T1 arg1;
	T2 arg2;
};

//   онтейнер дл€ хранени€ указател€ на метод.
class IContainer
{
public:
	virtual void Call(IArguments*) = 0;
};
template< class T, class M > class Container: public IContainer {};

//  —пециализаци€ дл€ метода без аргументов.
template< class T >
class Container< T, void (T::*)(void) >: public IContainer
{
	typedef void (T::*M)(void);
public:
	Container(T* c, M m): m_class(c), m_method(m) {}
private:
	T* m_class;
	M m_method;
public:
	void Call(IArguments* i_args)
	{
		(m_class->*m_method)();
	}
};

//  —пециализаци€ дл€ метода с одним аргументом.
template< class T, class A1 >
class Container< T, void (T::*)(A1) >: public IContainer
{
	typedef void (T::*M)(A1);
	typedef Arguments<A1> A;
	public:
		Container(T* c, M m): m_class(c), m_method(m) {}
	private:
		T* m_class;
		M m_method;
	public:
		void Call(IArguments* i_args)
		{
			A* a = dynamic_cast< A* >(i_args);
			assert(a);
			if(a) (m_class->*m_method)(a->arg1);
		}
};

//  —пециализаци€ дл€ метода с двум€ аргументами
template< class T, class A1, class A2 >
class Container< T, void (T::*)(A1, A2) >: public IContainer
{
	typedef void (T::*M)(A1, A2);
	typedef Arguments<A1, A2> A;
	public:
		Container(T* c, M m): m_class(c), m_method(m) {}
	private:
		T* m_class;
		M m_method;
	public:
		void Call(IArguments* i_args)
		{
			A* a = dynamic_cast< A* >(i_args);
			assert(a);
			if(a) (m_class->*m_method)(a->arg1, a->arg2);
		}
};

//  —обственно делегат.
class Delegate
{
public:

	Delegate(): m_container(0) {}
	~Delegate() { if(m_container) delete m_container; }

	template< class T, class U > void Connect(T* i_class, U i_method)
	{
		if(m_container) delete m_container;
		m_container = new Container< T, U >(i_class, i_method);
	}

	void operator()()
	{
		m_container->Call(&Arguments<>());
	}

	template< class T1 > void operator()(T1 i_arg1)
	{
		m_container->Call(&Arguments< T1 >(i_arg1));
	}

	template< class T1, class T2 > void operator()(T1 i_arg1, T2 i_arg2)
	{
		m_container->Call(&Arguments< T1, T2 >(i_arg1, i_arg2));
	}

private:
	IContainer* m_container;
};

struct Int
{
	int i = 0;
	void Add()
	{
		i = 5;
	}
	int Get()
	{
		return i;
	}
};


class IClass
{
public:
	virtual void Call() = 0;
};

template< class C>
class Clas: public IClass
{
private:
public:
	C m_class;
	Clas(C c): m_class(m) {}
};
//
//  онтейнер дл€ хранени€ указател€ на метод.
class ICont
{
public:
	virtual void Call(char *v, ...) = 0;
};

template<class M>
class ContV: public ICont
{
private:
	M m_method;
public:
	ContV(M m): m_method(m) {}
	void Call(char *v, ...)
	{
		(*m_method)();
	}
};

template<class C, class M>
class Cont: public ICont
{
private:
	M m_method;
//	typename result_of<decltype(m_method)(C)>::type val;
public:
	Cont(M m): m_method(m) {}
	void Call(char *v, ...)
	{
		((C*)v->*m_method)();
	}
};

class Del
{
	ICont* mCont = nullptr;
public:
	template<class C, class M> void Connect(M method)
	{
		if(mCont) delete mCont;
		mCont = new Cont<C, M>(method);
	}
	template<class M> void Connect(M method)
	{
		if(mCont) delete mCont;
		mCont = new ContV<M>(method);
	}
	void Call()
	{
		mCont->Call(nullptr);
	}
	template<typename... Args> void Call(void *v, Args... args)
	{
		mCont->Call((char*)v, args...);
	}
};

void Vr()
{
	cout << "vr" << endl;
}

int main()
{
	//void *v = Int::Add;
	Int id;
	Del d;
	d.Connect<Int>(&Int::Add);
	d.Call(&id, 5, 8, 5);

	d.Connect(&Vr);
	d.Call();

	cout << id.i;
	string code = "int i = 5, v = 6 + 2; i = 8;";
	Compiler comp;
	comp.Init();
	comp.Compile(code);
	int i;
	cin >> i;
	return 0;
}