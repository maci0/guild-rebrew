int __cdecl m_pool_clear();
int __cdecl fcn_00437270();
int __cdecl fcn_004372d0();
void __cdecl d3_SetFogRange(float a, float b);
int __cdecl fcn_004385e0();
int __cdecl fcn_00440f70();
int __cdecl fcn_00441400();
int __cdecl d3_UpdateFloorVisibility();
float __cdecl fcn_004424c0();
int __cdecl fcn_00437160();
void __cdecl d3_CollectSceneLights(int ctx, unsigned char mask);
void __cdecl fcn_004509c0(void);
int __cdecl fcn_00450e90();
int __cdecl fcn_00451df0();
int __cdecl d3_RenderSceneList();
int __cdecl fcn_00456e50();
int __cdecl fcn_00458bf0();
int __cdecl fcn_00459530();

typedef struct Dev_43ad20 Dev_43ad20;
typedef struct DevVtbl_43ad20 {
	char pad0[0x90];
	int (__stdcall* Clear)(Dev_43ad20* self, int count, void* rects, int flags, int color, float z, int stencil);
	int (__stdcall* SetTransform)(Dev_43ad20* self, int state, void* m);
	char pad98[0xc8 - 0x98];
	int (__stdcall* SetRenderState)(Dev_43ad20* self, int state, int value);
	char padcc[0xf4 - 0xcc];
	int (__stdcall* SetTexture)(Dev_43ad20* self, int stage, int tex);
} DevVtbl_43ad20;
struct Dev_43ad20 {
	DevVtbl_43ad20* vtbl;
};

typedef struct Mesh_43ad20 Mesh_43ad20;
typedef struct MeshVtbl_43ad20 {
	void* QueryInterface;
	void* AddRef;
	void* Release;
	int (__stdcall* DrawSubset)(Mesh_43ad20* self, int i);
} MeshVtbl_43ad20;
struct Mesh_43ad20 {
	MeshVtbl_43ad20* vtbl;
};

extern void* g_6b5de0;
#include "client_lighting.h"
extern char g_6b8018, g_6b8060, g_6b8061;
extern float g_104329c, g_10425fc, g_10432a0, g_662c94;
extern int g_6b89c0, g_6b8050, g_1042a08, g_10432a8, g_1042a04, g_6b8034;
extern void* g_6b8068;
extern char* g_6b86ec;
extern char g_1052bd0[1];
extern unsigned char g_6b7ffe;
#define DEV_43ad20 ((Dev_43ad20*) g_6b5de0)
/* ADDRESS: GOLDTL 0x0043ad20 */
void __cdecl fcn_0043ad20(char a0, int a1)
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
			fcn_004509c0();
		}
		if ((unsigned char) g_1052bd0[0] & 0x1c) {
			fcn_00456e50();
		}
		if (*(int*) 0x6b8300) {
			if (g_6b8060 && g_6b8061) {
				fogDistance = fcn_004424c0(*(int*) 0x6b8300, *(int*) 0x6b8014 + 0x4c, *(int*) 0x6b8014 + 0x18c);
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
		fcn_00437160(g_6b8060, *(int*) 0x6b805c, 1);
		if (g_6b89c0) {
			fcn_00459530(g_6b89c0);
		}
		if (*(int*) 0x6b8300) {
			fcn_00441400(*(int*) 0x6b8300);
		}
		*(int*) 0x6b8054 = 0;
		g_6b8050 = 0;
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x89, 1);
		for (v3 = (int) g_6b86ec; v3; v3 = *(int*) (v3 + 0x1f0)) {
			fcn_004385e0(v3, 0);
		}
		if (*(int*) 0x1043028) {
			fcn_00451df0(*(int*) 0x1043028);
		}
		for (outer = (int*) g_6b8068; outer; outer = (int*) outer[10]) {
			DEV_43ad20->vtbl->SetTransform(DEV_43ad20, 0x100, (void*) outer[1]);
			if (outer[6] >= 0) {
				fcn_00450e90(outer[4], outer[5], *(int*) (*outer + 0x1cc) + 0x280, 0, 0);
			} else {
				fcn_00450e90(outer[4], outer[5], *(int*) (*outer + 0x1cc) + 0x280, 0x1040cc0, 0x1040c80);
			}
			drawNode = outer;
			do {
				v3 = drawNode[3];
				DEV_43ad20->vtbl->SetTexture(DEV_43ad20, 0, *(int*) (v3 + 0x50));
				drawFlags = *(unsigned char*) ((int) drawNode + 0x1e);
				fcn_004372d0(*(unsigned char*) ((int) drawNode + 0x1c), (*(unsigned char*) (v3 + 0x54) & 1) * 2 | (drawFlags & 1), drawNode[8], (*(unsigned char*) (v3 + 0x54) >> 3) & 1, (drawFlags >> 1) & 1);
				if (!(*(unsigned char*) (v3 + 0x54) & 8) && ((unsigned int) drawNode[6] >> 0x1b & 1) != (unsigned int) (v10 == 2)) {
					v10 = (~drawNode[6] & 0x8000000U | 0x10000000) >> 0x1b;
					DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x16, v10);
				}
				((Mesh_43ad20*) drawNode[2])->vtbl->DrawSubset((Mesh_43ad20*) drawNode[2], drawNode[6] & 0x7ffffff);
				drawNode = (int*) drawNode[9];
			} while (drawNode);
		}
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x16, (g_6b7ffe == 0) * 2 + 1);
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x89, 0);
		if ((unsigned char) g_1052bd0[0] & 0x1c) {
			fcn_00458bf0(*(int*) 0x6b8014);
		}
		if (*(int*) 0x6b8300) {
			fcn_00440f70(*(int*) 0x6b8300, a1);
		}
		m_pool_clear(0x6b8064);
		g_6b8068 = 0;
		d3_RenderSceneList();
		fcn_00437270();
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
