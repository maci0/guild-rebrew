extern char g_77e020[];

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
void __cdecl gm_GenerateShuffledIndices(int, char*);

void __cdecl he_InitEvent0x84Rumors(char* action)
{
	pos14_7f4c00* ts;

	ts = (pos14_7f4c00*) (action + 0x52);
	*ts = gm_GameTime;
	if (he_StartHandlungSearch(1, 0, 0x83) != 0) {
		ts->a = gm_GameTime.a + 4;
	} else {
		ts->a = gm_GameTime.a;
	}
	*(short*) (action + 0x56) = 8;
	*(int*) (action + 0x58) = 0;
	gm_GenerateShuffledIndices(0x1a, g_77e020);
}
