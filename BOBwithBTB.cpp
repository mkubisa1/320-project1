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
    
    //initialize bimodal table (all values = Taken)
    for(int i = 0; i < tableSize; i++) { 
        table[getBinary(i,binaryLength)] = "T";
    }

    //initialize BTB (all values = 0)
    for(int i = 0; i < tableSize; i++) {
        btbTable[getBinary(i,binaryLength)] = 0;
    }

};

void BOBwithBTB::predictTarget(long long unsigned int inputAddr, string actualOutcome, long long unsigned int inputTarget) {
    
    //get bimodal prediction by looking up the address in the bimodal table (store in bimodalPrediction):
    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-binaryLength);         //extract the table index to retrieve using addr:
    auto iterator = table.find(pcBits);                                                                     //get taken/not taken based on pcBits:
    string bimodalPrediction = iterator->second;
    
    //get the predicted PC from the branch target buffer (store in btbAddress):
    auto btbIterator = btbTable.find(pcBits);
    long long unsigned int btbAddress = btbIterator->second;

    //if the bimodal prediction is taken...
    
    if(bimodalPrediction == "T") {
        numPredictions++;                                                                                   //increment numPredictions
        
        //...and also the predicted target equals the actual target...
        if(btbAddress == inputTarget) { btbCorrect += 1; }  //increment count of correct branch predictions
    }

    //if the branch is taken...
    if(actualOutcome == "T") {
        btbIterator->second = inputTarget;  //update branch in BTB with actual target:
    }
    
    //update the bimodal predictor:
    if(iterator->second != actualOutcome) {iterator->second = actualOutcome;}

    
    /*
    bool bobCorrect;                                                                                        //holds the state of the bimodalOneBit prediction
    if(iterator->second == actualOutcome) {                                                                 //compare table entry to actual outcome:
        bobCorrect = true;
    }
    else {
        iterator->second = actualOutcome; //update prediction entry in table for this binary
        bobCorrect = false;
    }
    */
    
    
    /*
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
    */
};