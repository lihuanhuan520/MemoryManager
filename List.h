#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

class MemoryManager;
template <class T> 
class Node
{
	template<class T>
	friend class List;
	friend class MemoryManager;
public:
	Node(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
private:
	T _data;
	Node<T>* _prev;
	Node<T>* _next;

};

template<class T>
class List
{
	friend class MemoryManager;
public:
	List()
		:_head(NULL)
		, _tail(NULL)
	{}
	~List()
	{
		Node<T>* begin = _head;
		while (begin != NULL)
		{
			Node<T>* del = begin;
			begin = begin->_next;
			delete del; 
		}
		_head = NULL;
		_tail = NULL;
	}

	void PushBack(const T& x)
	{
		//1.没有节点
		//2.有节点
		if (_head == NULL)
		{
			_head = new Node<T>(x);
			_tail = _head;
		}
		else
		{
			Node<T>* tmp = new Node<T>(x);
			_tail->_next = tmp;
			tmp->_prev = _tail;
			_tail = _tail->_next;
		}
	}

	Node<T>* Find(const T& x)
	{
		Node<T>* begin = _head;
		while (begin)
		{
			if (begin->_data == x)
			{
				return begin;
			}
			begin = begin->_next;
		}
		return NULL;
	}

	void Erase(Node<T>* n)
	{
		assert(n);
		//1.空链表
		//2.一个节点
		//3.多个节点
		if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail && _head == n)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			Node<T>* del = n;			
			if (_head == n)
			{
				_head = _head->_next;
				_head->_prev = NULL;
			}
			else if (_tail == n)
			{
				_tail = _tail->_prev;
				_tail->_next = NULL;
			}
			else
			{
				Node<T>* prev = n->_prev;
				Node<T>* next = n->_next;
				prev->_next = next;
				next->_prev = prev;
			}
			delete del;
		}
	}
	void Print()
	{
		//cout << "List->";
		if (_head == NULL)
		{
			cout << "NULL" << endl;
		}
		else
		{
			Node<T>* begin = _head;
			while (begin)
			{
				cout << begin->_data;
				begin = begin->_next;
			}
			//cout << "NULL" << endl;
		}
	}
private:
	Node<T>* _head;
	Node<T>* _tail;

};