


typedef struct {
	int a;
	int b;
} pair8;
// SIZE 0x8

typedef struct {
	int flag;
	pair8 slot[8];
} rec44;
// SIZE 0x44

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;
extern char gm_TownTable[];
extern char g_680890[];
extern int g_67fca4;
extern int g_67fcb0;

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl txt_ReleaseTextBank(char*);

/* ADDRESS: GOLDDE 0x004a02a0 */
void __cdecl hst_ResetHistoryState(void)
{
	char buf[0x40];
	int i;
	int j;

	for (i = 0; i < 4; i++) {
		((rec44*)hst_HistoryGroups)[i].flag = 1;
		for (j = 0; j < 4; j++) {
			((rec44*)hst_HistoryGroups)[i].slot[j].a = -1;
			((rec44*)hst_HistoryGroups)[i].slot[j].b = 0xffff;
		}
	}
	fcn_0064d41a(buf, g_680890, gm_TownTable + gm_ActiveTownIndex * 0x2f4);
	txt_ReleaseTextBank(buf);
	hst_HistoryTextBase = -1;
	g_67fca4 = -1;
	g_67fca8 = -1;
	g_67fcac = -1;
	g_67fcb0 = -1;
	g_67fcb4 = -1;
}
