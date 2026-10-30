#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern s_77e8c0 g_77e8c0[16];

int __cdecl fcn_00500cb0(pos14_7f4c00*, pos14_7f4c00*);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x005455b0 */
unsigned int __cdecl fcn_005455b0(void)
{
	pos14_7f4c00 pos;
	s_77e8c0* r;
	char* p;
	char* found;
	int foundi;
	int i;

	pos = g_7f4c00;
	found = 0;
	foundi = -1;
	for (i = 0, r = g_77e8c0; (int) r < (int) (g_77e8c0 + 16); r++, i++) {
		if (r->p != 0 && r->h != -1) {
			if (fcn_00500cb0((pos14_7f4c00*) (r->p + 0x44), &pos) < 0) {
				p = r->p;
				foundi = i;
				pos = *(pos14_7f4c00*) (p + 0x44);
				found = p;
			}
		}
	}
	if (found != 0) {
		fcn_00545780(found);
		fcn_00546190(found);
		return 0xf;
	}
	if (foundi != -1) {
		__asm { int 3 }
	}
	return foundi;
}
