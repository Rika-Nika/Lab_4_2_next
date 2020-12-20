#pragma once
#include <string>
#include "Util.hpp"
#include "Exception.h"

class PersonForIndex
{
private:
	std::wstring _firstName;
	std::wstring _middleName;
	std::wstring _lastName;
	std::wstring _index;
	int _birthYear{};
	bool _isNull = true;

public:

	PersonForIndex(const std::wstring& first_name, const std::wstring& middle_name, const std::wstring& last_name, int birth_year);
	PersonForIndex(const std::wstring& index);

	PersonForIndex() = default;

	std::wstring GetFirstName() const;

	std::wstring GetMiddleName() const;

	std::wstring GetLastName() const;

	int GetBirthYear() const;


	void SetFirstname(const std::wstring& first_name);

	void SetMiddlename(const std::wstring& middle_name);

	void SetLastname(const std::wstring& last_name);

	void SetBirthYear(const int birth_year);

	std::wstring GetFIO() const; // Фамилия И.О.
	std::wstring GetIndex() const;

	void set_index(const std::wstring& index);

	int GetAge(int year)const; // вычислить возраст на заданный момент

	bool Equals(PersonForIndex person);
	bool IsNull();
	friend bool operator==(const PersonForIndex& left, const PersonForIndex& right);
	friend bool operator!=(const PersonForIndex& left, const PersonForIndex& right);
};

inline bool operator==(const PersonForIndex& left, const PersonForIndex& right)
{
	return left.GetIndex() == right.GetIndex();
}

inline bool operator!=(const PersonForIndex& left, const PersonForIndex& right)
{
	return left.GetIndex() != right.GetIndex();
}



inline PersonForIndex::PersonForIndex(const std::wstring& first_name, const std::wstring& middle_name, const std::wstring& last_name,
	int birth_year) : _firstName(first_name),
	_middleName(middle_name),
	_lastName(last_name),
	_birthYear(birth_year)
{
	std::wostringstream oss1;
	oss1 << GetFIO() << L" "  << GetAge(2020);
	this->_index = oss1.str();
	this->_isNull = false;
}

inline PersonForIndex::PersonForIndex(const std::wstring& index)
{
	_index = index;
}

inline std::wstring PersonForIndex::GetFirstName() const
{
	return _firstName;
}

inline std::wstring PersonForIndex::GetMiddleName() const
{
	return _middleName;
}

inline std::wstring PersonForIndex::GetLastName() const
{
	return _lastName;
}

inline int PersonForIndex::GetBirthYear() const
{
	return _birthYear;
}

inline void PersonForIndex::SetFirstname(const std::wstring& first_name)
{
	_firstName = first_name;
}

inline void PersonForIndex::SetMiddlename(const std::wstring& middle_name)
{
	_middleName = middle_name;
}

inline void PersonForIndex::SetLastname(const std::wstring& last_name)
{
	_lastName = last_name;
}

inline void PersonForIndex::SetBirthYear(const int birth_year)
{
	_birthYear = birth_year;
}

inline std::wstring PersonForIndex::GetFIO()const
{
	std::wostringstream oss1;
	oss1<< _firstName << L" " << _middleName << L" " << _lastName;
	return oss1.str();
}

inline int PersonForIndex::GetAge(int year) const
{
	if (year < _birthYear)
	{
		throw Exception("Invalid Year");
	}
	return year - _birthYear;
}

inline std::wstring PersonForIndex::GetIndex() const
{
	return _index;
}

inline void PersonForIndex::set_index(const std::wstring& index)
{
	_index = index;
}

inline bool PersonForIndex::Equals(PersonForIndex person)
{
	return this->GetIndex() == person.GetIndex();
}

inline bool PersonForIndex::IsNull()
{
	return _isNull;
}

