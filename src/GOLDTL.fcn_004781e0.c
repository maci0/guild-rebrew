#include <string.h>

char* __cdecl m_alloc(unsigned int size, char* file);
short __cdecl fcn_0041bac0(unsigned char r, unsigned char g, unsigned char b);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x004781e0 */
unsigned int* __cdecl fcn_004781e0(int a0, int a1, unsigned int* a2, unsigned int a3, int a4, char a5, int a6)
{
	unsigned int* v6;
	unsigned int* v8;
	unsigned int* v18;
	unsigned short y0;
	unsigned short* v20;
	unsigned short* v21;
	unsigned short x0;
	unsigned short x1;
	unsigned short y1;
	int j;
	int v10;
	unsigned int v11;
	unsigned int v4;
	int i;

	v6 = (unsigned int*) m_alloc(((int) a2 * 8 + 4) * a3 + 0x32, (char*) 0x67d9c0);
	x0 = 0;
	x1 = (unsigned short) a2;
	y1 = (unsigned short) a3;
	v21 = (unsigned short*) (a4 + (a1 * a6 + a0) * 2);
	v10 = 0;
	if (1 <= (int) a3) {
		do {
			j = 0;
			if (1 <= (int) a2) {
				v20 = v21;
				do {
					if (*v20) {
						if (x0 < j) {
							x0 = j;
						}
						if (j < x1) {
							x1 = j;
						}
						if (y0 < v10) {
							y0 = v10;
						}
						if (v10 < y1) {
							y1 = v10;
						}
					}
					j++;
					v20++;
				} while (j < (int) a2);
			}
			v10++;
			v21 = v21 + a6;
		} while ((int) v10 < (int) a3);
	}
	if (x0 < x1 || y0 < y1) {
		y1 = 0;
		x0 = 0;
		x1 = 0;
		y0 = 0;
	}
	*(unsigned short*) ((char*) v6 + 4) = x1;
	*(unsigned short*) ((char*) v6 + 6) = x0 + 1;
	*(unsigned short*) ((char*) v6 + 8) = y1;
	*(unsigned short*) ((char*) v6 + 0xa) = y0 + 1;
	*(unsigned short*) ((char*) v6 + 0xe) = x1;
	*(unsigned short*) ((char*) v6 + 0x10) = y1;
	*(unsigned short*) ((char*) v6 + 0x12) = x0 + 1;
	*(unsigned short*) ((char*) v6 + 0x14) = y0 + 1;
	*(unsigned short*) ((char*) v6 + 0x16) = x1;
	*(unsigned short*) ((char*) v6 + 0x18) = y1;
	*(unsigned short*) ((char*) v6 + 0x1a) = x0;
	*(unsigned short*) ((char*) v6 + 0x1c) = y0;
	*v6 = 0x32;
	fcn_0041bac0(*(unsigned char*) 0x100f1a0, *(unsigned char*) 0x100f1a1, *(unsigned char*) 0x100f1a2);
	v8 = (unsigned int*) ((char*) v6 + *v6);
	if (*(unsigned short*) ((char*) v6 + 0xa) != 0) {
		i = 0;
		a3 = a6 * 2;
		v11 = *(unsigned short*) ((char*) v6 + 6) * 2;
		a2 = (unsigned int*) (a4 + (a1 * a6 + a0) * 2);
		do {
			v10 = v11 >> 2;
			memcpy(v8, a2, v11);
			v11 = *(unsigned short*) ((char*) v6 + 6) * 2;
			*(unsigned int*) ((char*) v6 + 0x2e) = *(unsigned int*) ((char*) v6 + 0x2e) + *(unsigned short*) ((char*) v6 + 6);
			a2 = (unsigned int*) ((char*) a2 + a3);
			v8 = (unsigned int*) ((char*) v8 + v11);
			i++;
			*v6 = *v6 + v11;
		} while (i < (int) *(unsigned short*) ((char*) v6 + 10));
	}
	*(unsigned int*) ((char*) v6 + 0x2a) = 0;
	*(char*) ((char*) v6 + 0xd) = a5;
	*(unsigned int*) ((char*) v6 + 0x26) = 0xffffffff;
	v18 = (unsigned int*) m_alloc(*v6, (char*) 0x67d970);
	v4 = *v6;
	memcpy(v18, v6, v4);
	m_FreeTracked(v6);
	return v18;
}
