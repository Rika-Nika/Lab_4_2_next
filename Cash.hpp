#pragma once

#include "HashTable.hpp"
#include "PriorityQueue.hpp"


int DEFAULT_SIZE = 16;

template<typename T>
class LRUCache {
public:
    LRUCache(int capacity = DEFAULT_SIZE /* = 16 */);
    ~LRUCache();
    bool ContainsKey(T key);
    void Add(T key);
    T Get(T key);

    friend std::ostream& operator<< (std::ostream& out, LRUCache<T>& cache) {
        out << (*cache.table);
        return out;
    };

private:
    int startCount;
    PriorityQueue<T> priorityQueue;
    HashTable<T>* table;
    int _capacity;
};


template<typename T>
LRUCache<T>::LRUCache(int capacity) :_capacity(capacity), startCount(0), priorityQueue() {
    table = new HashTable<T>();

}


template<typename T>
LRUCache<T>::~LRUCache<T>() {
    priorityQueue.Clear();
    delete table;
}


template<typename T>
bool LRUCache<T>::ContainsKey(T key) {
    auto item =  table->Find(key);
    return !item.IsNull();
}


template<typename T>
void LRUCache<T>::Add(T key) {
	if (table->GetSize() == _capacity) {
        T minKey = priorityQueue.ExtractMinValue();
        table->Remove(minKey);
    }
    try {
        table->Add(key);
        priorityQueue.Add(key, startCount);
    }
    catch (...) {
        if (key != table->Find(key)) {
            table->Remove(key);
            table->Add(key);
        }
        priorityQueue.Set(key, startCount);
    }
    startCount += 1;
}


template<typename T>
T LRUCache<T>::Get(T key) {
    try {
        priorityQueue.Set(key, startCount);
        startCount += 1;
        return table->Find(key);
    }
    catch (...) {
        throw Exception("Key error: your cache isn`t contains this key");
    }
}
