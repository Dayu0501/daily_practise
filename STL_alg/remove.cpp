#include "algorithmUnity.h"

int main() {

	cout << "test remove start !" << endl;
	string testDate_0 = "465875906556";
	char b = '5';

	cout << "operation data is " << testDate_0 << endl;
	cout << "Need to delete is " << b << endl;

	testDate_0.erase(DY_remove(testDate_0.begin(), testDate_0.end(), b), testDate_0.end());

	cout << "result = " << testDate_0 << endl;

	return 0;
}