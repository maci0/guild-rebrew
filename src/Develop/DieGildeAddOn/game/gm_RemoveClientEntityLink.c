


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl cm_SendSetHE(int a, char* q);
int __cdecl d3_GetContextIndex(int x);
void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl ch_DestroyCharacter(char* r);
char* __cdecl gm_EntityAccumulate(char* p);
int __cdecl gm_RemoveLinkedNodeById(char* list, int id);

void __cdecl gm_RemoveClientEntityLink(char* p)
{
	int save;
	char* q;
	char* r;
	char* e;

	save = d3_CurrentContextIndex;
	q = *(char**) (p + 0x24);
	if (q != 0 && (q[0x78] & 2)) {
		*(int*) (q + 0x84) = cm_SendSetHE(-1, q);
	}
	r = *(char**) (p + 0x3b);
	if (r != 0) {
		d3_SelectSceneContext(d3_GetContextIndex(*(int*) (r + 0x88)), 1);
		ch_DestroyCharacter(r);
		d3_SelectSceneContext(save, 1);
	}
	e = gm_EntityAccumulate(p);
	if (e != 0) {
		gm_RemoveLinkedNodeById(e + 0x5d, *(int*) (p + 2));
	}
}
