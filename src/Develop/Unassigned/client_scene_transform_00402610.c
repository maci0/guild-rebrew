#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;
extern int g_6b8300;
extern char g_10432c0[];
int __cdecl d3_GetContextIndex(char* p);
void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl d3_InitUniverse(int flags);
int __cdecl fcn_0045b700(int a, int b, int c);
void __cdecl ch_BackupGrid(int r);
void __cdecl d3_DeinitUniverse(int flags);
int __cdecl d3_GetContextIndex(char* p);
void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl d3_InitUniverse(int flags);
int __cdecl fcn_0045b700(int a, int b, int c);
void __cdecl ch_BackupGrid(int r);
void __cdecl d3_DeinitUniverse(int flags);

/* ADDRESS: GOLD 0x00402140 */
/* ADDRESS: GOLDTL 0x00402610 */
int __cdecl d3sm_GetObjectSuperMap(char* obj)
{
	int saved;
	int flags;
	int ctx_flags;
	int supermap;
	char* scene;

	saved = d3_CurrentContextIndex;
	scene = *(char**) (obj + 0x88);
	flags = 0;
	supermap = *(int*) (scene + 0xb0);
	if (supermap == 0) {
		ctx_flags = g_6b8058;
		if (scene != (*(char**)&g_67a370)) {
			ctx_flags = *(int*) (scene + 0x3d8);
		}
		if (*(scene + 0x3d5) == 0 && ctx_flags != 0) {
			d3_SelectSceneContext(d3_GetContextIndex(scene), 1);
			flags = ctx_flags & ~2;
			d3_InitUniverse(flags);
		}
		*(int*) (*(char**) (obj + 0x88) + 0xb0) =
			fcn_0045b700(g_6b8300, *(int*) (*(char**) (obj + 0x88) + 0xb4), 2);
		scene = *(char**) (obj + 0x88);
		supermap = *(int*) (scene + 0xb0);
		if (scene != g_10432c0 && (*(char**)&g_67a370) == scene && supermap != 0) {
			ch_BackupGrid(supermap);
		}
		if (flags != 0) {
			d3_DeinitUniverse(flags);
			d3_SelectSceneContext(saved, 1);
		}
	}
	return supermap;
}

/* ADDRESS: GOLD 0x00402220 */
/* ADDRESS: GOLDTL 0x004026f0 */
int __cdecl d3sm_GetSceneSuperMap(char* scene)
{
	int supermap;
	int ctx_flags;
	int flags;
	int saved;

	saved = d3_CurrentContextIndex;
	flags = 0;
	supermap = *(int*) (scene + 0xb0);
	if (supermap == 0) {
		ctx_flags = g_6b8058;
		if (scene != (*(char**)&g_67a370)) {
			ctx_flags = *(int*) (scene + 0x3d8);
		}
		if (*(scene + 0x3d5) == 0 && ctx_flags != 0) {
			d3_SelectSceneContext(d3_GetContextIndex(scene), 1);
			flags = ctx_flags & ~2;
			d3_InitUniverse(flags);
		}
		supermap = fcn_0045b700(g_6b8300, *(int*) (scene + 0xb4), 2);
		*(int*) (scene + 0xb0) = supermap;
		if (scene != g_10432c0 && (*(char**)&g_67a370) == scene && supermap != 0) {
			ch_BackupGrid(supermap);
		}
		if (flags != 0) {
			d3_DeinitUniverse(flags);
			d3_SelectSceneContext(saved, 1);
		}
	}
	return supermap;
}
