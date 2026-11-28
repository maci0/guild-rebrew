#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern int g_6a25b8;
extern int g_6a25bc;
extern int d2_CurrentValueBar;
extern int g_6a25c4[4];
extern int g_6a25d4;
extern int g_6a25d8;
extern int g_6a25e8;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int main_LoopFlags;
extern int g_7746f0;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char* d2_SelectedBuilding;
extern int* d2_SelectedItem;
extern int d2_SelectedPerson;
extern char* lpObjektePROT;
extern char gm_TownTable[];
extern Win_1015f40 d2_Windows[0x60];

extern float flt_0_0;

extern double dbl_0_01;
extern double g_662c38;

extern char str_dollar_C[];
extern char g_6a2f24[];
extern char g_6a2f30[];
extern char g_6a2fec[];
extern char g_6a2fe4[];
extern char g_67d444[];

int __cdecl gm_GetEntityMood(char* a);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_AppendText(char* fmt, ...);
void __cdecl io_FormatEntityNameMarkup(int id, int a, int b, char* out);
char* __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
int __cdecl gm_GetElapsedMinutes(void* a, void* b);
void __cdecl gm_AddTime(void* p, int a, int b, int c);
int __cdecl d2_AddElementToWindow(int x, int y, int kind, int owner);
int __cdecl d2_AddWindowImage(int x, int y, int z, int owner, int flag);
void __cdecl d2_DestroyElement(int element);
int __cdecl d2_GetEntityGearIcons(char* s, int* out);
float __cdecl gm_GetEntityHealthRatio(char* e);
int __cdecl d2_ClearWindowChildren(int win, int keep);
void __cdecl d2_RunTradeRouteEditor(char* e);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
char* __cdecl fcn_00502cd0(int a, int b, int c, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetMsgField(int a, int b);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
#include "Develop/DieGildeAddOn/game/client_data.h"
/* ADDRESS: GOLDTL 0x0052ea30 */
void __cdecl d2_UpdateSelectionPanel(void)
{
	char name[256];
	char buf[0x40];
	int kinds[8];
	pos14_7f4c00 pos;
	int pct;
	int i;
	int k;
	int x;
	int y;
	unsigned short flags;
	char* e;
	char* s;
	char* p;
	unsigned char c;
	float ratio;
	int n;

	ratio = 0.0f;
	if (g_6a25b8 == -1) {
		return;
	}
	if (d2_SelectedBuilding == 0 || d2_CurrentValueBar == -1 || g_6a25bc == -1) {
		goto no_header;
	}
	pct = gm_GetEntityMood(d2_SelectedBuilding);
	d2_SetForm(g_6a25b8, 1);
	io_AppendText(str_dollar_C);
	if (*d2_SelectedBuilding != 0x47) {
		io_FormatEntityNameMarkup(*(unsigned short*) (d2_SelectedBuilding + 0x27), 2, 1, name);
		if (d2_SelectedBuilding[5] != 0) {
			io_AppendText(g_6a2f30, name, *d2_SelectedBuilding * 0xe + 0x48e, d2_SelectedBuilding + 5);
			goto header_done;
		}
		io_AppendText(g_6a2f24, name, *d2_SelectedBuilding * 0xe + 0x48e);
	} else {
		io_AppendText(g_6a2f24, (char*) 0x870, gm_TownTable + *(int*) (d2_SelectedBuilding + 0x65) * 0x2f4);
	}
header_done:
	d2_SetElementValue(d2_CurrentValueBar, 0, 100, pct);
	flags = *(unsigned short*) (d2_SelectedBuilding + 0x5a);
	if (flags & 4) {
		e = he_StartHandlungSearch(2, 0, 0x1c, 3, *(int*) (d2_SelectedBuilding + 1));
		if (e == 0) {
			return;
		}
		ratio = (float) gm_GetElapsedMinutes(e + 0x44, e + 0xb8);
		ratio = (float) gm_GetElapsedMinutes(e + 0x44, (char*) &gm_GameTime) / ratio;
		((D2_CONTROL_TL*) (d2_Controls))[g_6a25bc].value_1f4.real = ratio;
		if (g_6a25c4[0] == -1) {
			d2_SetForm(g_6a25b8, 0);
			g_6a25c4[0] = d2_AddElementToWindow(((((D2_WIN*) d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, d2_CurrentWindowId);
		}
		return;
	}
	if (flags & 1) {
		e = he_StartHandlungSearch(2, 0, 0xd, 3, *(int*) (d2_SelectedBuilding + 1));
		ratio = 0.05f;
		if (e != 0) {
			if (*(int*) (e + 0x70) >= 4) {
				ratio = (float) *(int*) (e + 0xc8) / (float) *(int*) (e + 0xc4);
			}
			if (ratio < 0.01) {
				ratio = (float) dbl_0_01;
			}
			if (g_6a25c4[0] == -1) {
				d2_SetForm(g_6a25b8, 0);
				g_6a25c4[0] = d2_AddElementToWindow(((((D2_WIN*) d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, d2_CurrentWindowId);
			}
		}
		((D2_CONTROL_TL*) (d2_Controls))[g_6a25bc].value_1f4.real = ratio;
		return;
	}
	if (flags & 0x40) {
		e = he_StartHandlungSearch(2, 0, 0x1e, 3, *(int*) (d2_SelectedBuilding + 1));
		if (e == 0) {
			return;
		}
		ratio = (float) gm_GetElapsedMinutes(e + 0x44, e + 0x52);
		ratio = (float) gm_GetElapsedMinutes(e + 0x44, (char*) &gm_GameTime) / ratio;
		((D2_CONTROL_TL*) (d2_Controls))[g_6a25bc].value_1f4.real = ratio;
		if (g_6a25c4[0] == -1) {
			d2_SetForm(g_6a25b8, 0);
			g_6a25c4[0] = d2_AddElementToWindow(((((D2_WIN*) d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, d2_CurrentWindowId);
		}
		return;
	}
	if ((signed char) flags >= 0) {
		if (g_6a25c4[0] != -1) {
			d2_DestroyElement(g_6a25c4[0]);
			g_6a25c4[0] = -1;
		}
		return;
	}
	e = he_StartHandlungSearch(2, 0, 0x1f, 3, *(int*) (d2_SelectedBuilding + 1));
	if (e == 0) {
		return;
	}
	ratio = (float) gm_GetElapsedMinutes(e + 0x44, e + 0x52);
	ratio = (float) gm_GetElapsedMinutes(e + 0x44, (char*) &gm_GameTime) / ratio;
	((D2_CONTROL_TL*) (d2_Controls))[g_6a25bc].value_1f4.real = ratio;
	if (g_6a25c4[0] == -1) {
		d2_SetForm(g_6a25b8, 0);
		g_6a25c4[0] = d2_AddElementToWindow(((((D2_WIN*) d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, d2_CurrentWindowId);
	}
	return;

no_header:
	if (d2_SelectedPerson == 0) {
		goto no_target;
	}
	s = (char*) d2_SelectedPerson;
	if (g_7746f0 < 2) {
		d2_SetForm(g_6a25b8, 1);
		pct = (int) (gm_GetEntityHealthRatio(s) * g_662c38);
		io_FormatEntityNameMarkup(*(unsigned short*) s, 1, 4, name);
		io_AppendText(g_6a2fec, name, pct);
	}
	if (*(int*) (s + 0x16c) == 0) {
		goto drop_elements;
	}
	if (*(unsigned short*) (*(int*) (s + 0x16c) + 0x27) != gm_LocalPlayerSlot) {
		goto drop_elements;
	}
	if (g_7746f0 >= 2) {
		goto drop_elements;
	}
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			d2_DestroyElement(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	d2_SetForm(g_6a25b8, 0);
	x = (((D2_WIN*) d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1;
	n = d2_GetEntityGearIcons(s, kinds);
	if (n > 0) {
		y = 0x38;
		for (i = 0; i < n; i++) {
			if (kinds[i] >= 0xdf && kinds[i] < 0x3bb) {
				g_6a25c4[i] = d2_AddWindowImage(x + 0x32, y, kinds[i], d2_CurrentWindowId, -2);
			} else {
				g_6a25c4[i] = d2_AddElementToWindow(x + 0x32, y, kinds[i], d2_CurrentWindowId);
			}
			y += 0x1a;
		}
	}
	p = *(char**) (s + 0x17c);
	if (p == 0) {
		if (g_6a25d8 != -1) {
			((D2_CONTROL_TL*) (d2_Controls))[g_6a25d8].value_1f4.bits = 0;
		}
		return;
	}
	if (g_6a25d8 == -1) {
		return;
	}
	c = (unsigned char) *p;
	switch (c) {
	case 0x8f:
		n = gm_GetElapsedMinutes(p + 0x44, p + 0xb8);
		if (n != 0) {
			ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
		}
		break;
	case 0x16:
		n = gm_GetElapsedMinutes(p + 0x44, p + 0xb8);
		if (n != 0) {
			ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
		}
		break;
	case 0x40:
		if (*(int*) (p + 0x70) < 2) {
			ratio = 0.01f;
		} else if (*(int*) (p + 0x70) == 2) {
			n = gm_GetElapsedMinutes(p + 0x44, p + 0x52);
			if (n != 0) {
				ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
			}
		}
		break;
	case 0x61:
		pos = *(pos14_7f4c00*) (p + 0xc4);
		gm_AddTime(&pos, 8, 0, 0);
		n = gm_GetElapsedMinutes(p + 0xc4, &pos);
		if (n != 0) {
			ratio = (float) gm_GetElapsedMinutes(p + 0xc4, (char*) &gm_GameTime) / (float) n;
		}
		break;
	case 0x43:
		pos = *(pos14_7f4c00*) (p + 0x44);
		gm_AddTime(&pos, 0x18, 0, 0);
		n = gm_GetElapsedMinutes(p + 0x44, &pos);
		if (n != 0) {
			ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
		}
		break;
	case 0x62:
		if (*(int*) (p + 0x70) < 4) {
			ratio = 0.01f;
		} else if (*(int*) (p + 0x70) == 4) {
			pos = *(pos14_7f4c00*) (p + 0x44);
			gm_AddTime(&pos, 0x60, 0, 0);
			n = gm_GetElapsedMinutes(p + 0x44, &pos);
			if (n != 0) {
				ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
			}
		}
		break;
	case 0x65:
		if (*(int*) (p + 0x70) < 2) {
			ratio = 0.01f;
		} else {
			pos = *(pos14_7f4c00*) (p + 0x44);
			gm_AddTime(&pos, 0x18, 0, 0);
			n = gm_GetElapsedMinutes(p + 0x44, &pos);
			if (n != 0) {
				ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
			}
		}
		break;
	case 0x48:
		if (*(int*) (p + 0x70) < 1) {
			ratio = 0.01f;
		} else if (*(int*) (p + 0x70) == 1) {
			n = gm_GetElapsedMinutes(p + 0x44, p + 0xcc);
			if (n != 0) {
				ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
			}
		}
		break;
	case 0x6c:
		n = gm_GetElapsedMinutes(p + 0x44, p + 0xb4);
		if (n != 0) {
			ratio = (float) gm_GetElapsedMinutes(p + 0x44, (char*) &gm_GameTime) / (float) n;
		}
		break;
	}
	((D2_CONTROL_TL*) (d2_Controls))[g_6a25d8].value_1f4.real = ratio;
	return;

drop_elements:
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			d2_DestroyElement(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	return;

no_target:
	if (g_6a25d4 == -1 || d2_SelectedItem == 0) {
		goto drop_elements;
	}
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			d2_DestroyElement(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	if (d2_SelectedItem == 0 || (*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) d2_SelectedItem].kind) != 0x1d) {
		return;
	}
	if (g_6a25e8 != -1 && d2_DialogButtonAction != -1
	    && d2_CurrentElementId == g_6a25e8 && (main_LoopFlags & 0x2000)) {
		d2_RunTradeRouteEditor((char*) d2_SelectedItem);
	}
	if (d2_CurrentValueBar != -1) {
		d2_SetElementValue(d2_CurrentValueBar, 0, 100, *((unsigned char*) d2_SelectedItem + 0x12));
	}
	d2_SetForm(g_6a25b8, 2);
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			d2_DestroyElement(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	d2_ClearWindowChildren(d2_CurrentWindowId, 1);
	e = *(char**) ((char*) d2_SelectedItem + 0x24);
	if (e != 0) {
		s = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb4));
		if (s != 0) {
			io_AppendText(g_6a2fe4, (unsigned char) *s * 0xe + 0x48e);
		}
	}
	e = fcn_00502cd0(*(int*) ((char*) d2_SelectedItem + 0x14), 1, 0, 0x1dd);
	if (e == 0) {
		return;
	}
	s = fcn_00502cd0(*(int*) (e + 0x14), 1, 5);
	if (s == 0) {
		return;
	}
	k = 0;
	for (i = 3; i < 0x83; i += 0x20) {
		g_6a25c4[k] = d2_AddWindowImage(i, 0x28, *(unsigned short*) s + 0xdf, d2_CurrentWindowId, -2);
		fcn_0064d41a(buf, "%i", gm_GetMsgField((int) e, (int) s));
		n = d2_ShowTxt(i - 2, 0x1c, buf, d2_CurrentWindowId);
		((D2_CONTROL_TL*) (d2_Controls))[n].value_05c = 1;
		((D2_CONTROL_TL*) (d2_Controls))[n].value_06c = 1;
		((D2_CONTROL_TL*) (d2_Controls))[n].width = 0x20;
		s = gm_NextEntityQueryMatch();
		k++;
		if (s == 0) {
			return;
		}
	}
	return;
}
unsigned char _dpad_7e2760[828];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7e2aa0[2848];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7e2aa4[28];
unsigned char _dpad_7e2b80[1344];
unsigned char _dpad_7e3140[1152];
#endif
