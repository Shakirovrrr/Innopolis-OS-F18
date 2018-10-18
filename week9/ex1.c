/*
 * Aging memory page replacement
 * algorithm simulation.
 *
 * Author: Ruslan Shakirov
 */

#include <stdio.h>
#include <stdlib.h>

#define FIRST_BIT_ONLY UINT_MAX ^ ((unsigned int) INT_MAX)

typedef struct PageFrame {
	unsigned int pageRef;
	unsigned int age;
	unsigned char R;
} PageFrame;

static FILE *inputFile;
unsigned int refCount, hitCount, nFrames;
PageFrame *frames;

unsigned int nextRef() {
	unsigned int ref;
	int scanned = fscanf(inputFile, "%d ", &ref);
	if (scanned == -1) {
		return 0;
	}

	return ref;
}

PageFrame makeEmptyFrame() {
	PageFrame frame;
	frame.pageRef = 0;
	frame.age = 0;
	frame.R = 0;

	return frame;
}

PageFrame makeFrame(unsigned int pageRef) {
	PageFrame newFrame;
	newFrame.pageRef = pageRef;
	newFrame.age = FIRST_BIT_ONLY; // Sets leftmost bit to 1 and other to 0.
	newFrame.R = 1;

	return newFrame;
}

PageFrame *initFrames(unsigned int nFrames) {
	PageFrame *frames = (PageFrame *) calloc(nFrames, sizeof(PageFrame));
	for (int i = 0; i < nFrames; ++i) {
		frames[i] = makeEmptyFrame();
	}

	return frames;
}

char isEmptyFrame(PageFrame frame) {
	return frame.pageRef == 0 && frame.age == 0;
}

PageFrame *getFrameByRef(unsigned int ref, PageFrame *fromFrames) {
	for (int i = 0; i < nFrames; ++i) {
		if (fromFrames[i].pageRef == ref) {
			return fromFrames + i;
		}
	}

	return NULL;
}

PageFrame *getFreeFrame(PageFrame *fromFrames) {
	for (int i = 0; i < nFrames; ++i) {
		if (isEmptyFrame(fromFrames[i])) {
			return fromFrames + i;
		}
	}

	return NULL;
}

PageFrame *getOldestFrame(PageFrame *fromFrames) {
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
	static unsigned int minCount, maxCount;

	// Try to fetch frame by ref
	PageFrame *currentFrame = getFrameByRef(pageRef, frames);
	if (currentFrame) {
		currentFrame->R = 1;
		hitCount++;
		refCount++;
		return;
	}

	// If not found, try to fetch free frame
	currentFrame = getFreeFrame(frames);
	if (!currentFrame) {
		// If there are no more free frames
		// fetch oldest
		currentFrame = getOldestFrame(frames);
	}
	if (currentFrame) {
		*currentFrame = makeFrame(pageRef);
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
	frames = initFrames(nFrames);

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