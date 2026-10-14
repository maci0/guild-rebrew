#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>
#pragma intrinsic(strcpy, strcat)

// SIZE 0x21c
typedef struct {
	char pad0[0x1b1];
	unsigned char f1b1;
	char pad1b2[0x6a];
} House5a74;

extern char g_7f4ca0[];
extern unsigned char* g_868050;
extern unsigned short g_774970;
extern unsigned char g_7747b0;
extern char* g_14ad474;
extern unsigned short g_7f4c04;
extern int g_7e2700;


int __cdecl fcn_00506380(int id, unsigned char* store, int a, int b);
int __cdecl fcn_005a7400(unsigned char* p, int* lo, int* hi);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005263d0(char*, char*, int);

int __cdecl fcn_005a74a0(unsigned char* p)
{
	volatile int a;
	int b;
	char line[0x80];
	char title[0x80];
	char text[0x400];
	unsigned char* tbl;
	int kind;
	int r;
	int x;
	unsigned short own;

	tbl = g_868050 + p[0] * 0x24d;
	kind = gm_GetBuildingTypeCategory(p[0]);
	r = fcn_00506380(g_774970, p, 0, 0);
	if ((*(unsigned short*) (p + 0x5a) & 0x400) != 0) {
		return 0;
	}
	if (((*(signed char*)&g_7747b0) & 0x80) == 0) {
		x = ((House5a74*)g_7f4ca0)[g_774970].f1b1;
		if (!(x > 0 && (*tbl == 6 || *tbl == 4)) && (r & 0x200) == 0) {
			own = *(unsigned short*) (p + 0x27);
			if (own != g_774970) {
				if ((r & 1) == 0) {
					return 0;
				}
				if (fcn_005a7400(p, (int*) &a, &b) == 0) {
					strcpy(title, g_14ad474);
					x = a;
					if (((*(int*)&g_7f4c04) & 0xffff) < x) {
						if (kind == 3 || kind == 5) {
							fcn_0051af00(text, 0x2059, p);
						}
						else {
							fcn_0051af00(text, 0x2056, own, p);
						}
					}
					else {
						if (kind == 3 || kind == 5) {
							fcn_0051af00(text, 0x205a, p);
						}
						else {
							fcn_0051af00(text, 0x2057, own, p);
						}
					}
					fcn_0051af00(line, 0x2058, x, b);
					strcat(text, line);
					g_7e2700 = 0;
					fcn_005263d0(title, text, 4);
					return 0;
				}
			}
		}
	}
	return 1;
}
