#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_ENTRIES 128

typedef struct {
	ino_t iNodeNum;
	char names[128];
	nlink_t nLinks;
} FileEntry;

FileEntry newFileEntry(ino_t iNodeNum, char *name) {
	FileEntry entry;
	entry.iNodeNum = iNodeNum;
	strcpy(entry.names, name);
	entry.nLinks = 1;

	return entry;
}

int main() {
	DIR *tmpDir = opendir("tmp");
	if (!tmpDir) {
		perror("Failed to open directory.\n");
		return ENOENT;
	}

	struct dirent *dirEntry;
	struct stat entryStat;
	FileEntry entries[MAX_ENTRIES];
	unsigned int entryCount = 0;
	while ((dirEntry = readdir(tmpDir))) {
		// Concat "tmp/" + file name
		char fileName[32];
		strcpy(fileName, "tmp/");
		strcat(fileName, dirEntry->d_name);

		if (stat(fileName, &entryStat)) {
			return ENOENT;
		}

		char found = 0;
		for (int i = 0; i < entryCount; ++i) {
			if (entries[i].iNodeNum == entryStat.st_ino) {
				strcat(strcat(entries[i].names, ", "), dirEntry->d_name);
				entries[i].nLinks++;
				found = 1;
				break;
			}
		}
		if (!found) {
			if (entryCount >= MAX_ENTRIES) {
				return EAGAIN;
			}
			entries[entryCount] = newFileEntry(entryStat.st_ino, dirEntry->d_name);
			entryCount++;
		}
	}
	closedir(tmpDir);

	FILE *outFile = fopen("ex4.txt", "w");
	for (int j = 0; j < entryCount; ++j) {
		if (entries[j].nLinks > 1) {
			fprintf(outFile, "I-node %lu ", entries[j].iNodeNum);
			fprintf(outFile, "has %lu links: ", entries[j].nLinks);
			fprintf(outFile, "%s\n", entries[j].names);
		}
	}
	fclose(outFile);

	return 0;
}