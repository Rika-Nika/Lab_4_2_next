#pragma once
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "ArraySequence.hpp"
#include "Cash.hpp"
#include "HashTable.hpp"
#include "Person.hpp"

enum class SizeSeq {
	SMALL = 1000,
	MEDIUM = 5000,
	LARGE = 15000
};
enum class SizeCash {
	SMALL = 10,
	MEDIUM = 100,
	LARGE = 1000
};

enum class Alg {
	Alg1,
	Alg2
};

//int integerCompare(int a, int b) {
//    if (a > b) {
//        return 1;
//    }
//    else if (a < b) {
//        return 0;
//    }
//    else {
//        return 2;
//    }
//}



bool chckValue(const int* arr, int size, int x) {
	bool res = false;
	for (int i = 0; i < size; ++i) {
		if (arr[i] == x) {
			res = true;
		}
	}
	return res;
}

int* getRandomNumbers(int min, int max) {
	static const auto fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	auto* values = new int[max - min];
	auto size = 0;
	for (auto i = min; i < max; ++i) {
		const auto value = static_cast<int>(rand() * fraction * (max - min + 1) + min);
		if (!chckValue(values, size, value)) {
			values[i] = value;
			size++;
		}
		else {
			i--;
		}
	}
	return values;
}

ArraySequence<int>* getFromFile(const char* path) {

	ArraySequence<int>* res = new ArraySequence<int>();

	int* values = nullptr;
	const char* pathPref = "c:\\tmp\\";
	std::stringstream ss;
	ss << pathPref << path;
	std::ifstream file(ss.str(), std::ios_base::in);

	int a;
	while (file >> a)
	{
		res->Append(a);
	}
	return res;
}

Person loadFromFile(boost::uuids::uuid index)
{
	unsigned int microseconds = 10;
	// boost::interprocess::winapi::sleep(microseconds);
	auto  fileName = "c:\\tmp\\laba4_2\\" + to_string(index) + ".txt";
	// std::ofstream ofs(fileName);

	Person restoredPerson = Person();
	{
		try {
			// create and open an archive for input
			std::ifstream ifs(fileName);


			boost::archive::text_iarchive ia(ifs);

			// read class state from archive
			ia >> restoredPerson;
			// archive and stream closed when destructors are called
		}
		catch (const boost::archive::archive_exception& e)
		{
			std::cerr << e.what();
		}
	}
	restoredPerson.SetIndex(index);
	restoredPerson.SetIsNull();
	return restoredPerson;
}

void saveToFile(Person person)
{
	std::string fileName = "c:\\tmp\\laba4_2\\" + to_string(person.GetIndex()) + ".txt";

	std::ofstream ofs(fileName);

	{
		boost::archive::text_oarchive oa(ofs);
		// write class instance to archive
		oa << person;
		// archive and stream closed when destructors are called

	}
}

template<typename T>
Person getFromHashTable(boost::uuids::uuid index, HashTable<T>* hash)
{
	T item = T(index);
	auto res = hash->Find(item);
	if (hash->ContainsKey(item))
	{
		res = loadFromFile(index);
		hash->Add(res);
	}
	return res;
}

template<typename T>
T getFromCache(boost::uuids::uuid index, LRUCache<T>* cache) {
	T item = T(index);
	if (cache->ContainsKey(item)) {
		return cache->Get(item);
	}
	T res = loadFromFile(index);
	cache->Add(res);
	return res;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}