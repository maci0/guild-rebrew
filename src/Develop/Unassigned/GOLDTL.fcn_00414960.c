#include <stdlib.h>

extern char* d3_ActiveCamera;

void __cdecl d3_UpdateObjectCameraTransform(char* obj, char* cam, char force);
int __cdecl d3_ExpandObjectWorldBounds(void);

/* ADDRESS: GOLDTL 0x00414960 */
void __cdecl d3_ComputeObjectWorldBounds(float* minBounds, float* maxBounds, char* obj)
{
	float* p;
	char* node;
	int i;

	if (*(int*) (obj + 0x1cc) == 0) {
		return;
	}
	if ((*(unsigned char*) (obj + 0x216) & 0x20) == 0) {
		d3_UpdateObjectCameraTransform(obj, d3_ActiveCamera, 0);
	}
	p = (float*) (*(int (__cdecl**) (char*, int, int)) (*(int*) (*(int*) (obj + 0x1cc) + 0x318) + 0x1f0)) (obj, *(int*) (obj + 0x1cc), *(int*) (obj + 0x1ec) + 8);
	if (p != 0) {
		minBounds[0] = p[0];
		minBounds[1] = p[1];
		minBounds[2] = p[2];
		maxBounds[0] = p[0];
		maxBounds[1] = p[1];
		maxBounds[2] = p[2];
		p += 0x14;
		for (i = 7; i != 0; i--) {
			minBounds[0] = __min(minBounds[0], p[0]);
			minBounds[1] = __min(minBounds[1], p[1]);
			minBounds[2] = __min(minBounds[2], p[2]);
			maxBounds[0] = __max(maxBounds[0], p[0]);
			maxBounds[1] = __max(maxBounds[1], p[1]);
			maxBounds[2] = __max(maxBounds[2], p[2]);
			p += 0x14;
		}
	}
	node = *(char**) (obj + 0x200);
	while (node != 0) {
		d3_ExpandObjectWorldBounds((char*) minBounds, (char*) maxBounds, node);
		node = *(char**) (node + 0x1f4);
	}
}
