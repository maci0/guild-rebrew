

extern char g_6a4144[];
extern int g_772514;
extern char* g_77255c;
extern char* g_14b5e38;
extern int g_14b5e3c;
extern int g_14b5e40;
extern int g_14b5e44;
extern int g_14b5e48;
extern int g_14b5e4c;
extern int g_7e1fa0[];
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern float g_6640cc;
extern float g_66292c;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00468cd0(int, int);
void __cdecl fcn_00468b80(int, char*);
void __cdecl fcn_00468bb0(int, int, int, int, int, int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void (__cdecl*)(int), int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_0053eb60(int n)
{
	int h;
	int ids[0x10];
	char buf[0x100];
	int w;
	int x;
	int i;
	int ok;

	h = fcn_00470820(0, 0, g_6a4144);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 1);
	fcn_00519190(0x42c5);
	d2_SetForm(h, 3);
	w = (int) (g_6640cc / n * g_66292c);
	x = (*(int*) (g_77255c + 0x10) - w * n) / 2 + 0xe;
	for (i = 0; i < n; i++) {
		sprintf(buf, "%s %c", g_14b5e38, i + 0x41);
		ids[i] = fcn_004677e0(0x80, x + i * w, 0xc8, 0, 0x64, 0x7b, 0x802, g_772514);
		d2_SetElementValue(ids[i], 0, 4, g_7e1fa0[i]);
		fcn_00468cd0(ids[i], 0x82);
		fcn_00468b80(ids[i], buf);
		fcn_00468bb0(ids[i], 5, g_14b5e3c, g_14b5e40, g_14b5e44, g_14b5e48, g_14b5e4c);
	}
	d2_SetForm(h, 2);
	ok = fcn_00472250(h, 2, fcn_00519190(0x7d));
	while (fcn_005373e0(fcn_0053eb60, 0xc6) != 0) {
		if (g_14ce8e0 != 0 || g_14cf950 == 1 || (g_100f1dc == 2 && g_67d370 == ok)) {
			g_774654 = 1;
		}
	}
	for (i = 0; i < n; i++) {
		g_7e1fa0[i] = fcn_00471f80(ids[i]);
	}
	fcn_00471e30(h);
}
