


#include "Develop/Unassigned/evidence_link.h"




// SIZE 0x8

#include "client_types.h"
extern Pair_99f800 g_99f800[0x800];
extern char g_6903a8[];

int __cdecl fcn_004f58b0(int b, int a);
int __cdecl sprintf(char* buf, const char* fmt, ...);

int __cdecl gs_AddBeweis(int a, int b)
{
	char buf[0x200];
	int k;

	k = fcn_004f58b0(b, a);
	if (k > -1) {
		g_99f800[k].owner = b;
		g_99f800[k].key = a;
		sprintf(buf, g_6903a8, b, a, k);
		return 1;
	}
	return 0;
}
