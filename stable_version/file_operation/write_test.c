#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TOTAL  10000

int writeToFile(int fd, char *buf, int len) {
	int wlen = 0;
	if ((wlen = write(fd, buf, len)) < 0) {
		fprintf(stderr, "write to %d failed, reason: %s. \n", fd, strerror(errno));
		return -1;
	}
	//fsync(fd);

	return wlen;
}

int main(int argc, char **argv) {
	const char *TEXT = "This is a test.\n";
	const char *filename = "./write.txt";
	int fd = -1;
	int i = 0;

	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT);
	if (fd < 0) {
		fprintf(stderr, "fopen %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
		return -1;;
	}

	printf("Start to sleep 10 seconds\n");
	for (i = 0; i < TOTAL; i++) {
		//sleep(1);
		if (writeToFile(fd, TEXT, strlen(TEXT)) < 0) {
			fprintf(stderr, "write to %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
		}

		printf(" %d\n", i + 1);
	}
	printf(" finished.\n");
	int ret = fsync(fd);
	if (ret) fprintf(stderr, "write failed. reason: %s\n", strerror(errno));
	sleep(30);

	close(fd);
	return 0;
}