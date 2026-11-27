


#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_player.h"


float __cdecl eval_ObjektPreis2Credits(int, char);
int __cdecl main_GetLanguage(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl gm_RemoveClientEntityLink(char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);

void __cdecl d2_SellObjectsDialog(int n, char** items)
{
	char buf[0x400];
	int total;
	int i;
	int price;

	if (n > 0x20 || n == 0) {
		return;
	}
	total = 0;
	for (i = 0; i < n; i++) {
		total = (int)(total + (eval_ObjektPreis2Credits(*(unsigned short*) items[i], items[i][0x12])));
	}
	price = (int) (total * 0.4);
	switch (main_GetLanguage()) {
	case 0:
		if (n > 1) {
			io_FormatTextBuffer(buf, 0xdc, price, n, 0xc10);
		}
		else {
			io_FormatTextBuffer(buf, 0xdc, price, n, *(unsigned short*) items[0] * 2 + 0x9a8);
		}
		break;
	case 1:
		if (n > 1) {
			io_FormatTextBuffer(buf, 0xdc, n, 0xc10, price);
		}
		else {
			io_FormatTextBuffer(buf, 0xdc, n, *(unsigned short*) items[0] * 2 + 0x9a8, price);
		}
		break;
	}
	if (d2_ShowModalMessageBox(buf, 0x101) != 0) {
		for (i = 0; i < n; i++) {
			gm_RemoveClientEntityLink(items[i]);
		}
		cm_RequestMoveCredits(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])->entity_id, -1, (*(char*)&g_773d75), price);
	}
}
