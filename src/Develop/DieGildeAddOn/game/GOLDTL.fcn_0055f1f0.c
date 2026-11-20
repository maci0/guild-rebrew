#include "Develop/DieGildeAddOn/game/spiel.h"



#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl he_FreeAction(char*);

void __cdecl fcn_0055f1f0(char* e)
{
	unsigned char* r;

	r = 0;
	*(pos14_7f4c00*) (e + 0xc0) = *(pos14_7f4c00*) (e + 0x44);
	fcn_00500bb0((pos14_7f4c00*) (e + 0xc0), 0, *(int*) (e + 0xb8) * *(int*) (e + 0xb0), 0);
	*(pos14_7f4c00*) (e + 0x52) = *(pos14_7f4c00*) (e + 0x44);
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0, 1);
	gm_ResolveEntityById(0, (void**) (&r), 0, *(int*) (e + 0xac));
	if (r != 0) {
		if ((r[0x13] & 0x20) != 0) {
			he_FreeAction(e);
			return;
		}
		fcn_004c5420(*(int*) (r + 2), 0x13, 1, 0x20, 0);
	}
	*(pos14_7f4c00*) (e + 0x60) = gm_GameTime;
	*(int*) (e + 0xb4) = r[0x12] + *(int*) (e + 0xb0) < 100 ? r[0x12] + *(int*) (e + 0xb0) : 100;
}
