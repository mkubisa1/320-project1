#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <map>
#include <iostream>
#include "getBinary.h"

using namespace std;

class BOBwithBTB { //bimodalOneBit with Brach Target Buffer support
    private:
        map<string,string> table;
        int tableSize;      
        int binaryLength;   

        map<string,long long unsigned int> btbTable;    //btbTable is indexed with pcBits; each pcBits corresponds to a target.
        int numPredictions = 0;
        int btbCorrect = 0;

    public:
        BOBwithBTB(int entriesCount);
        void predictTarget(long long unsigned int inputAddr, string actualOutcome, long long unsigned int inputTarget);
        int getAttempts() {return numPredictions;}
        int getCorrect() {return btbCorrect;}
};

#endif