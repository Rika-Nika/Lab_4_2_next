#include "Sequence.hpp"
#include "DynamicArray.hpp"
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include "LinkedList.hpp"
#include "QueueSequence.hpp"
#include"Exception.h"
#pragma once

template <class T>
class QueueLinkedList :public QueueSequence<T>
{
private:
	Sequence<T>* items;
public:
	QueueLinkedList() {
		this->items = new LinkedListSequence<T>();
	};
	QueueLinkedList(const T* items, const int count) {
		{
			this->items = new LinkedListSequence<T>();
			for (int i = 0; i < count; i++)
				this->items->Prepend(*(items + i));
		}

	};
	QueueLinkedList(Sequence<T>* items)
	{
		this->items = items->GetSubsequence(0,items->GetLength()-1);
		/*for (int i = 0; i < items->GetLength(); i++)
			this->items->Prepend(items->Get(i));*/
	}
public:
	int GetSize() const override
	{
		return this->items->GetLength();
	}
	bool IsEmpty() const override
	{
		return this->items->GetLength() == 0;
	}
	T Peek(const int index = 0) const override
	{
		if (index < 0 || index >= this->items->GetLength())
			throw Exception("IndexOutOfRange");
		return items->Get(index);
	}

	void Enqueue(T value) const override
	{
		this->items->Prepend(value);
	}

	T Dequeue()const override
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
public:
	virtual ~QueueLinkedList() {}
};