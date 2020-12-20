#pragma once
template <class T>
class QueueSequence
{
public:
    virtual void Enqueue(T value) const = 0;
    virtual T Dequeue() const = 0;
    virtual T Peek(const int index = 0) const = 0;
    virtual int GetSize() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual void Print() const = 0;
public:
    virtual ~QueueSequence() {}
};

