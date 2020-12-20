#ifndef SECOND_LAB1_SEM3_OPTION_HPP
#define SECOND_LAB1_SEM3_OPTION_HPP

#include "Exceptions.hpp"

template<typename T>
class Option {
private:
    T data;
    bool has_value{};
public:
    Option();

    explicit Option(T);

    T getValue() const;

    void setValue(T);

    [[nodiscard]] bool hasValue() const;

    bool operator==(const Option &right);

    bool operator!=(const Option &right);

    ~Option();
};


template<typename T>
Option<T>::Option() {
    this->data = 0;
    this->has_value = false;
}

template<typename T>
Option<T>::Option(T data) {
    this->data = data;
    this->has_value = true;
}


template<typename T>
T Option<T>::getValue() const {
    if (this->has_value) {
        return this->data;
    } else {
        throw exceptions::OptionExceptions("Has no value!", __LINE__, __FILE__);
    }
}

template<typename T>
void Option<T>::setValue(T value) {
    this->data = value;
    if (!this->has_value) {
        this->has_value = true;
    }
}

template<typename T>
bool Option<T>::operator==(const Option<T> &right) {
    if (this->has_value && right.hasValue()) {
        return this->data == right.getValue();
    } else {
        throw exceptions::OptionExceptions("Can't compare options!", __LINE__, __FILE__);
    }
}

template<typename T>
bool Option<T>::operator!=(const Option<T> &right) {
    if (this->has_value && right.hasValue()) {
        return this->data != right.getValue();
    } else {
        throw exceptions::OptionExceptions("Can't compare options!", __LINE__, __FILE__);
    }
}

template<typename T>
bool Option<T>::hasValue() const {
    return this->has_value;
}

template<typename T>
Option<T>::~Option() = default;


#endif //SECOND_LAB1_SEM3_OPTION_HPP
