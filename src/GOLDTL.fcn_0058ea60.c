// FUNCTION: GOLD 0x5864c0
// SIZE: 860
// FUNCTION: GOLDTL 0x58ea60
// SIZE: 860

#include <string.h>

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

// SIZE 0x10
struct offer {
	int id;
	int taken;
	int pad8;
	int padc;
};

// SIZE 0xc
struct level {
	int n;
	int total;
	int x;
};

extern struct house g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_004c2db0(int, int);
char* __cdecl fcn_0058e220(char*, char*);
void __cdecl fcn_004a51d0(struct house*, int, struct offer*, struct level*);
float __cdecl fcn_004f4770(char*);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_005782f0(struct house*, int);
int __cdecl fcn_00519190();
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00428720(char*);

void __cdecl fcn_0058ea60(char* e, char* res)
{
	char* m;
	float f;
	struct level lv;
	struct offer list[15];
	int mode;
	int id;
	int t;
	int h;
	int i;
	int v;

	id = 0;
	t = fcn_004c2db0(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	m = fcn_0058e220(e, res);
	memset(list, 0, sizeof(list));
	list[0].id = 0x2b8;
	list[1].id = 0x2bb;
	list[2].id = 0x2bc;
	list[3].id = 0x2bf;
	list[4].id = 0x2c2;
	list[5].id = 0x2c3;
	list[6].id = 0x2bd;
	list[7].id = 0x2c1;
	list[8].id = 0x2c4;
	list[9].id = 0x2c5;
	list[10].id = 0x2c6;
	list[11].id = 0x2ba;
	list[12].id = 0x2c0;
	list[13].id = 0x2be;
	list[14].id = 0x2b9;
	fcn_004a51d0(&g_7f4ca0[g_774970], 0xf, list, &lv);
	if ((lv.n == 6 && lv.x == 0) || lv.total == 0xf) {
		mode = 1;
	} else {
		i = fcn_0042e410(0xf);
		while (list[i].taken != 0) {
			i = (i + 1) % 0xf;
		}
		id = list[i].id;
		mode = 0;
	}
	f = fcn_004f4770(e);
	if (gm_RandomFloat01() + f - 0.2f < 1.0f) {
		mode = 2;
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Friedhof");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	g_100f1dc = -1;
	fcn_004727a0(h, 1);
	if (mode == 0) {
		fcn_004c51f0(g_7f4ca0[g_774970].handle, -1, id, 1, g_773d75, 0);
		fcn_005782f0(&g_7f4ca0[g_774970], 2);
		fcn_00519190(0x40f2, 0x40cc, id * 2 + 0x9a8);
		fcn_004c3030(t, 0, "GEIST_KOMMT", fcn_0042e410(8));
	} else if (mode == 1) {
		v = (fcn_0042e410(0x400) + 1000) << 5;
		fcn_004c5150(g_7f4ca0[g_774970].handle, -1, g_773d75, v);
		fcn_00519190(0x40f3, 0x40cc, v);
		fcn_004c3030(t, 0, "GEIST_KOMMT", fcn_0042e410(8));
	} else {
		fcn_00519190(0x40d3, 0x40cc);
		fcn_004c3030(t, 0, "GEIST_KOMMT_NICHT", fcn_0042e410(8));
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_0058ea60, 0x777c7) != 0);
	fcn_00471e30(h);
	if (m != 0) {
		fcn_00428720(m);
	}
}
