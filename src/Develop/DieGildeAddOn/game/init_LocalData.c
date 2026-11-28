


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Variant;


extern char gm_TownTable[];
extern unsigned char gm_ClientModeFlags;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern char* g_773db4[];

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl gm_UpdateAllTownSeasonPrices(void);
void __cdecl gm_InitTownGoodsTable(int);
#include "Develop/Units/Error/error_message.h"
void __cdecl init_AssignBuildingNames(void);
void __cdecl gm_ResetWarehouseStock(void);

/* ADDRESS: GOLDDE 0x004ffcc0 */
void __cdecl init_LocalData(void)
{
	ENTITY_RECORD** p;
	int i;
	int n;

	d3_SelectSceneContext(0, 0);
	if ((gm_ClientModeFlags & 0x40) == 0) {
		gm_UpdateAllTownSeasonPrices();
		for (i = 0; i < 4; i++) {
			if (((Variant*)gm_TownTable)[i].name[0] == 0) {
				break;
			}
			gm_InitTownGoodsTable(i);
		}
	}
	n = 2;
	for (i = 1; i < 768; i++) {
		if (n == 0) {
			break;
		}
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type == 0xc) {
			if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].side == 0) {
				(*(ENTITY_RECORD**)&gm_RichterKatholisch) = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
				n--;
			} else if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].side == 1) {
				(*(ENTITY_RECORD**)&gm_RichterEvangelisch) = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
				n--;
			}
		}
	}
	p = ((ENTITY_RECORD**)g_773db4);
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type == 0xb) {
			*p++ = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
		}
	}
	if ((*(ENTITY_RECORD**)&gm_RichterKatholisch) == 0) {
		ReportClientMessage("init_LocalData(): gm_RichterKatholisch==NULL");
	}
	if ((*(ENTITY_RECORD**)&gm_RichterEvangelisch) == 0) {
		ReportClientMessage("init_LocalData(): gm_RichterEvangelisch==NULL");
	}
	if ((gm_ClientModeFlags & 0x44) == 0) {
		init_AssignBuildingNames();
	}
	gm_ResetWarehouseStock();
}
