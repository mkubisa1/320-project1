#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <map>

#include "getBinary.h"

using namespace std;

/*
string binary(unsigned long long n, int customLength) {
    string output;
    int binaryNumber[100], num=n;
    int i = 0;

    while (n > 0) {
        binaryNumber[i] = n % 2;
        n = n / 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        if(binaryNumber[j] == 0) {output += "0";}
        if(binaryNumber[j] == 1) {output += "1";}
    }

    //add trailing zeroes, if specified (parameter is 0 => don't do this)
    if(customLength > 0 && output.length() < customLength ) {
        while(output.length() < customLength) { //while the output is shorter than what we want...
            output = "0" + output;
        }
    }
    else if (output.length() > customLength && customLength != 0) {
        cout << "binary function warning: specified length exceeds custom length parameter. output result is unaltered." << endl;
    }

    return output;
}
*/


string alwaysTaken() {return "T";} //the "always taken" predictor

string neverTaken() {return "NT";} //the "never taken" predictor


string bimodalOneBit(string pcBits, map<string,string> table) {
    auto iterator = table.find(pcBits); //get index in map of pcBits entry
    return iterator->second;            //return the value in table associated with pcBits
}


int main(int argc, char *argv[]) {
    unsigned long long addr, target; string behavior;   //parsed information from input line stored in these variables
                                                            //addr = program counter value (hex address)
                                                            //behavior = branch taken (T) or not taken (NT)
                                                            //target = target of the branch (hex address)
    string line;                                        //line = current line of input file during while loop
    ifstream infile("test_input.txt");                  //text file where input lines come from
    ofstream outfile("output.txt");

    int ATcorrect = 0, NTcorrect = 0, BOBcorrect = 0;

    //populate oneBitBimodal table:
        map<string,string> preTableSixteen;
        for(int i = 0; i < 16; i++) {
            preTableSixteen[getBinary(i,4)] = "T";
        }

    while(getline(infile, line)) {
        //cout << line << endl;
        stringstream s(line);
        s >> std::hex >> addr >> behavior >> std::hex >> target; //extract each portion of the input line and place into necessary variables

        cout << getBinary(addr,0) << endl;
        cout << getBinary(addr,0).substr(getBinary(addr,0).length()-4, 4) << endl;
        cout << endl;

        if(alwaysTaken() == behavior) {ATcorrect += 1;}
        if(neverTaken() == behavior) {NTcorrect += 1;}
        //if( bimodalOneBit(get(addr,0).substr(get(addr,0).length()-4, 4), preTableSixteen) == behavior) {BOBcorrect += 1;}

    }
    //cout << "alwaysTaken() was correct " << ATcorrect << " times." << endl;
    //cout << "neverTaken() was correct " << NTcorrect << " times." << endl;

    return 0;
}

//todo: make it get "test_input.txt" from command line argument.