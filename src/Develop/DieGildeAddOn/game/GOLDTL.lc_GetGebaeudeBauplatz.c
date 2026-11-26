#include "client_placement.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_633444;
extern int g_67a370;
extern char s_6aa1b4[];

int __cdecl sprintf(char*, const char*, ...);
#ifdef REBREW_GOLD
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_TransformPoint(char*, float*, float*);
char __cdecl d3_VisitSceneObjectsUntilStopped(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_RenderState d3_SelectSceneContext
#define lc_ScenePoint d3_TransformPoint
#define lc_WalkScene d3_VisitSceneObjectsUntilStopped
#define lc_SavedRender g_633444
#else
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_TransformPoint(char*, float*, float*);
char __cdecl d3_VisitSceneObjects(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_RenderState d3_SelectSceneContext
#define lc_ScenePoint d3_TransformPoint
#define lc_WalkScene d3_VisitSceneObjects
#define lc_SavedRender d3_CurrentContextIndex
#endif
int __cdecl lc_GetGebaeudeBauplatz(LC_GEBAEUDE_BAUPLATZ* out, unsigned char* obj)
{
	char buf[0x100];
	int old;

	if (*(char**) (obj + 0x61) == 0) {
		return 0;
	}
	old = lc_SavedRender;
	lc_RenderState(0, 1);
	*(int*) out->name = 0;
	if (fcn_00597ff0(obj[0], out->name) == 0) {
		lc_RenderState(old, 1);
		return 0;
	}
	lc_ScenePoint(*(char**) (obj + 0x61), (float*) (*(char**) (obj + 0x61) + 0x4c), out->position);
	sprintf(buf, s_6aa1b4, out->position[0], out->position[1], out->position[2]);
	out->node = 0;
	lc_WalkScene((char*) g_67a370, 0, 0x180, lc_MatchGebaeudeBauplatzNode, out);
	if (out->node == 0) {
		lc_RenderState(old, 1);
		return 0;
	}
	lc_RenderState(old, 1);
	return 1;
}
