// Josh Mau
// Mar. 20, 2017
// U.cpp -- Test 'main' for U.h

#include <stdio.h>
#include <cstring>
#include "U.h"

using namespace std;

int main(int argc, char* argv[]){
	try {
		const U test("cantopen.txt", "Hello there");
		for ( auto a : test.props()){
			cout << a << ": " << test.propcount(a) << endl;	
		}
	}catch (const string error){
		cout << error << endl;
	}
}
