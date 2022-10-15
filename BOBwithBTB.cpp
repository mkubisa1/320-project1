#include <string>
#include <map>
#include <iostream>
#include "BOBwithBTB.h"

using namespace std;

/*
BOBwithBTB::BOBwithBTB() { //default constructor
    tableSize = 16;
    binaryLength = getBinary(16-1,0).length(); //should be 4
    for(int i = 0; i < tableSize; i++) { 
        table[getBinary(i,binaryLength)] = "T"; 
    }
};
*/

BOBwithBTB::BOBwithBTB(int entriesCount) {
    tableSize = entriesCount;
    binaryLength = getBinary(entriesCount-1,0).length(); //get how long each binary table entry should be, using the maximum possible value
    
    
    for(int i = 0; i < tableSize; i++) { 
        table[getBinary(i,binaryLength)] = "T";     //initialize the prediction table
    }

};

bool BOBwithBTB::predictTarget(long long unsigned int inputAddr, string actualOutcome, long long unsigned int inputTarget) {
    
    //extract the table index to retrieve using addr:
    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-binaryLength); 

    //get taken/not taken based on pcBits:
    auto iterator = table.find(pcBits); 
    
    //branch target buffer
    bool btbResult;
    if(iterator->second == "T") {
        
        btbAttempts += 1;

        if(actualOutcome == "T") {
            if(btbTable[inputAddr] == inputTarget) {btbResult = true;}
            else {
                btbTable[inputAddr] = inputTarget;
                return btbResult = false;
            }
            
        }
    }

    //making prediction
    if(iterator->second != actualOutcome) {iterator->second = actualOutcome;}

    /*
    bool bobCorrect;    //holds the state of the bimodalOneBit prediction
    //compare table entry to actual outcome:
    if(iterator->second == actualOutcome) {
        bobCorrect = true;
    }
    else {
        iterator->second = actualOutcome; //update prediction entry in table for this binary
        bobCorrect = false;
    }
    */

    return btbResult;

    cout << "BOBwithBTB error: could not finish prediction. returning false." << endl;
    return false;
};