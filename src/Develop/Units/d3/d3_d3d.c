#include "d3_d3d.h"

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
