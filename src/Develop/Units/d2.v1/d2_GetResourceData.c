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

void __cdecl d2_Show(int resource_id, int arg);

/* ADDRESS: GOLDTL 0x00466190 */
/* ADDRESS: GOLDDE 0x00459d10 */
void* __cdecl d2_GetResourceData(int resource_id)
{
	int original_resource_id;

	d2_ResourceOffset = 0;
	if (((VfsEntry*)d2_FileObjTable)[resource_id].flags & 2) {
		resource_id += g_772510;
	}
	if ((((VfsEntry*)d2_FileObjTable)[resource_id].kind == 5 || ((VfsEntry*)d2_FileObjTable)[resource_id].kind == 8) && ((VfsEntry*)d2_FileObjTable)[resource_id].offset == 0) {
		if (((VfsEntry*)d2_FileObjTable)[((VfsEntry*)d2_FileObjTable)[resource_id].link].data == 0) {
			d2_Show(((VfsEntry*)d2_FileObjTable)[resource_id].link, 0);
		}
		original_resource_id = resource_id;
		resource_id = ((VfsEntry*)d2_FileObjTable)[resource_id].link;
		d2_ResourceOffset = original_resource_id - resource_id;
	} else if (((VfsEntry*)d2_FileObjTable)[resource_id].data == 0) {
		d2_Show(resource_id, 0);
	}
	return ((VfsEntry*)d2_FileObjTable)[resource_id].data;
}
