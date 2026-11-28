/* Black-board ("schwarzes Brett") dialogue: lists up to four messages and
 * runs the modal click loop until the dialogue closes. */

#include "Develop/client_types.h"

typedef struct {
	char pad0[4];
	int f4;
	char pad8[0x68];
	int f70;
	char pad74[0x48];
	int fbc;
	char padc0[1];
	unsigned char fc1;
} D2_SCHWARZES_BRETT_ENTRY;
#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
char* __cdecl he_fn_Handlung(void);
int __cdecl he_StartHandlungSearch();
unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_CheckActionBlocker(char*, int);
int __cdecl cm_SendSetHE(int, char*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d3_EndCameraAndUiMode(void);
int __cdecl gm_ModifyHealth(int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005c1110 */
int __cdecl d2_RunSchwarzesBrettDialog(void)
{
	int n;
	unsigned int t;
	unsigned short* p;
	int a[4];
	int b[4];
	D2_SCHWARZES_BRETT_ENTRY* ent;
	int h;
	int k;
	int i;
	int j;
	int o;
	int r;
	int* q;

	a[0] = -1;
	a[1] = -1;
	a[2] = -1;
	a[3] = -1;
	b[0] = -1;
	b[1] = -1;
	b[2] = -1;
	b[3] = -1;
	t = (unsigned int) gm_GameTicks;
	h = d2_LoadForm(0, 0, (char*) 0x6ac514);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 0);
	io_AppendText(0x1912);
	*(int*) &d2_DialogButtonAction = -1;
	do {
		if (t <= (unsigned int) gm_GameTicks) {
			n = 1;
			t = (unsigned int) gm_GameTicks + 0x1f4U;
			a[0] = -1;
			b[0] = -1;
			a[1] = -1;
			b[1] = -1;
			a[2] = -1;
			a[3] = -1;
			b[2] = -1;
			b[3] = -1;
			ent = (D2_SCHWARZES_BRETT_ENTRY*) he_StartHandlungSearch(n, 0, 0x35);
			if (ent != 0) {
				i = 2;
				k = 0;
				do {
					if (k >= 0x10) {
						goto done;
					}
					if (ent->f70 > -1) {
						p = gm_LookupEntityRecordById(ent->fbc);
						if (p != 0) {
							d2_SetForm(h, i - 1);
							io_AppendText(0x6811b0);
							io_AppendText(0x1913, 0x1916 + (int) ent->fc1,
							    (int) *p);
							d2_SetForm(h, i);
							io_AppendText(0x6811b0);
							*(int*) ((char*) a + k) = d2_GetWindowListItem(h, i,
							    io_AppendText(0x1914, 2));
							*(int*) ((char*) b + k) = ent->f4;
							d2_SetSlotVisibility(*(int*) ((char*) &d2_WindowElementIdView
							    + 0x3cc * *(int*) ((char*) &d2_Forms
							    + h * 0x2bc + n * 8)), 1);
							n++;
							i += 2; k += 4;
						}
					}
					ent = (D2_SCHWARZES_BRETT_ENTRY*) he_fn_Handlung();
				} while (ent != 0);
			}
			if (n < 5) {
				q = (int*) ((char*) &d2_Forms + h * 0x2bc + n * 8);
				j = n * 2 - 1;
				do {
					d2_SetForm(h, j);
					io_AppendText(0x6811b0);
					d2_SetSlotVisibility(*(int*) ((char*) &d2_WindowElementIdView
					    + 0x3cc * *q), 0);
					j += 2; q += 2;
				} while (j < 9);
			}
done:;

		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (*(int*) &d2_DialogButtonAction != -1 && *(int*) 0x67d370 != -1) {
			for (k = 0; k < 4; k++) {
				if (a[k] == *(int*) 0x67d370) {
					break;
				}
			}
			if (k < 4) {
				o = he_StartHandlungSearch(1, 1, b[k]);
				if (o != 0) {
					if (d2_CheckActionBlocker((char*) &gm_EntitySlotTable + 0x21c
					    * (unsigned int) *(unsigned short*) &gm_LocalPlayerSlot, 2) != 0) {
						*(pos14_7f4c00*) ((char*) o + 0x52) =
						    *(pos14_7f4c00*) &gm_GameTime;
						r = cm_SendSetHE(-1, (char*) o);
						while (r != -1 && cm_GetCommandStatus(r) == 0) {
							main_RunFrameLoop(0, 0x677c7);
						}
						if (cm_GetCommandStatus(r) == 1) {
							gm_ModifyHealth(*(int*) ((char*) &gm_EntitySlotTable
							    + 4 + 0x21c
							    * (unsigned int) *(unsigned short*) &gm_LocalPlayerSlot), -2);
						}
						t = (unsigned int) gm_GameTicks;
					}
				}
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunSchwarzesBrettDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	return d3_EndCameraAndUiMode();
}
