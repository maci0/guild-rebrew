


extern char s_6ad2f8[];
extern char s_6ad2e8[];
extern int g_7e46ac;
extern int g_772514;
extern unsigned char g_7766a0[4];
extern unsigned char g_7766a4[4];
extern int g_14ac564;
extern int g_14ac568;
extern int g_14ac56c;
extern int g_14ac570;
extern int g_14ac574;
extern int g_14ac53c;
extern int g_14ac540;
extern int g_14ac544;
extern int g_14ac548;
extern int g_14ac54c;
extern int g_14ac5a8;
extern int g_14ac5ac;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_14ce8d0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern char* g_7747b8;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00537320(int);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00468cd0(int, int);
void __cdecl fcn_00468b80(int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_004238d0(int);
void __cdecl fcn_0041fc80(int);
int __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
void __cdecl fcn_005e12d0(void);
void __cdecl fcn_005e2590(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005e3150(void)
{
	int s2;
	int s0;
	int s3;
	float master;
	int playing;
	int changed;
	int ok;
	int cancel;
	float sfx;
	float music;
	int btn[2];
	int dlg;
	int wait;
	int s1;
	int s4;

	changed = 0;
	playing = 0;
	wait = g_7e46ac & ~0x2000;
	dlg = fcn_00470820(0, 0, s_6ad2f8);
	fcn_00537320(wait);
	fcn_00471db0(dlg, 1);
	fcn_00471d80(dlg, 2);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 2);
	fcn_00519190(0x1c5b);
	fcn_004727a0(dlg, 1);
	s0 = fcn_00472250(dlg, 1, 0);
	s1 = fcn_00472250(dlg, 1, 1);
	s2 = fcn_00472250(dlg, 1, 2);
	s3 = fcn_00472250(dlg, 1, 3);
	s4 = fcn_00472250(dlg, 1, 4);
	d2_SetElementValue(s0, 0, 0x7f, g_7766a0[0]);
	fcn_00468cd0(s0, 0x882);
	fcn_00468b80(s0, g_14ac564);
	d2_SetElementValue(s1, 0, 0x7f, g_7766a0[1]);
	fcn_00468cd0(s1, 0x882);
	fcn_00468b80(s1, g_14ac568);
	d2_SetElementValue(s2, 0, 0x7f, g_7766a0[2]);
	fcn_00468cd0(s2, 0x882);
	fcn_00468b80(s2, g_14ac56c);
	d2_SetElementValue(s3, 0, 0x7f, g_7766a0[3]);
	fcn_00468cd0(s3, 0x882);
	fcn_00468b80(s3, g_14ac570);
	d2_SetElementValue(s4, 0, 4, g_7766a4[0]);
	fcn_00468cd0(s4, 0x82);
	fcn_00468b80(s4, g_14ac574);
	fcn_00468bb0(s4, 5, g_14ac53c, g_14ac540, g_14ac544, g_14ac548, g_14ac54c);
	fcn_004727a0(dlg, 3);
	fcn_00533a60(g_772514, 0, btn, 2, g_14ac5a8, g_14ac5ac);
	ok = btn[0];
	cancel = btn[1];
	while (fcn_005373e0((void*) fcn_005e3150, wait) != 0) {
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				changed = 1;
				g_774654 = 1;
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8d0 != 0 && (g_67d370 == s0 || g_67d370 == s1 || g_67d370 == s2 || g_67d370 == s3)) {
			master = fcn_00471f80(s0) * 0.01f;
			music = (float)(fcn_00471f80(s1));
			sfx = (float)(fcn_00471f80(s2));
			fcn_004238d0((int) (music * master));
			fcn_0041fc80((int) (sfx * master));
			if (g_67d370 == s1 && playing == 0) {
				playing = fcn_004234e0(g_7747b8, s_6ad2e8, 1, 0x3f, 0x7f, 0, 0);
			}
		}
	}
	if (changed) {
		g_7766a0[0] = (unsigned char) fcn_00471f80(s0);
		g_7766a0[1] = (unsigned char) fcn_00471f80(s1);
		g_7766a0[2] = (unsigned char) fcn_00471f80(s2);
		g_7766a0[3] = (unsigned char) fcn_00471f80(s3);
		g_7766a4[0] = (unsigned char) fcn_00471f80(s4);
		fcn_005e12d0();
		fcn_005e2590();
	}
	fcn_00471e30(dlg);
}
