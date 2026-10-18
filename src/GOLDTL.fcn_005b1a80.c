#include "g_774a78.h"

extern Node* g_774a78;

/* ADDRESS: GOLD 0x005a8600 */
/* ADDRESS: GOLDTL 0x005b1a80 */

char* __cdecl fcn_005b1a80(int key)
{
	char* p;

	p = (char*) g_774a78;
	while (p != 0) {
		if (*(int*) p == key) {
			return p;
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}

void __cdecl fcn_005b1980(int a, char* o);

/* ADDRESS: GOLD 0x005a89a0 */
/* ADDRESS: GOLDTL 0x005b1e20 */

void __cdecl fcn_005b1e20(char* p)
{
	char* o;

	o = fcn_005b1a80(*(int*) (p + 1));
	if (o != 0) {
		fcn_005b1980((int) p, o);
	}
}

float __cdecl fcn_005b1910(char* o);
extern float g_662cf8;

/* ADDRESS: GOLD 0x005a89c0 */
/* ADDRESS: GOLDTL 0x005b1e40 */

int __cdecl fcn_005b1e40(char* p)
{
	char* o;
	int thr;
	int k;
	int res;
	int sum;
	int* e;

	o = fcn_005b1a80(*(int*) (p + 1));
	if (o == 0) {
		return 0;
	}
	thr = (int) (fcn_005b1910(o) * g_662cf8);
	k = 0;
	res = 0;
	sum = 0;
	e = (int*) (o + 0xc);
	for (; k < 7; k++, e += 2) {
		if (res != 0) {
			break;
		}
		if (e[0] != 0) {
			sum += *(unsigned char*) (e + 1);
			if (*(unsigned char*) (e + 1) != 0 && thr < sum) {
				res = e[0];
			}
		}
	}
	return res;
}
