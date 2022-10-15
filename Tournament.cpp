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

bool Tournament::predict(long long unsigned int inputAddr, string actualOutcome) {
    
    //index table similar to bimodalTwoBit:
    int binaryLength = 11;                                                                          //length of each teble entry is 11 bits
    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-binaryLength); //extract the last binaryLength bits from addr
    auto iteration = table.find(pcBits);                                                            //get index in map of pcBits entry

    //make prediction based on entry at index:
        // 00 = prefer gShare
        // 01 = weakly prefer gShare
        // 10 = weakly prefer bimodal
        // 11 = prefer bimodal

    bool gResult = gs.predict(pcBits, actualOutcome);
    bool btbResult = btb.predict(pcBits, actualOutcome);
    //predict function will return whether or not the prediction was correct, and automatically perform updates to internal values based on that.

    //set which algorithm is preferred based on table entry:
    bool predictPref;
    if(iteration->second == "00" || iteration->second == "01") { predictPref = gResult; }
    if(iteration->second == "10" || iteration->second == "11") { predictPref = btbResult; }

    //analyze results of both predictors:
    if(gResult != btbResult) { //if the two algorithms produced different results...
            if(gResult == true) { //if gResult was correct
                if(iteration->second == "11"){iteration->second = "10";} //strongly prefered bimodal
                else if(iteration->second == "10"){iteration->second = "01";} //weakly prefered bimodal
                else if(iteration->second == "01"){iteration->second = "00";} //strongly prefered bimodal
            }
            else if(btbResult == true) {
                if(iteration->second == "00"){iteration->second = "01";} //strongly prefered gShare
                else if(iteration->second == "01"){iteration->second = "10";}
                else if(iteration->second == "10"){iteration->second = "11";}
            }
    }

    //return final result. if the preferred prediciton was correct, pass true.
    if(predictPref == true) {return true;}
    else {return false;}

    cout << "Tournament error: prediction did not finish correctly. Returning false" << endl;
    return false;
}