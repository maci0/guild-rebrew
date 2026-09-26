// FUNCTION: GOLD 0x004ebfb0
// SIZE: 400
// FUNCTION: GOLDTL 0x004edd30
// SIZE: 400

#include "g_772f90.h"

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern Slot772f90 g_772f90[3];

unsigned int __cdecl fcn_00430910(void* p, int size, int n, void* file);

int __cdecl fcn_004edd30(void* file)
{
	int i;

	if (fcn_00430910(&g_772f78, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f7c, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f80, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f84, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f88, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f8c, 2, 1, file) <= 0)
		return 0;
	for (i = 0; i < 3; i++) {
		if (fcn_00430910(&g_772f90[i].active, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].y, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].x, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].v.b, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].v.c, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].v.d, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].v.e, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].v.k, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].v.f, 4, 1, file) <= 0)
			return 0;
	}
	return 1;
}
