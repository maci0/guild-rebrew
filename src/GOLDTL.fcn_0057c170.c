


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
	char pad8[0x15c];
	unsigned char trade;
	char pad165[7];
	char* site;
	char pad170[0xac];
};

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);

void __cdecl fcn_0057c170(struct house* a, struct house* b)
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
		if (((struct house*)g_7f4ca0)[i].type == 0 && ((struct house*)g_7f4ca0)[i].site != 0 && ((struct house*)g_7f4ca0)[i].trade == 0
		    && *(unsigned short*) (((struct house*)g_7f4ca0)[i].site + 0x27) == b->id) {
			h = &((struct house*)g_7f4ca0)[i];
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
	m.when = g_7f4c00;
	m.code = 1;
	m.who = h->owner;
	fcn_004c5530(&m);
	if (b == a) {
		id = 0x41dd;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_02");
	} else {
		id = 0x41dc;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_01");
	}
	fcn_0051af00(text1, 0x41e0, h->id, h->site);
	fcn_0051af00(text2, id, text1);
	fcn_00545d40(b->owner, -1, text2, 1, 0x5fb, name);
}
