// FUNCTION: GOLD 0x00539880
// SIZE: 581
// FUNCTION: GOLDTL 0x5413d0
// SIZE: 581

#include <string.h>

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	unsigned char active;
	unsigned char female;
	char pada[0x26];
	char name[0x20];
	unsigned short serial;
	char pad52[0xa];
	int slots[8];
	char pad7c[0x1a0];
};

// SIZE 0x14c

// SIZE 0x114
struct building {
	int handle;
	char pad4[4];
	unsigned char kind;
	char pad9[0x27];
	unsigned char used;
	char pad31[0xe3];
};

extern char g_7f4ca0[];
#include "client_types.h"
extern unit_77e980 g_77e980[1024];
extern char g_9a9660[];
extern int g_774954;
extern int g_773d68;
extern char* g_14a5dbc[];
extern char* g_14a60d0[];

void __cdecl fcn_00546190(unit_77e980*);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004e6200(int, struct building*);
void __cdecl fcn_004e6b10(int);

void __cdecl fcn_005413d0(int idx)
{
	int keep[3];
	int kill[15];
	int i;
	int j;
	int found;
	struct house* h;
	unit_77e980* u;
	struct building* b;
	unsigned char k;

	kill[0] = 0x5d;
	kill[1] = 0x11;
	kill[2] = 0x30;
	kill[3] = 0x35;
	kill[4] = 0x42;
	kill[5] = 0x60;
	kill[6] = 0x4b;
	kill[7] = 0x5b;
	kill[8] = 0x5c;
	kill[9] = 0x5a;
	kill[10] = 0x46;
	kill[11] = 0x2e;
	kill[12] = 0x2d;
	kill[13] = 0x41;
	kill[14] = 0;
	keep[0] = 0x45;
	keep[1] = 0x47;
	keep[2] = 0;
	found = 0xffff;
	for (i = 0; i < 768; i++) {
		if (((struct house*)g_7f4ca0)[i].type == 6 && ((struct house*)g_7f4ca0)[i].active != 0) {
			found = i;
			break;
		}
	}
	if (found == 0xffff) {
		g_774954 = 1;
		return;
	}
	if (((struct house*)g_7f4ca0)[idx].type == 6 && ((struct house*)g_7f4ca0)[idx].active == 0) {
		h = &((struct house*)g_7f4ca0)[idx];
		for (j = 0; j < 1024; j++) {
			u = &g_77e980[j];
			if (u->kind != 0 && u->house == idx) {
				for (i = 0; kill[i] != 0; i++) {
					if (kill[i] == u->kind) {
						fcn_00546190(u);
						break;
					}
				}
				for (i = 0; keep[i] != 0; i++) {
					if (kill[i] == u->kind) {
						u->target = -1;
						break;
					}
				}
			}
		}
		h->type = 5;
		if (h->female == 0) {
			strcpy(h->name, g_14a5dbc[fcn_0042e410(0xbf)]);
		} else {
			strcpy(h->name, g_14a60d0[fcn_0042e410(0x70)]);
		}
		h->serial = g_773d68;
		memset(h->slots, 0xff, sizeof(h->slots));
		g_773d68++;
		for (j = 0; j < 96; j++) {
			if (((struct building*)g_9a9660)[j].used != 0 && fcn_004e6200(h->owner, &((struct building*)g_9a9660)[j]) != 0) {
				if (((struct building*)g_9a9660)[j].kind == 3 || ((struct building*)g_9a9660)[j].kind == 5 || ((struct building*)g_9a9660)[j].kind == 4
				    || ((struct building*)g_9a9660)[j].kind == 6 || ((struct building*)g_9a9660)[j].kind == 9 || ((struct building*)g_9a9660)[j].kind == 7) {
					fcn_004e6b10(((struct building*)g_9a9660)[j].handle);
				}
			}
		}
	}
}
