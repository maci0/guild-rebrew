#include <string.h>

typedef struct Req {
	int id;
	unsigned short x4;
} Req;
// SIZE 0x8

typedef struct Player {
	char pad0[2];
	unsigned char x2;
	char pad3[0x162];
	unsigned char x165;
	char pad166[6];
	char* x16c;
	char pad170[0xac];
} Player;
// SIZE 0x21c

typedef struct Packet {
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	int x28;
	int x2c;
	int x30;
	short x34;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	char pad5c[0x9c];
} Packet;
// SIZE 0xf8

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_00504bd0(int);
unsigned short __cdecl fcn_0042e410(int);
float __cdecl fcn_0050f980(int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_004c5530(Packet*);

// FUNCTION: GOLDTL 0x004ba080
// SIZE: 600
int __cdecl fcn_004ba080(Req* r)
{
	char* o;
	float dist;
	char* list[8];
	char buf[0x200];
	int n;
	int m;
	int i;
	char* e;
	char* p1;
	char* p2;

	n = 0;
	p2 = 0;
	o = fcn_00508e40(r->id);
	if (o == 0) {
		return 1;
	}
	if (fcn_005c6270(o, 0x290) != 0) {
		return 0x400;
	}
	e = gm_StartFilteredEntitySearch(1, 3, *(unsigned short*) o);
	if (e == 0) {
		return 0x400;
	}
	do {
		if (n >= 8) {
			break;
		}
		if (fcn_00504bd0(*(unsigned char*) e) == 1) {
			list[n] = e;
			n++;
		}
		e = gm_AddObjekt();
	} while (e != 0);
	if (n == 0) {
		return 0x400;
	}
	m = 0;
	p1 = list[fcn_0042e410(n)];
	for (i = 0; i < 768; i++) {
		if (m >= 6) {
			break;
		}
		if (((Player*)g_7f4ca0)[i].x2 == 0 && ((Player*)g_7f4ca0)[i].x16c == p1 && ((Player*)g_7f4ca0)[i].x165 != 0) {
			list[m] = (char*) &((Player*)g_7f4ca0)[i];
			m++;
		}
	}
	if (m > 2) {
		p2 = list[fcn_0042e410(m)];
	}
	if (p1 == 0 || p2 == 0) {
		return 0x400;
	}
	dist = fcn_0050f980(*(unsigned short*) o, *(unsigned short*) p2, 1);
	if (!((float) fcn_0042e410(50) > dist)) {
		return 0x400;
	}
	fcn_0051af00(buf, r->x4 + 0x12e7, (p2[9] ? 0x230 : 0x20d) + *(unsigned char*) (p2 + 0x165),
		*(unsigned short*) p2, p1);
	fcn_00545d40(*(int*) (o + 4), *(int*) (o + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	{
		Packet msg;

		memset(&msg, 0, sizeof(msg));
		msg.x8 = *(int*) (o + 4);
		msg.xc = *(int*) (p1 + 1);
		msg.x28 = (*(int*)&g_7f4c00);
		msg.x2c = (*(int*)&g_7f4c04);
		msg.x30 = g_7f4c08;
		msg.type = 0x31;
		msg.x36 = 1;
		msg.x34 = g_7f4c0c;
		msg.x58 = *(int*) (p2 + 4);
		fcn_004c5530(&msg);
	}
	return 0;
}
