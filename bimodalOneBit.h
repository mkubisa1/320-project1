#ifndef BOB_H
#define BOB_H

#include <string>
#include <map>
#include <iostream>
#include "getBinary.h"

class bimodalOneBit {
    private:
        map<string,string> table;
        int tableSize;      //number of prediction table entries; given by user (usually)
        int binaryLength;   //the length of each binary table entry (dependent on tableSize)

    public:
        bimodalOneBit();                //default constructor will assume tableSize 16
        bimodalOneBit(int inputSize);   //this is the constructor usually used
        //map<string,string> getTable() {return table;}
        bool predict(long long unsigned int inputAddr, string actualOutcome);
};

#endif