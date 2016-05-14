#include"MemoryManager.h"

MemoryManager* MemoryManager::_sInstance = NULL;

MemoryBlockInfo::MemoryBlockInfo(void* ptr = NULL, const char* filename = "", int line = 0)
	:_ptr(ptr)
	, _filename(filename)
	, _line(line)
{}

bool MemoryBlockInfo:: operator==(const MemoryBlockInfo& x)
{
	return _ptr == x._ptr;
}

ostream& operator<<(ostream& os, const MemoryBlockInfo& info)
{
os << "Prt->" << info._ptr << endl;
os << "Filename:" << info._filename << endl;
os << "Line:" << info._line << endl;
return os;
}

MemoryManager* MemoryManager:: GetInstance()
{
	if (_sInstance == NULL)
	{
		_sInstance = new MemoryManager();
	}
	return _sInstance;
}

void* MemoryManager::Alloc(size_t size, const char* filename, int line)
{
	//申请内存
	void* ptr = malloc(size);
	//记录内存块信息
	if (ptr)
	{
		_infos.PushBack(MemoryBlockInfo(ptr, filename, line));
	}
	return ptr;
}

void MemoryManager::Dealloc(void* ptr)
{
	if (ptr)
	{
		Node<MemoryBlockInfo>* ret = _infos.Find(MemoryBlockInfo(ptr));
		_infos.Erase(ret);
	}
	return free(ptr);
}
void MemoryManager:: Print()	//属于类域里面的
{
	MemoryManager::GetInstance()->_Print();
}

MemoryManager::MemoryManager()
{
	//atexit(Print);
	atexit(SaveResult);
}
void MemoryManager::_Print()
{
	_infos.Print();
}
