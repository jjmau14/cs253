// Josh Mau
// Mar. 20, 2017
// U.cpp -- Test 'main' for U.h

#include <iostream>
#include <cstring>
#include "U.h"

using namespace std;

int main(int argc, char* argv[]){
	try {
		U test(argv[1], argv[2]);
		U assignment_ctor_test;
		assignment_ctor_test = test;
		U copy_ctor_test(test);

		cout << "Number of Lu: " << test.propcount("Lu") << endl;
		cout << "Size: " << test.size() << endl;
		cout << "At index 1: " << test.get(1) << endl;
	}catch (const string error){
		cout << error << endl;
	}
}
