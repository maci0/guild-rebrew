#include <string.h>

float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl fcn_005ca560(void*);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);

/* ADDRESS: GOLDTL 0x005cb860 */
unsigned int __cdecl fcn_005cb860(short* a0, unsigned int maxCount, int* a2, void* a3)
{
	unsigned char* c;
	int* e;
	int* p;
	float d;
	unsigned int found;
	unsigned int keep;
	unsigned int i;
	unsigned int kind;
	int tmp;
	double previous;

	found = 0;
	if (!maxCount) {
		for (c = (unsigned char*) 0x7f4ca0; (int) c < 0x85a0a0; c += 0x21c) {
			if (c == (unsigned char*) a0)
				continue;
			if (*(short*) c == -1)
				continue;
			if ((unsigned char) (c[2] - 2) > 5)
				continue;
			d = fcn_0050f980((unsigned short) *a0, *(unsigned short*) c, 1);
			if (d <= *(float*) 0x664394 || *(int*) (c + 0x210) == *(int*) ((char*) a0 + 4))
				found++;
		}
		return found;
	}
	memset(a2, 0, maxCount * 0x38);
	for (i = 0; i < maxCount; i++)
		a2[i * 14 + 11] = 100;
	for (c = (unsigned char*) 0x7f4ca0; (int) c < 0x85a0a0; c += 0x21c) {
		if (c == (unsigned char*) a0)
			continue;
		if (*(short*) c == -1)
			continue;
		if ((unsigned char) (c[2] - 2) > 5)
			continue;
		if (*(int*) (c + 0x210) != *(int*) ((char*) a0 + 4)) {
			d = fcn_0050f980((unsigned short) *a0, *(unsigned short*) c, 1);
			if (d > *(float*) 0x664394)
				continue;
		} else {
			d = 0.0f;
		}
		e = &a2[(maxCount - 1) * 14];
		if (!(d < (float) e[11]))
			continue;
		e[0] = (int) c;
		e[11] = (int) d;
		found++;
		i = maxCount - 1;
		if (i) {
			p = &e[-3];
			do {
				if (p[14] < *p) {
					previous = (double) *p;
					tmp = p[-11];
					p[-11] = p[3];
					*p = p[14];
					p[3] = tmp;
					p[14] = (int) previous;
				}
				p -= 14;
				i--;
			} while (i);
		}
	}
	keep = found;
	if (found >= maxCount) {
		keep = maxCount;
		found = maxCount;
	}
	if ((int) keep < 1)
		return keep;
	for (i = 0; i < keep; i++) {
		fcn_005ca560(&a2[i * 14]);
		a2[i * 14 + 12] = fcn_005cf720(*a0, *(short*) *(int*) (&a2[i * 14]), a3, 0);
	}
	return keep;
}
