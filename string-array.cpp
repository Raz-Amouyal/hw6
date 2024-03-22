//
// Created by raz on 14/03/2024.
//
#include "string-array.h"
#include "string.h"


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


String& StringArray::operator[](int index){
    return array[index]->as_string();
}

String& StringArray::operator[](int index) const{
    return array[index]->as_string();
}


size_t StringArray::size() const{
    return array.size();
}

