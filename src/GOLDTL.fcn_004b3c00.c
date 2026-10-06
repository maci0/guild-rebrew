typedef struct {
	short v[7];
} fcn_004b3c00_stamp;
// SIZE 0xe

typedef struct {
	char pad0[0x8];
	fcn_004b3c00_stamp when;
	char pad16[0x2];
	int f18;
	int f1c;
	char f20;
} fcn_004b3c00_rec;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

fcn_004b3c00_rec* __cdecl fcn_004b3bc0(int);

// FUNCTION: GOLD 0x004b3a90
// FUNCTION: GOLDTL 0x4b3c00

fcn_004b3c00_rec* __cdecl fcn_004b3c00(int a)
{
	fcn_004b3c00_rec* p;

	p = fcn_004b3bc0(a);
	if (p != 0) {
		p->when = (*(fcn_004b3c00_stamp*)&g_7f4c00);
		p->f18 = 0;
		p->f1c = 0;
		p->f20 = 0;
	}
	return p;
}
