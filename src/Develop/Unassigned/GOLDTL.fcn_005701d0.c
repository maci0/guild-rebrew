extern char g_77e020[];

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
void __cdecl gm_GenerateShuffledIndices(int, char*);

void __cdecl he_InitEvent0x84Rumors(char* o)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (o + 0x52);
	*p = gm_GameTime;
	if (he_StartHandlungSearch(1, 0, 0x83) != 0) {
		p->a = gm_GameTime.a + 4;
	} else {
		p->a = gm_GameTime.a;
	}
	*(short*) (o + 0x56) = 8;
	*(int*) (o + 0x58) = 0;
	gm_GenerateShuffledIndices(0x1a, g_77e020);
}
