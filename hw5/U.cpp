// Josh Mau
// Mar. 20, 2017
// U.cpp -- Test 'main' for U.h

#include <iostream>
#include <cstring>
#include "U.h"

using namespace std;

int main(int argc, char* argv[]){
	try {
		U test;
                test.propfile(argv[1]);
		test.readfile(argv[2]);
		cout << "Number of Lu: " << test.propcount("Lu") << endl;
		cout << "Size: " << test.size() << endl;
		cout << "At index 9: " << test.get(8) << endl;
	}catch (const string error){
		cout << error << endl;
	}
}
