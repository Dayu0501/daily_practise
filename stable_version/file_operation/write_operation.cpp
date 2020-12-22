/*
 * 标准的写文件操作函数，处理了异常的情况
 * 写文件时的异常情况
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cerrno>
#include <fcntl.h>


#define  BUFSIZE   1024
#define  SUCCESS   0
#define  FAILURE   -1

int write_to_file(int fd, const char *buf, const size_t nbytes) {
	size_t left = nbytes;
	size_t written_len = 0;
	const char *pTmp = buf;

	while (left > 0) {
		written_len = write(fd, pTmp, left);

		if (written_len < 0) {
			written_len = -errno;

			if (written_len == EINTR || written_len == EAGAIN) {
				continue;
			}
			if (written_len == EBADF) {
				/* 重新open 这个文件，对它进行重写 */
				break;
			}

			fprintf(stderr, "write failed. reason:%s\n", strerror(errno));
			return FAILURE;

		} else if (0 == written_len) {
			break;
		}

		left -= written_len;
		pTmp += written_len;
	}

	if (0 != left) return FAILURE;
	return SUCCESS;
}


int main(int argc, char **argv) {

	int fd = 0;

	fd = open("./demo.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);

	if (fd == -1) {
		fprintf(stderr, "open failed.reason: %s\n", strerror(errno));
		exit(-1);
	}

	off_t size = lseek(fd, 0, SEEK_END);
	char buf[BUFSIZE];
	int ret = 0;
	int i = 0;

	memset(buf, '8', BUFSIZE);

	for (i = 0; i < 10; i++) {
		ret = write_to_file(fd, buf, BUFSIZE);
		if (ret == FAILURE) {
			//log
			break;
		}
	}

	close(fd);
	return 0;

}

