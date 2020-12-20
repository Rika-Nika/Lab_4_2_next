#pragma once
#include "Sequence.hpp"
#include <iostream>
#include <chrono>


template  <typename T>
class ISorter
{
	//public:
	//	virtual Sequence
	//
	//	<T>* sortQuick(Sequence<T>* seq, int (*cmp)(T, T)) = 0;
	//	virtual Sequence<T>* sortPyramid(Sequence<T>* seq, int (*cmp)(T, T)) = 0;
	//	virtual Sequence<T>* ShellSort(Sequence<T>* seq, int (*cmp)(T, T)) = 0;
	//	virtual int comp(int a, int b) = 0;
	//	virtual int comp(double a, double b) = 0;
	//
	//	virtual ~ISorter() {};
protected:
	int (*cmp)(T, T);
	unsigned int timeOfIteration{};
	unsigned int countOfIter{};
public:
	unsigned int getCountOfIter();

	unsigned int getTimeOfIterationSeconds();

	void reset();

	virtual Sequence<T>* 
		sort(Sequence<T>*, int (*cmp)(T, T)) = 0;
protected:
	void Swap(Sequence<T>* seq, int index1, int index2)
	{
		T item = seq->Get(index1);
		seq->Get(index1) = seq->Get(index2);
		seq->Get(index2) = item;
	}
};

template<typename T>
unsigned int ISorter<T>::getTimeOfIterationSeconds() {
	return this->timeOfIteration;
}

template<typename T>
void ISorter<T>::reset() {
	this->countOfIter = 0;
	this->timeOfIteration = 0;
}

template<typename T>
unsigned int ISorter<T>::getCountOfIter() {
	return this->countOfIter;
}



template <typename T>
class ShellSorter : public ISorter<T>
{

public:
	ShellSorter();
	~ShellSorter();
	Sequence<T>* sort(Sequence<T>*, int (*cmp)(T, T)) override ;
};
template<typename T>
ShellSorter<T>::ShellSorter()=default;

template<typename T>
ShellSorter<T>::~ShellSorter() = default;

template<typename T>
Sequence<T>* ShellSorter<T>::sort(Sequence<T> * seq, int (*cmp)(T, T)) {
	this->reset();
	int step, i, j;
	//Option<T> el{};
	auto startTime = std::chrono::system_clock::now();
	// Выбор шага
	for (step = seq->GetLength() / 2; step > 0; step /= 2) {
		++this->countOfIter;
		// Перечисление элементов, которые сортируются на определённом шаге
		for (i = step; i < seq->GetLength(); i++) {
			// Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
			for (j = i - step; j >= 0 && cmp(seq->Get(j), seq->Get(j + step)) == 1; j -= step) {
				seq->swap(j, j + step);
			}
		}
	}
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> elapsedMilliseconds = endTime - startTime;
	this->timeOfIteration = elapsedMilliseconds.count();
	return seq;
}

template<typename T>
void heapify(Sequence<T>* arr, int n, int i, int (*cmp)(T, T)) {
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2

	// Если левый дочерний элемент больше корня
	if (l < n && cmp(arr->Get(l), arr->Get(largest)) == 1) {
		largest = l;
	}

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент

	if (r < n && cmp(arr->Get(r), arr->Get(largest)) == 1) {
		largest = r;
	}

	// Если самый большой элемент не корень
	if (largest != i) {
		arr->swap(i, largest);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(arr, n, largest, cmp);
	}
}


template<typename T>
class HeapSorter : public ISorter<T> {
public:
	HeapSorter();

	~HeapSorter();

	Sequence<T>* sort(Sequence<T>*, int (*cmp)(T, T)) override;
};

template<typename T>
Sequence<T>* HeapSorter<T>::sort(Sequence<T>* seq, int (*cmp)(T, T)) {
	auto startTime = std::chrono::system_clock::now();
	for (int i = seq->GetLength() / 2 - 1; i >= 0; i--)
		heapify<T>(seq, seq->GetLength(), i, cmp);

	// Один за другим извлекаем элементы из кучи
	for (int i = seq->GetLength() - 1; i >= 0; i--) {
		// Перемещаем текущий корень в конец
		seq->swap(0, i);

		// вызываем процедуру heapify на уменьшенной куче
		heapify<T>(seq, i, 0, cmp);
	}
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> elapsedMilliseconds = endTime - startTime;
	this->timeOfIteration = elapsedMilliseconds.count();
	return seq;
}


template<typename T>
HeapSorter<T>::~HeapSorter() = default;

template<typename T>
HeapSorter<T>::HeapSorter() = default;


