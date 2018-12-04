/*
 * Aging memory page replacement
 * algorithm simulation.
 *
 * Author: Ruslan Shakirov
 */

#include <stdio.h>
#include <limits.h>
#include <malloc.h>

#define FIRST_BIT_ONLY (UINT_MAX ^ ((unsigned int) INT_MAX))

typedef struct __PageEntry {
	unsigned int pageRef;
	unsigned int age;
	unsigned char R;
} PageEntry;

static FILE *inputFile;
unsigned int refCount, hitCount, nFrames;
PageEntry *frames;

unsigned int nextRef() {
	unsigned int ref;
	int scanned = fscanf(inputFile, "%d ", &ref);
	if (scanned == -1) {
		return 0;
	}

	return ref;
}

PageEntry createEmptyEntry() {
	PageEntry frame;
	frame.pageRef = 0;
	frame.age = 0;
	frame.R = 0;

	return frame;
}

PageEntry createEntry(unsigned int pageRef) {
	PageEntry newFrame;
	newFrame.pageRef = pageRef;
	newFrame.age = FIRST_BIT_ONLY; // Sets leftmost bit to 1 and other to 0.
	newFrame.R = 1;

	return newFrame;
}

PageEntry *initEntries(unsigned int nFrames) {
	PageEntry *frames = (PageEntry *) calloc(nFrames, sizeof(PageEntry));
	for (int i = 0; i < nFrames; ++i) {
		frames[i] = createEmptyEntry();
	}

	return frames;
}

char isEmptyEntry(PageEntry frame) {
	return frame.pageRef == 0 && frame.age == 0;
}

PageEntry *getEntryByRef(unsigned int ref, PageEntry *fromFrames) {
	for (int i = 0; i < nFrames; ++i) {
		if (fromFrames[i].pageRef == ref) {
			return fromFrames + i;
		}
	}

	return NULL;
}

PageEntry *getFreeEntry(PageEntry *fromFrames) {
	for (int i = 0; i < nFrames; ++i) {
		if (isEmptyEntry(fromFrames[i])) {
			return fromFrames + i;
		}
	}

	return NULL;
}

PageEntry *getOldestEntry(PageEntry *fromFrames) {
	unsigned int minAge = UINT_MAX;
	int iMin = 0;

	for (int i = 0; i < nFrames; ++i) {
		if (fromFrames[i].age < minAge) {
			minAge = fromFrames[i].age;
			iMin = i;
		}
	}

	return fromFrames + iMin;
}

void insertPage(unsigned int pageRef) {
	// Try to fetch frame by ref
	PageEntry *currentFrame = getEntryByRef(pageRef, frames);
	if (currentFrame) {
		currentFrame->R = 1;
		hitCount++;
		refCount++;
		return;
	}

	// If not found, try to fetch free frame
	currentFrame = getFreeEntry(frames);
	if (!currentFrame) {
		// If there are no more free frames
		// fetch oldest
		currentFrame = getOldestEntry(frames);
	}
	if (currentFrame) {
		*currentFrame = createEntry(pageRef);
		refCount++;
		return;
	}

}

void shiftAges() {
	for (int i = 0; i < nFrames; ++i) {
		frames[i].age >>= 1; // Shift bits
		frames->age |= FIRST_BIT_ONLY * ((unsigned int) frames[i].R);
		frames[i].R = 0;
	}
}

int main() {
	refCount = 0;
	hitCount = 0;

	scanf("%d", &nFrames);
	frames = initEntries(nFrames);

	inputFile = fopen("input.txt", "r");
	if (!inputFile) {
		perror("Cannot open file.\n");
		return 0;
	}

	unsigned int ref;
	ref = nextRef();
	while (ref) {
		if (refCount % nFrames == 0) {
			shiftAges();
		}
		insertPage(ref);
		ref = nextRef();
	}

	printf("Hits: %d\nTotal: %d\n", hitCount, refCount);
	printf("Hit rate: %f", hitCount / (float) refCount);

	return 0;
}