#include <math.h>
#include <stdlib.h>

extern void* g_14d0020[];
extern float g_6628a8;
extern float g_6628b0;

int __cdecl fcn_00451840(float* a, float* b, float eps);
void __cdecl fcn_004518a0(float* v);
int __cdecl fcn_0045b990(float* tex, float* pt, int* outx, int* outy, float* out);

/* ADDRESS: GOLDTL 0x00402d00 */
void __cdecl fcn_00402d00(char* a0)
{
	float limit = 50.0f;
	float t;
	float dist;
	int outx;
	int outy;
	float out;
	float dx;
	float dy;
	float dz;
	float pt[3];
	int list[16];
	int i;
	void** p;
	char* e;
	char* s;
	int type;

	if ((*(unsigned short*) (a0 + 0x8c) & 0x18) != 0) {
		return;
	}
	if (*(int*) (a0 + 0x124) != 0) {
		return;
	}
	if (*(char**) (a0 + 0x128) != 0 && *(char*) (*(char**) (a0 + 0x128) + 9) == '-') {
		return;
	}
	if (*(char**) (a0 + 0x128) != 0 && *(char*) (*(char**) (a0 + 0x128) + 9) == '-') {
		limit = 100.0f;
	}
	i = 0;
	p = g_14d0020;
	do {
		if (i >= 0xf) {
			break;
		}
		e = *p;
		if (e != 0 && a0 != e &&
		    *(int*) (a0 + 0x2c) == *(int*) (e + 0x2c) &&
		    *(int*) (a0 + 0x30) == *(int*) (e + 0x30) &&
		    (*(unsigned short*) (a0 + 0x8c) & 0x18) == 0 &&
		    *(int*) (a0 + 0x124) == 0) {
			s = *(char**) (e + 0x34);
			if (*(int*) (s + 0x218) == 1) {
				if (*(char**) (e + 0x22c) == 0) {
					goto next;
				}
				if (*(int*) (*(char**) (e + 0x22c) + 0x218) == 1) {
					goto next;
				}
			}
			if (fcn_00451840((float*) (*(char**) (a0 + 0x34) + 0x4c),
			                 (float*) (s + 0x4c), limit) != 0) {
				list[i] = (int) e;
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
		s = *(char**) (a0 + 0x34);
		dx = *(float*) (*(char**) (e + 0x34) + 0x4c) - *(float*) (s + 0x4c);
		dy = *(float*) (*(char**) (e + 0x34) + 0x50) - *(float*) (s + 0x50);
		dz = *(float*) (*(char**) (e + 0x34) + 0x54) - *(float*) (s + 0x54);
		dist = (float) sqrt(dx * dx + dy * dy + dz * dz);
		if (dist == g_6628a8) {
			dx = (float) (rand() % 2 - 1);
			dy = (float) (rand() % 2 - 1);
			dz = (float) (rand() % 2 - 1);
			dist = (float) sqrt(dx * dx + dy * dy + dz * dz);
		}
		t = (limit - dist - dist) / limit;
		if (t > g_6628a8) {
			t = t;
		} else {
			t = 0.0f;
		}
		dx = -dx;
		dy = -dy;
		dz = -dz;
		fcn_004518a0(&dx);
		t = t * g_6628b0;
		s = *(char**) (a0 + 0x34);
		pt[0] = *(float*) (s + 0x4c) + t * dx;
		pt[1] = *(float*) (s + 0x50);
		pt[2] = *(float*) (s + 0x54) + t * dz;
		*(unsigned short*) (a0 + 0x8c) |= 1;
		*(int*) (a0 + 0x58) = 0;
		*(float*) (a0 + 0x54) = t * dx;
		*(float*) (a0 + 0x5c) = t * dz;
		s = *(char**) (a0 + 0x88);
		e = *(char**) (s + 0xb0);
		if (e != 0 && fcn_0045b990((float*) e, pt, &outx, &outy, &out) != 0) {
			type = *(int*) (*(char**) (e + 0x24) + (*(int*) (e + 0x20) * outx + outy) * 0x1c);
			if (type == 0 || type == 0xd) {
				*(unsigned short*) (a0 + 0x8c) &= 0xfe;
			}
		}
	}
}
