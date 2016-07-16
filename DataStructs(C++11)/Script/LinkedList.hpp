#pragma once
#include <ostream>
#include <assert.h>
#include <iosfwd>
#include <iostream>
#include <functional>

template <class T>
class LinkedListNode {
public:
	LinkedListNode(const T& value, LinkedListNode *next = nullptr, LinkedListNode *prev = nullptr) :info(value), next(next), prev(prev) {
	}
	 T info;
	LinkedListNode<T> *next, *prev;

};
template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	int isEmpty() const;

	int Count() const { return count; }
	void AddToHead(const T&);
	void AddToLast(const T&);
	void DeleteFromHead();
	void DeleteFromTail();
	T& GetFromHead() const;
	T& GetFromLast() const;
	void ForEach(std::function<void( T&)>  op) ;

	friend std::ostream& operator<<(std::ostream& out,  LinkedList<T>& list) {
		return list.writeLegibly(out);
	}
private:
	int count;
	LinkedListNode<T> *tail, *head;
	std::ostream& writeLegibly(std::ostream& out) ;
	
};

template <class T>
std::ostream& LinkedList<T>::writeLegibly(std::ostream& out) 
{
	
	auto func =[&out](T& info){
		out<< info<<" ";
	};
	ForEach(func);
	
	return out;
}

template <class T>
LinkedList<T>::LinkedList()
{
	count = 0;
	tail = head = nullptr;
}
template <class T>
LinkedList<T>::~LinkedList()
{
	if(!isEmpty())
	{
		auto tmp = head;
		while(tmp!=nullptr)
		{
			auto tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		head = tail = nullptr;
	}
}

template <class T>
int LinkedList<T>::isEmpty() const
{
	return Count()==0;
}

template<class T>
inline void LinkedList<T>::AddToHead(const T & value)
{
	count++;
	if(head==nullptr)
	{
		head = tail = new  LinkedListNode<T>(value);
	}
	else
	{
		auto tmp = head;
		this->head = new  LinkedListNode<T>(value,tmp);
		tmp->prev = head;

	}
}

template <class T>
void LinkedList<T>::AddToLast(const T& value)
{
	count++;
	if (head == nullptr)
	{
		
		head = tail = new  LinkedListNode<T>(value);
	}
	else
	{
	
		auto tmp = tail;
		this->tail = new  LinkedListNode<T>(value,nullptr,tmp);
		tmp->next = tail;

	}
}

template <class T>
void LinkedList<T>::DeleteFromHead()
{
	if(head==nullptr)
	{
		return;
	}
	else if(Count()==1)
	{
		count--;
		delete head;
		head = this->tail = nullptr;
	}else
	{
		count--;
		auto tmp = this->head->next;
		delete head;
		head = tmp;
	}
}

template <class T>
void LinkedList<T>::DeleteFromTail()
{
	if (head == nullptr)
	{
		return;
	}
	else if (Count() == 1)
	{
		count--;
		delete head;
		head = this->tail = nullptr;
	}
	else
	{
		count--;
		auto tmp = this->tail->prev;
		delete tail;
		tail = tmp;
	}
}

template <class T>
T& LinkedList<T>::GetFromHead() const
{
	if (isEmpty())
		assert("try to get a element from a empty list");
	else
	{
		return this->head->info;
	}
	
}

template <class T>
T& LinkedList<T>::GetFromLast() const
{
	if (isEmpty())
		assert("try to get a element from a empty list");
	else
	{
		return this->tail->info;
	}
	
}

template <class T>
void LinkedList<T>::ForEach( std::function<void( T&)>  op) 
{
	auto tmp = head;
	while(tmp!=nullptr)
	{
		op(tmp->info);
		tmp = tmp->next; 
	}
}
