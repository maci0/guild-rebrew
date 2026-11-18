#ifndef D3D_DEVICE_VIEW_H
#define D3D_DEVICE_VIEW_H

typedef struct D3D_DEVICE_VIEW D3D_DEVICE_VIEW;

typedef struct D3D_DEVICE_VTABLE_VIEW {
	void* unk_00[37];
	long (__stdcall* SetTransform)(D3D_DEVICE_VIEW*, int, const float*);
	void* unk_98[12];
	long (__stdcall* SetRenderState)(D3D_DEVICE_VIEW*, int, int);
	void* unk_cc[12];
	long (__stdcall* SetTextureStageState)(D3D_DEVICE_VIEW*, int, int, int);
} D3D_DEVICE_VTABLE_VIEW;

struct D3D_DEVICE_VIEW {
	D3D_DEVICE_VTABLE_VIEW* vtbl;
};

extern void* g_6b5de0;

#endif
