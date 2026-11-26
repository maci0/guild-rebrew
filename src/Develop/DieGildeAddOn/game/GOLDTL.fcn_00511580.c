


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x8
typedef struct {
	char pad0[4];
	int owner;
} Figure;


extern unsigned char g_773d75;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
#include "client_packet_builder.h"

void __cdecl fcn_0064d3f8(void);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_0050b750(int, char);

void __cdecl cm_AppendPacketFieldValue(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_BeginCommandSync(void);
int __cdecl cm_RequestAllocSpieler(int, int, int, short, int, char, int, int);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_FlushCommandQueue(void);
void __cdecl cm_PollCommandQueue(void);
void __cdecl ls_ID2Ptr(void);
Figure* __cdecl cm_GetCommandResult(int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl fcn_00535960(void);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

void __cdecl gm_InitCityOfficialsAndCitizens(void)
{
	int flag;
	int money;
	int figures[16];
	int i;
	int catholic_judge_cmd;
	int evang_judge_cmd;

	fcn_0064d3f8();
	for (i = 0; i < 16; i++) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type < 5) {
			money = fcn_0050b750(gm_RandomMod(0x122) + 10, (*(char*)&g_773d75));
			cm_BeginPacketFieldDelta((char*) ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]), ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id);
			cm_AppendPacketFieldValue(4, 1, 0x1ac, &money);
			cm_RequestChangeAttribute();
		}
	}
	cm_BeginCommandSync();
	catholic_judge_cmd = cm_RequestAllocSpieler(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	evang_judge_cmd = cm_RequestAllocSpieler(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
	gm_RichterKatholisch = (char*) cm_GetCommandResult(catholic_judge_cmd);
	gm_RichterEvangelisch = (char*) cm_GetCommandResult(evang_judge_cmd);
	cm_BeginCommandSync();
	flag = 0;
	cm_BeginPacketFieldDelta(gm_RichterKatholisch, ((Figure*) gm_RichterKatholisch)->owner);
	cm_AppendPacketFieldDelta(1, 1, gm_RichterKatholisch - g_aed32c + 0xc, &flag);
	cm_RequestChangeAttribute();
	flag = 1;
	cm_BeginPacketFieldDelta(gm_RichterEvangelisch, ((Figure*) gm_RichterEvangelisch)->owner);
	cm_AppendPacketFieldDelta(1, 1, gm_RichterEvangelisch - g_aed32c + 0xc, &flag);
	cm_RequestChangeAttribute();
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
	cm_BeginCommandSync();
	for (i = 0; i < 8; i++) {
		figures[i] = cm_RequestAllocSpieler(0, -1, -1, gm_RandomMod(8) + 0x10, -1, (char) (gm_RandomMod(3) + 4), 0, 0);
	}
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		fcn_00535960();
	}
	cm_BeginCommandSync();
	for (i = 0; i < 8; i++) {
		figures[i] = cm_RequestAllocSpieler(0xb, -1, -1, gm_RandomMod(8) + 0x10, -1, 0, 0x13, 0);
		cm_SendSellObjekt(-2, -1, 0x154, 1, (*(char*)&g_773d75), 0);
	}
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		fcn_00535960();
	}
}
