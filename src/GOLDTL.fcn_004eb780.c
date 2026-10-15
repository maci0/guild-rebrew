#include "Develop/DieGildeAddOn/game/spiel.h"
typedef struct Rec {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x16c - 8];
	char* home;
	char pad170[0x21c - 0x170];
} Rec;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned char g_773d75;


float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void __cdecl fcn_00526120(char*, int);

/* ADDRESS: GOLDTL 0x004eb780 */
int __cdecl fcn_004eb780(char* e, int* msg)
{
	char* h;
	int cnt;
	char buf[0x400];
	float f;
	int amount;
	int i;

	if (msg[0] != 2) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&h), 0, 0, msg[1]);
	if (h == 0) {
		return 0;
	}
	if (*(unsigned short*) (h + 0x27) == *(unsigned short*) e || *(unsigned short*) (h + 0x27) == 0xffff) {
		return 0;
	}
	f = fcn_00507f10(e, 4);
	amount = (int) (((gm_RandomFloat01() + 1.0f) * f * 15.0f + 5.0) * 2.55f);
	fcn_004c51a0(-1, *(int*) (e + 4), (*(char*)&g_773d75), msg[2]);
	for (i = 0, cnt = 0; i < 0x300; i++) {
		if (((Rec*)g_7f4ca0)[i].id != 0xffff && ((Rec*)g_7f4ca0)[i].home == h && *(unsigned short*) (h + 0x27) != i) {
			fcn_004c54c0(((Rec*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].owner, ((Rec*)g_7f4ca0)[i].owner, -amount, 1);
			cnt++;
		}
	}
	if (cnt != 0) {
		amount = (int) ((float) msg[2] / cnt) + 0x20;
		for (i = 0; i < 0x300; i++) {
			if (((Rec*)g_7f4ca0)[i].id != 0xffff && ((Rec*)g_7f4ca0)[i].home == h && *(unsigned short*) (h + 0x27) != i) {
				fcn_004c51a0(((Rec*)g_7f4ca0)[i].owner, -1, (*(char*)&g_773d75), amount);
			}
		}
	}
	fcn_005100f0(*(int*) (e + 4), -5);
	fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x8000000, 0);
	if (((Rec*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].type == 7 || ((Rec*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].type == 6) {
		fcn_0051af00(buf, 0x1663, h);
		fcn_00545e80(((Rec*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].owner, -1, buf, 0, 0x5fb, *(int*) (h + 1), -1, 0, "");
	}
	fcn_0051af00(buf, 0x1662, *(unsigned short*) (h + 0x27), h);
	for (i = 0; i < 0x300; i++) {
		if ((((Rec*)g_7f4ca0)[i].type == 7 || ((Rec*)g_7f4ca0)[i].type == 6) && *(int*) (e + 4) != ((Rec*)g_7f4ca0)[i].owner
		    && ((Rec*)g_7f4ca0)[i].owner != ((Rec*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].owner) {
			fcn_00545d40(((Rec*)g_7f4ca0)[i].owner, -1, buf, 0, 0x5fd, "");
		}
	}
	if (e[2] == 6) {
		fcn_0051af00(buf, 0x1661, *(unsigned short*) (h + 0x27), h);
		fcn_00526120(buf, 0);
	}
	return 1;
}
