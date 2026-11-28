


#include <string.h>

// SIZE 0xf8
#include "Develop/client_types.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int who;
	int other;
	int value;
	char pad64[0x94];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







extern pos14_7f4c00 gm_GameTime;


char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_StartAction0x90(char* u)
{
	struct msg m;
	char* o;

	*(int*) (u + 0x70) = 0;
	if (u[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	for (o = he_StartHandlungSearch(2, 0, 0x90, 3, *(int*) (u + 0x10)); o != 0; o = he_fn_Handlung()) {
		if (o != u) {
			*(int*) (u + 0x84) = cm_SendSetHE(-1, u);
			return;
		}
	}
	memset(&m, 0, sizeof(m));
	m.owner = *(int*) (u + 0xc);
	m.target = *(int*) (u + 0xac);
	m.when = gm_GameTime;
	m.kind = 0x91;
	m.code = 0xa;
	m.who = *(int*) (u + 4);
	m.other = -1;
	m.value = *(int*) (u + 0xb0);
	cm_SendCopyEntityData(&m);
	*(int*) (u + 0xb8) = 0;
	if (*(int*) (u + 0xb4) > 2) {
		*(int*) (u + 0xb4) = 2;
	}
	if (*(int*) (u + 0xb0) > 2) {
		*(int*) (u + 0xb0) = 2;
	}
	gm_ModifyHealth(((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (u + 8)].entity_id, -((*(int*) (u + 0xb4) + 2) * (*(int*) (u + 0xb0) + 2)));
	gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
	cm_SendSetHE(0, u);
}
