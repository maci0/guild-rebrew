

// SIZE 0x21c
struct house {
	char pad0[0x1cc];
	unsigned char flags;
	char pad1cd[0x4f];
};

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f884;
extern int g_100f1dc;
extern char g_6a5a10[];
extern char g_6811b0[];
extern char g_6a7f1c[];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl d2_CloseActionPopup(char*);
void __cdecl he_FreeAction(char*);
int __cdecl gm_CompareGameTime(pos14_7f4c00*, char*);
void __cdecl he_DeclineDeathPactPayment(char*, struct house*);
void __cdecl he_AcceptDeathPactPayment(char*, struct house*);
int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d3snd_QueueSound(int, int, char*, int, int);

void __cdecl he_HandleDeathPactPrompt(char* u)
{
	char* h;
	char* p;

	p = u + 0xac;
	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	if (h == 0 || (((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].flags & 1) != 0) {
		*(int*) (u + 0x70) = -2;
	}
	if (*(int*) (u + 0x70) == -2) {
		if (*(char**) (u + 0x74) != 0) {
			d2_CloseActionPopup(u);
		}
		he_FreeAction(u);
		return;
	}
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
		io_AppendText(0x40fd, *(unsigned short*) h, *(int*) (u + 0xb8));
		d3snd_QueueSound(-7, 0, g_6a7f1c, -1, 0);
		*(int*) (u + 0x70) = 1;
		break;
	case 1:
		if (gm_CompareGameTime(&gm_GameTime, u + 0x52) > 0) {
			he_DeclineDeathPactPayment(p, &((struct house*)g_7f4ca0)[g_774970]);
			d2_CloseActionPopup(u);
			he_FreeAction(u);
			break;
		}
		if (*(char**) (u + 0x74) == 0) {
			*(int*) (u + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
			return;
		}
		if (g_100f1dc == 2) {
			he_AcceptDeathPactPayment(p, &((struct house*)g_7f4ca0)[g_774970]);
			d2_CloseActionPopup(u);
			he_FreeAction(u);
			return;
		}
		if (g_100f1dc == 1) {
			he_DeclineDeathPactPayment(p, &((struct house*)g_7f4ca0)[g_774970]);
			d2_CloseActionPopup(u);
			he_FreeAction(u);
		}
		break;
	}
}
