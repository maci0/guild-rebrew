


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;

int __cdecl fcn_004ee160(char*);
char* __cdecl fcn_004ec7d0(char*);
float __cdecl fcn_004ec8a0(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_0050b710(int, unsigned char);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_00471f80(int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl fcn_00526010(struct house*, int, unsigned char);
void __cdecl fcn_004eeb50(char*, float);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_00586800(char* e)
{
	int r;
	int ok;
	int c;
	int n;
	float f;
	int cancel;
	int tenth;
	char* p;
	int h;
	int line;
	int s;

	r = 0;
	n = fcn_004ee160(e);
	tenth = n / 10;
	p = fcn_004ec7d0(e);
	if (p == 0) {
		return 0;
	}
	f = fcn_004ec8a0(p, 3);
	h = fcn_00470820(0, 0, "Locations\\Domizil\\skill");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 1);
	line = fcn_00472250(h, 1, fcn_00519190(0x403a, 0x182, g_773d75));
	d2_SetElementValue(line, fcn_0050b710(tenth, g_773d75), fcn_0050b710(n, g_773d75), fcn_0050b710(tenth, g_773d75));
	d2_SetForm(h, 2);
	s = fcn_00519190(0x403b);
	ok = fcn_00472250(h, 2, s);
	cancel = fcn_00472250(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		p = fcn_004ec7d0(e);
		if (p == 0) {
			g_774654 = 1;
			fcn_005373e0(fcn_00586800, 0x20007);
			fcn_00471e30(h);
			return 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				c = fcn_0050b750(fcn_00471f80(line), g_773d75);
				if (fcn_00526010(&((struct house*)g_7f4ca0)[g_774970], c, g_773d75) != 0) {
					fcn_004eeb50(p, (float) c / n * f * 0.75f);
					r = 1;
					g_774654 = 1;
					fcn_004c5150(*(int*) (p + 4), ((struct house*)g_7f4ca0)[g_774970].handle, g_773d75, c);
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_00586800, 0x677c7) != 0);
	fcn_00471e30(h);
	return r;
}
