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

		u = string("☮☮☮");
		
		U u2 = string("☮☮☮");
		
		if (u == u2)
			cout << "You Should See This" << endl;
		if (u != u2)
			cout << "You Should NOT See This" << endl;
		if (u == "☮☮☮")
			cout << "You Should See This" << endl;
		if (u == "☮☮")
			cout << "You Should NOT See This" << endl;
		
		P p2;
		if (!p2) cout << "You Should See this" << endl;
		
		p2.readfile("UnicodeData.txt");
		
		if (!p2) cout << "You Should NOT See this" << endl;
		cout << u2.size() << endl;
		
		for (int i = 0 ; i < u2.size() ; i++)
            p2.count(u2.codepoint(i));
		
		cout << p2;
    }catch(const string error){
        cout << error << endl;
    }
}
