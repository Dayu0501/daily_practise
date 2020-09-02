#include "algorithmUnity.h"
#include "myalloc.h"

void test_DY_remove () {
	cout << "test remove start !" << endl;
	string testDate_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testDate_0 << endl;
	cout << "Need to delete is " << b << endl;

	testDate_0.erase(DY_remove(testDate_0.begin(), testDate_0.end(), b), testDate_0.end());

	cout << "result = " << testDate_0 << endl;
}

int main() {

#ifdef DY_REMOVE
	test_DY_remove();
#endif

	vector<string, my_alloc::allocator<string>> ins {"hello", "world"};



	return 0;
}