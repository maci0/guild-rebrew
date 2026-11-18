


extern int he_LastEventSlot;
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/he_action.h"
extern void (__cdecl* g_7dc440[])(unsigned char*);

void __cdecl fcn_00546be0(unsigned char*);

void __cdecl fcn_00546de0(void)
{
	int i;
	unsigned char* p;

	for (i = 0; i <= he_LastEventSlot && i < 0x400; i++) {
		p = &g_77e980[i].kind;
		if (*p != 0 && (p[0x78] & 0x10) != 0 && *p < 0xa7) {
			fcn_00546be0(p);
			g_7dc440[*p](p);
		}
	}
}
