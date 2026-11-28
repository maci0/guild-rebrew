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

#include "Develop/Units/d3/client_lighting.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct S143b0Box {
	char* obj;
	float lo;
	float hi;
	float level;
	float loAligned;
	float hiAligned;
	float pt[4][4];
	float min[4];
	float max[4];
} S143b0Box;

char __cdecl d3_ReparentObject(char*, int);
void __cdecl d3_SetObjectEulerRotation(char*, int, int, int);
int __cdecl d3_GetObjectVerticalBounds(char*, float*, float*);
int __cdecl d3_ComputeObjectFootprintCorners(char*, float, float*, float*, float*, float*);
int __cdecl d3_ComputeQuadHeightRange(char*, float*, float*, float*, float*, float*, float*);
int __cdecl d3_AccumulateMeshHeightRange(S143b0Box*, char*);

/* ADDRESS: GOLDTL 0x004143b0 */
int __cdecl d3_AlignObjectToTerrain(char* self, int arg1, int arg2)
{
	S143b0Box box;
	char* node;
	int link;
	int ok;
	float value;

	link = *(int*) (self + 0x1fc);
	if (link != 0) {
		d3_ReparentObject(self, 0);
		d3_SetObjectEulerRotation(self, 0, *(int*) (self + 0x88), 0);
	} else {
		link = 0;
	}
	if (*(int*) (self + 0x1cc) == 0) {
		goto fail;
	}
	box.obj = self;
	if (d3_GetObjectVerticalBounds(self, &box.lo, &box.hi) != 0) {
		goto fail;
	}
	box.level = (box.hi - box.lo) * 0.1f + box.lo;
	if (d3_ComputeObjectFootprintCorners(self, box.level, box.pt[0], box.pt[1], box.pt[2], box.pt[3]) != 0) {
		goto fail;
	}
	if (g_6b8300 != 0) {
		if (d3_ComputeQuadHeightRange((char*) g_6b8300, &box.loAligned, &box.hiAligned, box.pt[0], box.pt[1], box.pt[2], box.pt[3]) != 0) {
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
	box.min[0] = MIN(MIN(MIN(box.pt[0][0], box.pt[1][0]), box.pt[2][0]), box.pt[3][0]);
	box.min[1] = box.lo;
	box.min[2] = MIN(MIN(MIN(box.pt[0][2], box.pt[1][2]), box.pt[2][2]), box.pt[3][2]);
	box.max[0] = MAX(MAX(MAX(box.pt[0][0], box.pt[1][0]), box.pt[2][0]), box.pt[3][0]);
	box.max[1] = box.hi;
	box.max[2] = MAX(MAX(MAX(box.pt[0][2], box.pt[1][2]), box.pt[2][2]), box.pt[3][2]);
	ok = 1;
	node = self;
	while (*(char**) (node + 0x1f8) != 0) {
		node = *(char**) (node + 0x1f8);
	}
	do {
		if (self != node) {
			ok &= d3_AccumulateMeshHeightRange(&box, node);
		}
		node = *(char**) (node + 0x1f4);
	} while (node != 0);
	if (ok != 0 && g_6b8300 == 0) {
		goto fail;
	}
pick:
	if (arg2 != 0) {
		value = box.hiAligned;
	} else {
		value = box.loAligned;
	}
	*(unsigned char*) (self + 0x214) |= 4;
	*(float*) (self + 0x50) = value - box.lo + *(float*) (self + 0x50);
	if (link != 0) {
		d3_ReparentObject(self, link);
	}
	return 0;
fail:
	if (link != 0) {
		d3_ReparentObject(self, link);
	}
	return 1;
}
