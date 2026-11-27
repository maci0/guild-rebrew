

// SIZE 0x2f4

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern trade_868080 g_868080[];
extern unsigned char g_773d75;
extern int g_100f884;
extern int g_100f1dc;
extern char g_6a5a10[];
extern char g_6811b0[];

int __cdecl gm_CompareGameTime(pos14_7f4c00*, char*);
void __cdecl fcn_00545780(char*);
void __cdecl he_FreeAction(char*);
char* __cdecl he_StartHandlungSearch(int, ...);
int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);

void __cdecl he_RunMeisterpruefungNoticePrompt(char* u)
{
	char* o;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		switch (*(int*) (u + 0x70)) {
		case 0:
			if (*(char**) (u + 0x74) == 0) {
				d2_CreateActionPopupSlot(u, 0, 0, g_6a5a10, 0x5ec);
			}
			if (*(char**) (u + 0x74) == 0) {
				he_FreeAction(u);
				return;
			}
			d2_CenterDialogWindows(*(int*) (*(char**) (u + 0x74) + 8));
			d2_SetForm(*(int*) (*(char**) (u + 0x74) + 8), 0);
			io_AppendText((int) g_6811b0);
			io_AppendText(0x10b9, &g_868080[g_773d75], *(unsigned short*) (u + 8));
			*(int*) (u + 0x70) = 1;
			break;
		case 1:
			if (gm_CompareGameTime(&gm_GameTime, u + 0x52) > 0) {
				fcn_00545780(u);
				he_FreeAction(u);
				return;
			}
			if (*(char**) (u + 0x74) == 0) {
				*(int*) (u + 0x70) = 0;
				return;
			}
			if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
				return;
			}
			if (g_100f1dc == 2) {
				o = he_StartHandlungSearch(2, 2, *(unsigned short*) (u + 8), 1, *(int*) (u + 0xb0));
				*(int*) (o + 0xb0) = 1;
				fcn_00545780(u);
				he_FreeAction(u);
				return;
			}
			if (g_100f1dc == 1) {
				fcn_00545780(u);
				he_FreeAction(u);
			}
			break;
		}
	} else {
		if (*(char**) (u + 0x74) != 0) {
			fcn_00545780(u);
		}
		he_FreeAction(u);
	}
}
