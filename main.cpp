#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <map>

#include "getBinary.h"
#include "bimodalOneBit.h"
#include "bimodalTwoBit.h"
#include "gShare.h"

using namespace std;

string alwaysTaken() {return "T";} //the "always taken" predictor

string neverTaken() {return "NT";} //the "never taken" predictor

int main(int argc, char *argv[]) { //to run program: ./predictors test_input.txt output.txt

    unsigned long long addr, target; string behavior;   //parsed information from input line stored in these variables
                                                            //addr = program counter value (hex address)
                                                            //behavior = branch taken (T) or not taken (NT)
                                                            //target = target of the branch (hex address)
    string line;                                        //line = current line of input file during while loop
    ifstream infile(argv[1]);                           //text file where input lines come from
    ofstream outfile(argv[2]);

    int correctCount[27]; for(int i = 0; i < 27; i++){correctCount[i] = 0;}     // create and initialize tallies for correct predictions
                                                                                // [0] = always taken
                                                                                // [1] = always not taken
                                                                                // [2] to [8] = bimodalOneBit
                                                                                // [9] to [15] = bimodalTwoBit
                                                                                // [16] to [24] = gShare
                                                                                // [25] = torunament predictor
                                                                                // [26] = BTB statistics

    bimodalOneBit bob16(16), bob32(32), bob128(128), bob256(256), bob512(512), bob1024(1024), bob2048(2048);
    bimodalTwoBit btb16(16), btb32(32), btb128(128), btb256(256), btb512(512), btb1024(1024), btb2048(2048);
    gShare gs(3);
    int instCount = 0; //the number of instructions/lines in infile

    while(getline(infile, line)) {

        instCount += 1;

        stringstream s(line);
        s >> std::hex >> addr >> behavior >> std::hex >> target; //extract each portion of the input line and place into necessary variables

        /*
        //assert correctness of each method:
        cout << "running alwaysTaken()..." << endl;
        if(alwaysTaken() == behavior) {correctCount[0] += 1;}
        cout << "running alwaysNotTaken()..." << endl;
        if(neverTaken() == behavior) {correctCount[1] += 1;}

        cout << "running bimodalOneBit()..." << endl;
        if(bob16.predict(addr, behavior))   {correctCount[2] += 1;}
        if(bob32.predict(addr, behavior))   {correctCount[3] += 1;}
        if(bob128.predict(addr, behavior))  {correctCount[4] += 1;}
        if(bob256.predict(addr, behavior))  {correctCount[5] += 1;}
        if(bob512.predict(addr, behavior))  {correctCount[6] += 1;}
        if(bob1024.predict(addr, behavior)) {correctCount[7] += 1;}
        if(bob2048.predict(addr, behavior)) {correctCount[8] += 1;}

        cout << "running bimodalTwoBit()..." << endl;
        if(btb16.predict(addr, behavior))   {correctCount[9] += 1;}
        if(btb32.predict(addr, behavior))   {correctCount[10] += 1;}
        if(btb128.predict(addr, behavior))  {correctCount[11] += 1;}
        if(btb256.predict(addr, behavior))  {correctCount[12] += 1;}
        if(btb512.predict(addr, behavior))  {correctCount[13] += 1;}
        if(btb1024.predict(addr, behavior)) {correctCount[14] += 1;}
        if(btb2048.predict(addr, behavior)) {correctCount[15] += 1;}
        */
    }
    infile.close();
    
    outfile << correctCount[0] << "," << instCount << ";" << endl;                          //alwaysTaken
    outfile << correctCount[1] << "," << instCount << ";" << endl;                          //alwaysNotTaken
    for(int i = 2; i < 9; i++) { outfile << correctCount[i] << "," << instCount << "; ";}   //bimodalOneBit
    outfile << endl;
    for(int i = 9; i < 16; i++) { outfile << correctCount[i] << "," << instCount << "; ";}  //bimodalTwoBit
    outfile << endl;

    outfile.close();

    return 0;
}