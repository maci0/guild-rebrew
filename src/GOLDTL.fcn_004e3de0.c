extern unsigned char g_773d75;
extern int g_100f1dc;
extern char* g_77255c;
extern int g_772514;
extern int g_68bfb8;
extern int g_774654;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00508e40(int);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl fcn_005c9030(int, int, int, int*);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
char* __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, char*);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004e6e20(int, int, int);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_00471f80(int);
int __cdecl fcn_0050b750(char*, unsigned char);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x004e3de0 */

void __cdecl fcn_004e3de0(char* a, int* b)
{
	int i;
	int val;
	int cap;
	int max;
	int lo;
	int hi;
	int dlg;
	int w;
	int bar;
	int x;
	char* o;
	char* t;

	*(int*) (a + 0x98) = 0;
	for (i = 0; i < b[0x12]; i++) {
		if (b[9 + i] == *(int*) (a + 0x10))
			break;
	}
	if (i >= b[0x12])
		return;
	if (b[i] == -1)
		return;
	*(int*) (a + 0x94) = b[8];
	gm_StartFilteredEntitySearch(1, 1, b[0x11]);
	val = b[8];
	o = fcn_00508e40(*(int*) (a + 0x10));
	if (o == 0)
		return;
	cap = gm_AccumulateTyped2(o);
	fcn_005c9030(val, cap, 0x20, &max);
	lo = fcn_0050b710(val, g_773d75);
	hi = fcn_0050b710(max, g_773d75);
	if (cap < val)
		return;
	dlg = fcn_00470820(0, 0, "cutscenes\\pacht");
	fcn_00471d80(dlg, 3);
	g_100f1dc = -1;
	fcn_004727a0(dlg, 0);
	t = fcn_00519190(0x1aa6, g_773d75);
	fcn_00519190(0x1aa7);
	w = fcn_00472250(dlg, 0, t);
	d2_SetElementValue(w, lo, hi, lo);
	bar = fcn_004677e0((*(int*) (g_77255c + 0xc) - 0x12c) / 2 - 8, 8, 0x12c, 0, 100, 0x75, 0x42, g_772514);
	fcn_004e6e20(bar, 0x5dc, 1);
	g_100f1dc = -1;
	while (fcn_005373e0(fcn_004e3de0, g_68bfb8) != 0) {
		if (fcn_004e6e20(bar, 0, 0) == 0) {
			g_774654 = 1;
		} else {
			x = g_100f1dc;
			if (x != -1) {
				g_774654 = 1;
				if (x != 1 && x == 2) {
					*(int*) (a + 0x98) = 1;
					*(int*) (a + 0x94) = fcn_0050b750(fcn_00471f80(w), g_773d75);
				}
			}
		}
	}
	fcn_00471e30(dlg);
}
