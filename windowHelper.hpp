#pragma once

#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp> 
#include <boost/uuid/uuid.hpp>  
#include "framework.h"
#include "Util.hpp"
#include "ArraySequence.hpp"
#include "Cash.hpp"
#include "HashTable.hpp"
#include "HashTableExt.hpp"
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "PersonForIndex.hpp"
#include <boost/algorithm/string.hpp>

bool isValidTestAsc(Sequence<int>* seq)
{
	for (int i = 0; i < seq->GetLength() - 1; ++i)
	{
		if (seq->Get(i) > seq->Get(i + 1))
			return false;
	}
	return true;
}
bool isValidTestDsc(Sequence<int>* seq)
{
	for (int i = 0; i < seq->GetLength() - 1; ++i)
	{
		if (seq->Get(i) < seq->Get(i + 1))
			return false;
	}
	return true;
}


// Функция преобразования числа в строку
char* IntToStr(int n)
{
	char s[40], t, * temp;
	int i, k;
	int sign = 0;
	i = 0;
	k = n;
	if (k < 0)
	{
		sign = 1;
		k = -k;
	}
	do
	{
		t = k % 10;
		k = k / 10;
		s[i] = t | 0x30;
		i++;
	} while (k > 0);
	if (sign == 1)
	{
		s[i] = '-';
		i++;
	}
	temp = new char[i];
	k = 0;
	i--;
	while (i >= 0)
	{
		temp[k] = s[i];
		i--;
		k++;
	}
	temp[k] = '\0';
	return (temp);
}

ArraySequence<int>* getSeq(HWND hWnd, SizeSeq sizeSeq, bool gen, const char* path)
{
	ArraySequence<int>* res;
	int size = static_cast<int>(sizeSeq);
	int* testArr;
	std::string out;
	std::ostringstream oss;;
	if (gen)
	{
		testArr = getRandomNumbers(0, size);
		res = new ArraySequence<int>(testArr, size);

		for (int i = 0; i < size; i++)
		{
			oss << testArr[i] << "\r\n";
		}
	}
	else
	{
		res = getFromFile(path);
		for (int i = 0; i < res->GetLength(); i++)
		{
			oss << res->Get(i) << "\r\n";
		}
	}
	out = oss.str();
	std::wstring stemp = s2ws(out);
	LPCWSTR result = stemp.c_str();
	SetWindowText(hWnd, result);
	return res;
}
int integerCompare(int a, int b) {
	if (a > b) {
		return 1;
	}
	else if (a < b) {
		return 0;
	}
	else {
		return 2;
	}
}

int integerCompareDsc(int a, int b) {
	if (a < b) {
		return 1;
	}
	else if (a > b) {
		return 0;
	}
	else {
		return 2;
	}
}

Sequence<PersonForIndex>* generatePersonSeq(int maxPerson)
{

	PersonForIndex* personArr = new PersonForIndex[maxPerson];

	for (int i = 0; i < maxPerson; i++)
	{
		PersonForIndex person = PersonForIndex(s2ws("FirstName_" + std::to_string(i)), s2ws("MiddleName_" + std::to_string(i)),
			s2ws("LastName_" + std::to_string(i)), 2020 - i);
		personArr[i] = person;
	}
	Sequence<PersonForIndex>* seq = new ArraySequence<PersonForIndex>(personArr, maxPerson);
	return seq;
}

std::list<boost::uuids::uuid> generatePerson(int maxPerson)
{
	boost::system::error_code error;
	std::string fileName = "c:\\tmp\\laba4_2\\";
	boost::filesystem::remove_all(fileName, error);
	boost::filesystem::create_directories(fileName, error);
	std::list<boost::uuids::uuid> personList;
	for (int i = 0; i < maxPerson; i++)
	{
		Person person = Person("FirstName_" + std::to_string(i), "MiddleName_" + std::to_string(i),
			"LastName_" + std::to_string(i), 2020 - i);
		personList.push_back(person.GetIndex());
		saveToFile(person);
	}
	return personList;
}
bool comp(Person p1, Person p2)
{
	return p1.Equals(p2);
}

void getSearchStr(HWND SearchStr, std::wstring& str)
{
	int bufferLength = ::GetWindowTextLength(SearchStr) + 1;
	std::vector<wchar_t> buffer(bufferLength);
	::GetWindowText(SearchStr, buffer.data(), bufferLength);
	str = buffer.data();
}

void testSearch(Sequence<std::wstring>* seqIndex, HashTableExt<PersonForIndex>* hashTable, HWND hWndOutput0, HWND hWndOutput1, HWND hWndOutput2, 
                HWND SearchStr, HWND hSearchButtonFirstName , HWND hSearchButtonMiddleName, HWND hSearchButtonLastName, HWND hSearchButtonAge)
{
	SetWindowText(hWndOutput2, L"Нет данных");
	std::wostringstream oss1;
	std::wostringstream oss2;
	
	Sequence<std::wstring>* _seqIndex = new ArraySequence<std::wstring>();
	// Allocate string buffer of proper size

	std::wstring searchStr;
	getSearchStr(SearchStr, searchStr);
	boost::trim_right(searchStr);
	
	std::wstring searchStrIndex;
	std::wstring searchStrIndexTmp;
	getSearchStr(hSearchButtonFirstName, searchStrIndex);
	boost::trim_right(searchStrIndex);
	searchStrIndex.append(L" ");
	getSearchStr(hSearchButtonMiddleName, searchStrIndexTmp);
	boost::trim_right(searchStrIndexTmp);
	searchStrIndex.append(searchStrIndexTmp).append(L" ");
	getSearchStr(hSearchButtonLastName, searchStrIndexTmp);
	boost::trim_right(searchStrIndexTmp);
	searchStrIndex.append(searchStrIndexTmp).append(L" ");
	getSearchStr(hSearchButtonAge, searchStrIndexTmp);
	boost::trim_right(searchStrIndexTmp);
	searchStrIndex.append(searchStrIndexTmp);
	boost::trim_right(searchStrIndex);
	
	bool searcFromStr =searchStr.length()>0;
	bool searcFromStrindex = searchStrIndex.length()>0;
	
	if (searcFromStr)
	{
		for (int i = 0; i < seqIndex->GetLength(); ++i)
		{
			std::wstring str = seqIndex->Get(i);
			if (str.find(searchStr) != std::string::npos)
			{
				_seqIndex->Append(str);
			}
		}
	} else if(searcFromStrindex)
	{
		_seqIndex->Append(searchStrIndex);
	} else
	{
		_seqIndex = seqIndex;
	}
	
	bool res = true;

	oss2 << L"Тест поиска данных с использованием индекса." << "\r\n\r\n";
	if (_seqIndex->GetLength() == 0 && (searcFromStrindex || searcFromStr))
	{
		oss1 << L"Информация отсутствует " "\r\n";
	}
	for (int i = 0; i < _seqIndex->GetLength(); ++i)
	{
		oss1 << L"Поиск элемента (" << i + 1 << L") по индексу: \r\n" << _seqIndex->Get(i) << "\r\n\r\n";
		PersonForIndex person = PersonForIndex(_seqIndex->Get(i));
		person = hashTable->Find(person);
		if (searcFromStrindex || searcFromStr)
		{
			if (person.IsNull()) {
				oss1 << L"Информация отсутствует " "\r\n";
			}
			else
			{
				oss1 << L"ФИО: " << person.GetFIO() << "\r\n";
				oss1 << L"ГР: " << person.GetBirthYear() << "\r\n";
				oss1 << L"Возраст: " << person.GetAge(2020) << "\r\n\r\n";
			}
		}
		else {

			res = res && !person.IsNull();
			oss1 << L"ФИО: " << person.GetFIO() << "\r\n";
			oss1 << L"ГР: " << person.GetBirthYear() << "\r\n";
			oss1 << L"Возраст: " << person.GetAge(2020) << "\r\n\r\n";

			if (_seqIndex->GetLength() == 0)
			{
				oss1 << L"Информация отсутствует " "\r\n";
			}
		}
	}

		if (res && !(searcFromStrindex || searcFromStr))
		{
			oss2 << L"----Тест пройден----" << "\r\n\r\n";
		}
		else if(!(searcFromStrindex || searcFromStr))
		{
			oss2 << L"----Тест провален----" << "\r\n\r\n";
		}
	
	oss2<<oss1.str();
	//std::wstring temp = s2ws(out);
	auto tmp = oss2.str();
	LPCWSTR result = tmp.c_str();

	SetWindowText(hWndOutput2, result);
}

HashTableExt<PersonForIndex>* testIndex(Sequence<std::wstring>* seqIndex, SizeSeq sizeSeq, HWND hWndOutput0, HWND hWndOutput1, HWND hWndOutput2)
{
	SetWindowText(hWndOutput0, L"Нет данных");
	SetWindowText(hWndOutput1, L"Нет данных");
	SetWindowText(hWndOutput2, L"Нет данных");
	int maxPerson = static_cast<int>(sizeSeq) / 10;
	Sequence<PersonForIndex>* seq;
	seq = generatePersonSeq(maxPerson);
	std::wostringstream oss1;
	std::wostringstream oss2;
	oss1 << L"Тест индексирования данных." << "\r\n";
	oss1 << L"Создание коллекции с индексами " << "\r\n";
	oss1 << L"Количество элементов коллекции " << maxPerson << "\r\n";
	oss2 << L"Формирование списка индексов " << maxPerson << "\r\n";
	HashTableExt<PersonForIndex>* hash = new HashTableExt<PersonForIndex>();
	for (int i = 0; i < maxPerson; i++)
	{
		hash->Add(seq->Get(i));
		PersonForIndex pers = hash->Find(seq->Get(i));
		seqIndex->Append(seq->Get(i).GetIndex());

		oss2 << pers.GetIndex() << "\r\n";
	}
	auto tmp = oss1.str();
	LPCWSTR result = tmp.c_str();
	SetWindowText(hWndOutput0, result);

	tmp = oss2.str();
	result = tmp.c_str();
	SetWindowText(hWndOutput1, result);
	return hash;
}

void testCash(SizeSeq sizeSeq, SizeCash sizeCash, HWND hWndOutput0, HWND hWndOutput1, HWND hWndOutput2)
{
	SetWindowText(hWndOutput0, L"Нет данных");
	SetWindowText(hWndOutput1, L"Нет данных");
	SetWindowText(hWndOutput2, L"Нет данных");
	int maxPerson = static_cast<int>(sizeSeq);
	int cashSize = static_cast<int>(sizeCash);
	std::ostringstream oss;
	oss << "Тест чтения данных из файла без кэширования." << "\r\n";
	oss << "Количество элементов коллекции " << maxPerson << "\r\n";

	std::list<boost::uuids::uuid> personList = generatePerson(maxPerson);
	auto startTime = std::chrono::system_clock::now();
	auto count = 0;
	auto countTotal = 0;
	for (auto uuid : personList)
	{
		if (count > personList.size() * 0.25 && count < personList.size() * 0.75)
		{
			for (int i = 0; i < 4; i++)
			{
				loadFromFile(uuid);
				countTotal++;
			}
		}
		if (count > personList.size() * 0.45 && count < personList.size() * 0.55)
		{
			for (int i = 0; i < 4; i++)
			{
				loadFromFile(uuid);
				countTotal++;
			}
		}
		loadFromFile(uuid);
		count++;
		countTotal++;
	}

	auto endTime = std::chrono::system_clock::now();
	auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	oss << "Время чтения данных из файла (мс): " << delta.count() << "\r\n";
	oss << "Количество прочитанных элементов : " << countTotal << "\r\n";
	std::string out = oss.str();
	std::wstring temp = s2ws(out);
	LPCWSTR result = temp.c_str();
	SetWindowText(hWndOutput0, result);


	startTime = std::chrono::system_clock::now();
	oss.str(std::string());
	count = 0;
	countTotal = 0;
	oss << "Тест чтения данных из файла из Хэштаблицы." << "\r\n";
	oss << "Количество элементов коллекции " << maxPerson << "\r\n";
	auto hash = HashTable<Person>();
	for (auto& uuid : personList)
	{
		Person person = Person(uuid);
		if (count > personList.size() * 0.25 && count < personList.size() * 0.75)
		{
			for (int i = 0; i < 4; i++)
			{
				getFromHashTable<Person>(uuid, &hash);
				countTotal++;
			}
		}
		if (count > personList.size() * 0.45 && count < personList.size() * 0.55)
		{
			for (int i = 0; i < 4; i++)
			{
				getFromHashTable<Person>(uuid, &hash);
				countTotal++;
			}
		}
		person = getFromHashTable<Person>(uuid, &hash);
		count++;
		countTotal++;
	}


	endTime = std::chrono::system_clock::now();
	auto delta1 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	oss << "Время чтения данных из файла (мс): " << delta1.count() << "\r\n";
	oss << "Количество прочитанных элементов : " << countTotal << "\r\n";
	oss << "Эффективность (%): " << (static_cast<double>(delta.count() - delta1.count()) / static_cast<double>(delta.count()) * 100) << "\r\n";
	out = oss.str();
	temp = s2ws(out);
	result = temp.c_str();
	SetWindowText(hWndOutput1, result);


	oss.str(std::string());
	startTime = std::chrono::system_clock::now();
	count = 0;
	countTotal = 0;
	oss << "Тест чтения данных из файла из Кэша." << "\r\n";
	oss << "Количество элементов коллекции " << maxPerson << "\r\n";
	oss << "Размер Кэша " << cashSize << "\r\n";
	LRUCache<Person> cache = LRUCache<Person>(cashSize);

	for (auto uuid : personList)
	{
		Person person = Person(uuid);
		if (count > personList.size() * 0.25 && count < personList.size() * 0.75)
		{
			for (int i = 0; i < 4; i++)
			{
				person = getFromCache<Person>(uuid, &cache);
				countTotal++;
			}
		}
		if (count > personList.size() * 0.45 && count < personList.size() * 0.55)
		{
			for (int i = 0; i < 4; i++)
			{
				person = getFromCache<Person>(uuid, &cache);
				countTotal++;
			}
		}
		person = getFromCache<Person>(uuid, &cache);

		count++;
		countTotal++;
	}


	endTime = std::chrono::system_clock::now();
	auto delta2 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	oss << "Время чтения данных из файла (мс): " << delta2.count() << "\r\n";
	oss << "Количество прочитанных элементов : " << countTotal << "\r\n";
	oss << "Эффективность (%): " << (static_cast<double>(delta.count() - delta2.count()) / static_cast<double>(delta.count()) * 100) << "\r\n";
	out = oss.str();
	temp = s2ws(out);
	result = temp.c_str();
	SetWindowText(hWndOutput2, result);
}


