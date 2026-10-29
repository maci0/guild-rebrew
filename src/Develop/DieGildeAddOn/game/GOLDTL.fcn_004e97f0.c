#include "client_actions.h"

typedef struct {
	short lo;
	short hi;
	int min_cost;
	int max_cost;
	int a;
	int b;
	int c;
	int d;
} TierInfo;

int __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_004e9580(int id, TierInfo* out);
void __cdecl fcn_004c51a0(int a1, int a2, char a3, int a4);
void __cdecl fcn_004c4510(char* a1, int a2);
int __cdecl fcn_004c4570(unsigned char size, unsigned char count, unsigned short off, char* src);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004e7d40(char* a0, int a1);

/* ADDRESS: GOLDTL 0x004e97f0 */
int __cdecl fcn_004e97f0(unsigned char* a0, int a1)
{
	int mode;
	TierInfo info;
	unsigned short rnd;

	mode = 3;
	if (a0[2] != 0x13) {
		return 0;
	}
	if (fcn_004e9580(a1, &info) == 0) {
		return 0;
	}
	fcn_004c51a0(*(int*) (a0 + 4), -1, g_773d75,
	    (unsigned short) gm_RandomMod((unsigned short) (info.max_cost - info.min_cost + 1)) + info.min_cost);
	rnd = (unsigned short) gm_RandomMod((unsigned short) (info.b - info.a + 1)) + info.a;
	fcn_004c4510(a0, *(int*) (a0 + 4));
	fcn_004c4570(1, 1, 0xd, (char*) &rnd);
	fcn_004c4570(1, 1, 2, (char*) &mode);
	fcn_004c4570(1, 1, 0x167, (char*) &a1);
	fcn_004c5360();
	fcn_004e7d40(a0, a1);
	return 1;
}
