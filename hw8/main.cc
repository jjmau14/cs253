#include "U.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(){
    try {
        U u("ABC 123");
        
    }catch(const string error){
        cout << error << endl;
    }
}
