int* __cdecl gm_GetEquippedCombatGear(char*);

// SIZE 0x20

#include "Develop/client_types.h"
extern s_7e2ac0 g_7e2ac0[48];



/* ADDRESS: GOLDTL 0x00529800 */
int __cdecl d2_GetEntityGearIcons(char* entity, int* out)
{
	int n;
	int i;
	unsigned char* s;
	int* p;

	n = 0;
	s = *(unsigned char**) (entity + 0x17c);
	if (s != 0 && *s != 0) {
		for (i = 0; i < 48; i++) {
			if (g_7e2ac0[i].key == *s) {
				out[n++] = g_7e2ac0[i].v;
				if (g_7e2ac0[i].w != -1) {
					out[n++] = *(unsigned short*) (s + g_7e2ac0[i].w) + 0xdf;
					break;
				}
			}
		}
	}
	p = gm_GetEquippedCombatGear(entity);
	if (p != 0 && *p != 0) {
		out[n++] = *p + 0xdf;
	}
	return n;
}
