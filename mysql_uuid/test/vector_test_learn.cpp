//
// Created by yulichao on 2020/7/27.
//
/*
 * 对于vector在遍历过程中，插入一个对象的话，会出现问题。
 * */



#include <iostream>
#include <vector>

using namespace std;


int main() {

    vector<string> hello{"wang", "zhou", "li", "zhao", "cui", "guo"};

    for (const auto& item : hello) {
        cout << "item is " << item << ", hello size is " << hello.size() << endl;
        if (item == "zhao") {
            hello.emplace_back("xin");
        }
    }


    return 0;
    curStamp
