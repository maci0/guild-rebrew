

#include "client_types.h"
typedef Btn_776c60 Btn;
// SIZE 0x8

typedef Win_f8f120 Win;
// SIZE 0x3c4

extern int g_6abb00;
extern short g_fb9070;
extern short g_fb9072;
extern Win_f8f120 g_f8f120[];
extern int g_772514;
extern unsigned short g_774970;
extern Btn_776c60 g_776c60[6];
extern int g_100f1dc;
extern int g_67d370;
extern int g_14a92bc;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ac77c[];

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(short, short, char*);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_005c5da0(int, int, int, unsigned short, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005c5e70(void);

int __cdecl fcn_005c61e0(int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_005c6540(char*);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_005c61c0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005bad60(void)
{
	int dlg;
	int i;

	if (g_6abb00 != -1) {
		return;
	}
	if (fcn_0057ec20(0x1000) == 0) {
		return;
	}
	fcn_0057e880(0x14, 0, 0, 0);
	dlg = fcn_00470820(g_fb9072 - 0x158, g_fb9070 - 0x108, s_6ac77c);
	fcn_004727a0(dlg, 0);
	g_f8f120[g_772514].x398 = 0x18;
	g_f8f120[g_772514].x39c = 0x18;
	g_f8f120[g_772514].x3a0 = 0x18;
	g_f8f120[g_772514].x3a4 = 0x18;
	fcn_004727a0(dlg, 0);
	fcn_00473a90(0, 0);
	fcn_005c5da0(g_772514, 0, 0, g_774970, 0x1f3b);
	if (fcn_005373e0((void*) fcn_005bad60, 0x657c7) != 0) {
		do {
			fcn_005c5e70();
			if (g_100f1dc != -1 || CountDisplayCounters() != 0) {
				for (i = 0; i < 6; i++) {
					if (g_776c60[i].item != 0 && g_67d370 == g_776c60[i].btn) {
						if (fcn_005c61e0(*(unsigned short*) g_776c60[i].item) != 0) {
							fcn_00471af0(dlg, 0);
							fcn_005c6540(g_776c60[i].item);
							d2_SetElementValue(g_776c60[i].btn, 0, 0x3e7, 0);
							ResetDisplayCounters();
							fcn_00471af0(dlg, 1);
						}
						else {
							fcn_00526120(g_14a92bc, 0);
						}
					}
				}
			}
			if (g_14ce8e0 != 0) {
				if (CountDisplayCounters() != 0) {
					for (i = 0; i < 6; i++) {
						if (g_776c60[i].item != 0 && fcn_00471f80(g_776c60[i].btn) != 0) {
							d2_SetElementValue(g_776c60[i].btn, 0, 0x3e7, 0);
						}
					}
					ResetDisplayCounters();
				}
				else {
					g_774654 = 1;
				}
			}
		} while (fcn_005373e0((void*) fcn_005bad60, 0x657c7) != 0);
	}
	fcn_005c61c0();
	fcn_00471e30(dlg);
	fcn_0057e880(0x14, 0, 1, 0);
}
