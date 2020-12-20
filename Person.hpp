#pragma once
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include "Exception.h"
class Base
{
private:
	boost::uuids::uuid _index;
	bool _isNull = true;

public:
	boost::uuids::uuid GetIndex() const;
	void SetIndex(const boost::uuids::uuid& index);
	bool IsNull() const;
	void SetIsNull();
};
class Person : public Base
{
private:
	std::string _firstName;
	std::string _middleName;
	std::string _lastName;
	int _birthYear;
	//	boost::uuids::uuid _index;

	friend class boost::serialization::access;
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _firstName;
		ar& _middleName;
		ar& _lastName;
		ar& _birthYear;

	}

	//boost::uuids::uuid _index;

public:

	Person(const std::string& first_name, const std::string& middle_name, const std::string& last_name, int birth_year);

	Person(boost::uuids::uuid index);
	Person() = default;


	void SetIndex(const boost::uuids::uuid& index);

	std::string GetFirstName() const;

	std::string GetMiddleName() const;

	std::string GetLastName() const;

	int GetBirthYear() const;

	void set_first_name(const std::string& first_name);

	void set_middle_name(const std::string& middle_name);

	void set_last_name(const std::string& last_name);

	void set_birth_year(const int birth_year);

	std::string GetFIO(); // Фамилия И.О.

	int GetAge(int year); // вычислить возраст на заданный момент

	boost::uuids::uuid GetIndex() const;

	bool Equals(Person person);

	friend bool operator==(const Person& left, const Person& right);
	friend bool operator!=(const Person& left, const Person& right);
};

inline boost::uuids::uuid Base::GetIndex() const
{
	return _index;
}

inline void Base::SetIndex(const boost::uuids::uuid& index)
{
	_index = index;
}

inline bool Base::IsNull() const
{
	return _isNull;
}

inline void Base::SetIsNull()
{
	_isNull = false;
}


inline Person::Person(const std::string& first_name, const std::string& middle_name, const std::string& last_name,
                      int birth_year) : _firstName(first_name),
                                        _middleName(middle_name),
                                        _lastName(last_name),
                                        _birthYear(birth_year)
{
	SetIndex(boost::uuids::random_generator()());
	SetIsNull();

}

inline Person::Person(boost::uuids::uuid index)
{
	Base::SetIndex(index);
}

inline void Person::SetIndex(const boost::uuids::uuid& index)
{
	Base::SetIndex(index);
}

inline std::string Person::GetFirstName() const
{
	return _firstName;
}

inline std::string Person::GetMiddleName() const
{
	return _middleName;
}

inline std::string Person::GetLastName() const
{
	return _lastName;
}

inline int Person::GetBirthYear() const
{
	return _birthYear;
}

inline void Person::set_first_name(const std::string& first_name)
{
	_firstName = first_name;
}

inline void Person::set_middle_name(const std::string& middle_name)
{
	_middleName = middle_name;
}

inline void Person::set_last_name(const std::string& last_name)
{
	_lastName = last_name;
}

inline void Person::set_birth_year(const int birth_year)
{
	_birthYear = birth_year;
}

inline std::string Person::GetFIO()
{
	return _firstName + " " + _middleName + " " + _lastName;
}

inline int Person::GetAge(int year)
{
	if (year < _birthYear)
	{
		throw Exception("Invalid Year");
	}
	return year - _birthYear;
}

inline boost::uuids::uuid Person::GetIndex() const
{
	return Base::GetIndex();
}

inline bool Person::Equals(Person person)
{
	return this->GetIndex() == person.GetIndex();
}



inline bool operator==(const Person& left, const Person& right)
{
	return left.GetIndex() == right.GetIndex();
}

inline bool operator!=(const Person& left, const Person& right)
{
	return left.GetIndex() != right.GetIndex();
}

inline int PersonCompare(Person a, Person b) {
	if (a.GetIndex() > b.GetIndex()) {
		return 1;
	}
	else if (a.GetIndex() < b.GetIndex()) {
		return 0;
	}
	else {
		return 2;
	}
}

class CashWrapper :public Person
{
private:
	int itemCounter = 1;

public:

	int GetItemCounter() const
	{
		return itemCounter;
	}

	void SetItemCounter(const int item_counter)
	{
		itemCounter = item_counter;
	}

	CashWrapper(int item_counter, Person person)
		: itemCounter(item_counter)
	{
		SetIndex(person.GetIndex());
		set_first_name(person.GetFirstName());
		set_middle_name(person.GetMiddleName());
		set_last_name(person.GetLastName());
		set_birth_year(person.GetBirthYear());
	}

	CashWrapper() = default;
	friend bool operator==(const Person& left, const Person& right);
};



