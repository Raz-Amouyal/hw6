//
// Created by raz on 14/03/2024.
//

#include "string.h"
#include "string-array.h"
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <cstring>



#define SPACE ' '
#define M 4         //num of byte in ip address

String::String() : data("") {}


String::String(const std::string& str) : data(str){}


String::String(const String& other) : data(other.data) {}

String::~String(){}

size_t String::size() const
{
    return data.size();
}


std::string String::str() const
{
    return this->data;
}


String& String::operator=(const String &other)
{
    if (this != &other) {
        this->data = other.data;
    }
    return *this;
}

String& String::operator=(const char* str)
{
    this->data = str;

    return *this;
}

bool String::operator==(const GenericString &other) const
{

    String s = other.as_string();

    return this->data == s.data;
}

bool String::operator==(const char *other) const
{
    return this->data == other;
}


StringArray String::split(const char *delimiters) const
{

    StringArray strings;
    /*
    char* cData = new char[data.length() + 1];
    std::strcpy(cData, data.c_str());
    */
    std::string str = data;
    std::string token;
    size_t first;
    while (str.length()){
        first = str.find_first_of(delimiters);
        if (first == std::string::npos){
            first = str.length();
        }
        token = str.substr(0,first);
        str.erase(0, first + 1);
        GenericString *str_ptr = new String(token);
        strings.addElem(str_ptr);
    }

/*
    char* token = std::strtok(cData, delimiters);

    while(token != nullptr) {
        const char *temp = token;
        GenericString *str_ptr = new String(temp);
        strings.addElem(str_ptr);
        token = strtok(nullptr, delimiters);
    }

    delete[] cData;
    */
    return strings;

}


int String::to_integer() const
{
    return stoi(data);

}


String& String::trim(){
    int start = data.find_first_not_of(SPACE);
    if (start > 0){
        data.erase(0, start);
    }
    int end = data.find_last_not_of(SPACE);
    if (end < data.length() -1){
        data.erase(end + 1);
    }
    return *this;
}


String& String::as_string()
{
    return dynamic_cast<String&>(*this);
}


const String& String::as_string() const
{
    return dynamic_cast<const String&>(*this);
}

int String::to_ip_W_mask(int mask) const
{
    StringArray ipArr = this->split(".");
    int ip = 0;
    for (int i = 0; i < M; ++i) {
        ip |= ( ipArr[i].to_integer() << ((3-i)*8) );
    }

    ip &= mask;

    return ip;

}


GenericString* make_string(const char *str)
{
    GenericString* ptr = new String(str);
    return ptr;
}

