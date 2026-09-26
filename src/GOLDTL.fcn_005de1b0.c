// FUNCTION: GOLD 0x005d1c80
// SIZE: 624
// FUNCTION: GOLDTL 0x005de1b0
// SIZE: 624

#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int f14;
	int pad18;
	unsigned short ids[16];
	int pad3c[5];
} Req;

#pragma pack(1)
// SIZE 0x29
typedef struct {
	char pad0[0x27];
	unsigned short w27;
} Unit;
#pragma pack()

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char b2;
	char pad3;
	int f4;
	char pad8[0x14];
	float f1c;
	char pad20[0x14c];
	Unit* f16c;
	char pad170[0xac];
} House;

extern char g_7f4ca0[];
extern __int64 g_666018;
extern char* g_14a558c;
extern char* g_14a5590;

Unit* __cdecl fcn_005bdc30(int, Req*, char*, int, int);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005015e0(Unit**, int, int, int);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c54c0(int, int, int, int);
float __cdecl gm_RandomFloat01(void);
float __cdecl fcn_004ff210(int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005de1b0(unsigned char* obj, int* arg)
{
	Unit* q;
	Req req;
	char text2[0x200];
	char text[0x800];
	unsigned char* e;
	int i;

	if (obj[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		req.a = 1;
		req.size = -1;
		req.kind = 6;
		req.cd = 0x1a0744300;
		q = fcn_005bdc30(1, &req, g_14a558c, 0, 0);
		if (q == 0) {
			return 0;
		}
		req.f14 = 3;
		req.ids[0] = q->w27;
		req.size = 0x400;
		req.kind = 6;
		req.cd = g_666018;
		e = fcn_005cd440(&req, g_14a5590, 0, 0);
		if (e == 0) {
			return 0;
		}
	} else {
		e = fcn_00508e40(arg[1]);
		if (e == 0) {
			return 0;
		}
		fcn_005015e0(&q, 0, 0, arg[2]);
		if (q == 0) {
			return 0;
		}
	}
	fcn_004c54c0(*(unsigned short*) e, ((House*)g_7f4ca0)[q->w27].f4, -20 - fcn_0042e410(0x20), 1);
	for (i = 0; i < 768; i++) {
		if (((House*)g_7f4ca0)[i].b2 == 0 && ((House*)g_7f4ca0)[i].f16c == q) {
			fcn_004ff210(i, (int) -((gm_RandomFloat01() * 0.2f + 0.1f) * ((House*)g_7f4ca0)[i].f1c));
		}
	}
	if (e[2] == 6 || e[2] == 7) {
		fcn_0051af00(text, 0x100b, q->w27, q->w27, q);
		fcn_00545d40(*(int*) (e + 4), -1, text, 0, 0x5fb, 0);
	}
	if (obj[2] == 6) {
		fcn_0051af00(text2, 0x109b, *(unsigned short*) e, q->w27, q);
		fcn_0051af00(text, 0xfe8, text2);
		fcn_005dbe90(text);
	}
	arg[4] = 1;
	return 1;
}
