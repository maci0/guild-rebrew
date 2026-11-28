typedef struct {
	int used;
	char pad4[0x3d8];
} Slot_439490;
// SIZE 0x3dc

typedef void (__cdecl* node_fn_439490)(char* node);

extern char g_6b8018;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/client_types.h"
extern Slot_1043340 g_1043340[64];
extern int g_6b8484;
extern int d3_CurrentFloor;
extern int d3_ActiveScene;
extern int g_6b8064;

void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl d3_DisposeObject(char* p);
void __cdecl d3_FreeMeshObject(char* p);
void __cdecl d3_ReleaseRenderDeviceContext(int a);
void __cdecl d3_FreeSkyDome(int a);
void __cdecl m_FreeTracked(void* p);
void __cdecl d3_ReleaseRenderVertexBuffer(void);
#include "Develop/Units/d3/d3_animation.h"
void __cdecl m_pool_free_all(int* p);
void __cdecl d3_DestroySkySystem(void);
void __cdecl d3s_ReleaseCache(void);
void __cdecl fcn_0043bc20(void);
void __cdecl d3_ReleaseAllRenderTextures(void);
void __cdecl d3_ResetLightBuffers(void);
void __cdecl fcn_00436fc0(void);

/* ADDRESS: GOLDTL 0x00439490 */
/* ADDRESS: GOLDDE 0x004323a0 */
void __cdecl d3_Shutdown(void)
{
	int saved;
	int i;

	if (g_6b8018 == 0) {
		return;
	}
	saved = d3_CurrentContextIndex;
	g_6b8018 = 0;
	for (i = 0; i < 64; i++) {
		if (i != saved && ((Slot_439490*)g_1043340)[i].used != 0) {
			d3_SelectSceneContext(i, 1);
			while (d3_ObjectListHead != d3_SceneObjectSentinel) {
				d3_DisposeObject(d3_ObjectListHead);
			}
			g_6b8484 = 0;
			while (d3_SceneRenderListHead != g_1040640) {
				d3_FreeMeshObject(d3_SceneRenderListHead);
			}
			if (d3_CurrentFloor != 0) {
				d3_ReleaseRenderDeviceContext(d3_CurrentFloor);
				d3_CurrentFloor = 0;
			}
			if (g_6b89c0 != 0) {
				d3_FreeSkyDome(g_6b89c0);
				g_6b89c0 = 0;
			}
			if (*(void**) (((char*)d3_ActiveScene) + 0x3c8) != 0) {
				m_FreeTracked(*(void**) (((char*)d3_ActiveScene) + 0x3c8));
				*(void**) (((char*)d3_ActiveScene) + 0x3c8) = 0;
			}
		}
	}
	if (saved != d3_CurrentContextIndex) {
		d3_SelectSceneContext(saved, 1);
	}
	while (d3_ObjectListHead != d3_SceneObjectSentinel) {
		d3_DisposeObject(d3_ObjectListHead);
	}
	if (d3_CurrentFloor != 0) {
		d3_ReleaseRenderDeviceContext(d3_CurrentFloor);
		d3_CurrentFloor = 0;
	}
	if (g_6b89c0 != 0) {
		d3_FreeSkyDome(g_6b89c0);
		g_6b89c0 = 0;
	}
	d3_ReleaseRenderVertexBuffer();
	if (*(void**) (((char*)d3_ActiveScene) + 0x3c8) != 0) {
		m_FreeTracked(*(void**) (((char*)d3_ActiveScene) + 0x3c8));
		*(void**) (((char*)d3_ActiveScene) + 0x3c8) = 0;
	}
	while (g_1042c38 != g_1042d00) {
		(*(node_fn_439490*) (g_1042c38 + 0x1ec))(g_1042c38);
	}
	while (g_1042320 != g_1052a40) {
		d3_ReleaseAnim(g_1042320, 1);
	}
	m_pool_free_all(&g_6b8064);
	d3_DestroySkySystem();
	d3s_ReleaseCache();
	fcn_0043bc20();
	d3_ReleaseAllRenderTextures();
	d3_ResetLightBuffers();
	g_1041d08 = 0;
	fcn_00436fc0();
}
