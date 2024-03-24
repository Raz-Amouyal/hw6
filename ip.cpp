//
// Created by raz on 13/03/2024.
//
#include <string>
#include <cstring>
#include <cstdlib>
#include "ip.h"

#define N 8   //len of packet.split()
#define M 4   //num of byte in ip address
#define NUM_OF_BITS 32

Ip::Ip(const std::string& ipType, const std::string& ipStr, int maskVal)
: type(ipType), mask(maskVal)
{
    mask = make_mask(mask);
    String sIp(ipStr);

    ip = sIp.to_ip_W_mask(mask);

}


Ip::~Ip(){}

/*
 * packet = "src-ip=XXX.XXX.XXX.XXX,dst-ip=YYY.YYY.YYY.YYY,src-port=PRT,dst-port=PRT"
 * pktArr[0] = src-ip
 * pktArr[1] = XXX.XXX.XXX.XXX
 * pktArr[2] = dst-ip
 * pktArr[3] = YYY.YYY.YYY.YYY
 * pktArr[4] = src-port
 * pktArr[5] = PRT
 * pktArr[6] = dst-port
 * pktArr[7] = PRT
 * index of type : 2n   , 0 <= n <= 3
 * index of data : 2n+1 , 0 <= n <= 3
 *
 * for match we need:
 * 1- turn packet to String
 * 2- split by "," and "=" to pktArr - pktArr[i] contain type or data
 * 3- trim all pktArr elements
 * 4- find the element of the rule by comp pktArr[0,2,4,6] to rule type
 * 5- check if pktArr[rule] == rule ip according to mask
 *
 */
bool Ip::match(const GenericString &packet) const{
    int rule = 0;

    //step 1
    String tmp = packet.as_string();

    const String input = tmp.trim();

    if (!input.str().length()){
	    return false;
    }

    //step 2
    StringArray pktArr = input.split(",=");
    int n = pktArr.size();

    //step 3
    for (int i = 0 ; i < n ; ++i) {
        pktArr[i].trim();
    }

    //step 4
    for (int i = 0; i < n ; i += 2) {
        if (pktArr[i].str() == type ){
            rule = i+1; //add "continue" here
        }
    }

    //step 5

    if (rule >= n){
	    return false;
    }
    int pktIp = pktArr[rule].to_ip_W_mask(mask);


    return (ip == pktIp);

}

int Ip::make_mask(int val)
{
    if (val == NUM_OF_BITS){
        return 0;
    }
    int temp = 1;
    for (int i = 1; i < NUM_OF_BITS - val; ++i) {
        temp <<= 1;
        temp++;
    }
    return temp;
}
