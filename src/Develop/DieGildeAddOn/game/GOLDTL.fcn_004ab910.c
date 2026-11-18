typedef struct Kind {
	unsigned char type;
	char pad1[0x24c];
} Kind;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;
extern char g_7f4ca0[];
extern unsigned char g_773d75;

int __cdecl gm_CheckStatLevel(int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00510470(unsigned char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004a5340(unsigned short* e, int n, int* lim, float a4, float r, unsigned short* ids);
int __cdecl fcn_0050b810(int a, char b);
#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x004ab910 */
int __cdecl ai_StartVerfluchen(int action, unsigned short* entity, int a3, char* out)
{
	int lim;
	unsigned short id;
	int lvl;
	int i;
	int n;
	int v;
	int best_v;
	int money;
	unsigned char* e;
	unsigned char* best;
	char* p;

	lvl = gm_CheckStatLevel(*entity, 0xe);
	best_v = 0;
	best = 0;
	lim = 0;
	if ((*((unsigned char*) entity + 0x1cc) & 0x10) != 0)
		return 0;
	if (action != 0x45 && action != 0)
		return 0;
	if (a3 != 0 || lvl == 0 || *((unsigned char*) entity + 2) == 3)
		return 0;
	e = lpGebaeudeINST;
	for (i = 0; i < 0x100; i++, e += 0xa9) {
		if (e[0] != 0 && *(unsigned short*) (e + 0x27) == *entity
		    && ((Kind*)lpGebaeudePROT)[e[0]].type == 0x1f
		    && fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x28a) != 0) {
			if (best == 0) {
				best = e;
				best_v = fcn_00510470(e);
			} else {
				v = fcn_00510470(e);
				if (v > best_v) {
					best = e;
					best_v = v;
				}
			}
		}
	}
	if (best == 0 || best_v == 0)
		return 0;
	lim = 0xf00500;
	if (fcn_004a5340(entity, 1, &lim, 0.0f, gm_RandomMod(0x20) + 25.0f, &id) == 0)
		return 0;
	p = g_7f4ca0 + id * 540;
	money = (int) (fcn_0050b810(*(int*) ((char*) entity + 0x178), (*(char*)&g_773d75)) * 0.25f);
	gm_WalkEntityChain(*entity);
	for (n = best_v - 1; n > 0; n--) {
		if (money > (n > 1 ? n : 1) * 32000)
			break;
	}
	if (n == 0)
		return 0;
	n = gm_RandomMod(n + 1);
	*(int*) (out + 4) = *(int*) (p + 4);
	*(int*) (out + 0x10) = (n > 1 ? n : 1) * 32;
	*(int*) (out + 0xc) = n;
	out[0] = 7;
	return 0x45;
}
