#include "Develop/DieGildeAddOn/game/spiel.h"
extern unsigned char* lpGebaeudePROT;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;





void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c6090(unsigned char*, int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_005500a0(char* o)
{
	unsigned char* e;
	unsigned char* t;

	e = 0;
	gm_ResolveEntityById((void**) (&e), 0, 0, *(int*) (o + 0xb0));
	if (e == 0) {
		fcn_00546190(o);
	}
	t = lpGebaeudePROT + *e * 0x24d;
	*(int*) (o + 0xbc) = fcn_004c6090(e, 0, t[0x22f], 0);
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 6, 0);
}
