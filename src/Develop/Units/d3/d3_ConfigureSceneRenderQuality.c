

// SIZE 0x3dc
typedef struct Player {
	int active;
	char rest[0x3d8];
} Player;

// SIZE 0x1
typedef struct Flags {
	unsigned char lo : 2;
	unsigned char on : 3;
	unsigned char hi : 3;
} Flags;

extern int d3_CurrentContextIndex;
#include "Develop/client_types.h"
extern Slot_1043340 g_1043340[64];
extern unsigned int g_10405fc;
extern unsigned int g_104061c;
extern Flags d3_RenderQualityFlags;
extern unsigned char g_6b7ff8;

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_ResetSceneAuxSlots(void);
void __cdecl d3_ReleaseAllShadowTextures(void);
void __cdecl d3_AllocShadowTextures(void);
void __cdecl fcn_0043bbf0(unsigned char);
#include "Develop/Units/d3/client_scene_loader.h"

/* ADDRESS: GOLDDE 0x004325a0 */
void __cdecl d3_ConfigureSceneRenderQuality(unsigned char a1, int a2, unsigned char a3, unsigned int a4, SCENE_PROGRESS progress)
{
	int save;
	unsigned int i;
	unsigned int t;

	save = d3_CurrentContextIndex;
	d3_ResetSceneAuxSlots();
	for (i = 0; i < 64; i++) {
		if (i != (unsigned int)save && ((Player*)g_1043340)[i].active != 0) {
			d3_SelectSceneContext(i, 1);
			d3_ResetSceneAuxSlots();
		}
	}
	d3_SelectSceneContext(save, 1);
	t = g_10405fc;
	d3_ReleaseAllShadowTextures();
	d3_RenderQualityFlags.on = a4 > 0;
	g_104061c = t < a4 ? t : a4;
	d3_AllocShadowTextures();
	fcn_0043bbf0(a1);
	if (g_6b7ff8 != a3) {
		g_6b7ff8 = a3;
		d3_ReloadSceneTextureSurfaces(progress);
	}
}
