// FUNCTION: GOLD 0x00491d70
// FUNCTION: GOLDTL 0x491340

#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;

int __cdecl fcn_004f4830(int idx, void* dst);
float __cdecl fcn_004fbd40(void);
char* __cdecl fcn_0050e4a0(int k);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int a, char b);
int __cdecl fcn_004ec710(void);

int __cdecl fcn_00491340(char* a1, char* a2, int* out)
{
	int info[9];
	char* p;
	int v;
	int t;
	int lvl;

	if ((*(int*)&g_7f4c00) < 4) {
		return 0;
	}
	fcn_004f4830(0xf, info);
	fcn_004fbd40();
	p = fcn_0050e4a0(1);
	p = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	v = fcn_0050b810(*(int*) (p + 0x14), (*(char*)&g_773d75));
	t = fcn_004ec710();
	if (v < t * 3) {
		lvl = 4;
	} else if (v > t * 12) {
		lvl = 0;
	} else if (v > t * 8) {
		lvl = 1;
	} else {
		lvl = (v <= t * 6) + 2;
	}
	if (abs(info[6] - lvl) < 2) {
		return 0;
	}
	if (lvl > info[6]) {
		lvl = info[6] + 1;
	} else if (lvl < info[6]) {
		lvl = info[6] - 1;
	}
	*out = max(min(lvl, info[2]), info[1]);
	return 1;
}
