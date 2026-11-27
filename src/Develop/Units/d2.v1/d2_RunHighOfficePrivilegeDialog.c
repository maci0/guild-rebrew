


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
	int x14;
	int x18;
	char pad1c[0x34];
} Query;
// SIZE 0x50

#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_14aad38;
extern int g_14aad18;
extern int g_14aacf8;
extern int g_14aacd0;

int __cdecl amt_CheckHighOfficeEligibility(char*);
void __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl d2_OpenTargetPicker(Query*, int, int, void*);
void __cdecl d2_RunAmtChamberMenu(void*, int, int);
int __cdecl d2_RunOfficeDismissalDialog(unsigned short*);
void __cdecl d2_RunOfficeDiscordDialog(int);
void __cdecl d2_RunOfficeFeudDialog(int);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_RunHighOfficePrivilegeDialog(void)
{
	Query q;
	int r;
	char lvl;

	r = amt_CheckHighOfficeEligibility((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]);
	if (r != 1) {
		if (r == -1) {
			d2_ShowModalMessageBox(g_14aad38, 0);
			return;
		}
		d2_CheckActionBlocker((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 8);
		return;
	}
	lvl = ((ENTITY_RECORD*)g_7f4ca0)[g_774970].unk_165[4];
	if (lvl == 0x1e) {
		memset(&q, 0, sizeof(q));
		q.x4 = 0xc00;
		q.x10 = 6;
		q.x18 = 1;
		d2_OpenTargetPicker(&q, g_14aad18, 0, (void*) d2_RunOfficeDismissalDialog);
	} else if (lvl == 0x1f || lvl == 0x21) {
		d2_RunAmtChamberMenu((void*) d2_RunOfficeDiscordDialog, g_14aacd0, 0);
	} else if (lvl == 0x20) {
		d2_RunAmtChamberMenu((void*) d2_RunOfficeFeudDialog, g_14aacf8, 0);
	}
	d3_EndCameraAndUiMode();
}
