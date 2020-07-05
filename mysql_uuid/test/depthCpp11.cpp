//
// Created by Administrator on 2020/7/5.
//

#include <vector>
#include <list>

using namespace std;

enum class myType {
    _today,
    _tomorrow
};

int main() {
    vector<list<int> > hello;
    //int x = myType::_today;       //98标准是准许的，11标准是不准许的。
    //myType y = 1;                 //98标准是准许的，11标准是不准许的。
    myType z = myType::_tomorrow;   //98标准不准许，11标注准许



    return 0;
}
