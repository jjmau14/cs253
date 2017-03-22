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
		for ( auto a : test.props()){
			cout << a << ": " << test.propcount(a) << endl;	
		}
		cout << test.propcount("Sm") << endl;
		cout << test.size() << endl;
		cout << test.get(1) << endl;
	}catch (const string error){
		cout << error << endl;
	}
}
