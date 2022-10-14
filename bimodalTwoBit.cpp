#include <string>
#include <map>
#include <iostream>
#include "bimodalTwoBit.h"

using namespace std;

bimodalTwoBit::bimodalTwoBit() {
    tableSize = 16;
    binaryLength = 4;
    for(int i = 0; i < tableSize; i++) { table[getBinary(i,binaryLength)] = "TT"; }
}

bimodalTwoBit::bimodalTwoBit(int entriesCount) {
    tableSize = entriesCount;
    binaryLength = getBinary(entriesCount-1,0).length(); //get how long each binary table entry should be, using the maximum possible value
    for(int i = 0; i < tableSize; i++) { table[getBinary(i,binaryLength)] = "TT"; }
}

bool bimodalTwoBit::predict(long long unsigned int inputAddr, string actualOutcome) {

    //Table entries legend:
         // TT = strong taken
        // TN = weak taken
        // NT = weak not taken
        // NN = strong not taken

    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-binaryLength); //extract the last binaryLength bits from addr
    auto iteration = table.find(pcBits); //get index in map of pcBits entry

                    //cout << "pcBits = " << pcBits << " = table entry of " << iteration->first << endl;

    //consolidate strong and weak versions of prediction into a single predicton:
    string prediction;
    if(iteration->second == "TT" || iteration->second == "TN") {prediction = "T";}  //taken
    if(iteration->second == "NN" || iteration->second == "NT") {prediction = "NT";} //not taken (NOTE: "NT" in prediction table means "weak not taken"; actualOutcome of NT has no weak/strong affiliation.)

                    //cout << "based on table entry of " << iteration->second << ", overall prediction is " << prediction << endl;
                    //cout << "does actual outcome " << actualOutcome << " = " << prediction << "?" << endl;

    //compare prediction to actualOutcome:
    if(prediction == actualOutcome) {
        //make weak predictions stronger:

                    //cout << "prediction correct. table entry " << iteration->second;

        if(iteration->second == "TN") {iteration->second = "TT";}
        else if(iteration->second == "NT") {iteration->second = "NN";}

                    //cout << " updated to " << iteration->second << endl << endl;

        return true;
    }
    else {
        //update prediction for this pcBits:

                    //cout << "prediction wrong. table entry " << iteration->second;

        if(iteration->second == "NN") {iteration->second = "NT";}       //case: was strong not taken
        else if(iteration->second == "NT") {iteration->second = "TN";}  //case: was weak not taken
        else if(iteration->second == "TN") {iteration->second = "NT";}  //case: was weak taken
        else if(iteration->second == "TT") {iteration->second = "TN";}  //case: was strong not taken

                    //cout << " updated to " << iteration->second << endl << endl;

        return false;
    }
                    cout << "ERROR: bimodalTwoBit could not deduce prediction." << endl << endl;
    return false;
}