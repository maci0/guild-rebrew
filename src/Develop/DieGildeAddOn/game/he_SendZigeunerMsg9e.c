


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
	char pad8[0x214];
};

extern pos14_7f4c00 gm_GameTime;

void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);

void __cdecl he_SendZigeunerMsg9e(struct house* a, struct house* b)
{
	struct msg m;
	char name[0x64];
	char text1[0x400];
	char text2[0x400];
	int id;

	memset(&m, 0, sizeof(m));
	m.kind = 0x9e;
	m.owner = b->owner;
	m.target = -1;
	m.when = gm_GameTime;
	m.code = 1;
	m.who = a == b ? -1 : a->owner;
	m.other = b->owner;
	cm_SendCopyEntityData(&m);
	if (b == a) {
		id = 0x41dd;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_02");
	} else {
		id = 0x41dc;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_01");
	}
	io_FormatTextBuffer(text1, 0x41e2);
	io_FormatTextBuffer(text2, id, text1);
	he_PostEntityMessage(b->owner, -1, text2, 1, 0x5fb, name);
}
