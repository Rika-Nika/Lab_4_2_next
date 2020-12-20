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
		return HashFunctionHorner(s, table_size, table_size - 1); // ключи должны быть взаимопросты, используем числа <размер таблицы> плюс и минус один.
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
	static const int default_size = 1000; // начальный размер нашей таблицы
	constexpr static const double rehash_size = 0.75; // коэффициент, при котором произойдет увеличение таблицы
	struct Node
	{
		T value;
		bool state; // если значение флага state = false, значит элемент массива был удален (deleted)
		Node(const T& value_) : value(value_), state(true) {}
	};
	Node** arr; // соответственно в массиве будут хранится структуры Node*
	int size; // сколько элементов у нас сейчас в массиве (без учета deleted)
	int capacity; // размер самого массива, сколько памяти выделено под хранение нашей таблицы
	int size_all_non_nullptr; // сколько элементов у нас сейчас в массиве (с учетом deleted)

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
	// заполняем nullptr - то есть если значение отсутствует, и никто раньше по этому адресу не обращался
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
			Add(arr2[i]->value); // добавляем элементы в новый массив
	}
	// удаление предыдущего массива
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
	// удаление предыдущего массива
	for (int i = 0; i < capacity; ++i)
		if (arr2[i])
			delete arr2[i];
	delete[] arr2;
}

template <class T, class THash1, class THash2>
T HashTable<T, THash1, THash2>::Find(const T& value, const THash1& hash1, const THash2& hash2)
{
	int h1 = hash1(value, capacity); // значение, отвечающее за начальную позицию
	int h2 = hash2(value, capacity); // значение, ответственное за "шаг" по таблице
	int i = 0;
	while (arr[h1] != nullptr && i < capacity)
	{
		if (arr[h1]->value == value && arr[h1]->state)
			return arr[h1]->value; // такой элемент есть
		h1 = (h1 + h2) % capacity;
		++i;
		// если у нас i >=  buffer_size, значит мы уже обошли абсолютно все ячейки, именно для этого мы считаем i, иначе мы могли бы зациклиться.
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
			res = arr[h1]->value; // такой элемент есть
		h1 = (h1 + h2) % capacity;
		++i;
		// если у нас i >=  buffer_size, значит мы уже обошли абсолютно все ячейки, именно для этого мы считаем i, иначе мы могли бы зациклиться.
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
		Rehash(); // происходит рехеш, так как слишком много deleted-элементов
	int h1 = hash1(value, capacity);
	int h2 = hash2(value, capacity);
	int i = 0;
	int first_deleted = -1; // запоминаем первый подходящий (удаленный) элемент
	while (arr[h1] != nullptr && i < capacity)
	{
		if (arr[h1]->value == value && arr[h1]->state)
			return false; // такой элемент уже есть, а значит его нельзя вставлять повторно
		if (!arr[h1]->state && first_deleted == -1) // находим место для нового элемента
			first_deleted = h1;
		h1 = (h1 + h2) % capacity;
		++i;
	}
	if (first_deleted == -1) // если не нашлось подходящего места, создаем новый Node
	{
		arr[h1] = new Node(value);
		++size_all_non_nullptr; // так как мы заполнили один пробел, не забываем записать, что это место теперь занято
	}
	else
	{
		arr[first_deleted]->value = value;
		arr[first_deleted]->state = true;
	}
	++size; // и в любом случае мы увеличили количество элементов
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
