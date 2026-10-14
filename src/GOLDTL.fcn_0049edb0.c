#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

typedef struct Ent {
	char pad0[4];
	int x4;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern char* g_aed32c;
extern char g_67eb48[];


void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4510(char* p, int id);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);

int __cdecl fcn_0049edb0(char* a1, char* a2, char* a3)
{
	char* p1;
	char* p2;
	int v;
	char msg[0xf8];

	if (*a2 == 4 && *a3 == 0x14) {
		gm_ResolveEntityById((void**) (&p1), 0, 0, *(int*) (a2 + 4));
		if (p1 != 0) {
			gm_ResolveEntityById((void**) (&p2), 0, 0, *(int*) (a2 + 8));
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x23;
			*(int*) (msg + 8) = ((Ent*)g_7f4ca0)[*(unsigned short*) (p1 + 0x27)].x4;
			*(int*) (msg + 0xc) = *(int*) (p1 + 1);
			*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
			*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
			*(int*) (msg + 0x30) = g_7f4c08;
			*(short*) (msg + 0x34) = g_7f4c0c;
			msg[0x36] = 0x12;
			*(int*) (msg + 0x58) = *(int*) (p1 + 1);
			*(int*) (msg + 0x5c) = *(int*) (a1 + 4);
			*(int*) (msg + 0x60) = *(int*) (a3 + 4);
			*(int*) (msg + 0x64) = *(int*) (a3 + 8);
			*(int*) (msg + 0x6c) = *(int*) (a3 + 0x10);
			v = *(int*) (a3 + 4);
			fcn_004c4eb0(g_67eb48);
			fcn_004c5150(*(int*) (a1 + 4), *(int*) (p1 + 1), (*(char*)&g_773d75), *(int*) (a3 + 4));
			fcn_004c5530(msg);
			if (p2 != 0) {
				fcn_004c4510(p2, *(int*) (p2 + 1));
				fcn_004c4670(4, 1, (int) p2 - (*(int*)&g_aed32c) + 0x39, &v);
				fcn_004c5360();
			}
			fcn_004c4ef0(g_67eb48);
		}
	}
	return 0;
}
