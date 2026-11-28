

#include <string.h>

// SIZE 0x58
typedef struct Bone {
	char name[0x40];
	float a[3];
	float b[3];
} Bone;

/* ADDRESS: GOLDDE 0x004457c0 */
int __cdecl d3_CalcMeshBinarySize(char* mesh, char* obj)
{
	int sz;
	int n;
	int i;
	char* p;
	char* q;

	sz = 0x18;
	if (*(int*) (mesh + 0x44) > 0) {
		sz = (*(int*) (mesh + 0x44) * 3 + 0x1b) * 8;
	}
	n = *(int*) (mesh + 0x1e4);
	if (n > 0xfe) {
		sz += *(int*) (mesh + 0x4c) * 52;
	} else {
		sz += *(int*) (mesh + 0x4c) * 49;
	}
	sz += n * 6;
	if (n > 0) {
		p = *(char**) (obj + 0x10);
		q = p + 0x40;
		for (i = 0; i < n; i++) {
			sz += strlen(p) + strlen(q) + strlen(q + 0x40) + 3;
			p += 0xe0;
			q += 0xe0;
		}
	}
	n = *(int*) (obj + 0x34);
	sz += n * 24;
	for (i = 0; i < n; i++) {
		sz += strlen(((Bone*) (obj + 0x38))[i].name) + 1;
	}
	return sz;
}
