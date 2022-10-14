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

bimodalOneBit::bimodalOneBit(int inputSize) {
    tableSize = inputSize;
    binaryLength = getBinary(inputSize-1,0).length(); //get how long each binary table entry should be, using the maximum possible value
    cout << "each prediction table entry should be " << binaryLength << " bits long for a " << inputSize << " size table" << endl;
    
    for(int i = 0; i < tableSize; i++) { 
        table[getBinary(i,binaryLength)] = "T"; 
    }
};

bool bimodalOneBit::predict(long long unsigned int inputAddr, string actualOutcome) {
    
    //extract the table index to retrieve using addr:
    string pcBits = getBinary( inputAddr,0 ).substr( getBinary(inputAddr,0).length()-binaryLength); //extract the last tableSize bits from addr

    cout << "pcBits = " << pcBits << endl;

    //get taken/not taken based on pcBits:
    auto iterator = table.find(pcBits); //get index in map of pcBits entry
    cout << "Compare: " << iterator->second << " = " << actualOutcome << "?" << endl;

    //compare table entry to actual outcome:
    if(iterator->second == actualOutcome) {
        cout << "prediction correct" << endl << endl;
        return true;
    }
    else {
        cout << "predicton false; ";
        iterator->second = actualOutcome; //update prediction entry in table for this binary
        cout << "prediction is now " << iterator->second << endl << endl;
        return false;
    }

    return "";
};