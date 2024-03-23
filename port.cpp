//
// Created by raz on 14/03/2024.
//

#include "port.h"
#include <cstring>
#include <cstdlib>

#define N 8   //len of packet.split() == pktArr.size()
#define M 4   //num of byte in ip address

Port::Port(const std::string& portType, const std::string& portStr)
: type(portType)
{
    int pos = portStr.find('-');
    first = stoi(portStr.substr(0,pos));
    last = stoi(portStr.substr(pos+1));
}

Port::~Port() {}


/*
 * packet = "src-ip=XXX.XXX.XXX.XXX,dst-ip=YYY.YYY.YYY.YYY,src-port=PRT,dst-port=PRT"
 * pktArr[0] = src-ip              :type
 * pktArr[1] = XXX.XXX.XXX.XXX     :data
 * pktArr[2] = dst-ip              :type
 * pktArr[3] = YYY.YYY.YYY.YYY     :data
 * pktArr[4] = src-port            :type
 * pktArr[5] = PRT                 :data
 * pktArr[6] = dst-port
 * pktArr[7] = PRT
 * index of type : 2n   , 0 <= n <= 3
 * index of data : 2n+1 , 0 <= n <= 3
 *
 * for match we need:
 * 1- turn packet to String
 * 2- split by "," and "=" to pktArr ; pktArr[i] contain type or data
 * 3- trim all pktArr elements
 * 4- find the element of the rule by comp pktArr[0,2,4,6] to rule type
 * 5- check if pktArr[rule] in the range of ports
 *
 */
bool Port::match(const GenericString &packet) const{
    int rule = 0;

    //step 1 : turn packet to String
    const String input = packet.as_string();

    //step 2 : split by "," and "=" to pktArr ; pktArr[i] contain type or data
    StringArray pktArr = input.split(",=");
    int n = pktArr.size();

    //step 3 : trim all pktArr elements
    for (int i = 0 ; i < n ; ++i) {
        pktArr[i].trim();
    }

    //step 4 : find the element of the rule by comp pktArr[0,2,4,6] to rule type
    for (int i = 0; i < n ; i += 2) {
        if (pktArr[i].str() == type ){
            rule = i+1;
        }
    }

    //step 5 : check if pktArr[rule] in the range of ports
    int pktPort = pktArr[rule].to_integer();


    return (first <= pktPort && pktPort <= last);

}
