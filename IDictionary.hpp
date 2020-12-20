#pragma once

template<typename TKey, typename TElement>
class IDictionary {
public:
	virtual int GetSize() const = 0;
	virtual int GetCapacity() = 0;
	virtual TElement Get(TKey key) = 0;
	virtual bool ContainsKey(TKey key) = 0;
	virtual void AddItem(const TKey key, const TElement elem) = 0;
	virtual void RemoveItem(TKey key) = 0;
	~IDictionary() = default;
};