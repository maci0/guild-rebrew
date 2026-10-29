extern char* lpObjektePROT;
extern int g_774800;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0055c1f0(char* o)
{
	char* t;

	t = lpObjektePROT + *(unsigned short*) (o + 0xac) * 0x41;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	if (g_774800 != 0) {
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
	} else {
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, *(int*) (t + 0x22), 0);
	}
}
