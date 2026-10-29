#include <string.h>

void __cdecl fcn_00433780(char* a0);
char* __cdecl m_alloc(unsigned int size, char* file);
int __cdecl fcn_004321a0(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
void __cdecl fcn_004337c0(void* a0);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004339e0 */
int* __cdecl fcn_004339e0(char* a0, int a1, int a2, void* a3, int a4, void* a5)
{
	int* v12;
	int* v3;
	int v6;
	int i;

	v12 = 0;
	if (*(int*) (a0 + 0x1d0) != 0) {
		fcn_00433780(a0);
	}
	if (*(int*) (a0 + 0x218) == 4 || *(int*) (a0 + 0x218) == 3) {
		v12 = (int*) m_alloc(0x44, (char*) 0x67a0f8);
		v12[0] = a4;
		v12[0xb] = a1;
		v12[4] = 100;
		v12[0xe] = 0x3f800000;
		v12[0xc] = a2;
		v12[0xf] = 0;
		v12[0xd] = (int) a3;
		*(unsigned char*) ((char*) v12 + 0x2d) = *(unsigned char*) ((char*) v12 + 0x2d) & 0xdf;
		*(unsigned char*) ((char*) v12 + 0x34) = *(unsigned char*) ((char*) v12 + 0x34) & 0xdf | 0x10;
		v3 = (int*) m_alloc(a4 * 0x58, (char*) 0x67a0dc);
		v12[0x10] = (int) v3;
		memcpy(v3, a5, *v12 * 0x58);
		*(int*) (v12[0x10] - 0x58 + *v12 * 0x58) = *(int*) (v12[0x10] + *v12 * 0x58 - 0xb0);
		for (i = 0; i < *v12; i++) {
			int* e;

			e = (int*) (v12[0x10] + i * 0x58);
			*e = *e * 3;
		}
		v12[5] = *(int*) (a0 + 0x4c);
		v12[6] = *(int*) (a0 + 0x50);
		v12[7] = *(int*) (a0 + 0x54);
		v12[8] = *(int*) (a0 + 0x84);
		v12[9] = *(int*) (a0 + 0x88);
		v12[10] = *(int*) (a0 + 0x8c);
		if ((*(unsigned char*) ((char*) v12 + 0x2d) & 2) != 0) {
			v6 = *v12 - 1;
			v12[1] = v6;
			v12[3] = *(int*) (v12[0x10] + v6 * 0x58) - 1;
			v12[2] = fcn_004321a0(v12[0xb], v12[0xc], v12[0xd], v6, 0, v6, v6);
		} else {
			v12[1] = 0;
			v12[3] = 0;
			v12[2] = 1;
		}
		fcn_004337c0(v12);
	}
	*(int**) (a0 + 0x1d0) = v12;
	*(int*) (a0 + 0x40) = *(int*) 0x6b7fac;
	return v12;
}
