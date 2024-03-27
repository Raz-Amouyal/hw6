//
// Created by raz on 14/03/2024.
//
#include "string-array.h"
#include "string.h"
#include <stdexcept>
#include <iostream>


StringArray::StringArray() {}

StringArray::StringArray(const StringArray &other)
{
    int len = other.array.size();
    for (int i = 0 ; i < len ; ++i) {
        String* ptr = new String(other[i].str());
        this->addElem(ptr);
    }
}

StringArray::~StringArray(){
    int len = array.size();
    for (int i = 0 ; i < len ; ++i) {
        delete array[i];
    }
}


void StringArray::addElem(GenericString* ptr){
    array.push_back(ptr);
}


String& StringArray::operator[](size_t index){
    if (index < array.size() && array[index] != nullptr) {
        return array[index]->as_string();
    } else {
        // Handle error gracefully, such as throwing an exception or returning a default value
	    std::cout << "\n\n!!!!!!!!!!!\n\n index:" << index << "\narr size:" << array.size() << "\n\n\n" <<  std::endl;
	throw std::out_of_range("Index out of range or pointer is null");
    }

}

String& StringArray::operator[](size_t index) const{

    if (index < array.size() && array[index] != nullptr) {
        return array[index]->as_string();
    } else {
        // Handle error gracefully, such as throwing an exception or returning a default value
            std::cout << "\n\n!!!!!!!!!!!\n\n index:" << index << "\narr size:" << array.size() << "\n\n\n" <<  std::endl;
        throw std::out_of_range("Index out of range or pointer is null");
    }

}


size_t StringArray::size() const{
    return array.size();
}

