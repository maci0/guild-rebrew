

#include <string.h>
#pragma intrinsic(memset)

#pragma pack(push, 1)
typedef struct {
	int id;
	char p4[0x18];
	unsigned char kind;
	char p1d[0x10];
} Rec5bfd;
// SIZE 0x2d
#pragma pack(pop)

typedef struct {
	int pad[3];
	int count;
	int pad2[5];
} Stat5bfd;
// SIZE 0x24

typedef struct {
	int name;
	int pad[4];
} Kind5bfd;
// SIZE 0x14

#include "Develop/client_types.h"
extern Rec2d_9a3800 cm_CrimeRecords[512];
#include "Develop/Units/d2.v1/crime_description.h"
extern char g_6ac4c8[];
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl gs_CollectEvidenceIndicesForTarget(int, int*, unsigned short);
void __cdecl d2_SortCrimeRecordsByKind(int n, Rec5bfd* arr);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_AddWindowScrollButtons(int x, int y, int win, int target, int id);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_ShowWrappedText(int, int, int, int, int);
int __cdecl gm_GetLawEntry(int, Stat5bfd*);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
int __cdecl gm_CheckPrivilege(int, unsigned short*, int*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005a2230 */
void __cdecl d2_ShowBeweiseDetails(unsigned short* who, unsigned short* e)
{
	int h;
	Stat5bfd st;
	int list[32];
	int q[0x88];
	Rec5bfd recs[32];
	int n;
	int i;
	int k;
	int w;

	if (*e == 0xffff) {
		return;
	}
	n = gs_CollectEvidenceIndicesForTarget(*(int*) (e + 2), list, *who);
	if (n < 1) {
		return;
	}
	for (i = 0; i < n; i++) {
		recs[i] = ((Rec5bfd*)cm_CrimeRecords)[list[i]];
	}
	d2_SortCrimeRecordsByKind(n, recs);
	h = d2_LoadForm(0, 0, g_6ac4c8);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 2);
	w = d2_CurrentWindowId;
	d2_SetForm(h, 4);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, w, 0x767);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	io_AppendText(0x1742, *e);
	d2_SetForm(h, 2);
	for (k = 0; k < n; k++) {
		d2_ShowWrappedText(g_14aa314[recs[k].kind].name, 10, k * 0x28 + 10, 0x13b, 0x55);
		if (gm_GetLawEntry(recs[k].kind, &st) != 0 && st.count != 0) {
			for (i = 0; i < st.count; i++) {
				d2_AddElementToWindow(i * 0x10 + 0x154, k * 0x28 + 10, 0x526, d2_CurrentWindowId);
			}
		}
	}
	memset(q, 0, sizeof(q));
	q[0] = 1;
	d2_SetForm(h, 3);
	if (gm_CheckPrivilege(0x16, e, q) & 2) {
		io_AppendText(0x174a);
	}
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_ShowBeweiseDetails, 0x657c7) != 0);
	d2_DestroyForm(h);
}
