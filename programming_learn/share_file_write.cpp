#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using namespace std;

char a[512];
char b[16];

int main() {
	int fd;

	memset(a, 'a', 512);
	memset(b, '-', 16);

	fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0660);
	cout << "fd  = "  << fd << endl;

	if (fork() == 0) {
		cout << "child process !" << endl;
		prctl(PR_SET_NAME, (unsigned long) "child");

		write(fd, b, 16);

		exit(0);
	}
	cout << "parent process !" << endl;

	write(fd, a, 512);
	exit(0);
}