#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
//#include "Queue.hpp"
#include"Exception.h"

template <class T>
class Queue
{
private:
	Sequence<T>* items;
public:
	Queue() {
		this->items = new ArraySequence<T>();
	};
	Queue(const T* items, const int count) {
		{
			this->items = new ArraySequence<T>();
			for (int i = 0; i < count; i++)
				this->items->Prepend(*(items + i));
		}

	};
	Queue(Sequence<T>* items)
	{
		this->items = items->GetSubsequence(0, items->GetLength() - 1);
		/*for (int i = 0; i < items->GetLength(); i++)
			this->items->Prepend(items->Get(i));*/
	}
public:
	int GetSize() 
	{
		return this->items->GetLength();
	}
	bool IsEmpty()  
	{
		return this->items->GetLength() == 0;
	}
	T Peek(const int index = 0)  
	{
		if (index < 0 || index > this->items->GetLength())
			throw Exception("IndexOutOfRange");
		return items->Get(index);
	}

	void Enqueue(T value)  
	{
		this->items->Prepend(value);
	}

	T Dequeue() 
	{
		if (this->GetSize() == 0) {
			throw Exception("IndexOutOfRange No Volue in Queue");
		}
		T res = this->items->GetFirst();
		this->items->RemoveAt(0);
		return res;
	}
	void Print() const {
		this->items->Print();
	}
	/*public:
		virtual ~QueueLinkedList() {}*/
};


