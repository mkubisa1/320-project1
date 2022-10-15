#ifndef BTB_H
#define BTB_H

#include <string>
#include <map>
#include <iostream>
#include "getBinary.h"

using namespace std;

class bimodalTwoBit {
    private:
        map<string,string> table;
        int tableSize;
        int binaryLength;

    public:
        bimodalTwoBit();
        bimodalTwoBit(int entriesCount);
        bool predict(long long unsigned int inputAddr, string actualOutcome);
};

#endif