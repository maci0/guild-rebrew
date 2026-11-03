#include <string.h>

int* __cdecl fcn_004339e0(char* a0, int a1, int a2, void* a3, int a4, void* a5);
void __cdecl fcn_00451720(void* a0, void* a1, void* a2, void* a3);
void __cdecl fcn_00438cb0(void* a0, void* a1);

/* The native body keeps an EBP frame (/Oy-, non-frame-omitted build). */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00412b10 */
unsigned int __cdecl fcn_00412b10(char* a0, float a1, float a2, float a3, float a4, float a5, float a6, unsigned int a7, unsigned char a8)
{
	unsigned int z[3];
	float v5;
	float v25;
	float v26;
	char v6[12];
	unsigned int v7;
	int* v3;

	v7 = a7;
	if (*(int*) 0x6b5cbc != 0 && *(char**) 0x6b8014 == a0) {
		return 0;
	}
	memset(z, 0, sizeof(z));
	memset(v6, 0, sizeof(v6));
	z[0] = (z[0] | 0x1400) & 0xfffff7ff;
	z[2] |= 2;
	v26 = a6;
	v5 = a4;
	v25 = a5;
	if ((a8 & 8) != 0) {
		fcn_00451720(a0 + 0x84, &v5, v6, &v5);
		fcn_00438cb0(a0, v6);
	}
	if (a0 == *(char**) 0x6b8014) {
		*(float*) 0x14ce890 = v5;
		*(float*) 0x14ce894 = v25;
		*(float*) 0x14ce898 = v26;
		*(float*) 0x14ce880 = a1;
		*(float*) 0x14ce884 = a2;
		*(float*) 0x14ce888 = a3;
	}
	v5 = v5 - *(float*) (a0 + 0x84);
	v25 = v25 - *(float*) (a0 + 0x88);
	v26 = v26 - *(float*) (a0 + 0x8c);
	v3 = fcn_004339e0(a0, (int) z[0], (int) z[1], (void*) z[2], 2, &v7);
	if (a0 != *(char**) 0x6b8014) {
		return 1;
	}
	*(unsigned char*) ((char*) v3 + 0x2d) |= 8;
	*(int*) 0x6b5cbc = 1;
	*(int**) 0x6b5cc0 = v3;
	return 1;
}
