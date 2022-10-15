#include <string>
#include <map>
#include <iostream>
#include <cmath>
#include "gShare.h"
using namespace std;

gShare::gShare(int ghrAccuracy) {
    GHR = getBinary(0,ghrAccuracy);                                     //initialize GHR to all zeroes
    for(int i = 0; i < 2048; i++) { table[getBinary(i,11)] = "TT"; }    //initialize all table entries to Strongly Taken. Populate with every 11 bit number from 0 to 2047.

}

bool gShare::predict(long long unsigned int inputAddr, string actualOutcome) {

    //construct tableIndex using inputAddr and GHR:
    string pcBits = getBinary(inputAddr,0).substr( getBinary(inputAddr,0).length()-GHR.length(), GHR.length() );    //get lower GHR.length() bits of inputAddr
    string pcXOR;
    for (int i = 0; i < GHR.length(); i++) {                                                                        //perform XOR and store result in pcXOR 
        if(pcBits.at(i) == GHR.at(i)) { pcXOR += "0"; }
        else { pcXOR += "1"; }
    }
    string tableIndex = getBinary(inputAddr,0);                                                                     //initialize tableIndex to the binary of inputAddr
    tableIndex = tableIndex.substr(tableIndex.length()-11, 11);    //shorten tableIndex to its last 11 bits
    tableIndex.erase( tableIndex.length()-pcXOR.length(), pcXOR.length() );                                         //remove last pcXOR bits from tableIndex
    tableIndex += pcXOR;                                                                                            //append XOR result to get final tableIndex

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

bool gShare::predict(string pcBitsFull, string actualOutcome) {

    string pcBits = pcBitsFull.substr( pcBitsFull.length()-GHR.length(), GHR.length() );    //get lower GHR.length() bits of fullpcbits

    //construct tableIndex using inputAddr and GHR:
    string pcXOR;
    for (int i = 0; i < GHR.length(); i++) {                                                                        //perform XOR and store result in pcXOR 
        if(pcBits.at(i) == GHR.at(i)) { pcXOR += "0"; }
        else { pcXOR += "1"; }
    }
    string tableIndex = pcBits;                                                                     //initialize tableIndex to the binary of pcBits
    tableIndex = tableIndex.substr(tableIndex.length()-11, 11);    //shorten tableIndex to its last 11 bits
    tableIndex.erase( tableIndex.length()-pcXOR.length(), pcXOR.length() );                                         //remove last pcXOR bits from tableIndex
    tableIndex += pcXOR;                                                                                            //append XOR result to get final tableIndex

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