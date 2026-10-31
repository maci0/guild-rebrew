

// SIZE 0x7c
typedef struct Req {
	int id;
	int x4;
	char pad8[0x74];
} Req;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
extern char g_6a6248[];

typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int handle;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned char* __cdecl gm_StartFilteredEntitySearch(int count, ...);
int __cdecl gm_CheckEntityType(unsigned char* e);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d);
int __cdecl fcn_004c51f0(int a, int b, int c, int d, char e, int f);
void __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
void __cdecl io_FormatTextBuffer(void* out, int id, ...);
char* __cdecl fcn_0050dc90(unsigned char* e);
void __cdecl he_MessageBoxQuickjump(int a, int b, char* text, int c, int d, int e, int f, int g, char* h);
void __cdecl fcn_00500bb0(pos14_7f4c00* t, int a, int b, int c);
int __cdecl fcn_004c5790(int kind, Req* r);
void __cdecl fcn_00546190(char* o);

void __cdecl fcn_00563f60(char* o)
{
	int kind;
	unsigned char* e;
	unsigned char* race;
	char* p;
	char* q;
	char buf[0x400];

	kind = 0x606;
	switch (*(int*) (o + 0x70)) {
	case 0:
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
		if (e != 0) {
			fcn_004c51f0(*(int*) (e + 1), -1, *(unsigned short*) (o + 0xb0), 1, (*(char*)&g_773d75), 0);
			fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 0, 0x80);
		}
		(*(int*) (o + 0x70))++;
		break;
	case 1:
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
		if (e != 0) {
			p = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, *(unsigned short*) (o + 0xb0));
			if (p != 0) {
				race = lpGebaeudePROT + *e * 0x24d;
				io_FormatTextBuffer(buf, 0x1c2b, e, *(unsigned short*) (o + 0xb0) * 2 + 0x9a8);
				if (*race != 6) {
					q = fcn_0050dc90(e);
					if (q != 0 && q[2] == 1 && (q[0x1b4] & 1)) {
						kind = 0x60b;
					}
				}
				he_MessageBoxQuickjump(((Ent*)g_7f4ca0)[*(unsigned short*) (o + 8)].handle, ((Ent*)g_7f4ca0)[*(unsigned short*) (o + 8)].handle, buf, 0, kind, *(int*) (e + 1), *(int*) (p + 2), 0, g_6a6248);
			}
			if (gm_CheckEntityType(e)) {
				Req m;

				p = fcn_00502cd0(*(int*) (e + 0x5d), 1, 4, 2);
				*(pos14_7f4c00*) &m = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) &m, 0, 0, 1);
				m.id = *(int*) (e + 1);
				m.x4 = *(int*) (p + 2);
				fcn_004c5790(4, &m);
			}
		}
		fcn_00546190(o);
		break;
	case -2:
	case -1:
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
		if (e != 0) {
			fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 0, 0x80);
		}
		fcn_00546190(o);
		break;
	}
}
