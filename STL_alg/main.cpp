#include "algorithmUnity.h"
#include "myalloc.h"

void test_DY_remove () {
	cout << "test remove start !" << endl;
	string testData_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testData_0 << endl;
	cout << "Need to delete is " << b << endl;

    testData_0.erase(DY_remove(testData_0.begin(), testData_0.end(), b), testData_0.end());

	cout << "result = " << testData_0 << endl;
}

void test_DY_remove_if() {
    cout << "test remove_copy_if test" << endl;

    string testData_0 {"465 87 5906 556"};
    cout << "operation data is " << testData_0 << endl;

    testData_0.erase(DY_remove_if(testData_0.begin(), testData_0.end(), [](unsigned char x){ return std::isspace(x); }), testData_0.end());

    cout << "result = " << testData_0 << endl;
}

#define DY_REMOVE_IF

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

#ifdef DY_REMOVE_IF
    test_DY_remove_if();
#endif



	return 0;
}