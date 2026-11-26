#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7f4ca0[];

int __cdecl amt_FindOfficeSlotByType(int, void*);
unsigned short* __cdecl gm_LookupEntityRecordById(int);
int* __cdecl gm_LookupHistoricalEntry(int, int*);
#include "Develop/DieGildeAddOn/game/aemter.h"
void __cdecl cm_RequestKillSpieler(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

struct HISTORICAL_OFFICE_SLOT {
	int kind;
	int id;
	int pad[4];
};
// SIZE 0x18


/* ADDRESS: GOLDTL 0x004acf60 */
void __cdecl amt_RetireExpiredRulers(void)
{
	int out;
	struct HISTORICAL_OFFICE_SLOT a;
	struct HISTORICAL_OFFICE_SLOT b;
	char buf[0x100];
	unsigned short* e1;
	unsigned short* e2;
	int* r;
	int lim;
	int i;

	lim = (*(int*)&gm_GameTime) + 0x578;
	if (amt_FindOfficeSlotByType(0x26, &a) == 0)
		return;
	if (amt_FindOfficeSlotByType(0x27, &b) == 0)
		return;
	e1 = gm_LookupEntityRecordById(a.id);
	e2 = gm_LookupEntityRecordById(b.id);
	if (a.id != -1 && g_7728c8 != -1) {
		r = gm_LookupHistoricalEntry(g_7728c8, &out);
		if (r != 0 && r[2] <= lim) {
			amt_SendOfficeCommand(a.kind, 0, 0, 1, 0xff);
			cm_RequestKillSpieler(a.id, 1);
			if (e1 != 0) {
				io_FormatTextBuffer(buf, 0x42b2, *e1);
				for (i = 0; i < 768; i++) {
					if (g_7f4ca0[i * 540 + 2] == 6 || g_7f4ca0[i * 540 + 2] == 7)
						he_PostEntityMessage(*(int*) (g_7f4ca0 + i * 540 + 4), -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_00");
				}
			}
		}
	}
	if (b.id != -1 && g_7728c0 != -1) {
		r = gm_LookupHistoricalEntry(g_7728c0, &out);
		if (r != 0 && r[2] <= lim) {
			amt_SendOfficeCommand(b.kind, 0, 0, 1, 0xff);
			cm_RequestKillSpieler(b.id, 1);
			if (e2 != 0) {
				io_FormatTextBuffer(buf, 0x42b4, *e2);
				for (i = 0; i < 768; i++) {
					if (g_7f4ca0[i * 540 + 2] == 6 || g_7f4ca0[i * 540 + 2] == 7)
						he_PostEntityMessage(*(int*) (g_7f4ca0 + i * 540 + 4), -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_02");
				}
			}
		}
	}
}
