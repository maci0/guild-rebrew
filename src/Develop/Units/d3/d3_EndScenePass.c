typedef int(__stdcall* Fn1)(void* self);
typedef int(__stdcall* Fn3)(void* self, int a, int b);
typedef int(__stdcall* Fn4)(void* self, int a, int b, int c);

#include "Develop/Units/d8_vesa/d3d_device_view.h"
extern unsigned char g_6b7ffd;

/* ADDRESS: GOLDTL 0x00437270 */
/* ADDRESS: GOLDDE 0x00430770 */
void __cdecl d3_EndScenePass(void)
{
	((Fn3) ((void**) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xc8 / 4])(((void**)g_6b5de0), 0x1c, 0);
	(*(char*)&g_6b7ffd) = 0;
	((Fn3) ((void**) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0xf4 / 4])(((void**)g_6b5de0), 0, 0);
	((Fn3) ((void**) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x154 / 4])(((void**)g_6b5de0), 0, 0);
	((Fn4) ((void**) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x14c / 4])(((void**)g_6b5de0), 0, 0, 0);
	((Fn1) ((void**) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl)[0x8c / 4])(((void**)g_6b5de0));
}
