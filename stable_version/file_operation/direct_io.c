#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define BUF_SIZE  1

int main(int argc, char **argv) {
	char *buf = NULL;
	const char *filename = "./write.txt";
	int fd = -1;
	time_t start, cur;
	int rlen = 0, ret = 0;
	static int read_total = 0;
	buf = (char *)malloc(BUF_SIZE);

	buf += 2;

	/* 申请512字节对齐的内存地址，空间大小是512个字节 */
	//ret = posix_memalign((void **) &buf, 512, BUF_SIZE);


	if (buf) fprintf(stderr, "posix_memalign failed. reason: %s\n", strerror(errno));

	//fsync(fd);
	start = time(NULL);

	do {
		read_total++;
		fd = open(filename, O_RDWR | O_DIRECT);
		//fd = open(filename, O_RDWR);
		if (fd < 0) {
			fprintf(stderr, "fopen %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
			return -1;;
		}

		do {
			//sleep(1);
			if ((rlen = read(fd, buf, BUF_SIZE)) < 0) {
				fprintf(stderr, "read from %s failed, reason: %s. \nexit.\n", filename, strerror(errno));
			}
			printf("read: %d\n", rlen);
		} while (rlen > 0);
		printf(" finished.\n");
		close(fd);

		cur = time(NULL);

	} while ((cur - start) < 20);
	printf("total num: %d\n", read_total);

	return 0;
}
