#include <string.h>

#pragma pack(push, 1)
// SIZE 0x24d
typedef struct {
	char type;
	char pad1[0x24c];
} Kind_5635b0;
#pragma pack(pop)

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp_5635b0;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x214];
} Entity_5635b0;

// SIZE 0xbc
typedef struct {
	char pad0[8];
	unsigned short ent;
	char pada[0x48];
	Stamp_5635b0 stamp;
	char pad60[0x10];
	int state;
	char pad74[4];
	unsigned char flags;
	char pad79[0xb];
	int event;
	char pad88[0x24];
	int who;
	int value;
	char padb4[4];
	int tries;
} Order_5635b0;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* g_868050;
extern char g_7f4ca0[];

unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004c4450(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_0050cf50(char*, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c5620(int, Order_5635b0*);
void __cdecl fcn_00500bb0(Stamp_5635b0*, int, int, int);
void __cdecl fcn_00546190(Order_5635b0*);

// FUNCTION: GOLDTL 0x5635b0

/* Order step: from the third try on, sends message 0x6e with a chance
 * scaled by the order's value, then re-arms the order. */
void __cdecl fcn_005635b0(Order_5635b0* o)
{
	char m[0xf8];
	float f;
	float d;
	int v;
	char* p;
	Kind_5635b0* k;

	if ((o->flags & 2) && o->event != -1) {
		if (fcn_004c4450(o->event) == 0) {
			return;
		}
		o->event = -1;
	}
	switch (o->state) {
	case 0:
		if (o->tries >= 2) {
			p = gm_StartFilteredEntitySearch(1, 1, o->who);
			if (p == 0) {
				fcn_00546190(o);
				return;
			}
			k = &((Kind_5635b0*)g_868050)[*(unsigned char*) p];
			if (k->type == 0xd || k->type == 0xc || k->type == 0xb) {
				fcn_00546190(o);
				return;
			}
			if (o->flags & 2) {
				if (*p == 0x27) {
					if (*(unsigned short*) (p + 0x27) == 0xffff) {
						goto next;
					}
					if (((Entity_5635b0*)g_7f4ca0)[*(unsigned short*) (p + 0x27)].type != 6 && ((Entity_5635b0*)g_7f4ca0)[*(unsigned short*) (p + 0x27)].type != 7) {
						goto next;
					}
				}
				v = fcn_0050cf50(p, p[0x5c]);
				d = v + 256.0f;
				f = o->value / d;
				if (fcn_0042e410(100) > f * 50.0f) {
					memset(m, 0, sizeof(m));
					m[4] = 0x6e;
					*(int*) (m + 0xc) = -1;
					m[0x36] = 1;
					*(int*) (m + 8) = ((Entity_5635b0*)g_7f4ca0)[o->ent].id;
					*(Stamp_5635b0*) (m + 0x28) = (*(Stamp_5635b0*)&g_7f4c00);
					*(int*) (m + 0x60) = o->who;
					*(int*) (m + 0x68) = o->value;
					fcn_004c5530(m);
					o->event = fcn_004c5620(-1, o);
					fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 2);
				}
			}
		}
next:
		o->tries = o->tries + 1;
		o->stamp = (*(Stamp_5635b0*)&g_7f4c00);
		fcn_00500bb0(&o->stamp, fcn_0042e410(3) + 4, 0, 0);
		return;
	case -2:
	case -1:
		p = gm_StartFilteredEntitySearch(1, 1, o->who);
		if (p == 0) {
			fcn_00546190(o);
			return;
		}
		fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 2);
		fcn_00546190(o);
		return;
	}
}
