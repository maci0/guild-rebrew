extern char d3_ActiveScene[];
extern char g_6b5cfc[];
#include "Develop/Units/d3/d3_object.h"


int __cdecl d3_GetContextIndex(int);
void __cdecl d3_SelectSceneContext(int, int);


/* ADDRESS: GOLDDE 0x004168e0 */
void __cdecl d3_DestroySunRayObject(char* p)
{
	int k;
	int save;

	save = *(int*) ((int) &g_6b5cfc + 0x2314);
	k = -1;
	if (*(int*) (p + 0x20c) != *(int*) &d3_ActiveScene) {
		k = d3_GetContextIndex(*(int*) (p + 0x20c));
		d3_SelectSceneContext(k, 1);
	}
	d3_DestroyObject((D3_OBJECT*) (p));
	*(int*) &g_6b5cfc = 0;
	if (k != -1) {
		d3_SelectSceneContext(save, 1);
	}
}
