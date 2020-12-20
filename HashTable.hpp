#pragma once
#include <string>

#include "IDictionary.hpp"
#include "Person.hpp"

inline int HashFunctionHorner(const std::string& s, int table_size, const int key)
{
	int hash_result = 0;
	for (int i = 0; i != s.size(); ++i)
		hash_result = (key * hash_result + s[i]) % table_size;
	hash_result = (hash_result * 2 + 1) % table_size;
	return hash_result;
}

inline int HashFunction(const int index, int table_size, const int key)
{
	int hash_result = index;
	hash_result = (hash_result * 2 + 1) % table_size;
	return hash_result;
}

struct HashFunction1
{
	int operator()(const Person& p, int table_size) const
	{
		std::string s = to_string(p.GetIndex());
		return HashFunctionHorner(s, table_size, table_size - 1); // ����� ������ ���� ������������, ���������� ����� <������ �������> ���� � ����� ����.
	}
};

struct HashFunction2
{
	int operator()(const Person& p, int table_size) const
	{
		std::string s = to_string(p.GetIndex());
		return HashFunctionHorner(s, table_size, table_size + 1);
	}
};


template <class T,  class THash1 = HashFunction1, class THash2 = HashFunction2>
class HashTable :public IDictionary<T,T>
{
	static const int default_size = 1000; // ��������� ������ ����� �������
	constexpr static const double rehash_size = 0.75; // �����������, ��� ������� ���������� ���������� �������
	struct Node
	{
		T value;
		bool state; // ���� �������� ����� state = false, ������ ������� ������� ��� ������ (deleted)
		Node(const T& value_) : value(value_), state(true) {}
	};
	Node** arr; // �������������� � ������� ����� �������� ��������� Node*
	int size; // ������� ��������� � ��� ������ � ������� (��� ����� deleted)
	int capacity; // ������ ������ �������, ������� ������ �������� ��� �������� ����� �������
	int size_all_non_nullptr; // ������� ��������� � ��� ������ � ������� (� ������ deleted)

public:

	int GetSize() const;

	HashTable();

	~HashTable();

	void Resize();

	void Rehash();

	T Find(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2());

	T FindLast(int count, const THash1& hash1 = THash1(), const THash2& hash2 = THash2());

	bool Remove(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2());

	bool Add(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2());

	T Get(T key) override;

	bool ContainsKey(T key) override;

	void AddItem(const T key, const T elem)  override;

	void RemoveItem(T key) override;
	int GetCapacity() override;;
};

template <class T, class THash1, class THash2>
int HashTable<T, THash1, THash2>::GetSize() const
{
	return size;
}

template <class T, class THash1, class THash2>
HashTable<T, THash1, THash2>::HashTable()
{
	capacity = default_size;
	size = 0;
	size_all_non_nullptr = 0;
	arr = new Node*[capacity];
	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;
	// ��������� nullptr - �� ���� ���� �������� �����������, � ����� ������ �� ����� ������ �� ���������
}

template <class T, class THash1, class THash2>
HashTable<T, THash1, THash2>::~HashTable()
{
	for (int i = 0; i < capacity; ++i)
		if (arr[i])
			delete arr[i];
	delete[] arr;
}

template <class T, class THash1, class THash2>
void HashTable<T, THash1, THash2>::Resize()
{
	int past_buffer_size = capacity;
	capacity *= 2;
	size_all_non_nullptr = 0;
	size = 0;
	Node** arr2 = new Node*[capacity];
	for (int i = 0; i < capacity; ++i)
		arr2[i] = nullptr;
	std::swap(arr, arr2);
	for (int i = 0; i < past_buffer_size; ++i)
	{
		if (arr2[i] && arr2[i]->state)
			Add(arr2[i]->value); // ��������� �������� � ����� ������
	}
	// �������� ����������� �������
	for (int i = 0; i < past_buffer_size; ++i)
		if (arr2[i])
			delete arr2[i];
	delete[] arr2;
}

template <class T, class THash1, class THash2>
void HashTable<T, THash1, THash2>::Rehash()
{
	size_all_non_nullptr = 0;
	size = 0;
	Node** arr2 = new Node*[capacity];
	for (int i = 0; i < capacity; ++i)
		arr2[i] = nullptr;
	std::swap(arr, arr2);
	for (int i = 0; i < capacity; ++i)
	{
		if (arr2[i] && arr2[i]->state)
			Add(arr2[i]->value);
	}
	// �������� ����������� �������
	for (int i = 0; i < capacity; ++i)
		if (arr2[i])
			delete arr2[i];
	delete[] arr2;
}

template <class T, class THash1, class THash2>
T HashTable<T, THash1, THash2>::Find(const T& value, const THash1& hash1, const THash2& hash2)
{
	int h1 = hash1(value, capacity); // ��������, ���������� �� ��������� �������
	int h2 = hash2(value, capacity); // ��������, ������������� �� "���" �� �������
	int i = 0;
	while (arr[h1] != nullptr && i < capacity)
	{
		if (arr[h1]->value == value && arr[h1]->state)
			return arr[h1]->value; // ����� ������� ����
		h1 = (h1 + h2) % capacity;
		++i;
		// ���� � ��� i >=  buffer_size, ������ �� ��� ������ ��������� ��� ������, ������ ��� ����� �� ������� i, ����� �� ����� �� �����������.
	}
	T person = T();
	return person;
}

template <class T, class THash1, class THash2>
T HashTable<T, THash1, THash2>::FindLast(int count, const THash1& hash1, const THash2& hash2)
{
	T res = T();
	int i = 0;
	int h1 = HashFunction(count, capacity, capacity - 1);
	int h2 = HashFunction(count, capacity, capacity + 1);
	while (arr[h1] != nullptr && i < capacity)
	{
		if (arr[h1]->state)
			res = arr[h1]->value; // ����� ������� ����
		h1 = (h1 + h2) % capacity;
		++i;
		// ���� � ��� i >=  buffer_size, ������ �� ��� ������ ��������� ��� ������, ������ ��� ����� �� ������� i, ����� �� ����� �� �����������.
	}

	return res;
}

template <class T, class THash1, class THash2>
bool HashTable<T, THash1, THash2>::Remove(const T& value, const THash1& hash1, const THash2& hash2)
{
	int h1 = hash1(value, capacity);
	int h2 = hash2(value, capacity);
	int i = 0;
	while (arr[h1] != nullptr && i < capacity)
	{
		if (arr[h1]->value == value && arr[h1]->state)
		{
			arr[h1]->state = false;
			--size;
			return true;
		}
		h1 = (h1 + h2) % capacity;
		++i;
	}
	return false;
}

template <class T, class THash1, class THash2>
bool HashTable<T, THash1, THash2>::Add(const T& value, const THash1& hash1, const THash2& hash2)
{
	if (size + 1 > int(rehash_size * capacity))
		Resize();
	else if (size_all_non_nullptr > 2 * size)
		Rehash(); // ���������� �����, ��� ��� ������� ����� deleted-���������
	int h1 = hash1(value, capacity);
	int h2 = hash2(value, capacity);
	int i = 0;
	int first_deleted = -1; // ���������� ������ ���������� (���������) �������
	while (arr[h1] != nullptr && i < capacity)
	{
		if (arr[h1]->value == value && arr[h1]->state)
			return false; // ����� ������� ��� ����, � ������ ��� ������ ��������� ��������
		if (!arr[h1]->state && first_deleted == -1) // ������� ����� ��� ������ ��������
			first_deleted = h1;
		h1 = (h1 + h2) % capacity;
		++i;
	}
	if (first_deleted == -1) // ���� �� ������� ����������� �����, ������� ����� Node
	{
		arr[h1] = new Node(value);
		++size_all_non_nullptr; // ��� ��� �� ��������� ���� ������, �� �������� ��������, ��� ��� ����� ������ ������
	}
	else
	{
		arr[first_deleted]->value = value;
		arr[first_deleted]->state = true;
	}
	++size; // � � ����� ������ �� ��������� ���������� ���������
	return true;
}

template <class T, class THash1, class THash2>
T HashTable<T, THash1, THash2>::Get(T key) {
	return Find(key);
}

template <class T, class THash1, class THash2>
bool HashTable<T, THash1, THash2>::ContainsKey(T key) 
{
	return !Find(key).IsNull();
}

template <class T, class THash1, class THash2>
void HashTable<T, THash1, THash2>::AddItem(const T key, const T elem) 
{
	HashTable::Add(key);
}

template <class T, class THash1, class THash2>
void HashTable<T, THash1, THash2>::RemoveItem(T key)
{
	HashTable::Remove(key);
}

template <class T, class THash1, class THash2>
int HashTable<T, THash1, THash2>::GetCapacity()
{
	return capacity;
}
