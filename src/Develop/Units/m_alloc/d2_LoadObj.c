#include <stdio.h>

typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	char pad[8];
} VfsEntry;
// SIZE 0x54

extern char* d2_FileObjTable;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern FILE* g_772564;
extern char g_102d040[];
extern char s_67d410[];
extern char s_6750e8[];

char* __cdecl m_alloc(int size, const char* tag);

/* ADDRESS: GOLDTL 0x00465ba0 */
/* ADDRESS: GOLDDE 0x004597d0 */
char* __cdecl d2_LoadObj(int idx, const char* path)
{
	char* buf;

	if (((VfsEntry*)d2_FileObjTable)[idx].flags & 2) {
		idx += g_772510;
	}
	buf = m_alloc(((VfsEntry*)d2_FileObjTable)[idx].size, s_67d410);
	if (path) {
		g_772564 = fopen(path, s_6750e8);
	} else {
		g_772564 = fopen(g_102d040, s_6750e8);
	}
	if (g_772564 == 0) {
		return 0;
	}
	fseek(g_772564, ((VfsEntry*)d2_FileObjTable)[idx].offset, SEEK_SET);
	fread(buf, ((VfsEntry*)d2_FileObjTable)[idx].size, 1, g_772564);
	fclose(g_772564);
	return buf;
}
