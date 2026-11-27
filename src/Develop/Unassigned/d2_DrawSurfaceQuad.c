// SIZE 0x1c
typedef struct {
	float x;
	float y;
	float z;
	float w;
	int color;
	float u;
	float v;
} Vert;

// SIZE 0xa8
typedef struct {
	Vert v[6];
} Verts;

// SIZE 0xac
typedef struct {
	Verts vs;
	int pad;
} Quad;

typedef struct VB VB;

typedef struct {
	char p0[0x2c];
	int (__stdcall* Lock)(VB*, int, int, void**, int);
	int (__stdcall* Unlock)(VB*);
} VBVtbl;

struct VB {
	VBVtbl* vtbl;
};

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* D3D_SCENE_FN)(D3D_DEVICE_VIEW*);
typedef int (__stdcall* D3D_TEXTURE_FN)(D3D_DEVICE_VIEW*, int, int);
typedef int (__stdcall* D3D_DRAW_FN)(D3D_DEVICE_VIEW*, int, int, int);
















typedef struct Tex Tex;

typedef struct {
	char p0[0x38];
	int (__stdcall* GetLevelDesc)(Tex*, int, void*);
} TexVtbl;

struct Tex {
	TexVtbl* vtbl;
};

// SIZE 0x20
typedef struct {
	char pad0[0x18];
	int width;
	int height;
} TexDesc;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_772614;


int __cdecl d2_BuildQuadVertices(int, int, int, int, Quad*);
void __cdecl d2_SetQuadAlpha(Quad*, int);
void __cdecl d2_BindQuadVertexBuffer(void);
void __cdecl d3_SetRenderMaterialState(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0047c7b0 */
void __cdecl d2_DrawSurfaceQuad(int x, int y, int w, int h, Tex* tex, float alpha)
{
	TexDesc desc;
	Quad q;
	float t;
	int i;
	void* ptr;
	VBVtbl* vt;

	((Tex*) tex)->vtbl->GetLevelDesc(tex, 0, &desc);
	if (d2_BuildQuadVertices(x, y, w, h, &q) == 0) {
		return;
	}
	d2_SetQuadAlpha(&q, (int) (alpha * 255.0f));
	t = d2_DrawDepthIndex * 0.001f;
	for (i = 0; i < 6; i++) {
		q.vs.v[i].z = 1.0f - t;
		q.vs.v[i].w = t + 0.01f;
	}
	vt = ((VB*) g_772614)->vtbl;
	q.vs.v[0].u = 0.0f;
	q.vs.v[0].v = 0.0f;
	q.vs.v[1].u = (float) w / desc.width;
	q.vs.v[1].v = 0.0f;
	q.vs.v[2].u = 0.0f;
	q.vs.v[2].v = (float) h / desc.height;
	q.vs.v[3].u = (float) w / desc.width;
	q.vs.v[3].v = 0.0f;
	q.vs.v[4].u = (float) w / desc.width;
	q.vs.v[4].v = (float) h / desc.height;
	q.vs.v[5].u = 0.0f;
	q.vs.v[5].v = (float) h / desc.height;
	if (vt->Lock(((VB*) g_772614), 0, 0x18, &ptr, 0x2000) < 0) {
		return;
	}
	*(Verts*) ptr = q.vs;
	((VB*) g_772614)->vtbl->Unlock(((VB*) g_772614));
	d2_BindQuadVertexBuffer();
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 7, 0);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x88, 0);
	d3_SetRenderMaterialState(0xfe, 0, 0, 1, 1);
	if (((D3D_SCENE_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x88 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0)) >= 0) {
		((D3D_TEXTURE_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xf4 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, (int) tex);
		((D3D_DRAW_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x118 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 4, 0, 2);
		((D3D_SCENE_FN) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x8c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0));
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x88, 1);
	d2_DrawDepthIndex++;
}
