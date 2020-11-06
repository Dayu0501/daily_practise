#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
	std::string oldName = "./open_1.txt";
	std::string newName = "./open_1_new.txt";

	if (!rename(oldName.c_str(), newName.c_str())) {
		std::cout << "rename success " << std::endl;
	} else {
		std::cout << "rename error " << std::endl;
	}

	std::string str{"0"};

	std::cout << "str length is " << str.length() << std::endl;

	return 0;
}