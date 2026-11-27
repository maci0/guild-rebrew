


extern int d2_CurrentWindowId;
extern char g_6a96b8[];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d2_RenderCandidateStatCards(int*);

int __cdecl d2_CreateRentAGraveDialog(int* s, int a2)
{
	if (s[7] == 0) {
		return 0;
	}
	s[0] = d2_LoadForm(0, 0, g_6a96b8);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(s[0]);
	d2_SetForm(s[0], 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(s[0], 1);
	s[1] = d2_CurrentWindowId;
	io_AppendText(g_6a9694, a2);
	d2_SetForm(s[0], 2);
	s[2] = d2_CurrentWindowId;
	d2_SetForm(s[0], 3);
	s[4] = d2_CurrentWindowId;
	d2_SetForm(s[0], 5);
	s[5] = d2_CurrentWindowId;
	d2_SetForm(s[0], 4);
	s[6] = d2_CurrentWindowId;
	io_AppendText(g_6811b0);
	d2_RenderCandidateStatCards(s);
	return 1;
}
