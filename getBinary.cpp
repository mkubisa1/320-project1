#include <string>
#include <iostream>
using namespace std;

#include "getBinary.h"

string getBinary(unsigned long long n, int customLength) {
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

int getDecimal(string str) {
   string n = str;
   int val = 0;
   int temp = 1;
   int len = n.length();
   for (int i = len - 1; i >= 0; i--) {
      if (n[i] == '1')
      val += temp;
      temp = temp * 2;
   }
   return val;
}