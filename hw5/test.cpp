#include "U.h"
    #include <iostream>
    using namespace std;
    int main() {
        U foo("UnicodeData.txt", "a³+b³≠c³");
        cout << "Size hould be 8: " << foo.size() << '\n'
             << "Count of Sm should be 2: " << foo.propcount("Sm") << '\n'
             << "String from (3,5) should be b³: " << foo.get(3,5) << '\n';
        return 0;
    }