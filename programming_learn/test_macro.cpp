#include <iostream>


#ifdef _TEST_
void test()
{
    print("test function/n");
}
#else
#error("function test not defined")
#endif

using namespace std;

int main() {


	return 0;
}