


#include <string.h>
#pragma intrinsic(memset)

#include "client_types.h"


// SIZE 0xe

#include "Develop/DieGildeAddOn/game/entity_record.h"








extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern char g_77531c;

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl d2_DispatchTutorialEvent(int, char*, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_0050de80(char*, char*);
int __cdecl fcn_0050ddf0(int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0057e880(int, char*, int, int);

int __cdecl fcn_005b9df0(int idx, char* p, char* q, char* r)
{
	int res;
	char* e;
	char msg[0xf8];
	char info[0xb8];

	res = 0;
	for (e = he_StartHandlungSearch(2, 3, *(int*) (p + 2), 0, 0x11); e != 0; e = he_fn_Handlung()) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		*(int*) (e + 0x70) = -1;
	}
	if (d2_DispatchTutorialEvent(0x24, r, 0, 0) == 1) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0xf;
		*(int*) (msg + 8) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_id;
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 2;
		*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
		fcn_00500bb0((pos14_7f4c00*) (msg + 0x28), 0, 0, 1);
		*(int*) (msg + 0x58) = *(int*) (p + 2);
		*(int*) (msg + 0x5c) = *(int*) (q + 1);
		*(int*) (msg + 0x60) = *(int*) (r + 1);
		*(int*) (msg + 0x78) = p[0x28];
		g_77531c = (char) *(int*) (msg + 0x78);
		fcn_004c5530(msg);
		if (p[0x28] != 0) {
			fcn_0050de80(p, info);
			res = fcn_0050ddf0(*(int*) (info + 0xb0), p[0x28]);
			fcn_004c51a0(-1, ((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_id, g_773d75, res);
		}
		if (idx == g_774970) {
			fcn_0057e880(0x24, r, 0, 0);
		}
	}
	return res;
}
