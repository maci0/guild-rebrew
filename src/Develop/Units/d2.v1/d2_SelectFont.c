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
extern char* d2_CurrentFontBank;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d384;

char* __cdecl d2_GetResourceData(int idx);

/* ADDRESS: GOLDTL 0x00472880 */
char* __cdecl d2_SelectFont(int idx)
{
	if (((VfsEntry*)d2_FileObjTable)[idx].kind != 7) {
		return 0;
	}
	d2_CurrentFontBank = d2_GetResourceData(idx);
	d2_CurrentFont = idx;
	d2_FontHeight = *(unsigned short*) (d2_CurrentFontBank + 8);
	if (idx == d2_DefaultFont) {
		g_67d380 = 8;
	} else {
		g_67d380 = 4;
		if (idx == d2_DefaultFont + 2) {
			g_67d380 = 8;
		}
	}
	g_67d384 = 2;
	return d2_CurrentFontBank;
}
