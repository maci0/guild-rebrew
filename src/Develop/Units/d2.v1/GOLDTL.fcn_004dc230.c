extern char g_68c340[];
extern char* g_77255c;
extern int d2_CurrentWindowId;
extern int cut_EventLoopFlags;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl d2_UpdateProgressBar(int, int, int);
int __cdecl ai_CompareOfficeCandidates(unsigned short*, unsigned short*, unsigned short*, int*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);


/* ADDRESS: GOLDTL 0x004dc230 */
int __cdecl fcn_004dc230(unsigned short* a1, unsigned short* a2, unsigned short* a3, int* out)
{
	int aux;
	int h;
	int t;
	int b0;
	int b2;
	int w;
	int res;

	*out = 0;
	h = fcn_00470820(0, 0, g_68c340);
	fcn_00471d80(h, 1);
	d2_SetForm(h, 0);
	t = io_AppendText(0x12c6, *a2, *a1);
	b0 = d2_GetWindowListItem(h, 0, t);
	d2_GetWindowListItem(h, 0, t + 1);
	b2 = d2_GetWindowListItem(h, 0, t + 2);
	w = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
	d2_UpdateProgressBar(w, 0x5dc, 1);
	res = ai_CompareOfficeCandidates(a1, a2, a3, &aux);
	g_100f1dc = -1;
	while (main_RunFrameLoop(fcn_004dc230, cut_EventLoopFlags) != 0) {
		if (d2_UpdateProgressBar(w, 0, 0) == 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			res = 0;
			g_774654 = 1;
			if (d2_CurrentElementId != b0)
				res = (d2_CurrentElementId != b2) + 1;
		}
	}
	d2_DestroyForm(h);
	return res;
}
