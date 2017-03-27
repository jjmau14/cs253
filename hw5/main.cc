// Josh Mau
// Mar. 20, 2017
// U.cpp -- Test 'main' for U.h

#include <iostream>
#include <cstring>
#include "U.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3)
        cout << "USAGE: ./a.out [Properties File] [Data file]" << endl;
    else{
	try {
		U test;
                test.propfile(argv[1]);
		test.readfile(argv[2]);
                
                U copy_test(test);
                U &assign_test = copy_test;
                
		cout << "Number of Lu: " << test.propcount("Lu") << endl;
		cout << "Size: " << test.size() << endl;
		cout << "At index 9: " << test.get(4,test.size()) << endl;
                
                cout << "Number of Lu: " << copy_test.propcount("Lu") << endl;
		cout << "Size: " << copy_test.size() << endl;
		cout << "At index 9: " << copy_test.get(4,copy_test.size()) << endl;
                
                cout << "Number of Lu: " << assign_test.propcount("Lu") << endl;
		cout << "Size: " << assign_test.size() << endl;
		cout << "At index 9: " << assign_test.get(4,assign_test.size()) << endl;
                
	}catch (const string error){
		cout << error << endl;
	}
    }
}
