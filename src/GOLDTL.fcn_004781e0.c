#include <string.h>

char* __cdecl fcn_0041db70(unsigned int size, char* file);
short __cdecl fcn_0041bac0(unsigned char r, unsigned char g, unsigned char b);
void __cdecl fcn_0041ddd0(void* p);

/* ADDRESS: GOLDTL 0x004781e0 */
unsigned int* __cdecl fcn_004781e0(int a0, int a1, unsigned int* a2, unsigned int a3, int a4, char a5, int a6)
{
	unsigned int* v6;
	unsigned int* v8;
	unsigned int* v16;
	unsigned int* v18;
	unsigned int* v7;
	unsigned short* v20;
	unsigned short* v21;
	int w;
	int h;
	int i;
	int j;
	int x0;
	int y0;
	int x1;
	int y1;
	unsigned short v5;
	unsigned short v9;
	unsigned int v10;
	unsigned int v11;
	unsigned int v12;
	unsigned int v19;
	unsigned short v13;
	unsigned short v15;
	unsigned int v4;
	unsigned int v2;

	w = (int) a2;
	h = (int) a3;
	v6 = (unsigned int*) fcn_0041db70(((int) a2 * 8 + 4) * a3 + 0x32, (char*) 0x67d9c0);
	v11 = a3;
	v12 = (unsigned int) a2;
	x0 = 0;
	x1 = 0;
	y1 = 0;
	y0 = 0;
	v10 = 0;
	if (1 <= (int) v11) {
		v21 = (unsigned short*) (a4 + (a1 * a6 + a0) * 2);
		do {
			j = 0;
			if (1 <= w) {
				v20 = v21;
				do {
					if (*v20) {
						if (x0 < j) {
							x0 = j;
						}
						if (j < x1) {
							x1 = j;
						}
						if (y0 < (int) v10) {
							y0 = v10;
						}
						if ((int) v10 < y1) {
							y1 = v10;
						}
					}
					j++;
					v20++;
				} while (j < w);
			}
			v10++;
			v21 = v21 + a6;
		} while ((int) v10 < (int) a3);
	}
	v13 = (unsigned short) y1;
	v15 = (unsigned short) x1;
	if (x0 < (int) v15 || y0 < (int) v13) {
		v13 = 0;
		x0 = 0;
		v15 = 0;
		y0 = 0;
	}
	*(unsigned short*) ((char*) v6 + 4) = v15;
	v5 = fcn_0041bac0(*(unsigned char*) 0x100f1a0, *(unsigned char*) 0x100f1a1, *(unsigned char*) 0x100f1a1);
	*(unsigned short*) ((char*) v6 + 6) = v5;
	*(unsigned short*) ((char*) v6 + 8) = v13;
	v9 = (unsigned short) (y0 + 1);
	*(unsigned short*) ((char*) v6 + 10) = v9;
	*(unsigned short*) ((char*) v6 + 0xe) = v15;
	*(unsigned short*) ((char*) v6 + 0x10) = v13;
	*(unsigned short*) ((char*) v6 + 0x12) = v5;
	*(unsigned short*) ((char*) v6 + 0x14) = v9;
	*(unsigned short*) ((char*) v6 + 0x16) = v15;
	*(unsigned short*) ((char*) v6 + 0x18) = v13;
	*(unsigned short*) ((char*) v6 + 0x1a) = (unsigned short) x0;
	*(unsigned short*) ((char*) v6 + 0x1c) = (unsigned short) y0;
	*v6 = 0x32;
	v8 = (unsigned int*) ((char*) v6 + *v6);
	if (*(unsigned short*) ((char*) v6 + 0xa) != 0) {
		i = 0;
		a3 = a6 * 2;
		v11 = *(unsigned short*) ((char*) v6 + 6) * 2;
		a2 = (unsigned int*) (a4 + (a1 * a6 + a0) * 2);
		do {
			v10 = v11 >> 2;
			v7 = v8;
			{
				unsigned int* src = a2;
				unsigned int* dst = v7;
				unsigned int n = v10;

				while (n) {
					*dst++ = *src++;
					n--;
				}
				n = v11 & 3;
				{
					char* d = (char*) dst;
					char* s = (char*) src;

					while (n) {
						*d++ = *s++;
						n--;
					}
					dst = (unsigned int*) d;
					src = (char*) s;
				}
			}
			v11 = *(unsigned short*) ((char*) v6 + 6) * 2;
			*(unsigned int*) ((char*) v6 + 0x2e) = *(unsigned int*) ((char*) v6 + 0x2e) + *(unsigned short*) ((char*) v6 + 6);
			a2 = (unsigned int*) ((char*) a2 + a3);
			v8 = (unsigned int*) ((char*) v8 + v11);
			i++;
			*v6 = *v6 + v11;
		} while (i < (int) (unsigned int) *(unsigned short*) ((char*) v6 + 10));
	}
	*(unsigned int*) ((char*) v6 + 0x2a) = 0;
	*(char*) ((char*) v6 + 0xd) = a5;
	*(unsigned int*) ((char*) v6 + 0x26) = 0xffffffff;
	v18 = (unsigned int*) fcn_0041db70(*v6, (char*) 0x67d970);
	v4 = *v6;
	{
		unsigned int* src = v6;
		unsigned int* dst = v18;
		unsigned int n = v4 >> 2;
		unsigned int r = v4 & 3;

		while (n) {
			*dst++ = *src++;
			n--;
		}
		{
			char* d = (char*) dst;
			char* s = (char*) src;

			while (r) {
				*d++ = *s++;
				r--;
			}
		}
	}
	fcn_0041ddd0(v6);
	return v18;
}
