


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
void __cdecl fcn_00526120(int, int);
void __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl fcn_005cd440(Query*, int, int, void*);
void __cdecl fcn_005cde50(void*, int, int);
int __cdecl fcn_005aa860(unsigned short*);
void __cdecl fcn_005aa9a0(int);
void __cdecl fcn_005aaae0(int);
void __cdecl fcn_00532ef0(void);

void __cdecl d2_RunHighOfficePrivilegeDialog(void)
{
	Query q;
	int r;
	char lvl;

	r = amt_CheckHighOfficeEligibility((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]);
	if (r != 1) {
		if (r == -1) {
			fcn_00526120(g_14aad38, 0);
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
		fcn_005cd440(&q, g_14aad18, 0, (void*) fcn_005aa860);
	} else if (lvl == 0x1f || lvl == 0x21) {
		fcn_005cde50((void*) fcn_005aa9a0, g_14aacd0, 0);
	} else if (lvl == 0x20) {
		fcn_005cde50((void*) fcn_005aaae0, g_14aacf8, 0);
	}
	fcn_00532ef0();
}
