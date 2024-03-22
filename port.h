//
// Created by raz on 14/03/2024.
//

#ifndef FOR_STUDENTS_PORT_H
#define FOR_STUDENTS_PORT_H

#include "generic-field.h"
#include "generic-field.h"
#include "string.h"
#include "string-array.h"
#include <string>


class Port  : public GenericField{

    std::string type; //  type = "src-port" or "dst-port"
    int first;
    int last;

public:

    /**
     * @brief Port's C'tor, convert portType to string "type" and portStr to two integers.
     * @param portType A string that determines the filed that this rule will check.
     * @param portStr A string that contain the range of ports that legal :  portStr = "x-y".
     *
     */
    Port(const std::string& portType, const std::string& portStr);

    ~Port();

    bool match(const GenericString &packet) const;




};


#endif //FOR_STUDENTS_PORT_H
