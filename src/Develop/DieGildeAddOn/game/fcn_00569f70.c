#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

/* Finds a record other than the entity whose 0xac field matches the entity's,
 * flags that entity, then copies the current selection into it. */
/* ADDRESS: GOLDTL 0x00569f70 */
void __cdecl fcn_00569f70(char* ent)
{
	pos14_7f4c00* q;
	char* p;

	p = fcn_005463a0(1, 0, 0x3f);
	if (p != 0) {
		do {
			if (p != ent && *(int*) (p + 0xac) == *(int*) (ent + 0xac)) {
				break;
			}
			p = he_fn_Handlung();
		} while (p != 0);
		if (p != 0) {
			*(int*) (ent + 0x70) = -1;
		}
	}
	q = (pos14_7f4c00*) (ent + 0x52);
	*q = g_7f4c00;
	fcn_00500bb0(q, 0, 0, 1);
}
