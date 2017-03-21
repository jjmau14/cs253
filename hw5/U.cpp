// Josh Mau
// Mar. 20, 2017
// U.cpp -- Test 'main' for U.h

#include <iostream>
#include <cstring>
#include "U.h"

using namespace std;

int main(int argc, char* argv[]){
	try {
		U test("UnicodeData.txt", "Hello there");
		U assignment_ctor_test;
		assignment_ctor_test = test;
		U copy_ctor_test(test);
		for ( auto a : test.props()){
			cout << a << ": " << test.propcount(a) << endl;	
		}
	}catch (const string error){
		cout << error << endl;
	}
}
