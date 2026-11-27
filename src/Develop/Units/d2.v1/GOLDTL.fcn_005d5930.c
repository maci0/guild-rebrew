#include <string.h>
#include "client_types.h"
#include "client_actions.h"
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
extern int d2_CurrentWindowId;
#include "client_dialog_state.h"
extern pos14_7f4c00 gm_GameTime;
// SIZE 0xf8
typedef struct {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	char pad60[0x98];
} D2_ERPRESSUNG_MSG;

// SIZE 0x38
typedef struct {
	int p0;
	int f4;
	char pad8[8];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	int x30;
	unsigned int x34;
} D2_ERPRESSUNG_CRIME_REC;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gs_CollectEvidenceForTarget(int, int*, unsigned short);
int __cdecl gm_CollectEntityCrimesByGroup(int*, int*, int*, unsigned short);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendCopyEntityData(D2_ERPRESSUNG_MSG*);
int __cdecl d2_LoadForm(int, int, char*);
int __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
void __cdecl d2_BuildPersonStatusDesc(D2_ERPRESSUNG_CRIME_REC*);
void __cdecl d2_DrawPersonCard(int, int, int, int, D2_ERPRESSUNG_CRIME_REC*, int);
void __cdecl d2_CreateRightAlignedText(char*, int, int, int, int);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl d2_CheckActionBlocker(void*, int);
int __cdecl gm_HandleErpressung(unsigned char*, unsigned char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);

/* ADDRESS: GOLDTL 0x005d5930 */
int __cdecl d2_RunErpressungDialog(unsigned char* p, int* q)
{
	D2_ERPRESSUNG_CRIME_REC recs[0x20];
	char buf[0x200];
	int c[0x20];
	int ids[0x20];
	char text[0x40];
	int b[0x20];
	int cnt;
	int dlg;
	char* e;
	char* obj;
	int n;
	int i;
	int y;
	int k;
	int result;
	int* rp;
	D2_ERPRESSUNG_CRIME_REC* r;

	if (*(unsigned char*) (p + 2) != 6 && *(unsigned char*) (p + 2) != 7) {
		e = gm_LookupEntityRecordById(q[0x85]);
		if (e == 0) {
			return 0x60;
		}
		b[0] = gs_CollectEvidenceForTarget(*(int*) (e + 4), ids, *(unsigned short*) p);
		if (b[0] >= gm_RandomMod(8)) {
			D2_ERPRESSUNG_MSG m;
			pos14_7f4c00 pos;
			int sender;
			pos = gm_GameTime;
			gm_AddTime(&pos, 0x60, 0, 0);
			memset(&m, 0, sizeof(m));
			sender = *(int*) (p + 4);
			m.f8 = sender;
			m.fc = sender;
			m.pos.a = gm_GameTime.a;
			m.pos.b = gm_GameTime.b;
			m.pos.c = gm_GameTime.c;
			m.f58 = sender;
			m.b4 = 0x45;
			m.b36 = 2;
			m.pos.d = gm_GameTime.d;
			m.f5c = *(int*) (e + 4);
			cm_SendCopyEntityData(&m);
			return 0x10;
		} else {
			cm_RequestCopyEntityData(*(int*) (p + 4), *(int*) (e + 4), -0x1a, 1);
			return 0x10;
		}
	}
	dlg = d2_LoadForm(0, 0, "privillegien\\erpressung");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1d55);	d2_SetForm(dlg, 2);
	k = d2_CurrentWindowId;
	d2_SetForm(dlg, 3);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, k, 0x767);
	n = gm_CollectEntityCrimesByGroup(ids, b, c, *(unsigned short*) p);
	cnt = i = 0;
	for (; i < n; i++) {
		obj = gm_LookupEntityRecordById(ids[i]);
		if (obj != 0) {
			recs[cnt].p0 = (int) obj;
			recs[cnt].x2c = c[i];
			recs[cnt].x34 = b[i];
			d2_BuildPersonStatusDesc(&recs[cnt]);
			recs[cnt].x30 = 1;
			cnt++;
		}
	}
	d2_SetForm(dlg, 2);
	if (cnt != 0) {
		if (cnt > 0) {
			y = 0xa;
			k = cnt;
			r = recs;
			do {
				io_FormatTextBuffer(text, (int) "%i (%i) %s", r->x2c, r->x34, (r->x2c != 1) + 0x1748);
				r->x10 = 0x32;
				r->x14 = y;
				d2_DrawPersonCard(0x32, y, d2_CurrentWindowId, 0x56, r, 1);
				d2_CreateRightAlignedText(text, *(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c) - 0xf, y + 0x2d, 200, 0x55);
				r++;
				y += 0x69;
			} while (--k != 0);
		}
	} else {
		io_AppendText(0x1d50);
	}
	result = 0x20;
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			for (i = 0, rp = (int*) recs; i < cnt; i++, rp += 0xe) {
				if (d2_CurrentElementId == rp[1]) {
					if (d2_CheckActionBlocker(p, 2) != 0) {
						if ((*(unsigned int*) (recs[i].p0 + 0x1c8) & 0x200) != 0) {
							io_FormatTextBuffer(buf, 0x1d52, *(unsigned short*) recs[i].p0);
							d2_ShowModalMessageBox(buf, 0);
						} else if (recs[i].x34 < 3) {
							d2_ShowModalMessageBox(*(char**) 0x14ac864, 0);
						} else {
							obj = gm_LookupEntityRecordById(ids[i]);
							if (gm_HandleErpressung(p, (unsigned char*) obj) != 0) {
								g_774654 = 1;
							}
							result = 0x92;
						}
					}
					break;
				}
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunErpressungDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
