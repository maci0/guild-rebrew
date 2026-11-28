


#include <string.h>

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);
void __cdecl gm_AddTime(struct pos14*, int, int, int);
#include "Develop/DieGildeAddOn/game/client_placement.h"
int __cdecl d3_CollectUnusedSceneObjects(char*, char*);
int __cdecl d3_FindNearestSceneObject(char*, char*);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00559b80 */
void __cdecl he_AllocGebaeudeBauen(char* u)
{
	char text[0x80];
	char list[0x400];
	char* e;
	int saved;
	int n;
	int i;

	for (e = he_StartHandlungSearch(1, 0, 0xd); e != 0; e = he_fn_Handlung()) {
		if (e != u && *(int*) (e + 0x70) < 5) {
			he_FreeAction(u);
			return;
		}
	}
	*(struct pos14*) (u + 0x52) = *(struct pos14*) (u + 0x44);
	*(struct pos14*) (u + 0x60) = *(struct pos14*) (u + 0x44);
	gm_AddTime((struct pos14*) (u + 0x52), 0, 1, 0);
	*(int*) (u + 0xc4) = 0;
	*(int*) (u + 0xc8) = 0;
	if (lc_GetBauplatzPrefix(*(int*) (u + 0xb0), text) == 0) {
		he_FreeAction(u);
		return;
	}
	saved = d3_CurrentContextIndex;
	memset(list, 0, sizeof(list));
	d3_SelectSceneContext(0, 1);
	n = d3_CollectUnusedSceneObjects(text, list);
	if (n == 0) {
		d3_SelectSceneContext(saved, 1);
		he_FreeAction(u);
		return;
	}
	for (i = 0; i < n; i++) {
		if (d3_FindNearestSceneObject(u + 0xd4, list) == 0) {
			he_FreeAction(u);
			d3_SelectSceneContext(saved, 1);
			return;
		}
	}
	io_FormatTextBuffer(text, (int) "he_AllocGebaeudeBauen: %1N1", *(unsigned short*) (u + 8));
	d3_SelectSceneContext(saved, 1);
	*(int*) (u + 0x84) = -1;
}
