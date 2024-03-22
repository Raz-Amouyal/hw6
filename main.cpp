//
// Created by raz on 14/03/2024.
//
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "input.h"
#include "generic-field.h"
#include "generic-string.h"
#include "ip.h"
#include "port.h"
#include "string-array.h"
#include "string.h"

#define SLASH '/'
#define EQUALS '='

class MyClass {
private:
    std::vector<int> myVector;

public:
    // Default constructor
    MyClass() {
        // You can initialize the vector here if needed
    }

    // Other constructors, member functions, etc.
    // ...

    // Function to add elements to the vector
    void addElement(int value) {
        myVector.push_back(value);
    }

    // Function to print elements of the vector
    void printVector() const {
        for (int num : myVector) {
            std::cout << num << " \n";
        }
        std::cout << std::endl;
    }
};

void printBits(int num) {
    // Size of int in bits
    int numBits = sizeof(int) * 8;

    // Mask to extract each bit
    int mask = 1 << (numBits - 1);

    // Loop through each bit and print
    for (int i = 0; i < numBits; ++i) {
        std::cout << ((num & mask) ? '1' : '0');
        mask >>= 1; // Shift mask to the right
    }
    std::cout << std::endl;
}

void trimLocal(std::string& s)
{
    int start = s.find_first_not_of(' ');
    if (start > 0){
        s.erase(0, start);
    }
    int end = s.find_last_not_of(' ');
    if (end < s.length() -1 ){
        s.erase(end + 1);
    }
}



/*
 * main gets in argv[1] pointer to c.string with the full rule
 * *argv[1] look like:
 *      type=data/mask (for ports without the /mask part)
 * flow line:
 * 1 - check the rule general type by check for'/' (ip have '/' for the mask) : port or ip
 * 2 - convert the string to filed by its type
 * 3 - call parse_input with the rule
 */

int main(int argc, char* argv[]) {


    std::string rule = argv[1];

    GenericField* rulePtr;
    int equalPos = rule.find(EQUALS);
    std::string type = rule.substr(0,equalPos);
    trimLocal(type);
    std::string data;


    //step 1
    int maskPos = rule.find(SLASH);
    //if takes -> there is a mask therefor its ip rule
    if (maskPos >= 0){
        int mask = stoi(rule.substr(maskPos+1));
        data = rule.substr(equalPos+1, maskPos - equalPos -1); // -1 for data not contain '/'
        trimLocal(data);
        rulePtr = new Ip(type, data, mask);
    } else {
        data = rule.substr(equalPos+1);
        trimLocal(data);
        rulePtr = new Port(type, data);
    }
    parse_input(*rulePtr);




    return 0;
}
