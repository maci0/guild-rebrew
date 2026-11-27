#include "client_lighting.h"

float __cdecl d3_CalcFloorFogDistance();
void __cdecl d3_SetFogRange(float, float);

#if defined(REBREW_GOLD)
#include "Develop/Units/d3/d3_camera.h"

void __cdecl d3_ClearViewport(void*);
void __cdecl d3_ClearSoftwareViewport(void*, unsigned char, unsigned char, unsigned char);
void __cdecl d3_RenderFloor(void*, int);
void __cdecl d3_CollectFlaggedObjects(void);
char __cdecl d3_VisitSceneObjectsUntilStopped(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
char __cdecl d3_RenderSceneObject(char*, void*);
char __cdecl d3_RenderMirroredObject(char*, void*);
void __cdecl d3_UpdateAndRenderEffect(char*);
void __cdecl d3_RenderSky(void*);
void __cdecl d3_UpdateSceneOverlayObjects(void);
void __cdecl d3_FlushRenderQueues(void);
extern float g_5ebaa4;

/* ADDRESS: GOLD 0x0043e200 */
void __cdecl d3_RenderScene(unsigned int pass, int overlay)
{
    char* p;
    char* next;
    char* object;
    unsigned char c633450;
    float distance;
    float density;
    if (g_6b86d4 < 0)
        g_6b86d4 = 0;
    if (!*(unsigned char*) 0x633451 || g_6b86d4 || !d3_ActiveCamera)
        return;
    c633450 = *(unsigned char*) 0x633450;
    g_6b86d4 = 1;
    if (c633450)
        d3_ClearViewport((void*) 0xfc2930);
    else
        d3_ClearSoftwareViewport((void*) 0xfc2930, *(unsigned char*) 0x6334a2,
            *(unsigned char*) 0x6334a1, *(unsigned char*) 0x6334a0);
    *(int*) 0x633b08 = 0;
    *(int*) 0x633b0c = 0;
    *(float*) 0xfc5338 = 0.0f;
    *(float*) 0xfc5344 = 10000000000.0f;
    object = *(char**) 0x633448;
    *(int*) (*(char**) (object + 0x1ec) + 0x100) = 0;
    object = *(char**) 0x633448;
    *(int*) (*(char**) (object + 0x1ec) + 0xfc) = 0;
    if ((void*) g_6b8300) {
        if (*(unsigned char*) 0x6334a4 && *(unsigned char*) 0x6334a5) {
            object = d3_ActiveCamera;
            distance = d3_CalcFloorFogDistance((void*) g_6b8300, object + 0x4c, object + 0x18c);
            if (distance < *(float*) 0xfc5340) {
                density = (1.0f - (*(float*) 0xfc5340 - distance) / *(float*) 0xfc5340)
                    * *(float*) 0xfc29bc;
                d3_SetFogRange(density, distance);
            } else
                d3_SetFogRange(*(float*) 0xfc29bc, *(float*) 0xfc5340);
        }
        d3_RenderFloor((void*) g_6b8300, overlay);
    }
    *(int*) 0x63344c = 0;
    d3_CollectFlaggedObjects();
    *(int*) 0x633498 = 0;
    *(int*) 0x633494 = 0;
    d3_VisitSceneObjectsUntilStopped(*(char**) 0x5fb5b0, 0, pass, d3_RenderSceneObject, 0);
    object = *(char**) 0x633448;
    if (*(int*) (*(char**) (object + 0x1ec) + 0x100) > 0 &&
        (*(unsigned char*) 0xfe7671 & 7))
        d3_RenderSceneObject(object, 0);
    p = *(char**) 0xfb98f4;
    while (p != (char*) 0xfb9280) {
        next = *(char**) (p + 0x314);
        d3_UpdateAndRenderEffect(p);
        p = next;
    }
    if (*(void**) 0x633dd4)
        d3_RenderSky(*(void**) 0x633dd4);
    if ((unsigned char) overlay)
        d3_UpdateSceneOverlayObjects();
    if ((*(unsigned char*) 0xfe7670 & 0x40) && *(int*) 0x63344c &&
        *(int*) 0xfb9904 && *(int*) 0xfb9908 && (*(unsigned char*) 0xfb9928 & 1))
        d3_VisitSceneObjectsUntilStopped(*(char**) 0x5fb5b0, 0, pass, d3_RenderMirroredObject, (void*) 0xfb9900);
    if (*(float*) 0xfc5344 == g_5ebaa4)
        *(float*) 0xfc5344 = 0.0f;
    *(int*) 0x633470 = *(int*) 0xfc2dcc;
    *(int*) 0x633488 = *(int*) 0xfe75b0;
    *(int*) 0x633474 = *(int*) 0xfc7b60;
    *(int*) 0x633484 = *(int*) 0xfc2dc4;
    object = *(char**) (*(char**) 0x633448 + 0x1cc);
    *(int*) 0x633478 = *(int*) (object + 0xc);
    d3_FlushRenderQueues();
    *(int*) 0x63347c = *(int*) 0xfe75b4;
    *(int*) 0x633480 = *(int*) 0xfc2dc0;
    --g_6b86d4;
}
#else
int __cdecl m_pool_clear();
int __cdecl d3_EndScenePass();
int __cdecl d3_SetRenderMaterialState();
int __cdecl d3_RenderRootSceneObjects();
int __cdecl d3_RenderWaterFloorCells();
int __cdecl d3_RenderFloorTerrain();
int __cdecl d3_UpdateFloorVisibility();
int __cdecl d3_BeginScenePass();
void __cdecl d3_CollectSceneLights(int ctx, unsigned char mask);
void __cdecl d3_UpdateSceneLightFlickers(void);
int __cdecl d3_SelectActiveObjectLights();
int __cdecl d3_RenderPlanarReflections();
int __cdecl d3_RenderSceneList();
int __cdecl d3_BuildSceneShadows();
int __cdecl d3_RenderShadowPatches();
int __cdecl d3_UpdateAndRenderSky();

typedef struct D3_SCENE_DEVICE D3_SCENE_DEVICE;
typedef struct D3_SCENE_DEVICE_VTBL {
	char pad0[0x90];
	int (__stdcall* Clear)(D3_SCENE_DEVICE* self, int count, void* rects, int flags, int color, float z, int stencil);
	int (__stdcall* SetTransform)(D3_SCENE_DEVICE* self, int state, void* m);
	char pad98[0xc8 - 0x98];
	int (__stdcall* SetRenderState)(D3_SCENE_DEVICE* self, int state, int value);
	char padcc[0xf4 - 0xcc];
	int (__stdcall* SetTexture)(D3_SCENE_DEVICE* self, int stage, int tex);
} D3_SCENE_DEVICE_VTBL;
struct D3_SCENE_DEVICE {
	D3_SCENE_DEVICE_VTBL* vtbl;
};

typedef struct D3_SCENE_MESH D3_SCENE_MESH;
typedef struct D3_SCENE_MESH_VTBL {
	void* QueryInterface;
	void* AddRef;
	void* Release;
	int (__stdcall* DrawSubset)(D3_SCENE_MESH* self, int i);
} D3_SCENE_MESH_VTBL;
struct D3_SCENE_MESH {
	D3_SCENE_MESH_VTBL* vtbl;
};

extern void* g_6b5de0;
extern char g_6b8018, g_6b8060, g_6b8061;
extern float g_104329c, g_10425fc, g_10432a0, g_662c94;
extern int g_6b89c0, g_6b8050, g_1042a08, g_10432a8, g_1042a04, g_6b8034;
extern void* g_6b8068;
extern char* g_6b86ec;
extern char g_1052bd0[1];
extern unsigned char g_6b7ffe;
#define DEV_43ad20 ((D3_SCENE_DEVICE*) g_6b5de0)

/* ADDRESS: GOLDTL 0x0043ad20 */
void __cdecl d3_RenderScene(char a0, int a1)
{
	int v3;
	int v10;
	int* outer;
	int* drawNode;
	float fogDistance;
	int drawFlags;

	v3 = g_6b86d4;
	if (g_6b86d4 < 0) {
		v3 = 0;
		g_6b86d4 = 0;
	}
	if (g_6b8018 && !v3 && *(int*) 0x6b8014) {
		v10 = 3;
		g_6b86d4 = 1;
		DEV_43ad20->vtbl->Clear(DEV_43ad20, 1, (void*) 0x1042570, 3, *(int*) 0x6b805c, 1.0f, 0);
		*(int*) 0x1043294 = 0;
		*(int*) 0x10432a0 = 0x501502f9;
		if (*(int*) 0x6b8300) {
			d3_UpdateFloorVisibility(*(int*) 0x6b8300);
		}
		*(int*) 0x1043028 = 0;
		d3_CollectSceneLights(*(int*) 0x6b8014, ((unsigned char) g_1052bd0[0] & 0x1c) != 0);
		if (a0) {
			d3_UpdateSceneLightFlickers();
		}
		if ((unsigned char) g_1052bd0[0] & 0x1c) {
			d3_BuildSceneShadows();
		}
		if (*(int*) 0x6b8300) {
			if (g_6b8060 && g_6b8061) {
				fogDistance = d3_CalcFloorFogDistance(*(int*) 0x6b8300, *(int*) 0x6b8014 + 0x4c, *(int*) 0x6b8014 + 0x18c);
				if (fogDistance < g_104329c) {
					d3_SetFogRange((1.0f - (g_104329c - fogDistance) / g_104329c) * g_10425fc, fogDistance);
				} else {
					d3_SetFogRange(g_10425fc, g_104329c);
				}
			}
			DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x24, *(int*) 0x1042ce4);
			DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x25, *(int*) 0x1042a14);
		}
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x8b, -1);
		d3_BeginScenePass(g_6b8060, *(int*) 0x6b805c, 1);
		if (g_6b89c0) {
			d3_UpdateAndRenderSky(g_6b89c0);
		}
		if (*(int*) 0x6b8300) {
			d3_RenderFloorTerrain(*(int*) 0x6b8300);
		}
		*(int*) 0x6b8054 = 0;
		g_6b8050 = 0;
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x89, 1);
		for (v3 = (int) g_6b86ec; v3; v3 = *(int*) (v3 + 0x1f0)) {
			d3_RenderRootSceneObjects(v3, 0);
		}
		if (*(int*) 0x1043028) {
			d3_RenderPlanarReflections(*(int*) 0x1043028);
		}
		for (outer = (int*) g_6b8068; outer; outer = (int*) outer[10]) {
			DEV_43ad20->vtbl->SetTransform(DEV_43ad20, 0x100, (void*) outer[1]);
			if (outer[6] >= 0) {
				d3_SelectActiveObjectLights(outer[4], outer[5], *(int*) (*outer + 0x1cc) + 0x280, 0, 0);
			} else {
				d3_SelectActiveObjectLights(outer[4], outer[5], *(int*) (*outer + 0x1cc) + 0x280, 0x1040cc0, 0x1040c80);
			}
			drawNode = outer;
			do {
				v3 = drawNode[3];
				DEV_43ad20->vtbl->SetTexture(DEV_43ad20, 0, *(int*) (v3 + 0x50));
				drawFlags = *(unsigned char*) ((int) drawNode + 0x1e);
				d3_SetRenderMaterialState(*(unsigned char*) ((int) drawNode + 0x1c),
					(*(unsigned char*) (v3 + 0x54) & 1) * 2 | (drawFlags & 1), drawNode[8],
					(*(unsigned char*) (v3 + 0x54) >> 3) & 1, (drawFlags >> 1) & 1);
				if (!(*(unsigned char*) (v3 + 0x54) & 8) && ((unsigned int) drawNode[6] >> 0x1b & 1) != (unsigned int) (v10 == 2)) {
					v10 = (~drawNode[6] & 0x8000000U | 0x10000000) >> 0x1b;
					DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x16, v10);
				}
				((D3_SCENE_MESH*) drawNode[2])->vtbl->DrawSubset((D3_SCENE_MESH*) drawNode[2], drawNode[6] & 0x7ffffff);
				drawNode = (int*) drawNode[9];
			} while (drawNode);
		}
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x16, (g_6b7ffe == 0) * 2 + 1);
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x89, 0);
		if ((unsigned char) g_1052bd0[0] & 0x1c) {
			d3_RenderShadowPatches(*(int*) 0x6b8014);
		}
		if (*(int*) 0x6b8300) {
			d3_RenderWaterFloorCells(*(int*) 0x6b8300, a1);
		}
		m_pool_clear(0x6b8064);
		g_6b8068 = 0;
		d3_RenderSceneList();
		d3_EndScenePass();
		if (g_10432a0 == g_662c94) {
			*(int*) 0x10432a0 = 0;
		}
		*(int*) 0x6b8044 = *(int*) 0x1052bac;
		*(int*) 0x6b802c = g_1042a08;
		*(int*) 0x6b803c = *(int*) 0x1042a00;
		*(int*) 0x6b8030 = g_10432a8;
		g_6b86d4 -= 1;
		*(int*) 0x6b8040 = g_1042a04;
		g_6b8034 = 0;
		*(int*) 0x6b8038 = *(int*) 0x1052bb0;
	}
}
#endif
