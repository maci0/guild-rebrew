


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

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
void __cdecl hst_LoadHistoryText(void);

/* ADDRESS: GOLDDE 0x0050e490 */
int __cdecl ls_LoadHistoryState(void* file)
{
	int v;
	int i;
	int k;

	if (!ls_ReadVfsDataChecked(&(*(unsigned char*)&hst_HistoryTextActive), 1, 1, file))
		return 0;
	hst_LoadHistoryText();
	if (!ls_ReadVfsDataChecked(&v, 4, 1, file))
		return 0;
	g_67fca8 = hst_HistoryTextBase + v;
	if (!ls_ReadVfsDataChecked(&v, 4, 1, file))
		return 0;
	g_67fcb4 = g_67fcac + v;
	for (i = 0; i < 16; i++) {
		if (!ls_ReadVfsDataChecked(&((unsigned char*)g_1007ba0)[i], 1, 1, file))
			return 0;
	}
	for (i = 0; i < 4; i++) {
		if (!ls_ReadVfsDataChecked(&((Group*)hst_HistoryGroups)[i].count, 4, 1, file))
			return 0;
		for (k = 0; k < 8; k++) {
			if (!ls_ReadVfsDataChecked(&((Group*)hst_HistoryGroups)[i].pairs[k].a, 4, 1, file))
				return 0;
			if (!ls_ReadVfsDataChecked(&((Group*)hst_HistoryGroups)[i].pairs[k].b, 4, 1, file))
				return 0;
		}
	}
	return 1;
}
