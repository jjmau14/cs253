#include "U.h"
#include "P.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(){
    try {
        U u;
        u.readfile("data");

		P p("UnicodeData.txt");
		
        for (int i = 0 ; i < u.size() ; i++)
            p.count(u.codepoint(i));
		
		if (u.size() == 9)
			cout << "Method U::size() : test passed" << endl;
		else 
			cout << "Method U::size() : test failed" << endl;
		
		if (p.count("Lu")  == 1)
			cout << "Method P::count(""Lu"") : test passed" << endl;
		else
			cout << "Method P::count(""Lu"") : test failed" << endl;

		if (p.size() == 29)
			cout << "Method P::size() : test passed" << endl;
		else
			cout << "Method P::size() : test failed" << endl;
		
		if (u.get() == "a 5 Ω ䷊ 🐮")
			cout << "Method U::get() : test passed" << endl;
		else
			cout << "Method U::get() : test failed\n"
			"Maybe a newline at the end of data?" << endl;
			
		p.clear();
		p.readfile("UnicodeData.txt");
		U u_copy(u);
		
		for (int i = 0 ; i < u_copy.size() ; i++)
            p.count(u_copy.codepoint(i));
		
		if (u_copy.size() == 9 && p.count("Ll") == 1 && p.size() == 29 && u_copy.get() == "a 5 Ω ䷊ 🐮")
			cout << "Copy Constructor : test passed" << endl;
		else
			cout << "Copy Constructor : test failed" << endl;
			
		const U const_copy(u);
		u = string("☮☮☮");
		U u2 = string("☮☮☮");
		
		if (u == u2)
			cout << "U::operator==(U) : test passed" << endl;
		else
			cerr << "U::operator==(U) : test failed" << endl;
		
		if (u != u2) // should be false
			cout << "U::operator!=(u) : test failed" << endl;
		else
			cout << "U::operator!=(u) : test passed" << endl;
		
		if (u == "☮☮☮")
			cout << "U::operator==(string) : test passed" << endl;
		else
			cout << "U::operator==(string) : test failed" << endl;
		
		if (u == "☮☮") // should be false
			cout << "U::operator!=(string) : test failed" << endl;
		else
			cout << "U::operator!=(string) : test passed" << endl;
		
		P p2;
		if (!p2) 
			cout << "P::operator bool() returns true: test passed" << endl;
		else 
			cout << "P::operator bool() : test failed" << endl;
		
		p2.readfile("UnicodeData.txt");
		
		if (!p2) // should be false
			cout << "P::operator bool() returns false: test failed" << endl;
		else 
			cout << "P::operator bool() returns false: test passed" << endl;
		
		for (int i = 0 ; i < u2.size() ; i++)
            p2.count(u2.codepoint(i));
		
		cout << p2 << endl;
    }catch(const string error){
        cout << error << endl;
    }
}
