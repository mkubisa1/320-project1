#include <string>
#include <map>
#include <iostream>
#include <cmath>
#include "gShare.h"
using namespace std;

gShare::gShare(int ghrAccuracy) {
    GHR = getBinary(0,ghrAccuracy);                                                         //initialize GHR to all zeroes
    for(int i = 0; i < pow(2,ghrAccuracy); i++) { table[getBinary(i,ghrAccuracy)] = "TT"; } //initialize all table entries to Strongly Taken
}

bool gShare::predict(long long unsigned int inputAddr, string actualOutcome) {

    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-GHR.length()); //get last ghrAccuracy bits of inputAddr: (GHR.length() = ghrAccuracy)
    
    //XOR pcBits and GHR (XOR: 0 = bit is same; 1 = bit is different)
    string tableIndex;
    for(int i=0; i < GHR.length(); i++) {
        if(pcBits.at(i) == GHR.at(i)) {tableIndex += "0";}
        else {tableIndex += "1";}
    }

    auto iteration = table.find(tableIndex);
    string prediction;

    //consolidate strong and weak versions of prediction into a single predicton:
    if(iteration->second == "TT" || iteration->second == "TN") {prediction = "T";}  //taken
    if(iteration->second == "NN" || iteration->second == "NT") {prediction = "NT";} //not taken (NOTE: "NT" in prediction table means "weak not taken"; actualOutcome of NT has no weak/strong affiliation.)

    //compare prediction to actualOutcome:
    if(prediction == actualOutcome) {

        //make weak predictions stronger:
        if(iteration->second == "TN") {iteration->second = "TT";}
        else if(iteration->second == "NT") {iteration->second = "NN";}

        //update GHR with actualOutcome:
        GHR.erase(0,1);
        if(actualOutcome == "T")    { GHR += "1";}
        if(actualOutcome == "NT")   { GHR += "0";}

        return true;
    }
    else {
        //update prediction for this tableIndex:
        if(iteration->second == "NN") {iteration->second = "NT";}       //case: was strong not taken
        else if(iteration->second == "NT") {iteration->second = "TN";}  //case: was weak not taken
        else if(iteration->second == "TN") {iteration->second = "NT";}  //case: was weak taken
        else if(iteration->second == "TT") {iteration->second = "TN";}  //case: was strong taken

        //update GHR with actualOutcome:
        GHR.erase(0,1);
        if(actualOutcome == "T")    { GHR += "1";}
        if(actualOutcome == "NT")   { GHR += "0";}

        return false;
    }

    cout << "ERROR: gShare could not deduce prediction." << endl << endl;
    return false;
}