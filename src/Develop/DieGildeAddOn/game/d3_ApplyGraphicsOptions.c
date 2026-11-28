

typedef struct Flags215 {
	char pad0[0x215];
	unsigned char lit : 1;
	unsigned char mirror : 1;
} Flags215;
// SIZE 0x216

typedef struct Node {
	char pad0[0x34];
	Flags215* flags;
	char pad38[0x88 - 0x38];
	void* owner;
} Node;
// SIZE 0x8c

typedef struct Pair {
	int a;
	int b;
} Pair;
// SIZE 0x8

extern int d3_GfxDetails;
extern unsigned char g_776665;
extern unsigned char g_776666;
extern unsigned char g_776667;
extern unsigned char g_776668;
extern unsigned char g_776669;
extern unsigned char g_77666b;
extern int g_77666c;
extern float g_776670[3];
extern float g_77667c;
extern float g_776680[3];
extern float g_77668c;
extern float g_776690[3];
extern float g_77669c;
extern unsigned char ch_DefaultMirrorFlag;
extern int g_104336c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;
extern float g_67a964;
extern char d3_Universes[];
extern Pair g_6a2528[];
extern Pair g_6a2540[];
extern char gm_InWorldHud;
extern float g_774694;
extern unsigned char g_6b8304;

void __cdecl d3_UpdateSceneDetailLevel(int, int);
void __cdecl d3_SelectSceneContext(int, int);
#include "Develop/Units/d3/client_scene_loader.h"
void __cdecl ch_SetLowPolyMode(unsigned char);
void __cdecl d3_SetCameraHeightFraction(int);
void __cdecl fcn_0043bbf0(unsigned char);
void __cdecl d3_ReleaseUnusedSceneObjects(void);
void __cdecl d3_SetHighlightMode(int);
void __cdecl d3_SetGammaParams(float*, float*, float*);

/* ADDRESS: GOLDDE 0x005c3800 */
void __cdecl d3_ApplyGraphicsOptions(void)
{
	unsigned char hi;
	float c[3];
	float b[3];
	float a[3];
	int depth;
	int width;
	int saved;
	int i;
	float s;

	depth = 0;
	width = (*(int*)&g_104061c);
	hi = 0;
	if (g_776667 == 0) {
		hi = g_776667;
		ch_DefaultMirrorFlag = 1;
		width = 0x20;
	} else if (g_776667 == 1) {
		ch_DefaultMirrorFlag = g_776667;
		width = 0x20;
		hi = 1;
	} else if (g_776667 == 2) {
		ch_DefaultMirrorFlag = 0;
		width = 0x40;
		hi = 1;
	}
	d3_UpdateSceneDetailLevel(g_104336c, 0);
	if (g_776666 == 0) {
		depth = 2;
	} else if (g_776666 == 1) {
		depth = 4;
	}
	if (depth != d3_LODMode) {
		saved = d3_CurrentContextIndex;
		d3_LODMode = depth;
		d3_SelectSceneContext(0, 0);
		d3_ReloadSceneResources(0x40, 3, 0);
		d3_SelectSceneContext(saved, 0);
	}
	d3_ConfigureSceneRenderQuality(g_776668, 0, 2 - g_776665, hi * width, 0);
	if ((*(int*)&d2_VisitedBuilding) == 0 && (*(int*)&d2_InteriorBuilding) == 0) {
		g_67a964 = (float) (1.0 - (g_77666c & 0xff) * 0.01);
	}
	for (i = 0; i < 768; i++) {
		if (((Node**)ch_CharacterSlots)[i] != 0 && ((Node**)ch_CharacterSlots)[i]->owner == &(*(char*)d3_Universes)) {
			((Node**)ch_CharacterSlots)[i]->flags->mirror = ch_DefaultMirrorFlag;
		}
	}
	ch_SetLowPolyMode(g_77666b);
	(*(Pair*)&g_6a2558) = g_6a2528[g_776669];
	(*(Pair*)&g_6a2560) = g_6a2540[g_776669];
	if ((*(unsigned char*)&gm_InWorldHud)) {
		d3_SetCameraHeightFraction((*(int*)&g_774694));
	}
	if (g_6b8304 != g_776668) {
		fcn_0043bbf0(g_776668);
	}
	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	d3_ReleaseUnusedSceneObjects();
	if ((*(unsigned char*)&d3_GfxDetails) == 0) {
		d3_SetHighlightMode(0);
	} else {
		d3_SetHighlightMode(1);
	}
	d3_SelectSceneContext(saved, 1);
	s = (g_77667c + 0.5f) * 0.5f;
	for (i = 0; i < 3; i++) {
		a[i] = s + g_776670[i] - 0.5f;
		b[i] = g_77668c * g_776680[i];
		c[i] = g_77669c * g_776690[i];
	}
	d3_SetGammaParams(a, b, c);
}
