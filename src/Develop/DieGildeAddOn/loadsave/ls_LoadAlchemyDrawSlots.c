


#include "g_772f90.h"

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern ALCHEMY_DRAW_SLOT g_772f90[3];

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
void __cdecl ahm_ResetAlchemyState(int v);

int __cdecl ls_LoadAlchemyDrawSlots(void* file)
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
	ahm_ResetAlchemyState(0);
	return 1;
}
