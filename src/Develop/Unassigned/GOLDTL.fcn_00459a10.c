

typedef struct IUnk IUnk;
// SIZE 0xc
typedef struct IUnkVtbl {
	long (__stdcall* QueryInterface)(IUnk*, void*, void**);
	unsigned long (__stdcall* AddRef)(IUnk*);
	unsigned long (__stdcall* Release)(IUnk*);
} IUnkVtbl;
// SIZE 0x4
struct IUnk {
	IUnkVtbl* v;
};

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* Vertex459a10Fn)(D3D_DEVICE_VIEW*, unsigned int, unsigned long, unsigned long, int, IUnk**);
typedef long (__stdcall* Index459a10Fn)(D3D_DEVICE_VIEW*, unsigned int, unsigned long, int, int, IUnk**);










extern unsigned long g_14ce728;

void __cdecl fcn_00459a10(IUnk** o)
{
	IUnk** ib;

	if (o == 0) {
		return;
	}
	if (o[0] != 0) {
		g_14ce728 = o[0]->v->Release(o[0]);
		o[0] = 0;
	}
	((Vertex459a10Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[23])(((D3D_DEVICE_VIEW*)g_6b5de0), 0x600, 0x228, 0x1c4, 0, o);
	ib = &o[1];
	if (*ib != 0) {
		g_14ce728 = (*ib)->v->Release(*ib);
		*ib = 0;
	}
	((Index459a10Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[24])(((D3D_DEVICE_VIEW*)g_6b5de0), 0x1a4, 0x228, 0x65, 0, ib);
	((int*) o)[3] = -1;
}
