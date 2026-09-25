// FUNCTION: GOLD 0x00584bc0
// SIZE: 615
// FUNCTION: GOLDTL 0x58d180
// SIZE: 615

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

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x180];
	unsigned char grave;
	char pad189[0x93];
};

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	struct pos14 when;
	unsigned char code;
	char pad37;
	int field;
	char pad3c[0x20];
	int who;
	unsigned char slot;
	char pad61[0x97];
};

extern struct pos14 g_7f4c00;
extern struct house g_7f4ca0[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern int g_14b5798;
extern int g_14b579c;
extern int g_14b556c;

int __cdecl fcn_0057b9d0(char*, int, int);
void __cdecl fcn_005263d0(int, int, int);
void __cdecl fcn_0052a0c0(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00526120(int, int);
int __cdecl fcn_004c5530(struct msg*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);

int __cdecl fcn_0058d180(char* who, char* a2)
{
	int r;
	int ok;
	int cancel;
	struct msg m;
	int h;
	int s;
	int i;
	int id;
	struct house* hh;

	r = 0;
	if (fcn_0057b9d0(who, *(int*) (a2 + 4), *(unsigned char*) (a2 + 8)) != 0) {
		fcn_005263d0(g_14b5798, g_14b579c, 0);
		return 0;
	}
	fcn_0052a0c0(who, 0);
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Friedhof");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	fcn_00519190(0x4120, 0x411e, 0x228);
	fcn_004727a0(h, 2);
	s = fcn_00519190(0x4121);
	ok = fcn_00472250(h, 2, s);
	cancel = fcn_00472250(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				hh = 0;
				for (i = 0; i < 768; i++) {
					if (g_7f4ca0[i].grave != 0) {
						hh = &g_7f4ca0[i];
						break;
					}
				}
				if (hh == 0) {
					fcn_00526120(g_14b556c, 0);
				} else {
					memset(&m, 0, sizeof(m));
					m.kind = 0x8d;
					m.code = 1;
					m.owner = g_7f4ca0[*(unsigned short*) (who + 0x27)].handle;
					m.target = *(int*) (who + 1);
					m.when = g_7f4c00;
					m.who = *(int*) (a2 + 4);
					m.slot = a2[8];
					m.field = hh->handle;
					id = fcn_004c5530(&m);
					while (id != -1 && fcn_004c4450(id) == 0) {
						fcn_005373e0(0, 0x20007);
					}
					r = 1;
					g_774654 = 1;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_0058d180, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_0052a2d0();
	fcn_005305a0();
	return r;
}
