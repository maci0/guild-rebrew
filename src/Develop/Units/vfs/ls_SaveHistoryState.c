


// SIZE 0x8
typedef struct {
	int a;
	int b;
} Pair;

// SIZE 0x44
typedef struct {
	int count;
	Pair pairs[8];
} Group;

extern char hst_HistoryTextActive;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned int __cdecl vfs_fwrite(void* p, int size, int n, void* file);

/* ADDRESS: GOLDDE 0x0050a6f0 */
int __cdecl ls_SaveHistoryState(void* file)
{
	int v;
	int i;
	int k;

	if (vfs_fwrite(&(*(unsigned char*)&hst_HistoryTextActive), 1, 1, file) <= 0)
		return 0;
	v = g_67fca8 - hst_HistoryTextBase;
	if (vfs_fwrite(&v, 4, 1, file) <= 0)
		return 0;
	v = g_67fcb4 - g_67fcac;
	if (vfs_fwrite(&v, 4, 1, file) <= 0)
		return 0;
	for (i = 0; i < 16; i++) {
		if (vfs_fwrite(&((unsigned char*)g_1007ba0)[i], 1, 1, file) <= 0)
			return 0;
	}
	for (i = 0; i < 4; i++) {
		if (vfs_fwrite(&((Group*)hst_HistoryGroups)[i].count, 4, 1, file) <= 0)
			return 0;
		for (k = 0; k < 8; k++) {
			if (vfs_fwrite(&((Group*)hst_HistoryGroups)[i].pairs[k].a, 4, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(&((Group*)hst_HistoryGroups)[i].pairs[k].b, 4, 1, file) <= 0)
				return 0;
		}
	}
	return 1;
}
