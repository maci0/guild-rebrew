extern unsigned char* g_868050;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00565af0
// SIZE: 236
// FUNCTION: GOLDTL 0x56de60
// SIZE: 236

void __cdecl fcn_00546190(char*);
unsigned char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_004c6090(unsigned char*, int, int, int);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_004c4fc0(int, int, int, short, int, int, int, int);

void __cdecl fcn_0056de60(char* o)
{
	int x;
	unsigned char* t;
	unsigned char* r;
	int i;
	int k;

	k = 0;
	r = gm_SearchTable67(*(int*) (o + 0xb4));
	if (r == 0) {
		fcn_00546190(o);
		return;
	}
	t = g_868050 + *r * 0x24d;
	if (*t != 2) {
		for (i = 5; i >= 0; i--) {
			if (t[0x223 + i] != 0) {
				k = t[0x223 + i];
				break;
			}
		}
		*(int*) (o + 0xac) = fcn_004c6090(r, 1, t[0x230], k);
	} else {
		x = fcn_00507400(fcn_0042e410(12) + 1, 1);
		*(int*) (o + 0xac) = fcn_004c4fc0(2, -1, -1, fcn_0042e410(5) + 0x16, -1, x, 0, 2);
	}
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
}
