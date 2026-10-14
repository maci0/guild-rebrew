#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

typedef struct
{
	int id;
	char count;
	char data[0x77];
} Buf220;
// SIZE 0x7c

extern unsigned int g_aed208;
extern char g_aed220[];
extern char* g_aed32c;



void __cdecl fcn_004c4510(int a1, int a2)
{
	int l0;
	int l1;

	(*(Buf220*)g_aed220).id = a2;
	(*(Buf220*)g_aed220).count = 0;
	memset((*(Buf220*)g_aed220).data, 0, sizeof((*(Buf220*)g_aed220).data));
	(*(int*)&g_aed208) = 0;
	if (gm_ResolveEntityById((void**) (&l1), (void**) (&l0), (void**) (&a2), a2) != 0) {
		(*(int*)&g_aed32c) = a1;
	}
}
