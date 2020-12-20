#pragma once
template<typename T>
class IPriorityQueue {
public:
	virtual void Set(T elem, int priority) = 0;
	virtual void Add(T elem, int priority) = 0;
	virtual void Clear() = 0;
	virtual T ExtractMinValue() = 0;
	virtual int GetSize() = 0;
	~IPriorityQueue() = default;
};