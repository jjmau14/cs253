#include <iostream>
#include "U.h"
#include <iomanip>

using std::cout;
using std::endl;
using std::hex;

int main(){
	U u("∆ß jsß˚˚∑˜åµ¬˚µœµ˜ºˆÅ∏ÅØ ˆˆØÔÍ ·°Í·°ŒÔLKµåµ");
	for (auto x : u){
		cout << "0x" << hex << x << " ";
	}
	cout << endl;
}