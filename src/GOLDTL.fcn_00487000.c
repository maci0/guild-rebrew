#include <string.h>

#include "client_types.h"

/* One 0x21c-byte record of the 0x7f4ca0 table. Only the fields this body
 * reads are named; the rest stays padding. */
typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[0x165 - 3];
	unsigned char role;
	char pad166[0x16c - 0x166];
	char* home;
	char pad170[0x174 - 0x170];
	int slots;
	char pad178[0x21c - 0x178];
} Ent;
// SIZE 0x21c

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];
extern char* g_entity_type_table;

int __cdecl gm_RandomMod(int);
int __cdecl gm_CheckEntityType(unsigned char*);
char* __cdecl fcn_005463a0(int, int, int, int, int);
float __cdecl fcn_005101e0(unsigned char*, int, int, int);
void __cdecl fcn_004c5530(char*);

/* ADDRESS: GOLDTL 0x00487000 */
/* Offers a building slot to the local player: counts the records and work
 * slots already bound to the entity's owner, and either reports the pending
 * offer or asks for a new builder. */
void __cdecl fcn_00487000(char* e)
{
	char m[0xf8];
	char* ent;
	char* p;
	char* slot;
	int n;
	int tick;
	int i;

	if ((*(short*) &g_7f4c04) != 7 && (*(short*) &g_7f4c04) != 0xc && (*(short*) &g_7f4c04) != 0x12) {
		*(unsigned int*) (e + 0x1b4) &= 0xffffffbf;
		return;
	}
	if (*(unsigned int*) (e + 0x1b4) & 0x40) {
		return;
	}
	*(unsigned int*) (e + 0x1b4) |= 0x40;
	if ((*(unsigned char*) ((char*) 0x7f4ca0
	                        + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c + 2) == 6
	     || *(unsigned char*) ((char*) 0x7f4ca0 + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c + 2) == 7)
	    && !(*(unsigned int*) (e + 0x1b4) & 2)) {
		return;
	}
	ent = g_entity_type_table + *(unsigned char*) (*(char**) (e + 0x16c)) * 0x24d;
	for (p = (char*) 0x7f4e05; p < (char*) 0x85a205; p += 0x21c) {
		if (*(short*) (p - 0x165) == -1) {
			continue;
		}
		if (*(char**) (p + 7) != *(char**) (e + 0x16c)) {
			continue;
		}
		if (*(unsigned char*) p == 0) {
			continue;
		}
		if (*(unsigned char*) p != *(unsigned char*) (ent + 0x230)) {
			continue;
		}
		if (*(int*) (p + 0xf) < 4) {
			continue;
		}
		memset(m, 0, sizeof(m));
		m[4] = 0x32;
		*(int*) (m + 8) = *(int*) (g_7f4ca4
		                           + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(char**) (e + 0x16c) + 1);
		*(int*) (m + 0x28) = g_7f4c00.a;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 2;
		*(int*) (m + 0x58) = *(int*) (p - 0x161);
		fcn_004c5530(m);
	}
	n = 0;
	for (p = (char*) 0x7f4e0c; p < (char*) 0x85a20c; p += 0x21c) {
		if (*(short*) (p - 0x16c) == -1) {
			continue;
		}
		if (*(char**) p != *(char**) (e + 0x16c)) {
			continue;
		}
		if (*(unsigned char*) (p - 7) == 0) {
			continue;
		}
		n++;
	}
	slot = fcn_005463a0(2, 0, 6, 3, *(int*) (*(char**) (e + 0x16c) + 1));
	if (slot != 0) {
		p = slot + 0xb0;
		for (i = 0; i < 0xc; i++) {
			if (*(int*) (p + i * 4) != 0) {
				n++;
			}
		}
	}
	if (n >= (int) (*(unsigned char*) (g_entity_type_table
	                                    + *(unsigned char*) (*(char**) (e + 0x16c)) * 0x24d + 0x231)
	                + *(unsigned char*) (g_entity_type_table
	                                     + *(unsigned char*) (*(char**) (e + 0x16c)) * 0x24d + 0x232))) {
		return;
	}
	tick = (int) fcn_005101e0((unsigned char*) ((char*) 0x7f4ca0
	                                           + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c),
	                          *(unsigned char*) (*(char**) (e + 0x16c)), -1, 1);
	if (n != 0) {
		if (*(unsigned int*) (e + 0x1c8) & 8) {
			return;
		}
		if (*(int*) (e + 0x1b8) < tick) {
			return;
		}
		if ((int) (gm_RandomMod(0x48) & 0xffff) < (0x12 - n) * 2) {
			return;
		}
	}
	if (slot != 0) {
		return;
	}
	memset(m, 0, sizeof(m));
	m[4] = 6;
	*(int*) (m + 8) = *(int*) (g_7f4ca4
	                           + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c);
	*(int*) (m + 0xc) = *(int*) (*(char**) (e + 0x16c) + 1);
	*(int*) (m + 0x28) = g_7f4c00.a;
	*(int*) (m + 0x2c) = g_7f4c04;
	m[0x36] = 1;
	*(int*) (m + 0x30) = g_7f4c08;
	*(short*) (m + 0x34) = g_7f4c0c;
	*(int*) (m + 0x5c) = 1;
	gm_CheckEntityType((unsigned char*) *(char**) (e + 0x16c));
	*(int*) (m + 0x8c) = -1;
	m[0x59] = 1;
	m[0x58] = *(unsigned char*) (g_entity_type_table
	                             + *(unsigned char*) (*(char**) (e + 0x16c)) * 0x24d + 0x230);
	fcn_004c5530(m);
	*(int*) (e + 0x1b8) -= tick;
}
