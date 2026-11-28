


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
	char pad60[0x98];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x15c];
	unsigned char trade;
	char pad165[7];
	char* site;
	char pad170[0xac];
};

extern pos14_7f4c00 gm_GameTime;
extern char gm_EntitySlotTable[];

void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);

/* ADDRESS: GOLDDE 0x00561fa0 */
void __cdecl he_ApplyZigeunerBetrothal(struct house* a, struct house* b)
{
	struct msg m;
	char name[0x64];
	char text1[0x400];
	char text2[0x400];
	struct house* h;
	int i;
	int id;

	h = 0;
	for (i = 0; i < 768; i++) {
		if (((struct house*)gm_EntitySlotTable)[i].type == 0 && ((struct house*)gm_EntitySlotTable)[i].site != 0 && ((struct house*)gm_EntitySlotTable)[i].trade == 0
		    && *(unsigned short*) (((struct house*)gm_EntitySlotTable)[i].site + 0x27) == b->id) {
			h = &((struct house*)gm_EntitySlotTable)[i];
			break;
		}
	}
	if (h == 0) {
		return;
	}
	memset(&m, 0, sizeof(m));
	m.kind = 0x33;
	m.owner = b->owner;
	m.target = *(int*) (h->site + 1);
	m.when = gm_GameTime;
	m.code = 1;
	m.who = h->owner;
	cm_SendCopyEntityData(&m);
	if (b == a) {
		id = 0x41dd;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_02");
	} else {
		id = 0x41dc;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_01");
	}
	io_FormatTextBuffer(text1, 0x41e0, h->id, h->site);
	io_FormatTextBuffer(text2, id, text1);
	he_PostEntityMessage(b->owner, -1, text2, 1, 0x5fb, name);
}
