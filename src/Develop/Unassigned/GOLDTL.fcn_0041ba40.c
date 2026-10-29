

#include <windows.h>

typedef struct Font Font;

// SIZE 0x2c
typedef struct {
	void* m[10];
	long (__stdcall* OnResetDevice)(Font* self);
} FontVtbl;

// SIZE 0x4
struct Font {
	FontVtbl* vtbl;
};

typedef struct Device Device;

// SIZE 0x60
typedef struct {
	void* m[23];
	long (__stdcall* CreateVertexBuffer)(Device* self, unsigned int len, unsigned int usage, unsigned int fvf, int pool, void** out);
} DeviceVtbl;

// SIZE 0x4
struct Device {
	DeviceVtbl* vtbl;
};

extern void* g_6b5de0;
extern void* g_6b5de4;
extern void* g_6b5df4;
long __stdcall D3DXCreateFont(Device* dev, HFONT font, Font** out);
int __cdecl fcn_0041b870(void);

int __cdecl fcn_0041ba40(void)
{
	if ((*(Font**)&g_6b5de4) == 0) {
		D3DXCreateFont(((Device*)g_6b5de0), (HFONT) GetStockObject(0xc), &(*(Font**)&g_6b5de4));
	}
	if ((*(Font**)&g_6b5de4) != 0) {
		(*(Font**)&g_6b5de4)->vtbl->OnResetDevice((*(Font**)&g_6b5de4));
	}
	((Device*)g_6b5de0)->vtbl->CreateVertexBuffer(((Device*)g_6b5de0), 0x500, 0x208, 0x44, 0, &g_6b5df4);
	return fcn_0041b870();
}
