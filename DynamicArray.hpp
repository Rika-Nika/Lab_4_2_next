#pragma once
#include"Exception.h"
#include "Person.hpp"
#include "PersonForIndex.hpp"

template <class T>
class DynamicArray
{
private:
	T* items;
	bool * isSet;
	int size;
public:
	//Копировать элементы из 	переданного массива
	DynamicArray(T* items, int count) {
		this -> items = new T[count];
		this -> size = count;
		this->isSet = new bool[size];
		if (count < 0) {
			throw Exception("Index out of range");
		}

		for (int i = 0; i < count; i++)
		{
			//if (nullptr == *(items + i)) {
				//throw Exception("Index out of range");
		//	}
			this->Set(i, *(items + i));
			
		}

	};
	~DynamicArray() {
		delete items;
	}
	
	//Создать массив заданной длины
	DynamicArray(const int size)
	{
		if (size < 1) {
			throw Exception("Invalid index");
		}
		
		this->items = new T[size];
		this->isSet = new bool[size];
		this->size = size;
	}
	//Копирующий конструктор
	DynamicArray(const DynamicArray<T>& array, int size) {
		
		this->items = new T[size];
		this->isSet = new bool[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{
				this->Set(i, array.Get(i));
		}

	};

	//Получить элемент по индексу
	//Может выбрасывать исключения : − IndexOutOfRange(если индекс отрицательный, больше или равен числу 
	//элементов или указывает на не заданный элемент)
	T Get(const int index) const
	{
		if (index < 0 || index >= this->size)
			throw Exception("IndexOutOfRange");
		return this->items[index];
	}

	void Set(const int index, T value) const
	{
		if (index < 0 || index >= this->size)
			throw Exception("IndexOutOfRange");

		this->items[index]=value;
		this->isSet[index] = true;
	}

	//Задать элемент по индексу
	//Может выбросить IndexOutOfRange
	void Set(const int index, const T value)
	{
		if (index < 0 || index >= this->size)
			throw Exception("IndexOutOfRange");
		this->items[index] = value;
		this->isSet[index] = true;
	}
	//Получить размер массива
	int GetSize() const {
		return this->size;
	}

	//Изменить размер массива. 
	//Если размер увеличивается, все элементы копируются в начало новой памяти.
	//Если уменьшается: элементы, которые не помещаются, отбрасываются.
	void Resize(int newSize) {
		if (newSize < 0 )
			throw Exception("Invalid new Size");
		int oldSize = this->size;
		int size = this->size < newSize ? this->size : newSize;
		T* array = this->items;
		this->items = new T[newSize];
		this->size = newSize;
		//memccpy
		for (int i = 0; i < newSize; i++)
		{
			if (i >= oldSize) {
				this->Set(i, Empty(*(array + i)));
			}
			else {
				this->Set(i, *(array + i));
			}
		}
	};
	//Печать всех элемнтов 
	void PrintArray() {
		int size = this->GetSize();
		for (int i = 0; i < size; i++)
		{
			PrintItems(i, this->Get(i));
		}
	}
	

	std::string PrintArrayOut(int count) {
		std::ostringstream oss;
		if (count > this->GetSize()) {
			throw Exception("IndexOutOfRange");
		}
		for (int i = 0; i < count; i++)
		{
			//oss << this->Get(i) << "\r\n";
		}
		return oss.str();
	}

	bool Equals(const DynamicArray<T>& array) {
		if (this == &array) return true;
		if (this->GetSize() != array.GetSize()) return false;

		for (int i = 0; i < (this->GetSize()); i++) {
			if (!this->EqualsItems(this->Get(i), array.Get(i))) {
				return false;
			}
		}
		return true;
	}

	bool Equals(const DynamicArray<T>& array, int count) {
		if (this == &array) return true;
		if (this->GetSize() < count or array.GetSize()<count) return false;
		for (int i = 0; i < count; i++) {
			if (!this->EqualsItems(this->Get(i), array.Get(i))) {
				return false;
			}
		}
		return true;
	}

	T& operator[] (int index) {
		return *this.Get(index);
	};

	void PrintItems(int i, int value) {
		std::printf("A[%d] - %d\n", i, value);
	}
	void PrintItems(int i, double value) {
		std::printf("A[%d] - %f\n", i, value);
	}
	void PrintItems(int i, std::string value) {
		std::printf("A[%d] - %s\n", i, value);
	}
	bool EqualsItems(int value1, int value2) {
		return value1 == value2;
	}
	bool EqualsItems(double value1, double value2) {
		return value1 == value2;
	}

	bool EqualsItems(std::string value1, std::string value2) {
		return value1 == value2;
	}

	bool EqualsItems(Person value1, Person value2) {
		return value1.GetIndex() == value2.GetIndex();
	}

	bool EqualsItems(PersonForIndex value1, PersonForIndex value2) {
		return value1.GetIndex() == value2.GetIndex();
	}

	int Empty(int item ) {
		return 0;
	}
	double Empty(double item) {
		return 0.0L;
	}
	std::string Empty(std::string item) {
		return "";
	}
};
