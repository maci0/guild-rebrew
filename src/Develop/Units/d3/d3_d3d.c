#include "d3_d3d.h"

#ifdef REBREW_GOLD
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
        fcn_00418e90("D:\\develop\\Units\\d3\\d3_d3d.c", 0x167,
            "d3d_Device->lpVtbl->SetTexture(d3d_Device, 0, t)");
    }
    device = d3d_Device;
    result = ((int (__stdcall*)(void*, int, int, void*, int, int)) (*(void***) device)[28])(
        device, 4, 0x1c4, (void*) d3d_PrecacheBuffer, 3, 0);
    d3d_LastResult = result;
    if (result != 0) {
        fcn_00418e90("D:\\develop\\Units\\d3\\d3_d3d.c", 0x168,
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
        fcn_00418e90("D:\\develop\\Units\\d3\\d3_d3d.c", 0x4f0,
            "d3d_Device->lpVtbl->EndScene(d3d_Device)");
    }
}
