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
typedef int (__stdcall* Scene47c9c0Fn)(D3D_DEVICE_VIEW*);
typedef int (__stdcall* Texture47c9c0Fn)(D3D_DEVICE_VIEW*, int, int);
typedef int (__stdcall* Draw47c9c0Fn)(D3D_DEVICE_VIEW*, int, int, int);
















extern int d2_DrawDepthIndex;
extern int g_772614;


int __cdecl fcn_0047b8b0(int, int, int, int, Quad*);
void __cdecl fcn_0047b9f0(Quad*, int);
void __cdecl fcn_0047c4e0(void);
void __cdecl fcn_004372d0(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x0047c9c0 */
void __cdecl d2_DrawTexturedQuad(int a1, int a2, int a3, int a4, int tex, float alpha)
{
	Quad quad;
	float t;
	int i;

	if (fcn_0047b8b0(a1, a2, a3, a4, &quad) == 0) {
		return;
	}
	fcn_0047b9f0(&quad, (int) (alpha * 255.0f));
	t = d2_DrawDepthIndex * 0.001f;
	for (i = 0; i < 6; i++) {
		quad.vs.v[i].z = 1.0f - t;
		quad.vs.v[i].w = t + 0.01f;
	}
	{
		void* ptr;

		if (((VB*)g_772614)->vtbl->Lock(((VB*)g_772614), 0, 0x18, &ptr, 0x2000) < 0) {
			return;
		}
		*(Verts*) ptr = quad.vs;
	}
	((VB*)g_772614)->vtbl->Unlock(((VB*)g_772614));
	fcn_0047c4e0();
	fcn_004372d0(0xfe, 0, 0, 1, 1);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 7, 0);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x88, 0);
	if (((Scene47c9c0Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x88 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0)) >= 0) {
		((Texture47c9c0Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xf4 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, tex);
		((Draw47c9c0Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x118 / 4])(((D3D_DEVICE_VIEW*)g_6b5de0), 4, 0, 2);
		((Scene47c9c0Fn) ((void**)((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x8c / 4])(((D3D_DEVICE_VIEW*)g_6b5de0));
	}
	d2_DrawDepthIndex++;
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 7, 1);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x88, 1);
}
