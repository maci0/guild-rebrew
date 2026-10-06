// FUNCTION: GOLD 0x005d99e0
// FUNCTION: GOLDTL 0x005e6650

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37;
	int ids[4];
	char pad48[0xb0];
};

// SIZE 0x21c
typedef struct {
	int f0;
	int f4;
	char pad8[0x180];
	char b188;
	char pad189[0x93];
} House;

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char s_6ad434[];
extern char s_6811b0[];
extern int g_772514;
extern int g_14b5ac0;
extern int g_14b5ac4;
extern int g_14b5ac8;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;

void __cdecl fcn_0052a0c0(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_004c5530(struct msg*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005e6650(char* e)
{
	int ids[2];
	int list[4];
	struct msg m;
	int dlg;
	int n;
	int i;

	fcn_0052a0c0(e, 0);
	dlg = fcn_00470820(0, 0, s_6ad434);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(dlg, 1);
	fcn_00519190((int) s_6811b0);
	fcn_00519190(0x41e7, 0x41e6, 0xed6);
	fcn_004727a0(dlg, 3);
	fcn_00533a60(g_772514, 0, ids, 2, g_14b5ac0, g_14b5ac4);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ids[0]) {
				n = 0;
				for (i = 0; i < 768; i++) {
					if (n >= 4) {
						break;
					}
					if (((House*)g_7f4ca0)[i].b188 != 0) {
						list[n] = i;
						n++;
					}
				}
				if (n != 0) {
					memset(&m, 0, sizeof(m));
					m.b4 = (char) 0xa1;
					m.b36 = 1;
					m.f8 = ((House*)g_7f4ca0)[g_774970].f4;
					m.fc = *(int*) (e + 1);
					m.pos = g_7f4c00;
					for (i = 0; i < n; i++) {
						m.ids[i] = ((House*)g_7f4ca0)[list[i]].f4;
					}
					fcn_004c5530(&m);
					g_774654 = 1;
				} else {
					fcn_00526120(g_14b5ac8, 0);
				}
			} else if (g_67d370 == ids[1]) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005e6650, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_0052a2d0();
	fcn_005305a0();
	fcn_00532ef0();
}
