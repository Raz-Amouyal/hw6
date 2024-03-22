//
// Created by raz on 14/03/2024.
//

#ifndef FOR_STUDENTS_STRING_H
#define FOR_STUDENTS_STRING_H

#include "generic-string.h"
#include <string>
#include <cstring>

class String : public GenericString{
    std::string data;


public:
    String();
    String(const std::string& str);    // c'tor
    String(const String &other);    //copy c'tor
    ~String();

    /**
     * @brief Member function.
     * @returns the size of the string.
     */
    size_t size() const;

    /**
     * @brief Member function.
     * @returns the string.
     */
    std::string str() const;

    String& operator=(const String &other);

    /**
     * @brief Sets the contents of this to be a copy of "str".
     * @returns A reference to this.
     */
    String& operator=(const char *str);


    /**
     * @brief Returns true iff the contents of this == the contents of other.
     */
    virtual bool operator==(const GenericString &other) const;
    virtual bool operator==(const char *other) const;

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * @param delemiters A set of characters. For example, when delimieters=" ,"
     * this should be split according to spaces and commas.
     * @returns A "StringArray" object. See HW spec for more info.
     */
    virtual StringArray split(const char *delimiters) const;

    /**
     * @brief Returns an integer representation of the contents of this.
     * In case this cannot be represented as integer, returns 0.
     * @note You can use the "atol" function in the "cstring" library.
     */
    virtual int to_integer() const;

    /**
     * @brief Remove any leading or trailing white-spaces from this.
     * @returns A reference to this.
     */
    virtual String& trim();

    /**
     * @brief Returns a reference to this as "String" instead of "GenericString"
     */
    virtual String& as_string();
    virtual const String& as_string() const;



    int to_ip_W_mask(int mask) const;





};





#endif //FOR_STUDENTS_STRING_H
