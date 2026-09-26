// FUNCTION: GOLDTL 0x005bfdf0
// SIZE: 548

#include <string.h>
#pragma intrinsic(memset)

#pragma pack(push, 1)
typedef struct {
	int id;
	char p4[0x18];
	unsigned char kind;
	char p1d[0x10];
} Rec5bfd;
// SIZE 0x2d
#pragma pack(pop)

typedef struct {
	int pad[3];
	int count;
	int pad2[5];
} Stat5bfd;
// SIZE 0x24

typedef struct {
	int name;
	int pad[4];
} Kind5bfd;
// SIZE 0x14

#include "client_types.h"
extern Rec2d_9a3800 g_9a3800[512];
extern Kind5bfd g_14aa314[];
extern char g_6ac4c8[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_004f63d0(int, int*, unsigned short);
void __cdecl fcn_004f6780(int n, Rec5bfd* arr);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_005c91c0(int, int, int, int, int);
int __cdecl fcn_004f4830(int, Stat5bfd*);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_004fa5b0(int, unsigned short*, int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005bfdf0(unsigned short* who, unsigned short* e)
{
	int h;
	Stat5bfd st;
	int list[32];
	int q[0x88];
	Rec5bfd recs[32];
	int n;
	int i;
	int k;
	int w;

	if (*e == 0xffff) {
		return;
	}
	n = fcn_004f63d0(*(int*) (e + 2), list, *who);
	if (n < 1) {
		return;
	}
	for (i = 0; i < n; i++) {
		recs[i] = ((Rec5bfd*)g_9a3800)[list[i]];
	}
	fcn_004f6780(n, recs);
	h = fcn_00470820(0, 0, g_6ac4c8);
	fcn_00471b60(h);
	fcn_004727a0(h, 2);
	w = g_772514;
	fcn_004727a0(h, 4);
	fcn_0046e830(-1, -1, g_772514, w, 0x767);
	fcn_00473a90(0, 0);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1742, *e);
	fcn_004727a0(h, 2);
	for (k = 0; k < n; k++) {
		fcn_005c91c0(g_14aa314[recs[k].kind].name, 10, k * 0x28 + 10, 0x13b, 0x55);
		if (fcn_004f4830(recs[k].kind, &st) != 0 && st.count != 0) {
			for (i = 0; i < st.count; i++) {
				fcn_0046f740(i * 0x10 + 0x154, k * 0x28 + 10, 0x526, g_772514);
			}
		}
	}
	memset(q, 0, sizeof(q));
	q[0] = 1;
	fcn_004727a0(h, 3);
	if (fcn_004fa5b0(0x16, e, q) & 2) {
		fcn_00519190(0x174a);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005bfdf0, 0x657c7) != 0);
	fcn_00471e30(h);
}
