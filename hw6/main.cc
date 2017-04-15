#include "U.h"
#include "P.h"
#include <iostream>

using namespace std;

int main(){
    try {
        U u;
        u.readfile("data");
        U u_copy(u);

		P p("UnicodeData.txt");
		
        for (int i = 0 ; i < u.size() ; i++)
            p.count(u.codepoint(i));
		
        cout << "u:\nShould be 9: " << u.size() << '\n'
            << "Should be 1: " << p.count("Lu") << '\n'
            << "Number of Properties: " << p.size() << '\n'
            << "Accumulated String: " << u.get() << "\n\n";
			
		p.clear();
		p.readfile("UnicodeData.txt");
		for (int i = 0 ; i < u_copy.size() ; i++)
            p.count(u_copy.codepoint(i));
		cout << "u_copy:\nShould be 9: " << u_copy.size() << '\n'
            << "Should be 1: " << p.count("Ll") << '\n'
            << "Number of Properties: " << p.size() << '\n'
            << "Accumulated String: " << u_copy.get() << "\n\n";
			
		const U const_copy(u);
		u.append("aa  3");
			
    }catch(const string error){
        cout << error << endl;
    }
}