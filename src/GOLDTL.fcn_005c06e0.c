/* SIZE 0x21c */
typedef struct {
	char f0[4];
	int f4;
	char pad[0x214];
} Slot5c06;

extern Slot5c06 g_7f4ca0[];
extern unsigned short g_774970;
extern float g_6628a0;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern char g_6ac494[];

float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00525f60(void*, int);
int __cdecl fcn_00579640(void*, void*);
int __cdecl cm_ChkCutsceneReady(int, unsigned short);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, void*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005c9220(int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
float __cdecl fcn_00507e70(void*, unsigned short*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005c06e0 */
int __cdecl fcn_005c06e0(unsigned short* a0)
{
	int result;
	int h1;
	int h2;
	int dlg;
	int r;
	int t;
	int ids[6];
	char text[0x400];
	char ev[0xf8];
	float f;

	result = 0;
	if (!a0)
		return 0;
	if (*a0 == 0xffff)
		return 0;
	if (*a0 == g_774970)
		return 0;
	if (!fcn_00525f60(&g_7f4ca0[g_774970], 2))
		return 0;
	if (!fcn_00579640(a0, &g_7f4ca0[g_774970])) {
		fcn_0051af00(text, 0x409f, *a0);
		fcn_00526120(text, 0);
		return 0;
	}
	r = cm_ChkCutsceneReady(*(int*) (a0 + 2), g_774970);
	if (r <= 0) {
		fcn_0051af00(text, 0x1756, *a0);
		fcn_00526120(text, 0);
		return 0;
	}
	if (!fcn_00525f60(&g_7f4ca0[g_774970], 2))
		return 0;
	dlg = fcn_00470820(0, 0, g_6ac494);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	t = fcn_00519190(0x1759, r, (r != 1) + 0x1752, *a0, *a0);
	h1 = fcn_00472250(dlg, 1, t);
	h2 = fcn_00472250(dlg, 1, t + 1);
	ids[0] = dlg;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 4;
	ids[5] = 0x13;
	fcn_005c9220(ids);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == h1) {
				fcn_004c6ae0(g_7f4ca0[g_774970].f4, -2);
				f = fcn_00507e70(&g_7f4ca0[g_774970], a0, 4);
				if (gm_RandomFloat01() + f < g_6628a0) {
					fcn_0051af00(text, 0x175c, *a0, *a0);
				} else {
					ev[4] = 0x2e;
					*(int*) (ev + 8) = *(int*) (a0 + 2);
					*(int*) (ev + 0xc) = -1;
					ev[0x36] = 2;
					*(int*) (ev + 0x5c) = g_7f4ca0[g_774970].f4;
					*(int*) (ev + 0x58) = *(int*) (a0 + 2);
					fcn_004c5530(ev);
					fcn_0051af00(text, 0x175b, *a0);
				}
				fcn_00526120(text, 0);
				g_774654 = 1;
				result = 1;
			} else if (g_67d370 == h2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005c06e0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
