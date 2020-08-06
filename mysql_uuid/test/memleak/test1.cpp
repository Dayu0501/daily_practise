//
// Created by yulichao on 2020/7/30.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {
    
    char hello[100]{0}; 
    while (true) {
    cout << "test " << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	void * tmpPtr = (void *)malloc(1024 * 1024  * 10);
    memcpy(tmpPtr, hello, sizeof(hello));

    printf("hello size is %ld", sizeof(hello));
        

    }

    return 0;
}


