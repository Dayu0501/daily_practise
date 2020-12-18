#include <iostream>
#include <algorithm>

using namespace std;

std::string deleteMarks(string& des, char x) {
	des.erase(remove(des.begin(), des.end(), x), des.end());

	return des;
}

int main() {

	string hel = "hello world    china !   ";

	cout << "res = " << deleteMarks(hel, ' ') << endl;
	cout << "hel len = " << hel.length() << endl;

	return 0;
}