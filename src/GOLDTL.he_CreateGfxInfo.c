#include <stdio.h>
#include "he_tables.h"

extern int g_6b8010;
extern Rec7dc6e0 g_7dc6e0[64];

void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(char*, int, char*, char*);
char* __cdecl fcn_00546590(char*, char*, char*);

/* ADDRESS: GOLDTL 0x00546720 */
void __cdecl he_CreateGfxInfo(unsigned char* p, char* name, char* entity)
{
	char buf[0x200];
	Rec7dc6e0* slot;
	char* created;
	int saved;
	int i;

	saved = g_6b8010;
	if (*(unsigned char*) 0x7766bb == 0)
		goto done;
	for (i = 0; i < 0x40; i++) {
		if (*(int*) (0x7dc6e4 + i * 0x10) == 0)
			break;
	}
	if (i == 0x40)
		goto done;
	slot = &g_7dc6e0[i];
	fcn_004432d0(0, 1);
	created = fcn_00445600(0, 0x40, entity, 0);
	if (created == 0) {
		sprintf(buf, "he_CreateGfxInfo(): invalid parent :%s", entity);
		fcn_004432d0(saved, 1);
	} else {
		slot->b = (char*) p;
		slot->a = *(int*) (p + 4);
		slot->c = 0;
		*(unsigned char**) (p + 0x88) = (unsigned char*) slot;
		fcn_00546590((char*) slot, name, entity);
		fcn_004432d0(saved, 1);
	}
done:
	return;
}
