#include "d3_d3d.h"

#ifdef REBREW_GOLD
typedef struct Vec4Words {
	int a;
	int b;
	int c;
	int d;
} Vec4Words;

typedef int (__stdcall* ObjFn)(void*, int, Vec4Words*, int, int, float, int);

/* ADDRESS: GOLD 0x00435fb0 */
void __cdecl d3_ClearViewport(void)
{
	Vec4Words v;
	void* obj;
	unsigned char first;
	unsigned char second;
	int mask;
	int r;

	first = *(unsigned char*) 0x631223;
	second = *(unsigned char*) 0x631222;
	if (first != 0 && second != 0) {
		return;
	}
	mask = 0;
	if (*(int*) 0x633420 != 0 && first == 0) {
		mask = 2;
	}
	if (*(int*) 0x631208 != 0 && second == 0) {
		mask |= 1;
	}
	if (mask != 0) {
		v.a = *(int*) 0xfc2930;
		v.b = *(int*) 0xfc2934;
		v.c = *(int*) 0xfc2938;
		v.d = *(int*) 0xfc293c;
		obj = *(void**) 0x63341c;
		r = ((ObjFn) *(void**) (*(int*) obj + 0x50))(obj, 1, &v, mask, *(int*) 0x6334a0, 1.0f, 0);
		*(int*) 0x14661a4 = r;
		if (r != 0) {
			d3d_LogResultError((char*) 0x5f944c, 0x145, (char*) 0x5f9570);
		}
	}
	*(unsigned char*) 0x631222 = 1;
	*(unsigned char*) 0x631223 = 1;
}

/* Inferred function name; native unit and buffer name are attested. */
/* ADDRESS: GOLD 0x004360e0 */
void __cdecl d3d_PrecacheTexture(void* t)
{
    int result;
    void* device;

    if (t == 0) return;
    device = d3d_Device;
    result = ((int (__stdcall*)(void*, int, void*)) (*(void***) device)[38])(
        device, 0, t);
    d3d_LastResult = result;
    if (result != 0) {
        d3d_LogResultError("D:\\develop\\Units\\d3\\d3_d3d.c", 0x167,
            "d3d_Device->lpVtbl->SetTexture(d3d_Device, 0, t)");
    }
    device = d3d_Device;
    result = ((int (__stdcall*)(void*, int, int, void*, int, int)) (*(void***) device)[28])(
        device, 4, 0x1c4, (void*) d3d_PrecacheBuffer, 3, 0);
    d3d_LastResult = result;
    if (result != 0) {
        d3d_LogResultError("D:\\develop\\Units\\d3\\d3_d3d.c", 0x168,
            "d3d_Device->lpVtbl->DrawPrimitive(d3d_Device, D3DPT_TRIANGLELIST, D3D_VERTEX_STRUCT, (void*)d3d_PrecacheBuffer, 3, 0)");
    }
}
#endif

void __cdecl fcn_00438780(void)
{
    int result;
    void* device;

    device = d3d_Device;
    result = ((int (__stdcall*)(void*)) (*(void***) device)[10])(device);
    d3d_LastResult = result;
    if (result != 0) {
        d3d_LogResultError("D:\\develop\\Units\\d3\\d3_d3d.c", 0x4f0,
            "d3d_Device->lpVtbl->EndScene(d3d_Device)");
    }
}
unsigned char _dpad_fc28f4[151852];
