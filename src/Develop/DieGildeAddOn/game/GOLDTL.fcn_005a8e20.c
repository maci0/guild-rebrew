

typedef struct
{
	int btn;
	char* rel;
	char* obj;
	int flags;
} Row;
// SIZE 0x10

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

typedef struct
{
	char pad0[0x274];
	int x274;
	char pad278[0x154];
} Win;
// SIZE 0x3cc

extern char g_7f4ca0[];
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6aade4[];
extern char s_6811b0[];
extern char s_6b5c60[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_0046e830(int, int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0046f2c0(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00526010(Player*, int, char);
void __cdecl fcn_00526920(char*, int, char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a8e20(void)
{
	int flag;
	Row rows[128];
	int dlg;
	int w;
	int n;
	char* e;
	char* r;
	int i;

	n = 0;
	flag = 1;
	dlg = fcn_00470820(0, 0, s_6aade4);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 2);
	w = g_772514;
	d2_SetForm(dlg, 0);
	fcn_0046e830(-1, -1, g_772514, w, 0x767);
	d2_SetOverlayAnimation(0, 0);
	((Win*)g_1015f40)[w].x274 = 0x5a;
	do {
		if (flag != 0) {
			d2_SetForm(dlg, 1);
			io_AppendText(0x17f6);
			d2_SetForm(dlg, 2);
			io_AppendText((int) s_6811b0);
			fcn_0046f2c0(g_772514, 1);
			n = 0;
			for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
				if (e[0x5a] & 2) {
					for (r = fcn_005463a0(1, 0, 0x1b); r != 0; r = he_fn_Handlung()) {
						if (*(int*) (r + 0xac) == *(int*) (e + 1)) {
							rows[n].rel = r;
							rows[n].btn = fcn_00472250(dlg, 2, io_AppendText(0x17f5, (unsigned char) e[0] + 0x427, *(unsigned short*) (e + 0x27), e, *(int*) (r + 0xb0)));
							rows[n].obj = e;
							rows[n].flags = *(unsigned short*) (e + 0x5a);
							n++;
							break;
						}
					}
				}
			}
			flag = 0;
		}
		for (i = 0; i < n; i++) {
			if (rows[i].flags != *(unsigned short*) (rows[i].obj + 0x5a)) {
				flag = 1;
				break;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
			fcn_00532ef0();
		}
		if (g_100f1dc != -1) {
			for (i = 0; i < n; i++) {
				if (g_67d370 == rows[i].btn && *(unsigned short*) (rows[i].obj + 0x27) != g_774970 &&
				    fcn_00526010(&((Player*)g_7f4ca0)[g_774970], *(int*) (rows[i].rel + 0xb0), (*(char*)&g_773d75)) != 0) {
					fcn_00526920(rows[i].obj, -1, s_6b5c60);
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005a8e20, 0x677c7) != 0);
	fcn_00471e30(dlg);
}
