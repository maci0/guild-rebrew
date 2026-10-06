// FUNCTION: GOLDTL 0x005c6540

typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

typedef struct Rec {
	char pad0[0x10];
	int mask;
	char pad14[4];
	unsigned short price;
} Rec;

typedef struct Btn {
	int btn;
	unsigned short* item;
} Btn;
// SIZE 8

typedef struct Ent {
	char pad0[0x1ec];
	int mask;
	char pad1f0[0x21c - 0x1f0];
} Ent;
// SIZE 0x21c

typedef struct Player {
	int pad0;
	int handle;
} Player;

extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;
extern unsigned char g_7747b0;
extern unsigned short g_774970;
extern char g_7f4ca0[];
#include "client_types.h"
extern Btn_776c60 g_776c60[6];
extern char* g_775318;
extern unsigned char g_773d75;

Rec* __cdecl fcn_005c6220(int key, int* out);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
char* __cdecl fcn_005c61e0(int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00525ef0(void);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_004737c0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005dbf10(Ent* e, Req* r);

int __cdecl fcn_005c6540(unsigned short* item)
{
	Req r = {0};
	int tmp;
	char text[0x400];
	Rec* rec;
	int dlg;
	int buy;
	int id;
	int i;

	buy = 0;
	rec = fcn_005c6220(*item, &tmp);
	if (rec != 0) {
		dlg = fcn_00470820(0, 0, "panel\\useobj");
		fcn_00471b60(dlg);
		fcn_004727a0(dlg, 1);
		if ((rec->mask & ((Ent*)g_7f4ca0)[g_774970].mask) == 0 && fcn_005c61e0(id = *item) != 0) {
			fcn_00519190(0xfe3, id * 2 + 0x9a8, rec->price, id * 2 + 0x9a8);
		} else {
			fcn_00519190(0xfe4, *item * 2 + 0x9a8);
		}
		fcn_00473a90(0, 0);
		fcn_00525ef0();
		g_100f1dc = -1;
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
				buy = 0;
			}
			if (g_100f1dc != -1) {
				if (g_100f1dc == 2) {
					buy = 1;
					g_774654 = 1;
				} else if (g_100f1dc == 1 && ((*(char*)&g_7747b0) & 0x80) == 0) {
					fcn_0051af00(text, 0xfe6, *item * 2 + 0x9a8, *item * 2 + 0x9a8);
					fcn_00471af0(dlg, 0);
					if (fcn_00526120(text, 1) != 0) {
						for (i = 0; i < 6; i++) {
							if (((Btn*)g_776c60)[i].item != 0 && (id = fcn_00471f80(((Btn*)g_776c60)[i].btn)) != 0) {
								fcn_004c51f0(-1, ((Player*)g_775318)->handle, *((Btn*)g_776c60)[i].item, id, g_773d75, 0);
								fcn_00472380(((Btn*)g_776c60)[i].btn, 0, 0x3e7, 0);
							}
						}
						fcn_004737c0();
					}
					fcn_00471af0(dlg, 1);
					buy = 0;
					g_774654 = 1;
				}
			}
		} while (fcn_005373e0(fcn_005c6540, 0x677c7) != 0);
		fcn_00471e30(dlg);
		if (buy == 0) {
			return 0;
		}
		r.s = item;
		r.id = -1;
		r.arg = -1;
		r.dir = 0;
		r.pad = 0;
		fcn_005dbf10(&((Ent*)g_7f4ca0)[g_774970], &r);
	}
	return r.dir;
}
