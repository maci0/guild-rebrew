

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* Transform456e50Fn)(D3D_DEVICE_VIEW*, int, void*);
typedef long (__stdcall* Texture456e50Fn)(D3D_DEVICE_VIEW*, int, void*);














extern unsigned char g_1040600;
extern char* g_6b86ec;
extern char* g_1041d00;
extern float g_1052c00[16];

void __cdecl fcn_004372d0(int, int, int, int, int);
void __cdecl d3_ProjectNodeShadows(char*);

void __cdecl fcn_00456e50(void)
{
	char* p;

	fcn_004372d0(0xff, 0, 0, 0, 1);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 7, 0);
	((Texture456e50Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0);
	if (g_1040600 != 0) {
		for (p = g_6b86ec; p != 0; p = *(char**) (p + 0x1f0)) {
			d3_ProjectNodeShadows(p);
		}
		for (p = g_1041d00; p != 0; p = *(char**) (p + 0x1f0)) {
			d3_ProjectNodeShadows(p);
		}
	}
	((Transform456e50Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTransform)(((D3D_DEVICE_VIEW*)g_6b5de0), 3, ((char*)g_1052c00));
}
