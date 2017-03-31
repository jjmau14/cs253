#include "U.h"
#include "P.h"
#include <iostream>

using namespace std;

int main(){
    try {
        U u;
        u.readfile("data");
        u.append("a³+b³≠c³");
        P p("UnicodeData.txt");
        for (int i = 0 ; i < u.size() ; i++)
            p.count(u.codepoint(i));
        cout << "Should be 17: " << u.size() << '\n'
            << "Should be 1: " << p.count("Lu") << '\n'
            << "Size of P: " << p.size() << '\n'
            << "Accumulated String: " << u.get() << "\n\n";
    }catch(const string error){
        cout << error << endl;
    }
}