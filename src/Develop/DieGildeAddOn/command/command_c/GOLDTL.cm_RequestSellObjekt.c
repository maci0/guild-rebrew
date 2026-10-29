#include "Develop/DieGildeAddOn/game/spiel.h"



// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad1[0x24c];
};
#pragma pack()

extern char g_7f4ca0[];
extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);

unsigned short __cdecl gm_RandomMod(int);
char* __cdecl fcn_00502cd0();
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
float __cdecl fcn_0050bb50(int, unsigned char);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl cm_RequestSellObjekt(char* e)
{
	int v;
	int amt;
	unsigned char* list[16];
	char msg[0x418];
	char dbg[0x400];
	unsigned char* c;
	unsigned char* sel;
	char* r;
	char* q;
	int n;
	struct good* p;

	n = 0;
	amt = 0;
	if (*(int*) (e + 0x70) != -2) {
		if (*(int*) (e + 0x70) != 0) {
			return;
		}
		c = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (e + 8));
		if (c != 0) {
			for (; c != 0; c = gm_FindNextFilteredEntity()) {
				if (n >= 16) {
					break;
				}
				p = &((struct good*)lpGebaeudePROT)[*c];
				if (gm_GetBuildingTypeCategory(*c) == 1 || p->kind == 9) {
					list[n++] = c;
				}
			}
			if (n != 0) {
				sel = list[gm_RandomMod(n)];
				if (sel != 0) {
					r = fcn_00502cd0(*(int*) (sel + 0x5d), 2, 6, 0, 0x2a);
					if (r == 0) {
						r = fcn_00502cd0(*(int*) (sel + 0x5d), 2, 6, r, 0x116);
					}
					if (r != 0) {
						for (q = fcn_00502cd0(*(int*) (r + 0x14), 1, 5); q != 0; q = gm_NextEntityQueryMatch()) {
							v = gm_GetMsgField(r, q);
							v = (int) (v * 0.25f);
							if (v < 1) {
								v = 1;
							}
							fcn_0064d41a(dbg, "cm_RequestSellObjekt(%i, %i, %i, %i, %i, %i)", -1, *(int*) (r + 2),
							    *(unsigned short*) q, v, g_773d75, 0);
							fcn_004c51f0(-1, *(int*) (r + 2), *(unsigned short*) q, v, g_773d75, 0);
							amt = (int) (fcn_0050bb50(*(unsigned short*) q, g_773d75) * v + amt);
						}
					}
				}
				if (((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)].type == 6 && amt != 0) {
					fcn_0051af00(msg, 0x10b7, sel, amt);
					he_MessageBoxQuickjump(((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)].handle, ((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)].handle,
					    msg, 0, 0x5ec, *(int*) (sel + 1), -1, 0, 0);
				}
			}
		}
	}
	fcn_00546190(e);
}
