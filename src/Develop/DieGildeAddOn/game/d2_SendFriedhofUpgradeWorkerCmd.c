#include "Develop/client_types.h"



#include <string.h>





// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl cm_SendCopyEntityData(Packet*);

int __cdecl d2_SendFriedhofUpgradeWorkerCmd(char* building, unsigned short* worker, int level)
{
	Packet pkt;
	char buf[0x400];
	char* entry;

	io_FormatTextBuffer(buf, 0x413a, *worker);
	if (d2_ShowModalMessageBox(buf, 1) != 0) {
		entry = fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x211);
		memset(&pkt, 0, sizeof(pkt));
		pkt.type = 0x8f;
		pkt.x36 = 1;
		pkt.x8 = *(int*) (g_7f4ca0 + g_774970 * 540 + 4);
		pkt.xc = *(int*) (building + 1);
		pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
		if (entry != 0) {
			pkt.x60 = *(int*) (entry + 2);
		} else {
			pkt.x60 = -1;
		}
		pkt.x58 = *(int*) (worker + 2);
		pkt.x5c = level;
		cm_SendCopyEntityData(&pkt);
		return 1;
	}
	return 0;
}
