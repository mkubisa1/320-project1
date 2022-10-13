#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <map>

#include "getBinary.h"
#include "bimodalOneBit.h"

using namespace std;

string alwaysTaken() {return "T";} //the "always taken" predictor

string neverTaken() {return "NT";} //the "never taken" predictor

int main(int argc, char *argv[]) {
    unsigned long long addr, target; string behavior;   //parsed information from input line stored in these variables
                                                            //addr = program counter value (hex address)
                                                            //behavior = branch taken (T) or not taken (NT)
                                                            //target = target of the branch (hex address)
    string line;                                        //line = current line of input file during while loop
    ifstream infile("test_input.txt");                  //text file where input lines come from
    ofstream outfile("output.txt");

    int ATcorrect = 0, NTcorrect = 0, BOBcorrect = 0;   //tallies of how many times each method predicted correctly

    bimodalOneBit bob(16);

    while(getline(infile, line)) {

        stringstream s(line);
        s >> std::hex >> addr >> behavior >> std::hex >> target; //extract each portion of the input line and place into necessary variables

        //assert correctness of each method:
        if(alwaysTaken() == behavior) {ATcorrect += 1;}
        if(neverTaken() == behavior) {NTcorrect += 1;}
        if(bob.predict(addr, behavior)) {BOBcorrect += 1;}

    }

    cout << "one bit bimodal was correct " << BOBcorrect << " times." << endl;

    return 0;
}

//todo: make it get "test_input.txt" from command line argument.