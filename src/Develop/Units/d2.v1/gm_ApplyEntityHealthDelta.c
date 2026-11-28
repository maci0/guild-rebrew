void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// SIZE 0x21c
typedef struct
{
	unsigned short id;
	unsigned char kind;
	char pad3;
	int h;
	unsigned char alive;
	char pad9;
	unsigned short age;
	char padc[4];
	float lo;
	char pad14[8];
	float hi;
	float span;
	int bonus;
	char pad28[0x21c - 0x28];
} HEALTH_DELTA_ENTITY_VIEW;

extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
#include "Develop/client_types.h"







// SIZE 0xe


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;


int __cdecl cm_AppendCommandSyncField(unsigned char type, unsigned char count, short id, char* data);
void __cdecl cm_SendSetAttribute(void);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeFloat(int a1, int a2, float a3);

/* ADDRESS: GOLDTL 0x004ff210 */
/* ADDRESS: GOLDDE 0x004eac20 */
float __cdecl gm_ApplyEntityHealthDelta(unsigned short id, int delta)
{
	char dead;
	float res;
	char msg[0xf8];
	HEALTH_DELTA_ENTITY_VIEW* e;

	e = &((HEALTH_DELTA_ENTITY_VIEW*)gm_EntitySlotTable)[id];
	if (e->id == 0xffff || e->kind == 10 || e->alive == 0)
		return -1.0f;
	if (e->kind != 0x14) {
		res = (e->age <= e->span ? (e->hi - e->lo) / e->span * e->age + e->lo : e->hi) + ((float) e->bonus + delta);
		res = (float)(res > 0.0 ? res : 0.0);
		if (res <= 0.0) {
			dead = 0;
			cm_BeginPacketFieldDelta((char*) e, e->h);
			cm_AppendCommandSyncField(1, 1, (short) ((char*) e - cm_PacketDeltaBase + 8), &dead);
			cm_SendSetAttribute();
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = e->h;
			*(int*) (msg + 0xc) = -1;
			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
			*(int*) (msg + 0x58) = e->h;
			cm_SendCopyEntityData(msg);
			return 0.0f;
		}
		cm_BeginPacketFieldDelta((char*) e, e->h);
		cm_AppendPacketFieldValue(4, 1, 0x24, &delta);
		cm_RequestChangeAttribute();
		return res;
	}
	{
		float d;

		d = (float) delta;
		res = e->hi;
		res += d;
		if (res <= 0.0) {
			dead = 0;
			cm_BeginPacketFieldDelta((char*) e, e->h);
			cm_AppendCommandSyncField(1, 1, (short) ((char*) e - cm_PacketDeltaBase + 8), &dead);
			cm_SendSetAttribute();
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = e->h;
			*(int*) (msg + 0xc) = -1;
			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
			*(int*) (msg + 0x58) = e->h;
			cm_SendCopyEntityData(msg);
			return 0.0f;
		}
		cm_RequestChangeFloat(e->h, 0x1c, d);
		return res;
	}
}
