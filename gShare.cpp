#include <string>
#include <map>
#include <iostream>
#include <cmath>
#include "gShare.h"
using namespace std;

gShare::gShare(int ghrAccuracy) {
    GHR = getBinary(0,ghrAccuracy);
    for(int i = 0; i < pow(2,ghrAccuracy); i++) { 
        table[getBinary(i,ghrAccuracy)] = "TT"; 
        cout << getBinary(i,ghrAccuracy) << endl;
    } //initialize all table entries to Strongly Taken
}