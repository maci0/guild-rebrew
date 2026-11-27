

typedef struct {
	int btn;
	int bar;
	int value_text;
	int name_text;
	int value;
	unsigned char* e;
} Row5c89;
// SIZE 0x18

typedef struct {
	char pad[0x18];
	int w;
	char pad2[0x2d8];
} Font5c89;
// SIZE 0x2f4

extern Row5c89 g_777d00[128];
extern int g_776c90;
extern int g_777ca0;
extern int g_778b00;
extern char g_1016198[];
extern char* g_1015ea0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int d2_CurrentWindowId;
extern char g_6ac878[];
extern char g_6ac870[];
extern char g_68be7c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindBuildingOwner(unsigned char*);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_00467480(int x, int y, int a3, int a4, int a5, int win);
int __cdecl gm_AmountToUnits(int, unsigned char);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyForm(int);

int __cdecl fcn_005c89a0(void)
{
	int n;
	char* m;
	char buf[0x100];
	int h;
	int k;
	unsigned char* e;

	n = 0;
	h = fcn_00470820(0, 0, g_6ac878);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1934);
	for (k = 0; k < 128; k++) {
		g_777d00[k].btn = -1;
		g_777d00[k].bar = -1;
		g_777d00[k].value_text = -1;
		g_777d00[k].name_text = -1;
		g_777d00[k].value = 0;
	}
	d2_SetForm(h, 0);
	fcn_00533f40(0x206, 0x167, d2_CurrentWindowId, fcn_00472830(h, 2), 0x3e, &g_776c90, &g_777ca0, &g_778b00);
	*(int*) (g_1016198 + d2_CurrentWindowId * 0x3cc + 0x160) = -1;
	*(int*) (g_1016198 + d2_CurrentWindowId * 0x3cc + 0x164) = -1;
	d2_SetForm(h, 3);
	io_AppendText(0x1935);
	d2_SetForm(h, 4);
	io_AppendText(0x1936);
	d2_SetForm(h, 2);
	e = gm_StartFilteredEntitySearch(1, 4, g_774970);
	if (e != 0) {
		do {
			m = gm_FindBuildingOwner(e);
			if (m != 0 && *(unsigned short*) m != g_774970) {
				d2_SetForm(h, 2);
				g_777d00[n].btn = d2_AddElementToWindow(0, n * 0x3e, *e + 0x427, d2_CurrentWindowId);
				io_FormatTextBuffer(buf, g_6ac870, *e * 14 + 0x48e, e + 5);
				g_777d00[n].name_text = d2_ShowTxt(0x40, n * 0x3e + 8, buf, d2_CurrentWindowId);
				(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[g_777d00[n].name_text].width) = 0xa0;
				d2_SetElementFont(g_777d00[n].name_text, 0x54);
				io_FormatTextBuffer(buf, g_68be7c, *(int*) (m + 0x1b8));
				g_777d00[n].value_text = d2_ShowTxt(0x180, n * 0x3e + 0x14, buf, d2_CurrentWindowId);
				g_777d00[n].bar = fcn_00467480(0xea, n * 0x3e + 0x14, 0x40, 0x40, 0x82, d2_CurrentWindowId);
				d2_SetElementValue(g_777d00[n].bar, 0x3e8, 0x2328, gm_AmountToUnits(*(int*) (e + 0x39), g_773d75));
				g_777d00[n].value = d2_GetControlValue(g_777d00[n].bar);
				g_777d00[n].e = e;
				n++;
			}
			e = gm_FindNextFilteredEntity();
		} while (e != 0);
	}
	if (n == 0) {
		d2_DestroyForm(h);
		return -1;
	}
	return h;
}
