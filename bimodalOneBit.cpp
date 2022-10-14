#include <string>
#include <map>
#include <iostream>
#include "bimodalOneBit.h"

using namespace std;

bimodalOneBit::bimodalOneBit() { //default constructor
    tableSize = 16;
    binaryLength = getBinary(16-1,0).length(); //should be 4
    for(int i = 0; i < tableSize; i++) { 
        table[getBinary(i,binaryLength)] = "T"; 
    }
};

bimodalOneBit::bimodalOneBit(int entriesCount) {
    tableSize = entriesCount;
    binaryLength = getBinary(entriesCount-1,0).length(); //get how long each binary table entry should be, using the maximum possible value
    //cout << "each prediction table entry should be " << binaryLength << " bits long for a " << entriesCount << " size table" << endl;
    
    for(int i = 0; i < tableSize; i++) { 
        table[getBinary(i,binaryLength)] = "T"; 
    }
};

bool bimodalOneBit::predict(long long unsigned int inputAddr, string actualOutcome) {
    
    //extract the table index to retrieve using addr:
    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-binaryLength); 

    //get taken/not taken based on pcBits:
    auto iterator = table.find(pcBits); //get index in map of pcBits entry

    //compare table entry to actual outcome:
    if(iterator->second == actualOutcome) {
        return true;
    }
    else {
        iterator->second = actualOutcome; //update prediction entry in table for this binary
        return false;
    }

    return "";
};