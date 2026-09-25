// FUNCTION: GOLDTL 0x550980
// SIZE: 537

#include <string.h>

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x26];
	unsigned char code;
	char pad37[0x21];
	unsigned char who;
	char pad59[3];
	int other;
	char pad60[0x98];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern struct house g_7f4ca0[];
extern struct pos14 g_7f4c00;
extern struct house* g_773da8;
extern unsigned char g_773d75;
extern int g_100f884;
extern int g_100f1dc;

int __cdecl fcn_00500cb0(struct pos14*, struct pos14*);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_0050dac0(unsigned short);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl fcn_00550980(char* u)
{
	int t;
	struct msg m;
	int v;

	if (*(int*) (u + 0x70) == -1 || *(int*) (u + 0x70) == -2) {
		if (*(char**) (u + 0x74) != 0) {
			fcn_00545780(u);
		}
		fcn_00546190(u);
		return;
	}
	if (fcn_00500cb0(&g_7f4c00, (struct pos14*) (u + 0x44)) == -1) {
		return;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		t = fcn_0050dac0(*(unsigned short*) (u + 8));
		v = (int) (t * 0.05f);
		*(int*) (u + 0xb0) = v;
		if (*(char**) (u + 0x74) == 0) {
			fcn_00545670(u, 0, 0, "Berufe\\Messagebox_Meisterpruef", 0x5ec);
		}
		if (*(char**) (u + 0x74) == 0) {
			fcn_00546190(u);
			return;
		}
		fcn_004727a0(*(int*) (*(char**) (u + 0x74) + 8), 0);
		fcn_00519190((int) "$C");
		fcn_00519190(0x10b4, *(unsigned short*) (u + 8), v);
		*(int*) (u + 0x70) = 1;
		break;
	case 1:
		if (fcn_00500cb0(&g_7f4c00, (struct pos14*) (u + 0x52)) > 0) {
			fcn_00545780(u);
			fcn_00546190(u);
			return;
		}
		if (*(char**) (u + 0x74) == 0) {
			*(int*) (u + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
			return;
		}
		if (g_100f1dc == 2) {
			memset(&m, 0, sizeof(m));
			v = *(int*) (u + 0xb0);
			fcn_004c51a0(g_773da8->owner, g_7f4ca0[*(unsigned short*) (u + 8)].owner, g_773d75, v);
			m.kind = 0x56;
			m.target = -1;
			m.code = 0x11;
			m.who = 4;
			m.other = v;
			m.owner = g_7f4ca0[*(unsigned short*) (u + 8)].owner;
			fcn_004c5530(&m);
			fcn_00545780(u);
			fcn_00546190(u);
			return;
		}
		if (g_100f1dc == 1) {
			fcn_00545780(u);
			fcn_00546190(u);
			return;
		}
		break;
	}
}
