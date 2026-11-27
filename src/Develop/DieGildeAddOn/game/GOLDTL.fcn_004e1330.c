#include "Develop/DieGildeAddOn/game/event_callbacks.h"


#include <string.h>

typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x170 - 0x8];
	char* link;
	char pad174[0x1b1 - 0x174];
	char busy;
	char pad1b2[0x21c - 0x1b2];
} Ent;
// SIZE 0x21c

typedef struct Cmd {
	char pad0[0x34];
	int a;
	int b;
} Cmd;

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* g_14a9a54;
extern char* g_14a9a58;
extern char* g_14a9a5c;
extern char g_6b5c60[];

Ent* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_GetEntityHealthRatio(Ent*);
void __cdecl he_SendCmdMessage(Ent*, Cmd*, char*, char*);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);

int __cdecl cut_NotifyDuell(char* event)
{
	Cmd* cmd;
	char buf[0x200];
	Ent* a;
	Ent* b;
	char* link;
	int n;
	int result;

	cmd = (Cmd*) event;
	result = 0;
	a = gm_LookupEntityRecordById(cmd->a);
	b = gm_LookupEntityRecordById(cmd->b);
	if (a == 0 || b == 0) {
		return 0;
	}
	if (b->busy != 0 || a->busy != 0) {
		if (b->kind == 6 || b->kind == 7) {
			he_PostEntityMessage((*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[b->id].entity_id), -1, g_14a9a5c, 0, 0x5ec, 0);
		}
		if (a->kind == 6 || a->kind == 7) {
			he_PostEntityMessage((*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[a->id].entity_id), -1, g_14a9a5c, 0, 0x5ec, 0);
		}
		return 0;
	}
	if (gm_GetEntityHealthRatio(a) <= 0.0f) {
		if (b->kind == 6 || b->kind == 7) {
			he_PostEntityMessage((*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[b->id].entity_id), -1, g_14a9a58, 0, 0x5ec, 0);
		}
		return 0;
	}
	if (gm_GetEntityHealthRatio(b) <= 0.0f) {
		if (a->kind == 6 || a->kind == 7) {
			he_PostEntityMessage((*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[a->id].entity_id), -1, g_14a9a58, 0, 0x5ec, 0);
		}
		return 0;
	}
	if (a->kind == 6 || a->kind == 7) {
		io_FormatTextBuffer(buf, 0x11ca, b->id);
		strcat(buf, g_14a9a54);
		he_SendCmdMessage(a, cmd, buf, &(*(char*)g_6b5c60));
		result = 1;
	}
	if (b->kind == 6 || b->kind == 7) {
		io_FormatTextBuffer(buf, 0x11ca, a->id);
		strcat(buf, g_14a9a54);
		he_SendCmdMessage(b, cmd, buf, &(*(char*)g_6b5c60));
		result = 1;
	}
	if (result != 0) {
		n = -1;
		link = a->link;
		if (link == 0) {
			link = b->link;
		}
		if (link != 0) {
			n = *(int*) (link + 1);
		}
		gm_TryRecordCrime(0x14, 1, a->handle, b->handle, n);
	}
	return result;
}
