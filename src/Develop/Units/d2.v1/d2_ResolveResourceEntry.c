typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	int link;
	int pad;
} VfsEntry;
// SIZE 0x54

extern char* d2_FileObjTable;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ResourceOffset;

void __cdecl d2_Show(int idx, int arg);

/* ADDRESS: GOLDTL 0x00466260 */
int __cdecl d2_ResolveResourceEntry(int idx, void** out, int* out_idx)
{
	int j;

	d2_ResourceOffset = 0;
	if (((VfsEntry*)d2_FileObjTable)[idx].flags & 2) {
		idx += g_772510;
	}
	j = idx;
	if ((((VfsEntry*)d2_FileObjTable)[idx].kind == 5 || ((VfsEntry*)d2_FileObjTable)[idx].kind == 8) && ((VfsEntry*)d2_FileObjTable)[idx].offset == 0) {
		if (((VfsEntry*)d2_FileObjTable)[((VfsEntry*)d2_FileObjTable)[idx].link].data == 0) {
			d2_Show(((VfsEntry*)d2_FileObjTable)[idx].link, 0);
		}
		j = ((VfsEntry*)d2_FileObjTable)[idx].link;
		d2_ResourceOffset = idx - j;
	} else if (((VfsEntry*)d2_FileObjTable)[idx].data == 0) {
		d2_Show(idx, 0);
	}
	*out = ((VfsEntry*)d2_FileObjTable)[j].data;
	*out_idx = idx;
	return 1;
}
