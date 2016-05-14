#define _CRT_SECURE_NO_WARNINGS
#include"MemoryManager.h"



void Fun(char*& p)
{
	p = new char[20];
}


void Test()
{
	char* src = NULL;
	Fun(src);
	strcpy(src, "change world!");
	cout << src << endl;
	delete[] src;
}

void Test1()
{
	//List<Node<int>*> l;
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	l.Print();

	Node<int>* ret = l.Find(1);
	l.Erase(ret);
	l.Print();
	ret = l.Find(5);
	l.Erase(ret);
	l.Print(); 
	ret = l.Find(3);
	l.Erase(ret);
	l.Print();
}

class String
{
public:
	String(const char* ptr = "")
		:_ptr(new char[strlen(ptr) + 1])
	{
		cout << "String()" << endl;
		strcpy(_ptr, ptr);
	}
	~String()
	{

		if (_ptr)
		{
			cout << "~String()" << endl;
			delete[] _ptr;
		}
	}
private:
	char* _ptr;
};
void Test2()
{
	/*int *p1 = (int *)Alloc(sizeof(int)* 5, __FILE__, __LINE__);
	int *p2 = (int *)Alloc(sizeof(int)* 5, __FILE__, __LINE__);
	char *p3 = (char *)Alloc(sizeof(char)* 5, __FILE__, __LINE__);*/

	//int* p1 = (int*)NEW(sizeof(int)* 5);
	//int* p2 = (int*)NEW(sizeof(int)* 5);
	//char* p3 = (char*)NEW(sizeof(char)* 5);

	//String* p5 = new(p4)String;//new的定位表达式  返回值  
	//String* p4 = (String*)NEW(sizeof(String)* 5);

	//Dealloc(p1);
	//Dealloc(p2);
	//Dealloc(p3);

	//String* p4 = NEW(String);
	//DELETE(p4);

	String* p5 = NEW_ARRAY(String, 5);
	DELETE_ARRAY(p5);

}

void Test3()
{
	int* p1 = NEW(int);
	char* p2 = NEW(char);

	int* p3 = NEW_ARRAY(int,5);
	char* p4 = NEW_ARRAY(char, 5);

	String* p5 = NEW(String);
	String* p6 = NEW_ARRAY(String, 5);

	DELETE(p1);
	DELETE(p2);
	DELETE(p5);

	DELETE_ARRAY(p3);
	DELETE_ARRAY(p4);
	//DELETE_ARRAY(p6);
}

//atexit  注册一个函数，让这个函数在main函数结束以后执行。

//单例模式

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (_sInstance == NULL)
		{
			_sInstance = new Singleton();
		}
		return _sInstance;
	}

	void Print1()
	{
		cout << "xxx" << endl;
	}
	void Print2()
	{
		cout << "yyy" << endl;
	}
private:
	Singleton()
	{}
	Singleton(const Singleton& s)
	{}
	static Singleton* _sInstance;
};

Singleton* Singleton::_sInstance = NULL;
int main()
{
	//Test();
	//Test1();
	
	//Test2();
	Test3();

	//PtrList.Print();
	//atexit(&List<MemoryBlockInfo>::Print);

	return 0;
}