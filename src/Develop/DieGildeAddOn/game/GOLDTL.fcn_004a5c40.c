#include <stdlib.h>
#include <string.h>

extern int g_77261c;

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl fcn_004e99c0(int);

/* ADDRESS: GOLDTL 0x004a5c40 */
unsigned int __cdecl fcn_004a5c40(unsigned short* a0, unsigned int a1, unsigned int a2,
				  float lo, float hi, int range, unsigned short* out)
{
	unsigned int v12[20];
	int step;
	int base;
	int flag;
	unsigned int have;
	unsigned int tries;
	int cand;
	int hit;
	int diff;
	float f;

	step = *(int*) ((gm_RandomMod(0x10) & 0xffff) * 4 + 0x664398);
	memset(v12, 0, 0x50);
	memset((char*) v12 + 0x1c, 0xff, 0x20);
	*(int*) ((char*) v12 + 0x14) = 2;
	flag = 0;
	have = 0;
	if (g_77261c != 0) {
		v12[1] = a2;
		v12[16] = 0;
		if (fcn_005cf720(*a0, *(unsigned short*) g_77261c, v12, 0) != 0) {
			have = 1;
			*out = *(unsigned short*) g_77261c;
		}
	}
	if ((lo > *(double*) 0x662950 || hi < *(double*) 0x662c38) && lo < hi) {
		flag = 1;
	}
	base = fcn_004e99c0(*(unsigned char*) ((char*) a0 + 0x166));
	if (have < a1) {
		do {
			v12[1] = a2;
			if (have != 0) {
				*(unsigned short*) ((char*) v12 + 0x1c + have * 2) = out[have - 1];
			} else {
				*(unsigned short*) ((char*) v12 + 0x1c) = *a0;
			}
			tries = 0x300;
			hit = 0;
			cand = gm_RandomMod(0x300);
			for (; hit == 0; tries--, cand = (cand + step) % 0x300) {
				if (tries == 0) {
					break;
				}
				if (fcn_005cf720(*a0, cand, v12, 0) != 0) {
					if (flag != 0) {
						f = fcn_0050f980(cand, *a0, 1);
						if (f < lo || f > hi) {
							continue;
						}
					}
					diff = abs(base - fcn_004e99c0(
								     *(unsigned char*) (cand * 0x21c +
										0x7f4e06)));
					if (diff <= range) {
						hit = 1;
						out[have] = cand;
					}
				}
			}
			if (hit == 0) {
				return have;
			}
			have++;
		} while (have < a1);
	}
	return have;
}
