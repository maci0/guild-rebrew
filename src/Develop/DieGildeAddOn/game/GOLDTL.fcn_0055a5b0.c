#include "client_types.h"


#include <string.h>

#pragma pack(push, 2)
// SIZE 0xe






#pragma pack(pop)

// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 at;
	unsigned char code;
	char pad37[0x21];
	int owner2;
	int other;
	pos14_7f4c00 due;
	char pad6e[0x8a];
} Msg55a5;

#include "Develop/DieGildeAddOn/game/entity_record.h"

extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;
extern char g_6b5c60[];

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl cm_SendCopyEntityData(Msg55a5*);
void __cdecl he_FreeAction(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_004fef80(char*);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

/* ADDRESS: GOLD 0x5524c0 */
void __cdecl fcn_0055a5b0(char* u)
{
	float f;
	int a;
	Msg55a5 m;
	char buf[0x800];
	char* h;
	int d;

	if (*(int*) (u + 0x70) >= 0 && *(int*) (u + 0x70) <= 1) {
		if (*(int*) (u + 0x70) == 0) {
			memset(&m, 0, sizeof(m));
			m.kind = 0x7e;
			m.owner = *(int*) (u + 0xac);
			m.target = -1;
			m.at = (*(pos14_7f4c00*)&gm_GameTime);
			m.code = 9;
			m.owner2 = *(int*) (u + 0xac);
			m.other = *(int*) (u + 4);
			m.due = (*(pos14_7f4c00*)&gm_GameTime);
			gm_AddTime(&m.due, 2, 0, 0);
			cm_SendCopyEntityData(&m);
			*(int*) (u + 0x70) = 1;
			*(pos14_7f4c00*) (u + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 8, 0, 0);
			return;
		}
		if (*(int*) (u + 0x70) != 1) {
			return;
		}
		if (*(int*) (u + 0xb0) != 0) {
			h = ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (u + 8)]);
			f = gm_GetEntitySkill(h, 3) > 0.1f ? gm_GetEntitySkill(h, 3) : 0.1f;
			a = gm_WalkEntityChain(*(unsigned short*) h);
			fcn_004ff210(*(unsigned short*) h, -(int) ((int) fcn_004fef80(h) * ((1.0f - f) * 0.5f)));
			d = (int) (a * f * 0.06f);
			cm_RequestTransferCurrencyNoKill(*(int*) (u + 0xac), -1, g_773d75, d);
			io_FormatTextBuffer(buf, 0x10ba, d);
			fcn_00545d40(*(int*) (u + 0xac), -1, buf, 0x20, 0x5fd, g_6b5c60);
			he_FreeAction(u);
			return;
		}
		io_FormatTextBuffer(buf, 0x10bb);
		fcn_00545d40(*(int*) (u + 0xac), -1, buf, 0x20, 0x5fd, g_6b5c60);
	}
	he_FreeAction(u);
}
