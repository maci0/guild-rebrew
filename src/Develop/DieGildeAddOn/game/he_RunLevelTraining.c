#include "Develop/client_types.h"
#pragma pack(push, 1)







// SIZE 0xe
#pragma pack(pop)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"










extern pos14_7f4c00 gm_GameTime;


int __cdecl cm_GetCommandStatus(int id);
void __cdecl he_FreeAction(char* t);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl gm_GetJobTrainingAttributes(int k, int* a, int* b);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
int __cdecl gm_RandomMod(int n);
void __cdecl cm_AppendPacketFieldValue(int, int, int, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestSetEntityLevel(int, int);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl cm_SendSetHE(int a1, char* e);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl he_RegisterApEvent(int, char*, int, int);

/* ADDRESS: GOLDTL 0x005516e0 */
void __cdecl he_RunLevelTraining(char* t)
{
	char c;
	int a;
	int b;
	char buf[0x100];
	ENTITY_RECORD* e;
	char* p;
	int h;

	if (*(int*) (t + 0x70) == -2 || *(int*) (t + 0x70) == -1) {
		he_FreeAction(t);
		return;
	}
	if (t[0x78] & 4)
		return;
	if (*(int*) (t + 0x84) != -1 && cm_GetCommandStatus(*(int*) (t + 0x84)) == 0)
		return;
	*(int*) (t + 0x84) = -1;
	switch (*(int*) (t + 0x70)) {
	case 1:
		e = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (t + 8)]);
		gm_GetJobTrainingAttributes(gm_MapEntityStatRange(*(unsigned char*) (t + 0xb0)), &a, &b);
		cm_BeginPacketFieldDelta((char*) e, e->entity_id);
		c = gm_RandomMod(0x10) + 0x10;
		cm_AppendPacketFieldValue(1, 1, a + 0x80, &c);
		c = gm_RandomMod(0x10) + 0x10;
		cm_AppendPacketFieldValue(1, 1, b + 0x80, &c);
		cm_RequestChangeAttribute();
		cm_RequestSetEntityLevel(e->entity_id, *(unsigned char*) (t + 0xb0));
		p = gm_LookupEntityRecordById(*(int*) (t + 0xac));
		if (p == 0) {
			*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
			cm_SendSetHE(-1, t);
			return;
		}
		io_FormatTextBuffer(buf, 0x1a9c, e->entity_index, (e->gender ? 0x18f : 0x130) + *(unsigned char*) (t + 0xb0));
		h = *(int*) (p + 4);
		he_PostEntityMessage(h, h, buf, 0, 0x5f4, 0);
		*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		cm_SendSetHE(-1, t);
		return;
	case 0:
		e = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (t + 8)]);
		p = gm_LookupEntityRecordById(*(int*) (t + 0xac));
		if (p == 0) {
			*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
			cm_SendSetHE(-1, t);
			return;
		}
		io_FormatTextBuffer(buf, 0x1a9b, e->entity_index);
		t[0xb8]++;
		*(short*) (t + 0x56) += 0x18;
		cm_SendSetHE((unsigned char) t[0xb8] >= 3, t);
		he_RegisterApEvent(*(unsigned short*) p, buf, 0, -*(int*) (t + 0xb4));
		return;
	}
}
