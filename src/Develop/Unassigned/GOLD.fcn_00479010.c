#include <string.h>

#include "Develop/Units/d3/d3_d3d.h"

typedef struct SURFACE_VTABLE479010 {
	void *slots[25];
	int (__stdcall *Lock)(void *self, void *rect, void *desc, unsigned long flags, void *event);
} SURFACE_VTABLE479010;

typedef struct SURFACE479010 {
	SURFACE_VTABLE479010 *lpVtbl;
} SURFACE479010;

typedef struct SURFACE_DESC479010 {
	unsigned long dwSize;
	unsigned long dwFlags;
	unsigned long dwHeight;
	unsigned long dwWidth;
	long lPitch;
	unsigned long pad14[4];
	void *lpSurface;
	unsigned long pad28[21];
} SURFACE_DESC479010;

/* ADDRESS: GOLD 0x00479010 */
int __cdecl d2_LockSurface(char *s)
{
	SURFACE_DESC479010 ddsd;
	SURFACE479010 *surf;
	int mode;

	if (s == 0) {
		return 0;
	}
	if (*(int *) (s + 0x34) == 0) {
		surf = *(SURFACE479010 **) (s + 0x20);
		if (surf != 0) {
			memset(&ddsd, 0, sizeof(ddsd));
			mode = *(int *) 0x14635ac;
			ddsd.dwSize = 0x7c;
			if (mode == 3) {
				d3d_LastResult = surf->lpVtbl->Lock(surf, 0, &ddsd, 1, 0);
				if (d3d_LastResult != 0) {
					d3d_LogResultError("D:\\develop\\Units\\d2.v1\\GFX.C", 0x49a,
						"s->DDSurface->lpVtbl->Lock( s->DDSurface, NULL, &ddsd, DDLOCK_WAIT, NULL )");
				}
			} else {
				d3d_LastResult = surf->lpVtbl->Lock(surf, 0, &ddsd, 0x801, 0);
				if (d3d_LastResult != 0) {
					d3d_LogResultError("D:\\develop\\Units\\d2.v1\\GFX.C", 0x49c,
						"s->DDSurface->lpVtbl->Lock( s->DDSurface, NULL, &ddsd, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL )");
				}
			}
			*(void **) (s + 0x1c) = ddsd.lpSurface;
		}
		*(int *) (s + 0x34) = 1;
	}
	return 1;
}
