extern char g_102d278[];
#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00472900 */
/* ADDRESS: GOLDDE 0x00465ac0 */
void __cdecl d2_SetElementFont(int i, int v)
{
	D2_CONTROL_TL* e;

	e = &((D2_CONTROL_TL*)d2_Controls)[i];
	*(int*)&e->font = v;
	switch (*(int*)&e->kind) {
	case 0x40:
		*(int*) (((int) &d2_Controls + 0x32c) + *(int*)&e->value_088 * 0x3cc) = v;
		break;
	case 0x41:
		*(int*) ((int) &g_102d278 + *(int*)&e->value_088 * 0x160) = v;
		break;
	}
}
