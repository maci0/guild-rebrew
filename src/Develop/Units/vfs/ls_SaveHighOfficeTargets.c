


#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned int __cdecl vfs_fwrite(void*, int, int, void*);

/* ADDRESS: GOLDDE 0x0049bf80 */
int __cdecl ls_SaveHighOfficeTargets(void* stream)
{
	if (!(vfs_fwrite(&g_7728c0, 4, 1, stream) > 0))
		return 0;
	if (!(vfs_fwrite(&g_7728c4, 4, 1, stream) > 0))
		return 0;
	if (!(vfs_fwrite(&g_7728c8, 4, 1, stream) > 0))
		return 0;
	if (!(vfs_fwrite(&g_7728cc, 4, 1, stream) > 0))
		return 0;
	return vfs_fwrite(&g_7728d0, 4, 1, stream) > 0;
}
