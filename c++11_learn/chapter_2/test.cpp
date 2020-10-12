#include <iostream>
#include <vector>
#include <ext/pool_allocator.h>
#include <deque>
#include <algorithm>

using namespace std;

int main() {

    vector<string, __gnu_cxx::__pool_alloc<string>> hello{"kaka", "bubu", "lala"};
    for (const auto &item : hello) {
        cout << "item is " << item << endl;
    }

    vector<int, __gnu_cxx::__pool_alloc<int>> kaka{3, 5, 6, 7, 7};


    deque<string> dequeTetst;

    dequeTetst.begin();


    return 0;
}