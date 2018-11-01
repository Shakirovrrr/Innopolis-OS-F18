#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>

#define CHARPOINTER char *) (long

int main() {
	char *mapSrc, *mapDst;
	struct stat srcStat;
	int srcOpen, dstOpen;

	srcOpen = open("ex1.txt", O_RDONLY);
	if (srcOpen < 0) {
		perror("Cannot open source file");
		return ENOENT;
	}

	if (stat("ex1.txt", &srcStat) < 0) {
		perror("Cannot get source file stats");
		return ENOENT;
	}

	dstOpen = open("ex1.memcpy.txt", O_RDWR | O_CREAT | O_TRUNC);
	if (dstOpen < 0) {
		perror("Cannot create destination file");
		return EEXIST;
	}

	size_t srcSize = (size_t) srcStat.st_size;
	ftruncate(srcOpen, srcSize);

	mapSrc = (CHARPOINTER) (mmap(0, srcSize, PROT_READ, MAP_SHARED, srcOpen, 0));
	if (mapSrc == MAP_FAILED) {
		perror("Cannot map source file");
		return EBADF;
	}

	mapDst = (CHARPOINTER) (mmap(0, srcSize, PROT_WRITE, MAP_SHARED, dstOpen, 0));
	if (mapDst == MAP_FAILED) {
		perror("Cannot map destination file");
		return EBADF;
	}

	memcpy(mapDst, mapSrc, srcSize);

	munmap(mapSrc, srcSize);
	munmap(mapDst, srcSize);
	close(srcOpen);
	close(dstOpen);

	return 0;
}