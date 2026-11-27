#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

void __cdecl d2_CloseActionPopup(char* a);
void __cdecl he_FreeAction(char* a);
int __cdecl d2_CreateActionPopupSlot(char* a, int b, int c, char* d, int e);
void __cdecl he_ApplyAction0x92Favor(char* a);
void __cdecl he_RemoveAction0x92Favor(char* a);
void __cdecl d2_CenterDialogWindows(int id);
void __cdecl d2_SetForm(int a, int b);
void __cdecl d3snd_QueueSound(int a, int b, char* c, int d, int e);
int __cdecl io_AppendText(int a, ...);
int __cdecl gm_CompareGameTime(void* a, void* b);

/* ADDRESS: GOLDTL 0x0057b1f0 */
void __cdecl he_RunMeisterpruefung(char* a)
{
	int state;

	state = *(int*) (a + 0x70);
	if (state == -2) {
		if (*(int*) (a + 0x74) != 0)
			d2_CloseActionPopup(a);
		he_FreeAction(a);
		return;
	}
	switch (state) {
	case 1:
		if (gm_CompareGameTime((void*) 0x7f4c00, a + 0x52) > 0)
			goto activate;
		if (*(int*) (a + 0x74) == 0) {
			*(int*) (a + 0x70) = 0;
			return;
		}
		if (*(int*) 0x100f884 != *(int*) (*(int*) (a + 0x74) + 8))
			return;
		if (*(int*) 0x100f1dc == -1)
			return;
		if (*(int*) 0x100f1dc == 2) {
			he_ApplyAction0x92Favor(a);
			d2_CloseActionPopup(a);
			he_FreeAction(a);
			return;
		}
		if (*(int*) 0x100f1dc != 1)
			return;
	activate:
		he_RemoveAction0x92Favor(a);
		d2_CloseActionPopup(a);
		he_FreeAction(a);
		return;
	case 0:
		if (*(int*) (a + 0x74) == 0)
			d2_CreateActionPopupSlot(a, 0, 0, (char*) 0x6a5a10, 0x5ec);
	if (*(int*) (a + 0x74) == 0) {
		he_FreeAction(a);
		return;
	}
	d2_CenterDialogWindows(*(int*) (*(int*) (a + 0x74) + 8));
	d2_SetForm(*(int*) (*(int*) (a + 0x74) + 8), 0);
	io_AppendText(0x6811b0);
	io_AppendText(0x411c, *(int*) (a + 0xb8));
	d3snd_QueueSound(-7, 0, (char*) 0x6a8034, -1, 0);
	*(int*) (a + 0x70) = 1;
	}
}
