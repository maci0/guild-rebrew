


// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char b2;
	char pad3;
	int f4;
	char pad8[4];
	unsigned char bc;
	char padd[0x77];
	unsigned char b84;
	char pad85[0x197];
} House;

extern char g_7f4ca0[];
extern float g_662964;
extern unsigned char g_773d75;
extern char s_6acdcc[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_AccumulateTyped2(House*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c6ae0(int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c4510(House*, int);
void __cdecl fcn_004c4570(int, int, int, unsigned int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(House*, int);
int __cdecl fcn_00526010(House*, int, char);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d8af0(House* e)
{
	int i;

	if (e->b2 != 6) {
		unsigned int who;
		int money;
		unsigned int rank;

		*(unsigned char*) &rank = e->b84;
		who = e->bc;
		if (*(int*) ((char*) e + 0x194) < 6) {
			return 0x20;
		}
		money = (int) (gm_WalkEntityChain(e->id) * g_662964);
		if (gm_AccumulateTyped2(e) < money) {
			return 0x20;
		}
		fcn_004c5150(-1, e->f4, g_773d75, money);
		fcn_004c6ae0(e->f4, -6);
		for (i = 0; i < 768; i++) {
			if (((House*)g_7f4ca0)[i].id != 0xffff && ((House*)g_7f4ca0)[i].b2 < 10 && ((House*)g_7f4ca0)[i].b2 != 6 && ((House*)g_7f4ca0)[i].b2 != 7 &&
				((House*)g_7f4ca0)[i].bc != e->bc) {
				if ((unsigned char) rank > gm_RandomMod(0x7e) + ((House*)g_7f4ca0)[i].b84) {
					fcn_004c4510(&((House*)g_7f4ca0)[i], ((House*)g_7f4ca0)[i].f4);
					fcn_004c4570(1, 1, 0xc, &who);
					fcn_004c5360();
				}
			}
		}
		return 0x10;
	} else {
		int ok;
		int dlg;
		int money;
		unsigned char rank;
		int cancel;
		unsigned int who;
		char text[0x100];
		int id;
		int n;
		int result;
		House* h;

		result = 0;
		money = (int) (gm_WalkEntityChain(e->id) * g_662964);
		dlg = fcn_00470820(0, 0, s_6acdcc);
		fcn_00473a90(0, 0);
		fcn_00471b60(dlg);
		fcn_004727a0(dlg, 1);
		id = fcn_00519190(0x1de1, 6, money);
		ok = fcn_00472250(dlg, 1, id);
		cancel = fcn_00472250(dlg, 1, id + 1);
		g_100f1dc = -1;
		do {
			if (g_100f1dc != -1) {
				if (g_67d370 == ok) {
					n = 0;
					rank = e->b84;
					who = e->bc;
					if (fcn_00525f60(e, 6) && fcn_00526010(e, money, g_773d75)) {
						fcn_004c5150(-1, e->f4, g_773d75, money);
						fcn_004c6ae0(e->f4, -6);
						for (i = 0; i < 768; i++) {
							h = &((House*)g_7f4ca0)[i];
							/* the redundant b2 test keeps the loop pointer on b2, as in the original */
							if (h->id != 0xffff && h->b2 < 10 && h->b2 <= 10 && h->bc != e->bc) {
								if (rank > gm_RandomMod(0x7e) + h->b84) {
									n++;
									fcn_004c4510(h, h->f4);
									fcn_004c4570(1, 1, 0xc, &who);
									fcn_004c5360();
								}
							}
						}
						fcn_0051af00(text, 0x1de2, n);
						fcn_00526120(text, 0);
						result = 1;
						g_774654 = 1;
					}
				} else if (g_67d370 == cancel) {
					g_774654 = 1;
				}
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005d8af0, 0x657c7) != 0);
		fcn_00471e30(dlg);
		return result;
	}
}
