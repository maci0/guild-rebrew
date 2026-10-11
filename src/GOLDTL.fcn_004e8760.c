// FUNCTION: GOLD 0x004e6ba0
// FUNCTION: GOLDTL 0x4e8760

typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[7];
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl fcn_004c6b60(char*);

int __cdecl fcn_004e8760(char* x, unsigned char* a, unsigned char* b)
{
	char m[0xc];
	rec18 a1;
	rec18 b1;
	rec18 a2;
	rec18 b2;

	if (x == 0 || a == 0 || b == 0)
		return -1;
	if (srv_GetEntityOfficeSlot(a, &a1, &a2) == 0)
		return -1;
	if (srv_GetEntityOfficeSlot(b, &b1, &b2) == 0)
		return -1;
	if (a1.kind != b1.kind || a1.id != b1.id)
		return -1;
	*(int*) m = *(int*) (x + 4);
	m[4] = a2.c0;
	m[5] = b2.c0;
	*(int*) (m + 6) = 6;
	return fcn_004c6b60(m);
}
