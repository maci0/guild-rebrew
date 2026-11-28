typedef struct IRes IRes;
// SIZE 0xc
typedef struct {
	void* slots[2];
	unsigned long (__stdcall* Release)(IRes*);
} IResVtbl;
// SIZE 0x4
struct IRes {
	IResVtbl* v;
};

extern unsigned long d3_LastReleaseRefCount;
extern int d3_CurrentFloor;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_ReleaseVertexBufferPtr(void);
void __cdecl d3_ReleaseTerrainSurfaces(int a);
void __cdecl d3_ReleaseSkyDomeBuffers(int a);
void __cdecl d3_ResetSceneAuxSlots(void);
void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl d3_ReleaseAllShadowTextures(void);
void __cdecl d3_InvalidateDeviceResources(void);
void __cdecl d3_ResetGraphicsDevice(void);
int __cdecl d3_TestCooperativeLevel(void);
int __cdecl d3_RestoreDeviceResources(void);
void __cdecl d3_ResetRenderStates(int a);
void __cdecl d3_AllocRenderVertexBuffer(void);
void __cdecl d3_RebuildFloorMeshes(int a);
void __cdecl d3_CreateSkyDomeBuffers(int a);
void __cdecl d3_AllocShadowTextures(void);
#include "Develop/Units/d3/client_lighting.h"

/* ADDRESS: GOLDTL 0x0043b360 */
char __cdecl d3_ResetDeviceObjects(void)
{
	char* o;
	int saved;
	int i;
	char r;

	r = 0;
	d3_ReleaseVertexBufferPtr();
	for (o = g_1042c38; o != g_1042d00; o = *(char**) (o + 0x1f8)) {
		if (*(IRes**) (o + 0x268) != 0) {
			d3_LastReleaseRefCount = (*(IRes**) (o + 0x268))->v->Release(*(IRes**) (o + 0x268));
			*(IRes**) (o + 0x268) = 0;
		}
	}
	if (d3_CurrentFloor != 0) {
		d3_ReleaseTerrainSurfaces(d3_CurrentFloor);
	}
	if (g_6b89c0 != 0) {
		d3_ReleaseSkyDomeBuffers(g_6b89c0);
	}
	d3_ResetSceneAuxSlots();
	saved = d3_CurrentContextIndex;
	for (i = 0; i < 0x40; i++) {
		if (i != saved) {
			d3_SelectSceneContext(i, 1);
			if (d3_CurrentFloor != 0) {
				d3_ReleaseTerrainSurfaces(d3_CurrentFloor);
			}
			if (g_6b89c0 != 0) {
				d3_ReleaseSkyDomeBuffers(g_6b89c0);
			}
			d3_ResetSceneAuxSlots();
		}
	}
	d3_SelectSceneContext(saved, 1);
	d3_ReleaseAllShadowTextures();
	d3_InvalidateDeviceResources();
	d3_ResetGraphicsDevice();
	if (d3_TestCooperativeLevel() == 0) {
		d3_RestoreDeviceResources();
		d3_ResetRenderStates(0);
		d3_AllocRenderVertexBuffer();
		if (d3_CurrentFloor != 0) {
			d3_RebuildFloorMeshes(d3_CurrentFloor);
		}
		if (g_6b89c0 != 0) {
			d3_CreateSkyDomeBuffers(g_6b89c0);
		}
		d3_AllocShadowTextures();
		for (i = 0; i < 0x40; i++) {
			if (i != saved) {
				d3_SelectSceneContext(i, 1);
				if (d3_CurrentFloor != 0) {
					d3_RebuildFloorMeshes(d3_CurrentFloor);
					UpdateSceneLighting(1);
				}
				if (g_6b89c0 != 0) {
					d3_CreateSkyDomeBuffers(g_6b89c0);
				}
			}
		}
		d3_SelectSceneContext(saved, 1);
		UpdateSceneLighting(1);
		r = 1;
	}
	return r;
}
