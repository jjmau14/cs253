#include "U.h"
#include "P.h"
#include <iostream>

using namespace std;

int main(){
    try {
        U u;
        u.append("a³+b³≠c³");
        P p("UnicodeData.txt");
        for (int i = 0 ; i < u.size() ; i++)
            p.count(u.codepoint(i));
        cout << "should be 8: " << u.size() << '\n'
            << "Should be 2: " << p.count("Sm") << '\n'
            << "Should be b³: " << u.get(3,5) << "\n\n";
    }catch(...){
        cout << "caught an error!" << endl;
    }
}