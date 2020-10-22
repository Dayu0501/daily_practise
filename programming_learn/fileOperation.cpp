#include<iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int display_file(int fd, int count) {
	char buffer[100];
	memset(buffer, 0, sizeof(buffer));
	if (0 > fd || 0 >= count)
		return -1;
	int read_num = read(fd, buffer, count);
	if (read_num < 0) {
		printf("read file failed !\n");

		return -1;
	}


	printf("file content is ::: %s\n", buffer);
	return read_num;
}

int main(int argc, char *argv[]) {
	int fd = 0;

	fd = open("./open_1.txt", _O_RDWR);
	printf("fd = %d \r\n", fd);
	display_file(fd, 1024);

	cout << "开始休眠......" << endl;
	sleep(10);
	cout << "休眠结束......" << endl;



	close(fd);

	return 0;
}