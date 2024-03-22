//
// Created by raz on 13/03/2024.
//

#ifndef FOR_STUDENTS_IP_H
#define FOR_STUDENTS_IP_H

#include "generic-field.h"
#include "generic-field.h"
#include "string.h"
#include "string-array.h"

class Ip : public GenericField{

    int ip;
    std::string type; //  type = "src-ip" or "dst-ip"
    int mask;

public:

    /**
     * @brief Ip's C'tor, convert ipType to string "type" and ipStr, maskStr to two integers.
     * @param ipType A string that determines the filed that this rule will check.
     * @param ipStr A string that contain the ip that legal.
     * @param maskStr An integer that defined the mask.
     */
    Ip(const std::string& ipType, const std::string& ipStr, int maskVal);


    ~Ip();

    bool match(const GenericString &packet) const;

    int make_mask(int mask);


};


#endif //FOR_STUDENTS_IP_H
