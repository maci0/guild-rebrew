// FUNCTION: GOLD 0x00543a10
// SIZE: 754
// FUNCTION: GOLDTL 0x0054b940
// SIZE: 754

#include <string.h>

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x21c - 8];
} Entity;

// SIZE 0x2e
typedef struct {
	char pad0[0x1c];
	int ids[4];
	unsigned char a;
	unsigned char b;
} Group;

#pragma pack(push, 1)
// SIZE 0x61
typedef struct {
	char pad0[0x5d];
	int home;
} Player;
#pragma pack(pop)

// SIZE 0xbe
typedef struct {
	char pad0[8];
	unsigned short ent;
	char padA[6];
	int owner;
	char pad14[0x3e];
	Stamp stamp;
	char pad60[0x10];
	int state;
	char pad74[4];
	unsigned char flags;
	char pad79[0x33];
	int ids[4];
	unsigned char a;
	unsigned char b;
} Order;

// SIZE 0x8
typedef struct {
	Entity* ent;
	int value;
} Member;

// SIZE 0x34
typedef struct {
	Entity* ent;
	Member members[4];
	int a;
	int b;
	int text;
	unsigned char count;
} Party;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern char g_6b5c60[];

void __cdecl fcn_005015e0(Player**, int, int, int);
Group* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_004c5620(int, Order*);
Entity* __cdecl fcn_00508e40(int);
int __cdecl fcn_00494470(Party*, int);
void __cdecl fcn_0051af00(char*, int, ...);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00546190(Order*);

void __cdecl fcn_0054b940(Order* o)
{
	char msg[0x800];
	char line[0x100];
	Party party;
	int len;
	Party* fill;
	Player* pl;
	Group* g;
	Entity* e;
	int i;
	int n;
	int k;
	int first;

	pl = 0;
	g = 0;
	if (o->state == -2 || o->state == -1) {
		fcn_00546190(o);
		return;
	}
	if (o->flags & 4) {
		return;
	}
	fcn_005015e0(&pl, 0, 0, o->owner);
	if (pl != 0) {
		g = fcn_00502cd0(pl->home, 1, 0, 0x17);
		if (g == 0) {
			o->stamp = (*(Stamp*)&g_7f4c00);
			fcn_004c5620(-1, o);
			return;
		}
	}
	switch (o->state) {
	case 0:
		len = 4;
		fill = &party;
		/*
		 * The reference zero-fills with the hand-written block-fill
		 * prelude no msvc6 C spelling emits (docs/codegen-walls.md 6b).
		 */
		__asm {
			mov edi, fill
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		n = 0;
		party.ent = &((Entity*)g_7f4ca0)[o->ent];
		if (g != 0) {
			first = g->a;
			party.b = g->b;
			party.a = first;
			for (i = 0; i < 4; i++) {
				if (g->ids[i] != -1) {
					e = fcn_00508e40(g->ids[i]);
					if (e != 0) {
						party.members[n++].ent = e;
					}
				}
			}
		} else {
			party.a = o->a;
			party.b = o->b;
			for (i = 0; i < 4; i++) {
				if (g->ids[i] != -1) {
					e = fcn_00508e40(o->ids[i]);
					if (e != 0) {
						party.members[n++].ent = e;
					}
				}
			}
		}
		party.count = (unsigned char) n;
		if (fcn_00494470(&party, 1) == 0 && (party.ent->type == 6 || party.ent->type == 7)) {
			fcn_0051af00(msg, 0x1787, party.text);
			for (i = 0; i < party.count; i++) {
				k = party.members[i].value * 3 + 0x178f + fcn_0042e410(3);
				fcn_0051af00(line, 0x1788, party.members[i].ent->slot, k);
				strcat(msg, line);
			}
			fcn_00545d40(party.ent->id, -1, msg, 0x20, 0x5fd, g_6b5c60);
		}
		o->stamp = (*(Stamp*)&g_7f4c00);
		fcn_004c5620(-1, o);
		return;
	case 1:
		o->stamp = (*(Stamp*)&g_7f4c00);
		fcn_004c5620(-1, o);
		return;
	}
}
