#include <math.h>

extern int g_67a370;

char* __cdecl gm_LookupEntityRecordById(int);
char __cdecl fcn_0045b920(void*, int, int, float*);

/* ADDRESS: GOLDTL 0x004d3070 */
float __cdecl fcn_004d3070(char* self, int x, int z, float range)
{
	char* e;
	void* g;
	float* p;
	float best;
	float pos[4];
	float dx;
	float dy;
	float dz;
	float d;
	int* listA;
	int* listB;
	int i;

	g = *(void**) ((char*) g_67a370 + 0xb0);
	best = 0.0f;
	if (*(int*) (self + 0x16c) == *(int*) 0x772e9c) {
		listA = (int*) (*(int*) 0x772eb4 + 0x80);
		listB = (int*) (*(int*) 0x772eb4 + 0xc0);
	} else {
		listA = (int*) (*(int*) 0x772eb4 + 0xc0);
		listB = (int*) (*(int*) 0x772eb4 + 0x80);
	}
	fcn_0045b920(g, x, z, pos);
	for (i = 0; i < 16; i++) {
		if (listA[i] == -1) {
			continue;
		}
		e = gm_LookupEntityRecordById(listA[i]);
		if (e == 0) {
			continue;
		}
		if (*(unsigned char*) (e + 8) <= 0) {
			continue;
		}
		p = (float*) (*(int*) (*(int*) (e + 0x184) + 0x34));
		dx = pos[0] - p[0x13];
		dy = pos[1] - p[0x14];
		dz = pos[2] - p[0x15];
		d = (float) sqrt(dz * dz + dy * dy + dx * dx);
		if (d <= range) {
			best += 70.0f / d;
		}
	}
	for (i = 0; i < 16; i++) {
		if (listB[i] != -1) {
			e = gm_LookupEntityRecordById(listB[i]);
			if (e != 0 && *(unsigned char*) (e + 8) != 0 && e != self) {
				p = (float*) (*(int*) (*(int*) (e + 0x184) + 0x34));
				dx = pos[0] - p[0x13];
				dy = pos[1] - p[0x14];
				dz = pos[2] - p[0x15];
				d = (float) sqrt(dz * dz + dy * dy + dx * dx);
				if (!(d > range)) {
					best -= 70.0f / d;
				}
			}
		}
	}
	return best;
}
