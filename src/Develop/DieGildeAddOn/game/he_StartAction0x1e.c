


#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad1[0x24c];
};
#pragma pack()

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudePROT;
extern int g_774800;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_StartAction0x1e(char* e)
{
	unsigned char* t;
	char* g;
	int d;

	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	*(pos14_7f4c00*) (e + 0x44) = gm_GameTime;
	t = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
	if (t == 0) {
		he_FreeAction(e);
		return;
	}
	if (g_774800 == 0) {
		g = (char*) &((struct good*)lpGebaeudePROT)[*t];
		d = (*(int*) (g + 0x490) - *(int*) (g + 0x243)) * 24;
		if (d <= 0) {
			d = 24;
		}
		gm_AddTime((pos14_7f4c00*) (e + 0x52), d, 0, 0);
	} else {
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 0x1e, 0);
	}
	*(int*) (e + 0x10) = *(int*) (t + 1);
	if ((*(unsigned short*) (t + 0x5a) & 0x40) != 0) {
		he_FreeAction(e);
		return;
	}
	*(unsigned short*) (t + 0x5a) |= 0x40;
	cm_RequestChangeBits(*(int*) (t + 1), 0x5a, 2, 0x40, 0);
}
