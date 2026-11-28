#include "Develop/client_types.h"
extern D2_FORM_RECORD d2_Forms[];

void __cdecl d2_BlitBufferToSurface(int a, int b, int c, int d, int e, int f, int g, int h);

/* ADDRESS: GOLDTL 0x00471340 */
/* ADDRESS: GOLDDE 0x00464840 */
void __cdecl d2_ResetFormBackground(int form_idx)
{
	char* base;
	char** pp;
	int j;

	base = ((char*)d2_Forms) + form_idx * 0x2bc;
	pp = (char**) (base + 0x1ac);
	for (j = 2; j != 0; j--) {
		d2_BlitBufferToSurface(0, 0, *(int*) (*pp + 4), *(int*) (*pp + 8), *(int*) (*pp + 0x20), 0, 0, *(int*) ((char*) pp - 8));
		pp++;
	}
	base[0x1b4] = 0;
	base[0x1f4] = 0;
}
