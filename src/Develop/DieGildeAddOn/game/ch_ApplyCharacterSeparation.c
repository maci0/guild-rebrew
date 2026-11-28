#include <math.h>
#include <stdlib.h>

extern void* ch_CharacterSlots[];
extern float flt_0_0;
extern float g_6628b0;

int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d3_NormalizeVector(float* v);
char __cdecl d3sm_3D2SuperMap(float* tex, float* pt, int* col, int* row, float* out);

/* ADDRESS: GOLDTL 0x00402d00 */
void __cdecl ch_ApplyCharacterSeparation(char* character)
{
	float limit = 50.0f;
	float t;
	float dist;
	int col;
	int row;
	float out;
	float direction[4];
	float k;

	float pt[4];
	int list[16];
	int i = 0;
	void** p;
	char* e;
	char* s;
	int type;

	if ((*(unsigned short*) (character + 0x8c) & 0x18) != 0) {
		return;
	}
	if (*(int*) (character + 0x124) != 0) {
		return;
	}
	if (*(char**) (character + 0x128) != 0 && *(char*) (*(char**) (character + 0x128) + 9) == '-') {
		return;
	}
	if (*(char**) (character + 0x128) != 0 && *(char*) (*(char**) (character + 0x128) + 9) == '-') {
		limit = 100.0f;
	}
	p = ch_CharacterSlots;
	do {
		if (i >= 0xf) {
			break;
		}
		e = *p;
		if (e != 0 && character != e &&
		    *(int*) (character + 0x2c) == *(int*) (e + 0x2c) &&
		    *(int*) (character + 0x30) == *(int*) (e + 0x30) &&
		    (*(unsigned short*) (character + 0x8c) & 0x18) == 0 &&
		    *(int*) (character + 0x124) == 0) {
			s = *(char**) (e + 0x34);
			if (*(int*) (s + 0x218) == 1) {
				if (*(char**) (e + 0x22c) == 0) {
					goto next;
				}
				if (*(int*) (*(char**) (e + 0x22c) + 0x218) == 1) {
					goto next;
				}
			}
			if (CompareVector3WithinTolerance((float*) (*(char**) (character + 0x34) + 0x4c),
			                 (float*) (s + 0x4c), limit) != 0) {
				list[i] = (int) *p;
				i++;
			}
		}
next:
		p++;
	} while ((int) p < 0x14d0c20);
	list[i] = 0;
	for (i = 0; list[i] != 0; i++) {
		if (i >= 0xf) {
			break;
		}
		e = (char*) list[i];
		s = *(char**) (character + 0x34);
		direction[0] = *(float*) (*(char**) (e + 0x34) + 0x4c) - *(float*) (s + 0x4c);
		direction[1] = *(float*) (*(char**) (e + 0x34) + 0x50) - *(float*) (s + 0x50);
		direction[2] = *(float*) (*(char**) (e + 0x34) + 0x54) - *(float*) (s + 0x54);
		dist = (float) sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
		if (dist == flt_0_0) {
			direction[0] = (float) (rand() % 2 - 1);
			direction[1] = (float) (rand() % 2 - 1);
			direction[2] = (float) (rand() % 2 - 1);
			dist = (float) sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
		}
		t = (limit - (dist + dist)) / limit;
		if (flt_0_0 > t) {
			t = 0.0f;
		}
		direction[0] = -direction[0];
		direction[1] = -direction[1];
		direction[2] = -direction[2];
		d3_NormalizeVector(direction);
		k = t * g_6628b0;
		s = *(char**) (character + 0x34);
		pt[0] = *(float*) (s + 0x4c) + k * direction[0];
		pt[1] = *(float*) (s + 0x50);
		pt[2] = *(float*) (s + 0x54) + k * direction[2];
		*(unsigned short*) (character + 0x8c) |= 1;
		*(int*) (character + 0x58) = 0;
		*(float*) (character + 0x54) = k * direction[0];
		*(float*) (character + 0x5c) = k * direction[2];
		s = *(char**) (character + 0x88);
		e = *(char**) (s + 0xb0);
		if (e != 0 && d3sm_3D2SuperMap((float*) e, pt, &col, &row, &out) != 0) {
			type = *(int*) (*(char**) (e + 0x24) + (*(int*) (e + 0x20) * row + col) * 0x1c);
			if (type == 0 || type == 0xd) {
				*(unsigned short*) (character + 0x8c) &= 0xfe;
			}
		}
	}
}
