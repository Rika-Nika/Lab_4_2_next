#pragma once
#include "Exception.h"
#include "IPriorityQueue.h"

template<typename T>
struct PriorityQueueNode {
    PriorityQueueNode(T data_, int priority_) : data(data_), priority(priority_) {
        next = nullptr;
    }
    PriorityQueueNode* next;
    T data;
    int priority;
};


template<typename T>
class PriorityQueue : public IPriorityQueue<T>
{
public:
    PriorityQueue();
    void Set(T elem, int priority);
    void Add(T elem, int priority);
    void Clear();
    T ExtractMinValue();
    int GetSize();
    ~PriorityQueue();
private:
    PriorityQueueNode<T>* head;
    PriorityQueueNode<T>* tail;
};


template<typename T>
PriorityQueue<T>::PriorityQueue() {
    head = nullptr;
    tail = nullptr;
}


template<typename T>
void PriorityQueue<T>::Clear() {
    if (head) {
        PriorityQueueNode<T>* tmp;
        while (head) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
}


template<typename T>
PriorityQueue<T>::~PriorityQueue<T>() {
    Clear();
}


template<typename T>
void PriorityQueue<T>::Add(T elem, int priority) {
    if (tail) {
        tail->next = new PriorityQueueNode<T>(elem, priority);
        tail = tail->next;
        tail->next = nullptr;
    }
    else {
        head = new PriorityQueueNode<T>(elem, priority);
        tail = head;
    }
}


template<typename T>
void PriorityQueue<T>::Set(T elem, int priority) {
    if (head) {
        PriorityQueueNode<T>* tmp = head;
        PriorityQueueNode<T>* tmpPrev = nullptr;
        while (tmp->data != elem) {
            tmpPrev = tmp;
            if (tmp->next) {
            	
                tmp = tmp->next;
            }
            else {
                throw Exception("Wrong key in PriorityQueue");
            }
        }
        if (tmpPrev->next && tmp->next) {
            tmpPrev->next = tmp->next;
        }
        tmp->priority = priority;
        tail->next = tmp;
        tail=tail->next;
    }
    else {
        throw Exception("PriorityQueue is free");
    }
}


template<typename T>
T PriorityQueue<T>::ExtractMinValue() {
    if (head) {
        T minElem = head->data;
        PriorityQueueNode<T>* tmp = head;
        head = head->next;
        delete tmp;
        return minElem;
    }
    else {
        throw Exception("Your TimeQueue is free");
    }
}


template<typename T>
int PriorityQueue<T>::GetSize() {
    int size = 0;
    if (head) {
        PriorityQueueNode<T>* tmp = head;
        while (tmp) {
            size += 1;
            tmp = tmp->next;
        }
    }
    return size;
}
