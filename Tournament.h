#ifndef TOUR_H
#define TOUR_H

#include <string>
#include <map>
#include <iostream>

#include "getBinary.h"
#include "bimodalTwoBit.h"
#include "gShare.h"

using namespace std;

class Tournament {
    private:
        gShare gs = gShare(11);                     //gShare with GHR accuracy of 11 (table size auto-defined as 2048 in gShare class)
        bimodalTwoBit btb = bimodalTwoBit(2048);    //bimodalTwoBit with table size of 2048
        map<string,string> table;                   //table used to choose which predictor to run

    public:
        Tournament();
        bool predict(long long unsigned int inputAddr, string actualOutcome);
};

#endif