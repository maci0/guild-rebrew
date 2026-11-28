extern char* lb_LobbyPlayerList;
extern int g_779ce0;
extern int g_779c6c;
extern int d2_NetLobbyForm;
extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int txt_MaleTitleFirst;
extern int txt_FemaleTitleFirst;
extern int g_14a595c[];
extern int g_14a57e0[];
extern int g_14a6538[];
extern int g_14b5d40;
extern int g_14b5d44;
extern unsigned char g_779c70;
extern unsigned char g_779c6b;
extern unsigned char g_779c71;
extern char g_779c72[];
extern char g_779c82[];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d3_GetSceneEntry(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_EqualizeWindowButtonWidths(int, int, char*, int);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x00593360 */
void __cdecl d2_DrawNetLobbyPlayerInfo(void)
{
	char buf[0x100];
	char* rec;
	int v;
	int i;
	int x;
	int y;
	int z;

	rec = (char*) d3_GetSceneEntry(*(int*) (lb_LobbyPlayerList + g_779ce0 * 4 + 4));
	if (rec != 0)
		g_779c6c = *(int*) (rec + 0xc);
	d2_SetForm(d2_NetLobbyForm, 3);
	io_AppendText((int) str_dollar_C);
	i = *(int*)&((D2_CONTROL_TL*)d2_Controls)[d2_AddElementToWindow(5, 10, g_779c6c + 0x59a, d2_CurrentWindowId)].width + 0xf;
	if (!g_779c70) {
		v = txt_MaleTitleFirst;
	} else {
		v = txt_FemaleTitleFirst;
	}
	fcn_0064d41a(buf, "%s %s %s", v, g_779c72, g_779c82);
	x = 10;
	y = *(int*)&((D2_CONTROL_TL*)d2_Controls)[d2_EqualizeWindowButtonWidths(i, x, buf, d2_CurrentWindowId)].height + 2;
	x = x + y;
	if (g_779c70 == 1)
		v = g_14a595c[g_779c6b];
	else
		v = g_14a57e0[g_779c6b];
	fcn_0064d41a(buf, "%s: %s", g_14b5d40, v);
	d2_EqualizeWindowButtonWidths(i, x, buf, d2_CurrentWindowId);
	v = g_14a6538[g_779c71];
	fcn_0064d41a(buf, "%s: %s", g_14b5d44, v);
	y = x + y;
	d2_EqualizeWindowButtonWidths(i, y, buf, d2_CurrentWindowId);
}
