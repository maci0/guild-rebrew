/*
 * Room building alignment probe.
 *
 * Collects the ground height range of the room map, samples four world
 * points around the mid height, and derives axis aligned bounds from them.
 * A global tuning object can replace the four sample points; without it the
 * bounds are taken from the samples and the distance scan is skipped.
 * When arg2 is 0 the low bound feeds the result, otherwise the high bound.
 * A positive outcome moves the building by that bound minus the map low
 * height, marks it aligned (flag 0x04) and returns 0; every rejection
 * returns 1.
 */

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef struct S143b0Box {
	char* obj;
	float lo;
	float hi;
	float level;
	float loAligned;
	float hiAligned;
	float pt[4][4];
	float minX;
	float loX;
	float minY;
	float unused64;
	float maxX;
	float hiX;
	float maxY;
} S143b0Box;

char __cdecl fcn_004458e0(char*, int);
void __cdecl fcn_00438d70(char*, int, int, int);
int __cdecl fcn_004133e0(char*, float*, float*);
int __cdecl fcn_00413480(char*, float, float*, float*, float*, float*);
int __cdecl fcn_00413c40(char*, float*, float*, float*, float*, float*, float*);
int __cdecl fcn_00413fb0(S143b0Box*, char*);

/* ADDRESS: GOLDTL 0x004143b0 */
int __cdecl fcn_004143b0(char* self, int arg1, int arg2)
{
	S143b0Box box;
	char* node;
	char* next;
	int link;
	int ok;
	float value;

	link = *(int*) (self + 0x1fc);
	if (link != 0) {
		fcn_004458e0(self, 0);
		fcn_00438d70(self, 0, *(int*) (self + 0x88), 0);
	}
	if (*(int*) (self + 0x1cc) == 0) {
		goto fail;
	}
	box.obj = self;
	if (fcn_004133e0(self, &box.lo, &box.hi) != 0) {
		goto fail;
	}
	box.level = (box.hi - box.lo) * *(float*) 0x662a3c + box.lo;
	if (fcn_00413480(self, box.level, box.pt[0], box.pt[1], box.pt[2], box.pt[3]) != 0) {
		goto fail;
	}
	if (*(int*) 0x6b8300 != 0) {
		if (fcn_00413c40((char*) *(int*) 0x6b8300, &box.loAligned, &box.hiAligned, box.pt[0], box.pt[1], box.pt[2], box.pt[3]) != 0) {
			goto fail;
		}
		if (arg1 != 0) {
			goto pick;
		}
	} else {
		if (arg1 != 0) {
			goto fail;
		}
		box.loAligned = 1e35f;
		box.hiAligned = -1e35f;
	}
	box.minX = MIN(MIN(MIN(box.pt[0][0], box.pt[1][0]), box.pt[2][0]), box.pt[3][0]);
	box.loX = box.lo;
	box.minY = MIN(MIN(MIN(box.pt[0][1], box.pt[1][1]), box.pt[2][1]), box.pt[3][1]);
	box.maxX = MAX(MAX(MAX(box.pt[0][0], box.pt[1][0]), box.pt[2][0]), box.pt[3][0]);
	box.hiX = box.hi;
	box.maxY = MAX(MAX(MAX(box.pt[0][1], box.pt[1][1]), box.pt[2][1]), box.pt[3][1]);
	node = self;
	next = *(char**) (node + 0x1f8);
	while (next != 0) {
		node = next;
		next = *(char**) (node + 0x1f8);
	}
	ok = 1;
	do {
		if (node != self) {
			ok &= fcn_00413fb0(&box, node);
		}
		node = *(char**) (node + 0x1f4);
	} while (node != 0);
	if (ok != 0 && *(int*) 0x6b8300 == 0) {
		goto fail;
	}
pick:
	if (arg2 == 0) {
		value = box.loAligned;
	} else {
		value = box.hiAligned;
	}
	*(float*) (self + 0x50) = value - box.lo + *(float*) (self + 0x50);
	*(unsigned char*) (self + 0x214) |= 4;
	if (link != 0) {
		fcn_004458e0(self, link);
	}
	return 0;
fail:
	if (link != 0) {
		fcn_004458e0(self, link);
	}
	return 1;
}
