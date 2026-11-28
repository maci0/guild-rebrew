#include "Develop/DieGildeAddOn/game/game_timestamp.h"






extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int gm_RichterKatholisch;
extern int gm_RichterEvangelisch;
extern float g_6652c8;
extern char gm_EntityIdField[];

int __cdecl gm_CalcPersonWealth(unsigned short);
int __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(GAME_TIMESTAMP*, int, int, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl cm_SendBlockCharacter(int, int, int);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_EnqueueStagedPacket(void*);
int __cdecl srv_GetEntityOfficeSlot(unsigned char*, void*, void*);
int __cdecl amt_SendOfficeCommand(unsigned char, int, int, int, int);

/* ADDRESS: GOLDTL 0x004f6850 */
void __cdecl cut_ExecuteProzessPunishment(unsigned short* entity, int action)
{
	char level;
	int n;
	char msg[0xf8];
	char b9[0x144];
	int id;
	char* p;
	char* pkt;
	int* list;

	n = gm_CalcPersonWealth((unsigned short) entity[0]);

	switch (action) {
	case 0:
		msg[4] = 0x5c;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = gm_GameTime.a;
		*(int*) (msg + 0x2c) = gm_GameTimeHour;
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (msg + 0x34) = gm_GameTimeTailWord;
		gm_AddTime((GAME_TIMESTAMP*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (entity + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = 3;
		*(int*) (msg + 0x5c) = 1;
		cm_SendCopyEntityData(msg);
		return;
	case 1:
		msg[4] = 0x5b;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = gm_GameTime.a;
		*(int*) (msg + 0x2c) = gm_GameTimeHour;
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (msg + 0x34) = gm_GameTimeTailWord;
		gm_AddTime((GAME_TIMESTAMP*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (entity + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = (int) ((float) n * g_6652c8);
		*(int*) (msg + 0x5c) = 1;
		cm_SendCopyEntityData(msg);
		return;
	case 2:
		msg[4] = 0x5c;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = gm_GameTime.a;
		*(int*) (msg + 0x2c) = gm_GameTimeHour;
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (msg + 0x34) = gm_GameTimeTailWord;
		gm_AddTime((GAME_TIMESTAMP*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (entity + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = 3;
		*(int*) (msg + 0x5c) = 3;
		cm_SendCopyEntityData(msg);
		return;
	case 3:
		msg[4] = 0x5b;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = gm_GameTime.a;
		*(int*) (msg + 0x2c) = gm_GameTimeHour;
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (msg + 0x34) = gm_GameTimeTailWord;
		gm_AddTime((GAME_TIMESTAMP*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (entity + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = (int) ((float) n * g_6652c8);
		*(int*) (msg + 0x5c) = 4;
		cm_SendCopyEntityData(msg);
		return;
	case 4:
		cm_SendBlockCharacter(*(int*) (entity + 2), 1, 0);
		return;
	case 5:
		amt_SendOfficeCommand(((char*) entity)[0x166], 0, 0, 4, 0xff);
		return;
	case 6:
		cm_SendBlockCharacter(*(int*) (entity + 2), 2, 0);
		return;
	case 7:
		level = (char) (((unsigned char*) entity)[0xd] > 2 ? 2 : 1);
		cm_BeginPacketFieldDelta(entity, *(int*) (entity + 2));
		cm_AppendPacketFieldDelta(1, 1, 0xd, &level);
		cm_RequestChangeAttribute();
		return;
	case 8:
		cm_SendBlockCharacter(*(int*) (entity + 2), 3, 0);
		return;
	case 9:
		cm_SendBlockCharacter(*(int*) (entity + 2), 0xff, 1);
		pkt = b9 + 0x18;
		list = (int*) (pkt + 0x34);
		id = *(int*) (entity + 2);
		list[0] = id;
		list[1] = *(int*) (gm_RichterKatholisch + 4);
		list[2] = *(int*) (gm_RichterEvangelisch + 4);
		n = 3;
		for (p = (char*) 0x7f4ca2; n < 0x10 && (int) p < 0x85a0a2; p += 0x21c) {
			if (id != *(int*) (p + 2) &&
			    (p[0] == 6 || p[0] == 7 || p[0] == 5)) {
				list[n] = *(int*) (p + 2);
				n++;
			}
		}
		*(char*) (pkt + 0x30) = (char) n;
		*(int*) (pkt + 0x0c) = *(int*) (gm_EntityIdField + (unsigned int) gm_LocalPlayerSlot * 0x21c);
		*(int*) (pkt + 0x14) = -1;
		*(int*) (pkt + 0x18) = gm_GameTime.a;
		*(int*) (pkt + 0x1c) = gm_GameTimeHour;
		*(int*) (pkt + 0x20) = gm_GameTimeSliceDword;
		*(unsigned short*) (pkt + 0x24) = gm_GameTimeTailWord;
		gm_AddTime((GAME_TIMESTAMP*) (pkt + 0x18), 0x18, 0, 0);
		/* packed packet fields: 2-byte hour override, then 4 zeroed bytes */
		*(unsigned short*) (pkt + 0x1c) = 10;
		*(int*) (pkt + 0x1e) = 0;
		*(char*) (pkt + 0x08) = 5;
		*(char*) (pkt + 0x7c) = (char) gm_RandomMod(5);
		*(char*) (pkt + 0x7d) = 0;
		*(char*) (pkt + 0x26) = 0x22;
		if (((char*) entity)[2] == 6 || ((char*) entity)[2] == 7) {
			*(char*) (pkt + 0x26) = 0xa2;
		}
		cm_EnqueueStagedPacket(pkt);
		if (srv_GetEntityOfficeSlot((unsigned char*) entity, b9 + 0x12c, b9) == 0) {
			return;
		}
		amt_SendOfficeCommand(*(int*) b9, 0, 0, 3, 0xff);
		return;
	default:
		return;
	}
}
