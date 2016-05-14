#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdarg.h>
#include"List.h"

using namespace std;

class SaveAdapter
{
public:
	virtual void Save(const char* format, ...) = 0;
};

//����̨����������
class ConsoleSaveAdapter : public SaveAdapter
{
public:
	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(stdout, format, args);
		va_end(args);
	}
};

//�ļ�����������
class FileSaveAdapter : public SaveAdapter
{
public:
	FILE* _fout;
	FileSaveAdapter(const char* filename = "MemoryManagerReport.txt")
	{
		_fout = fopen(filename, "w");
	}
	virtual void Save(const char* format,...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(_fout, format, args);
		va_end(args);
	}
};

struct MemoryBlockInfo
{
	void* _ptr;
	string _filename;
	int _line;
	MemoryBlockInfo(void* ptr, const char* filename , int line);
	bool operator==(const MemoryBlockInfo& x);
	friend ostream& operator<<(ostream& os, const MemoryBlockInfo& info);
};

class MemoryManager
{
public:
	static MemoryManager* GetInstance();
	void* Alloc(size_t size, const char* filename, int line);
	void Dealloc(void* ptr);

	static void SaveResult()
	{
		MemoryManager::GetInstance()->_SaveResult(ConsoleSaveAdapter());
		MemoryManager::GetInstance()->_SaveResult(FileSaveAdapter());

	}

	void _SaveResult(SaveAdapter& sa)
	{
		Node<MemoryBlockInfo>* begin = _infos._head;
		while (begin)
		{
			//cout << begin->_data;
			sa.Save("Ptr: %p \n Filename: %s\n Line: %d\n", begin->_data._ptr
				,begin->_data._filename.c_str()
				,begin->_data._line);

			begin = begin->_next;
		}
	}
	static void Print();	//�������������
protected:
	MemoryManager();
	void _Print();
protected:
	static MemoryManager* _sInstance;
	List<MemoryBlockInfo> _infos;  //�洢�ڴ����Ϣ������
};


//��
//���캯��? // new/delete(�Զ�������)
//����   //new[] /delete[]

//Alloc(sizeof(type), __FILE__, __LINE__);
template<class T>
inline T* __NEW(size_t size,const char* filename,int line)
{
	return new(MemoryManager::GetInstance()->Alloc(sizeof(T),filename, line))T;
}

template<class T>
inline void __DELETE(T* ptr)
{
	ptr->~T();
	MemoryManager::GetInstance()->Dealloc(ptr);
}

template<class T>
inline T* __NEW_ARRAY(size_t num, const char* filename, int line)
{
	//���캯��
	T* ptr = (T*)MemoryManager::GetInstance()->Alloc(sizeof(T)*num + 4, filename, line);
	*(int*)ptr = num;
	T* selfPtr = (T*)((char*)ptr + 4);
	for (int i = 0; i < num; i++)
	{
		new(selfPtr + i)T;
	}
	return selfPtr;
}

template<class T>
inline void __DELETE_ARRAY(T* ptr)
{
	//��������
	T* selfPtr = (T*)((char*)ptr - 4);
	size_t  num = *(int*)selfPtr;
	for (int i = 0; i < num; i++)
	{
		ptr[i].~T();
	}
	MemoryManager::GetInstance()->Dealloc(selfPtr);
}

//������������꺯���ô��ǿ��Խ��е���

//�����ڴ����
#define NEW(type) \
	__NEW<type>(sizeof(type),__FILE__, __LINE__)
#define DELETE(ptr) \
	__DELETE(ptr)

//�����ڴ��������
#define NEW_ARRAY(type,num) \
	__NEW_ARRAY<type>(num,__FILE__,__LINE__)
#define DELETE_ARRAY(ptr) \
	__DELETE_ARRAY(ptr)