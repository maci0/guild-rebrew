


#include "g_772f90.h"

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern Slot772f90 g_772f90[3];

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
void __cdecl fcn_004ecaa0(int v);

int __cdecl fcn_004edec0(void* file)
{
	int i;

	if (!ls_ReadVfsDataChecked(&g_772f78, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f7c, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f80, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f84, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f88, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f8c, 2, 1, file))
		return 0;
	for (i = 0; i < 3; i++) {
		if (!ls_ReadVfsDataChecked(&g_772f90[i].active, 4, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].y, 4, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].x, 4, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].v.b, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].v.c, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].v.d, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].v.e, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].v.k, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].v.f, 4, 1, file))
			return 0;
	}
	fcn_004ecaa0(0);
	return 1;
}
