#include <string>
#include <map>
#include <iostream>

#include "bimodalTwoBit.h"
#include "gShare.h"
#include "Tournament.h"

using namespace std;

Tournament::Tournament() {
    /*
    note: these parameters are currently hardcoded, but a constructor could be made to user-define them:
        - gShare's number of global history bits
        - bimodalTwoBit's tableSize
    gShare's table size is hardcoded to 2048 entries in the gShare class, so more work would be needed to specify other sizes
    */

    //configure selector table with 2048 entries, all initialized to 00 (strong preger gShare)
    for(int i = 0; i < 2048; i++) { table[getBinary(i,11)] = "00"; }


}