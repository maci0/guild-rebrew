#include "Develop/Units/d8_vesa/d3d_device_view.h"

/* ADDRESS: GOLDTL 0x0041baa0 */
int __cdecl fcn_0041baa0(void)
{
	int hr = (int) 0x80004005;

	if (g_6b5de0 != 0) {
		hr = (*(int (__stdcall**) (int)) ((int) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl + 0xc))((int) g_6b5de0);
	}
	return hr;
}
