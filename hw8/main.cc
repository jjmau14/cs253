#include "U.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::hex;
using std::showbase;
using std::endl;

int main() {
    const char s[] = "\U0001f382 × 11 \u21d2 9\u00be";

    U u(s, s+sizeof(s)-1);
    assert(u == "\U0001f382 × 11 \u21d2 9\u00be");
    cout << u << '\n';			// 🎂 × 11 ⇒ 9¾

    assert(u.front() == 0x1f382);		// birthday cake
    assert(u.back() == 0xbe);		// three-quarters
    U::iterator it = u.begin();
    cout << *it << endl;
    assert(*it == 0x1f382);			// birthday cake
    it++;
    assert(*it == ' ');
    it = u.end();

    --it;
    assert(*it == 0xbe);			// ¾
    for (auto cp : u)
        cout << hex << showbase << cp << ' ';
    cout << '\n';
}