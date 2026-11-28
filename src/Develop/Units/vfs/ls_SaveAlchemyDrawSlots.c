


#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern ALCHEMY_DRAW_SLOT ahm_DrawSlots[3];

unsigned int __cdecl vfs_fwrite(void* p, int size, int n, void* file);

int __cdecl ls_SaveAlchemyDrawSlots(void* file)
{
	int i;

	if (vfs_fwrite(&g_772f78, 4, 1, file) <= 0)
		return 0;
	if (vfs_fwrite(&g_772f7c, 4, 1, file) <= 0)
		return 0;
	if (vfs_fwrite(&g_772f80, 4, 1, file) <= 0)
		return 0;
	if (vfs_fwrite(&g_772f84, 4, 1, file) <= 0)
		return 0;
	if (vfs_fwrite(&g_772f88, 4, 1, file) <= 0)
		return 0;
	if (vfs_fwrite(&g_772f8c, 2, 1, file) <= 0)
		return 0;
	for (i = 0; i < 3; i++) {
		if (vfs_fwrite(&ahm_DrawSlots[i].active, 4, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].y, 4, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].x, 4, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].v.b, 1, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].v.c, 1, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].v.d, 1, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].v.e, 1, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].v.k, 1, 1, file) <= 0)
			return 0;
		if (vfs_fwrite(&ahm_DrawSlots[i].v.f, 4, 1, file) <= 0)
			return 0;
	}
	return 1;
}
