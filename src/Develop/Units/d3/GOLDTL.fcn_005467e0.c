#include "Develop/Units/d3/d3_object.h"
#include "Develop/DieGildeAddOn/game/game_data.h"




void __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_FindSceneObject(int, int, char*, int);
void __cdecl fcn_00546480(char*);


void __cdecl d3_FreeEventGfxSlot(int* s)
{
	char* h;
	int save;

	h = (char*) s[2];
	if (s[3] != 0) {
		save = d3_CurrentContextIndex;
		s[2] = 0;
		d3_SelectSceneContext(0, 1);
		if (h != 0 && d3_FindSceneObject(0, 0x1c0, h, 0) != 0) {
			fcn_00546480(h);
		}
		d3_DestroyObject((D3_OBJECT*) ((char*) s[3]));
		s[3] = 0;
		d3_SelectSceneContext(save, 1);
	}
	s[1] = 0;
	s[0] = -1;
}
