#include <stdlib.h>
#include <string.h>

extern int g_77261c;

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl amt_GetRoleLevel(int);

/* ADDRESS: GOLDTL 0x004a5c40 */
unsigned int __cdecl fcn_004a5c40(unsigned short* source, unsigned int count, unsigned int a2,
				  float lo, float hi, int range, unsigned short* out)
{
	unsigned int query[20];
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
	memset(query, 0, 0x50);
	memset((char*) query + 0x1c, 0xff, 0x20);
	*(int*) ((char*) query + 0x14) = 2;
	flag = 0;
	have = 0;
	if (g_77261c != 0) {
		query[1] = a2;
		query[16] = 0;
		if (fcn_005cf720(*source, *(unsigned short*) g_77261c, query, 0) != 0) {
			have = 1;
			*out = *(unsigned short*) g_77261c;
		}
	}
	if ((lo > *(double*) 0x662950 || hi < *(double*) 0x662c38) && lo < hi) {
		flag = 1;
	}
	base = amt_GetRoleLevel(*(unsigned char*) ((char*) source + 0x166));
	if (have < count) {
		do {
			query[1] = a2;
			if (have != 0) {
				*(unsigned short*) ((char*) query + 0x1c + have * 2) = out[have - 1];
			} else {
				*(unsigned short*) ((char*) query + 0x1c) = *source;
			}
			tries = 0x300;
			hit = 0;
			cand = gm_RandomMod(0x300);
			for (; hit == 0; tries--, cand = (cand + step) % 0x300) {
				if (tries == 0) {
					break;
				}
				if (fcn_005cf720(*source, cand, query, 0) != 0) {
					if (flag != 0) {
						f = fcn_0050f980(cand, *source, 1);
						if (f < lo || f > hi) {
							continue;
						}
					}
					diff = abs(base - amt_GetRoleLevel(
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
		} while (have < count);
	}
	return have;
}
