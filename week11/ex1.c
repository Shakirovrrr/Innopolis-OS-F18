#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main() {
	char *mapped;
	struct stat fileStat;
	int fileOpen;

	if ((fileOpen = open("ex1.txt", O_RDWR)) < 0) {
		perror("Cannot open file");
		return ENOENT;
	}

	if (stat("ex1.txt", &fileStat) < 0) {
		perror("Cannot get file stats");
		return ENOENT;
	}

	size_t fileSize = (size_t) fileStat.st_size;
	char *niceDay = "This is a nice day";
	size_t niceLen = strlen(niceDay);
	if (fileSize < niceLen) {
		fileSize = niceLen;
	}

	if ((mapped = (char *) (long) (mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fileOpen, 0))) ==
	    MAP_FAILED) {
		perror("Cannot map the file to the memory");
		return EBADF;
	}

	memset(mapped, ' ', fileSize);
	strcpy(mapped, niceDay);
	mapped[niceLen] = ' ';
	munmap(mapped, fileSize);

	return 0;
}