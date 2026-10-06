// FUNCTION: GOLD 0x00573ee0
// FUNCTION: GOLDTL 0x57c420

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
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

extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);

void __cdecl fcn_0057c420(struct house* a, struct house* b)
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
	m.when = g_7f4c00;
	m.code = 1;
	m.who = a == b ? -1 : a->owner;
	m.other = b->owner;
	fcn_004c5530(&m);
	if (b == a) {
		id = 0x41dd;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_02");
	} else {
		id = 0x41dc;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_01");
	}
	fcn_0051af00(text1, 0x41e2);
	fcn_0051af00(text2, id, text1);
	fcn_00545d40(b->owner, -1, text2, 1, 0x5fb, name);
}
