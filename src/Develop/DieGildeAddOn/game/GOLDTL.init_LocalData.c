


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Variant;


extern char g_868060[];
extern unsigned char g_7747b0;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern char* g_773db4[];

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_005016c0(void);
void __cdecl fcn_005016f0(int);
#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_00515010(void);
void __cdecl gm_ResetWarehouseStock(void);

void __cdecl init_LocalData(void)
{
	ENTITY_RECORD** p;
	int i;
	int n;

	d3_SelectSceneContext(0, 0);
	if ((g_7747b0 & 0x40) == 0) {
		fcn_005016c0();
		for (i = 0; i < 4; i++) {
			if (((Variant*)g_868060)[i].name[0] == 0) {
				break;
			}
			fcn_005016f0(i);
		}
	}
	n = 2;
	for (i = 1; i < 768; i++) {
		if (n == 0) {
			break;
		}
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 0xc) {
			if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].side == 0) {
				(*(ENTITY_RECORD**)&gm_RichterKatholisch) = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
				n--;
			} else if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].side == 1) {
				(*(ENTITY_RECORD**)&gm_RichterEvangelisch) = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
				n--;
			}
		}
	}
	p = ((ENTITY_RECORD**)g_773db4);
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 0xb) {
			*p++ = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
		}
	}
	if ((*(ENTITY_RECORD**)&gm_RichterKatholisch) == 0) {
		ReportClientMessage("init_LocalData(): gm_RichterKatholisch==NULL");
	}
	if ((*(ENTITY_RECORD**)&gm_RichterEvangelisch) == 0) {
		ReportClientMessage("init_LocalData(): gm_RichterEvangelisch==NULL");
	}
	if ((g_7747b0 & 0x44) == 0) {
		fcn_00515010();
	}
	gm_ResetWarehouseStock();
}
