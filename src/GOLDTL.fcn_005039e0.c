// FUNCTION: GOLD 0x00500b90
// SIZE: 140
// FUNCTION: GOLDTL 0x005039e0
// SIZE: 140

#include "client_types.h"
#pragma pack(push, 1)
typedef Rec15_699058 Rec15;
// SIZE 0x15
#pragma pack(pop)

extern char* g_99ec10;
extern Rec15_699058 g_699058[37];
extern unsigned short g_7f3ee4;
extern int g_90d520[];

int __cdecl fcn_005039e0(unsigned char* p)
{
	Rec15* r;
	int i;
	int j;

	if (((void*)g_99ec10) == 0) {
		return 1;
	}
	r = 0;
	for (i = 0; i < 37; i++) {
		if (g_699058[i].k == *p) {
			r = &g_699058[i];
			break;
		}
	}
	if (r == 0) {
		return 1;
	}
	g_7f3ee4 = 0;
	for (j = 0; j < 10; j++) {
		if (r->ids[j] != 0) {
			g_90d520[g_7f3ee4++] = r->ids[j];
		}
	}
	return 0;
}
