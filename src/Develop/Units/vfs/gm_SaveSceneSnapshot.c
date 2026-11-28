#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* lpGebaeudeINST;



void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_SaveScene(int, int);

/* ADDRESS: GOLDDE 0x00507df0 */
int __cdecl gm_SaveSceneSnapshot(int a)
{
	int save;
	int i;
	char* e;

	save = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	for (i = 0; i < 0x100; i++) {
		if (((char*)lpGebaeudeINST)[i * 0xa9] != 0 && *(char**) (((char*)lpGebaeudeINST) + i * 0xa9 + 0x61) != 0) {
			*(int*) (*(char**) (((char*)lpGebaeudeINST) + i * 0xa9 + 0x61) + 0x204) =
			    *(int*) (((char*)lpGebaeudeINST) + i * 0xa9 + 1);
		}
	}
	d3_SaveScene(0, a);
	for (i = 0; i < 0x100; i++) {
		e = ((char*)lpGebaeudeINST) + i * 0xa9;
		if (*e != 0 && *(char**) (e + 0x61) != 0) {
			*(char**) (*(char**) (e + 0x61) + 0x204) = e;
		}
	}
	d3_SelectSceneContext(save, 1);
	return 1;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_869480[674836];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_8f9480[82080];
unsigned char _dpad_90d524[2924];
#endif
