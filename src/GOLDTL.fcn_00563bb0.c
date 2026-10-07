// FUNCTION: GOLD 0x55b970
// FUNCTION: GOLDTL 0x563bb0

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad1[0x24c];
};
#pragma pack()

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* g_868050;
extern int g_774800;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00563bb0(char* e)
{
	unsigned char* t;
	char* g;
	int d;

	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	*(pos14_7f4c00*) (e + 0x44) = g_7f4c00;
	t = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
	if (t == 0) {
		fcn_00546190(e);
		return;
	}
	if (g_774800 == 0) {
		g = (char*) &((struct good*)g_868050)[*t];
		d = (*(int*) (g + 0x490) - *(int*) (g + 0x243)) * 24;
		if (d <= 0) {
			d = 24;
		}
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), d, 0, 0);
	} else {
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0x1e, 0);
	}
	*(int*) (e + 0x10) = *(int*) (t + 1);
	if ((*(unsigned short*) (t + 0x5a) & 0x40) != 0) {
		fcn_00546190(e);
		return;
	}
	*(unsigned short*) (t + 0x5a) |= 0x40;
	fcn_004c5420(*(int*) (t + 1), 0x5a, 2, 0x40, 0);
}
