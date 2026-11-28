unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl gm_QueryEntities(int, int, ...);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* d2_VisitedBuilding; extern unsigned char* d2_InteriorBuilding; extern int* d2_SelectedItem;
extern char* d2_SelectedBuilding; extern char* d3_FocusedEntityObject; extern char g_7746f4;
/* ADDRESS: GOLDTL 0x00530510 */
void __cdecl sv_ResetSelectionState(void)
{
	unsigned short* entity;
	unsigned short id; int mode; char *table;

	mode = (int) d2_VisitedBuilding; entity = (unsigned short*) d2_InteriorBuilding;
	d2_SelectedItem = 0;
	d2_SelectedBuilding = 0;
	*(int*) 0x7ea3bc = 0;
	d3_FocusedEntityObject = 0;
	if (mode != 0) {

		if (entity == 0) {
			return;
		}
	}
	else {

		if (entity == 0) {
			entity = gm_StartFilteredEntitySearch(1, 0, 0x44);
		}
	}
	if (entity == 0) {
		return;
	}
	g_7746f4 = 0;
	entity = gm_QueryEntities(*(int*) ((char*) entity + 0x5d), 1, 5);
	if (entity == 0) {
		return;
	}
	do {
		table = g_item_def_table; id = *entity; table += (int)id * 64;
		if ((unsigned char)table[id] == 0x1d) {
			*(int*) ((char*) entity + 0x20) &= 0xfffffffd;
		}
	} while ((entity = gm_NextEntityQueryMatch()) != 0);
}
