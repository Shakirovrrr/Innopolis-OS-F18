#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int main() {
	DIR *tmpDir = opendir("tmp");
	if (!tmpDir) {
		perror("Failed to open directory.\n");
		return ENOENT;
	}

	struct dirent *dirEntry;
	struct stat entryStat;
	while ((dirEntry = readdir(tmpDir))) {
		char fileName[32];
		strcpy(fileName, "tmp/");
		strcat(fileName, dirEntry->d_name);
		if (stat(fileName, &entryStat)) {
			return ENOENT;
		}
		printf("%s - %lu\n", fileName, entryStat.st_ino);
	}
	closedir(tmpDir);

	return 0;
}