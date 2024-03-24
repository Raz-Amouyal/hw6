//
// Created by raz on 13/03/2024.
//

#ifndef FOR_STUDENTS_STRING_ARRAY_H
#define FOR_STUDENTS_STRING_ARRAY_H

#include "generic-string.h"
#include <vector>
#include <cstddef>

class StringArray{

    std::vector<GenericString*> array;


public:


    StringArray();
    StringArray(const StringArray &other);
    ~StringArray();

    void addElem(GenericString* ptr);

    String& operator[](int index);

    String& operator[](int index) const;

    //GenericString& operator=(int index);    //need to implement


    size_t size() const;



};

#endif //FOR_STUDENTS_STRING_ARRAY_H
