#include "Develop/DieGildeAddOn/game/spiel.h"


#include <string.h>

#include "client_types.h"

typedef struct House {
	char pad0[0x21c];
} House;
// SIZE 0x21c

typedef struct Query {
	int kind;
	char pad4[0x220 - 4];
} Query;
// SIZE 0x220

extern pos14_7f4c00 g_7f4c00;
extern int g_6643d8[];
extern __int64 g_666018;
extern char g_7f4ca0[];
extern char g_67ed14[];
extern char g_6a656c[];

unsigned char* __cdecl gm_LookupEntityRecordById(int id);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_004a5e60(House* h, int kind, __int64 f, int c, float r, int* out);
int __cdecl fcn_004fa5b0(int k, House* h, Query* q);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);

/* `close` is set in two if arms: one combined condition keeps it in a
 * register, three arms give it more slot weight than `o`. */
void __cdecl fcn_00562190(char* u)
{
	Query q;
	char* o;
	char* e;
	unsigned char* p;
	House* h;
	int close;
	int count;
	int r;

	close = 0;
	count = 0;
	if (u[0x78] & 4) {
		return;
	}
	*(int*) (u + 0xd8) = -1;
	p = gm_LookupEntityRecordById(*(int*) (u + 0xc4));
	if (p == 0) {
		*(int*) (u + 0x84) = fcn_004c5620(-1, u);
		return;
	}
	*(int*) (u + 0xbc) = gm_RandomMod(0x100);
	*(int*) (u + 0xc0) = g_6643d8[gm_RandomMod(0x10)];
	*(int*) (u + 0xb8) = 0;
	*(int*) (u + 0xb4) = -1;
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
	for (e = fcn_005463a0(1, 0, 0x18); e != 0; e = he_fn_Handlung()) {
		if (*(unsigned short*) (u + 8) == *(unsigned short*) (e + 8) && *(int*) (e + 4) != *(int*) (u + 4) && *(int*) (e + 0xc4) == *(int*) (u + 0xc4)) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
		if (*(int*) (e + 0xd8) != -1) {
			count++;
		}
	}
	gm_ResolveEntityById((void**) (&o), 0, 0, *(int*) (u + 0xac));
	if (o == 0) {
		fcn_004a5e60(&((House*)g_7f4ca0)[*(unsigned short*) (u + 8)], 6, g_666018, 0, 100.0f, (int*) (u + 0xac));
		gm_ResolveEntityById((void**) (&o), 0, 0, *(int*) (u + 0xac));
		if (o == 0) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
	}
	memset(&q, 0, sizeof(q));
	q.kind = 1;
	h = &((House*)g_7f4ca0)[*(unsigned short*) (u + 8)];
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	*(pos14_7f4c00*) (u + 0xc8) = g_7f4c00;
	if (fcn_004fa5b0(0x26, h, &q) == 2) {
		fcn_00500bb0((pos14_7f4c00*) (u + 0xc8), (*(int*) (u + 0xe8) + 4) * 24, 0, 0);
	} else {
		fcn_00500bb0((pos14_7f4c00*) (u + 0xc8), (*(int*) (u + 0xe8) + 3) * 24, 0, 0);
	}
	if (((char*) h)[2] == 6) {
		close = 1;
	} else if (p[2] == 6 || p[2] == 7 || count < 8) {
		close = 1;
	}
	fcn_004c4eb0(g_67ed14);
	if (close != 0) {
		*(int*) (u + 0xd8) = fcn_004c64b0(0x11, *(int*) (o + 1), -1, 0, 0, 0, g_6a656c);
		r = fcn_004c5620(0, u);
	} else {
		*(pos14_7f4c00*) (u + 0x52) = *(pos14_7f4c00*) (u + 0xc8);
		r = fcn_004c5620(4, u);
	}
	*(int*) (u + 0x84) = r;
	fcn_004c4ef0(g_67ed14);
}
