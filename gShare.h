#ifndef GS_H
#define GS_H

#include <string>
#include <map>
#include <iostream>
#include "getBinary.h"

class gShare {
    private:
        int tableSize = 2048;
        string GHR;
        map<string,string> table;   //all predictions initially set to "TT" (strong taken)

    public:
        gShare();
        gShare(int ghrAccuracy);    //in practice, int will vary from 3 to 11 bits
};

#endif