#pragma once
template <class T>
class Sequence
{
public:
	virtual int GetLength() const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(const int i) const = 0;
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const = 0;
	virtual std::string PrintOut() const = 0;
	virtual bool Equals(const Sequence<T>* sequence) const = 0;
public:
	virtual void Append(T value) = 0;
	virtual void Prepend(T value) = 0;
	virtual void InsertAt(const int index, T value) = 0;
	virtual void RemoveAt(const int index) = 0;
	virtual void Remove(T value) = 0; // Удаляет первое вхождение value
	virtual void RemoveAll()  = 0;
	virtual Sequence<T>* Concat(Sequence<T>* other) = 0;
	virtual void swap(int, int) = 0;

public:
	virtual ~Sequence(){}
};
