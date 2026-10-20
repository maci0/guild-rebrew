#include <string.h>

extern int g_77261c;

int __cdecl fcn_0042e410(int);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);
float __cdecl fcn_0050f980(unsigned short, unsigned short, int);

/* ADDRESS: GOLDTL 0x004a55c0 */
unsigned int __cdecl fcn_004a55c0(unsigned short* a0, unsigned int a1, unsigned int* a2,
				  float a3, float a4, unsigned short* a5)
{
	unsigned int v12[20];
	unsigned int step;
	unsigned int pos;
	unsigned int idx;
	int tries;
	int hit;
	unsigned short id;
	float f;
	int flag;

	idx = 0;
	flag = 0;
	step = *(unsigned int*) ((fcn_0042e410(0x10) & 0xffff) * 4 + 0x664398);
	memset(v12, 0, 0x50);
	memset((char*) v12 + 0x1c, 0xff, 0x20);
	*(int*) ((char*) v12 + 0x14) = 2;
	if (g_77261c != 0) {
		v12[1] = *a2;
		if (fcn_005cf720(*a0, *(unsigned short*) g_77261c, v12, 0) != 0) {
			idx = 1;
			*a5 = *(unsigned short*) g_77261c;
		}
	}
	if ((a3 > *(double*) 0x662950 || a4 < *(double*) 0x662c38) && a3 < a4) {
		flag = 1;
	}
	if (a1 <= idx) {
		return 1;
	}
	do {
		v12[1] = a2[idx];
		if (idx != 0) {
			*(unsigned short*) ((char*) v12 + 0x1c + idx * 2) = a5[idx - 1];
		} else {
			*(unsigned short*) ((char*) v12 + 0x1c) = *a0;
		}
		tries = 0x300;
		hit = 0;
		pos = fcn_0042e410(0x300) & 0xffff;
		do {
			if (tries == 0) {
				if (hit == 0) {
					return 0;
				}
				break;
			}
			id = *a0;
			if (fcn_005cf720(id, (unsigned short) pos, v12, 0) != 0) {
				if (flag == 0) {
					hit = 1;
					a5[idx] = (unsigned short) pos;
				} else {
					f = fcn_0050f980((unsigned short) pos, *a0, 1);
					if (a3 <= f && f <= a4) {
						hit = 1;
						a5[idx] = (unsigned short) pos;
					}
				}
			}
			tries--;
			pos = (pos + step) % 0x300;
		} while (hit == 0);
		idx++;
		if (a1 <= idx) {
			return 1;
		}
	} while (1);
}
