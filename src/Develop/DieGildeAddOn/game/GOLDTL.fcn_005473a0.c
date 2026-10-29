#include <string.h>

#include "client_types.h"
#include "client_actions.h"

extern pos14_7f4c00 g_7f4c00;

void* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl fcn_005463a0(int, ...);
void* __cdecl fcn_004ec7d0(unsigned char*);

#pragma pack(push, 2)
typedef struct {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	pos14_7f4c00 pos;
	unsigned char flag;
	char pad37[0xf8 - 0x37];
} Msg5473a0;
#pragma pack(pop)

void __cdecl fcn_004c5530(Msg5473a0*);

/* ADDRESS: GOLDTL 0x005473a0 */
void __cdecl fcn_005473a0(void)
{
	Msg5473a0 msg;
	char* slot;
	unsigned short* h;

	h = gm_StartFilteredEntitySearch(1, 5, 0x1e);
	if (h == 0) {
		return;
	}
	do {
		if (fcn_005463a0(2, 0, 0x98, 3, *(int*) ((char*) h + 1)) == 0 && (slot = fcn_004ec7d0((unsigned char*) h)) != 0) {
			memset(&msg, 0, sizeof(msg));
			msg.type = 0x98;
			msg.seed = *(int*) (slot + 4);
			msg.id = *(int*) ((char*) h + 1);
			msg.flag = 2;
			msg.pos = *(pos14_7f4c00*) &g_7f4c00;
			fcn_004c5530(&msg);
		}
		h = gm_FindNextFilteredEntity();
	} while (h != 0);
}
