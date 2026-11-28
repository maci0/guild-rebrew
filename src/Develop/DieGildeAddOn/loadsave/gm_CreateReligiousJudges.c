

extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"

void __cdecl cm_BeginCommandSync(void);
int __cdecl cm_RequestAllocSpieler(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_FlushCommandQueue(void);
void __cdecl cm_PollCommandQueue(void);
void __cdecl ls_ID2Ptr(void);
int* __cdecl cm_GetCommandResult(int h);

void __cdecl cm_AppendPacketFieldDelta(int a, int b, int off, int* v);
void __cdecl cm_RequestChangeAttribute(void);

void __cdecl gm_CreateReligiousJudges(void)
{
	int a;
	int b;
	int v;

	cm_BeginCommandSync();
	a = cm_RequestAllocSpieler(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	b = cm_RequestAllocSpieler(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	cm_EndCommandSync();
	while (!cm_AreQueuedCommandsDone()) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
	gm_RichterKatholisch = (char*) cm_GetCommandResult(a);
	gm_RichterEvangelisch = (char*) cm_GetCommandResult(b);
	cm_BeginCommandSync();
	v = 0;
	cm_BeginPacketFieldDelta(gm_RichterKatholisch, *(int*) (gm_RichterKatholisch + 4));
	cm_AppendPacketFieldDelta(1, 1, gm_RichterKatholisch - g_aed32c + 0xc, &v);
	cm_RequestChangeAttribute();
	v = 1;
	cm_BeginPacketFieldDelta(gm_RichterEvangelisch, *(int*) (gm_RichterEvangelisch + 4));
	cm_AppendPacketFieldDelta(1, 1, gm_RichterEvangelisch - g_aed32c + 0xc, &v);
	cm_RequestChangeAttribute();
	cm_EndCommandSync();
	while (!cm_AreQueuedCommandsDone()) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
}
