#include "Develop/DieGildeAddOn/game/spiel.h"



#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;

int __cdecl fcn_00500cb0(pos14_7f4c00*, pos14_7f4c00*);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00510820(int, char*, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunAction0x0c(char* u)
{
	char* x;

	switch (*(int*) (u + 0x70)) {
	case 0:
		if (fcn_00500cb0((pos14_7f4c00*) (u + 0x52), &gm_GameTime) > 0) {
			break;
		}
		*(int*) (u + 0xc8) = fcn_004c51f0(*(int*) (u + 0xac), -1, *(int*) (u + 0xb4), 1, g_773d75, 0);
		(*(int*) (u + 0x70))++;
		break;
	case 1:
		if (fcn_004c4450(*(int*) (u + 0xc8)) == 0) {
			break;
		}
		if (fcn_004c4450(*(int*) (u + 0xc8)) == 2) {
			goto kill;
		}
		x = fcn_004c4480(*(int*) (u + 0xc8));
		*(int*) (u + 0xb8) = *(int*) (x + 2);
		*(int*) (u + 0xc0) = 0x20;
		*(int*) (u + 0xc4) = 0;
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
		(*(int*) (u + 0x70))++;
		break;
	case 2:
		if (fcn_00500cb0((pos14_7f4c00*) (u + 0x52), &gm_GameTime) >= 0) {
			break;
		}
		do {
			gm_ResolveEntityById(0, (void**) (&x), 0, *(int*) (u + 0xb8));
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
			if (*(int*) (u + 0xc4) > *(int*) (u + 0xc0)) {
				fcn_00510820(*(int*) (x + 0x18), x, 1);
				he_FreeAction(u);
				break;
			}
		} while (fcn_00500cb0((pos14_7f4c00*) (u + 0x52), &gm_GameTime) < 0);
		break;
	case -2:
	case -1:
kill:
		he_FreeAction(u);
		break;
	}
}
