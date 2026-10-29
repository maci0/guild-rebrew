


typedef struct {
	unsigned short id;
	char pad2[7];
	unsigned char b9;
	char pada[0x15f];
	unsigned char b169;
	char pad16a[0xb2];
} Ent5aa1;
// SIZE 0x21c

typedef struct {
	int kind;
	int who;
	int cost;
	int pad[2];
} Req5aa1;
// SIZE 0x14

#define MAX5AA1(a, b) ((a) > (b) ? (a) : (b))

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern float g_662910;
extern float g_664388;
extern char g_6aaf58[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_00526010(Ent5aa1*, int, unsigned char);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004eb780(Ent5aa1*, Req5aa1*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005aa120(int unused, char* p)
{
	int w2;
	Req5aa1 req;
	int cost;
	int h;
	int name;
	int t;
	int w1;

	cost = (int) MAX5AA1(gm_WalkEntityChain(((Ent5aa1*)g_7f4ca0)[g_774970].id) * g_662910, g_664388);
	if (fcn_00526010(&((Ent5aa1*)g_7f4ca0)[g_774970], cost, g_773d75) == 0) {
		return 0;
	}
	h = fcn_00470820(0, 0, g_6aaf58);
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 1);
	fcn_00519190(0x165f);
	d2_SetForm(h, 2);
	if (((Ent5aa1*)g_7f4ca0)[g_774970].b9 == 0) {
		name = ((Ent5aa1*)g_7f4ca0)[g_774970].b169 + 0x253;
	} else {
		name = ((Ent5aa1*)g_7f4ca0)[g_774970].b169 + 0x27b;
	}
	t = fcn_00519190(0x1660, name, 5, cost, *(unsigned short*) (p + 0x27), p);
	w1 = fcn_00472250(h, 2, t);
	w2 = fcn_00472250(h, 2, t + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == w1 && fcn_00526010(&((Ent5aa1*)g_7f4ca0)[g_774970], cost, g_773d75) != 0) {
				req.kind = 2;
				req.who = *(int*) (p + 1);
				req.cost = cost;
				fcn_004eb780(&((Ent5aa1*)g_7f4ca0)[g_774970], &req);
				g_774654 = 2;
			} else if (g_67d370 == w2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_005aa120, 0x677c7) != 0);
	fcn_00471e30(h);
	return 1;
}
