#include "Develop/DieGildeAddOn/game/spiel.h"
// SIZE 0xe

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
#include "client_packet_builder.h"
extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_00500cb0(pos14_7f4c00*, pos14_7f4c00*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);

void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
char* __cdecl fcn_0050dc90(unsigned char*);
char* __cdecl fcn_005049a0(unsigned char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x0055fd10 */
void __cdecl fcn_0055fd10(char* u)
{
	char* h;
	int v;
	char text[0x400];
	unsigned char* p;
	unsigned char* t;
	char* r;
	char* w;
	int a;
	int b;
	int off;
	int msg;

	switch (*(int*) (u + 0x70)) {
	case 0:
		*(int*) (u + 0x70) += 1;
		return;
	case 1:
		if (fcn_00500cb0((pos14_7f4c00*) (u + 0x52), &g_7f4c00) >= 0) {
			return;
		}
		gm_ResolveEntityById(0, (void**) (&h), 0, *(int*) (u + 0xac));
		if (h == 0) {
			goto kill;
		}
		v = 1;
		p = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
		if (p == 0) {
			goto kill;
		}
		t = lpGebaeudePROT + *p * 0x24d;
		if (*(short*) h != 0x116) {
			a = t[0x240];
			b = t[0x241];
		} else {
			a = b = t[0x242];
		}
		if (*(int*) (u + 0xb0) > 0) {
			*(int*) (u + 0xb0) -= 1;
			if (*(unsigned char*) (h + 0x1c) < a) {
				fcn_004c4510(h, *(int*) (h + 2));
				off = h - g_aed32c + 0x1c;
				fcn_004c4670(1, 1, off, &v);
				fcn_004c5360();
			}
		} else if (*(int*) (u + 0xb4) > 0) {
			*(int*) (u + 0xb4) -= 1;
			if (*(unsigned char*) (h + 0x1d) < b) {
				fcn_004c4510(h, *(int*) (h + 2));
				off = h - g_aed32c + 0x1d;
				fcn_004c4670(1, 1, off, &v);
				fcn_004c5360();
			}
		}
		if (*(int*) (u + 0xb4) != 0 || *(int*) (u + 0xb0) != 0) {
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 0xf, 0);
			return;
		}
		msg = 0x5f6;
		p = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
		if (p == 0) {
			goto kill;
		}
		r = fcn_0050dc90(p);
		if (r != 0 && (*(unsigned char*) (r + 0x1b4) & 1)) {
			msg = 0x60b;
		}
		w = fcn_005049a0(p);
		fcn_0051af00(text, 0x1bba, p);
		if (w != 0) {
			he_MessageBoxQuickjump(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, -1, text, 0, msg, *(int*) (p + 1), *(int*) (w + 2), 0, 0);
		} else {
			he_MessageBoxQuickjump(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, -1, text, 0, msg, *(int*) (p + 1), -1, 0, 0);
		}
		fcn_00546190(u);
		break;
	case -2:
	case -1:
	kill:
		fcn_00546190(u);
		break;
	}
}
