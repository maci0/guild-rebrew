#include <string.h>

extern char* g_6b8300;
extern int g_1040494;
extern int g_6a25b8;
extern int d2_CurrentWindowId;
extern char* g_1015ea0;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern char* d3_ActiveCamera;
extern int g_14ce8cc;
extern int g_14ce8e0;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_CurrentElementId;
#include "game_player.h"
extern char g_773d75;
extern char g_14cf950;
extern double g_662908;

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_SetFormVisibility(int a, int b);
void __cdecl d2_SetForm(int a, int b);
int __cdecl d2_AddElementToWindow(int a, int b, int c, int d);
void __cdecl d2_AddToRadioGroup(int a, int b);
int __cdecl d2_CreateRadioGroup(int a, ...);
int __cdecl d3_PickFloorPoint(char* a, int b, int c, float d, float* out);
float* __stdcall D3DXMatrixTranspose(float* a, const float* b);
void __cdecl d3_SetNodePosition(int h, float* p);
int __cdecl plt_CheckZoneAvailability(int a, int b, int c, unsigned int d);
void __cdecl d3_SetSubtreeColor(int a, int b, int c, int d);
int __cdecl cm_SendChainRecordLookup(int a, int b, int c, int d, int e, int f);
int __cdecl cm_GetCommandStatus(int a);
int __cdecl main_RunFrameLoop(void* fn, int msg);
int __cdecl cm_GetCommandResult(int a);
float __cdecl eval_ObjektPreis2Credits(int, int);

void __cdecl cm_RequestMoveCredits(int a, int b, unsigned char c, int d);
int __cdecl init_SetPflanzenMap(int a, int b);
void __cdecl d3_AnimateObjectTransform(int a, float* p, int b, int c, int d);
void __cdecl d2_SelectRadioGroup(int a, int b);
int __cdecl plt_FindPlantInfo(int a);
void __cdecl d3_DestroyObject(int a);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
int __cdecl d3_LoadObjectFile(char* a, int b, int c);
void __cdecl d3_VisitObjectAttachments(int a, int p);
void __cdecl ReportClientMessage(char* a);
void __cdecl d2_ClearRadioGroup(int a);
void __cdecl d2_DestroyForm(int a);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005c5310 */
void __cdecl ob_HandleBepflanzung(int gebaeude)
{
	int v1;

	int v6;
	int v16;
	int v17;
	unsigned int v18;
	unsigned int v19;
	unsigned int v20;
	unsigned int v21;
	unsigned int v22;
	int v23;
	int v24;
	int v25;
	unsigned short* v26;
	int v3;



	int v33;
	unsigned int v34;
	int v35;
	unsigned int v36;
	int v37;
	int v38;
	unsigned int v39;
	unsigned short* v4;
	unsigned int v40;

	unsigned int v7[9];
	int v8[8];
	float pick[3];
	float matrix[16];
	float world[3];
	float place[3];












	char v14[256];
	char v15[256];


	v40 = *(unsigned int*) ((char*) gebaeude + 0x71);
	v33 = -1;
	v24 = -1;
	v17 = 0;
	v6 = 0;
	v16 = 0;
	pick[0] = 0.0f;
	pick[1] = 0.0f;
	pick[2] = 0.0f;
	v1 = 1;
	v34 = 0;
	v37 = 0;
	v36 = 0;
	v23 = 0;
	v26 = 0;
	v25 = 0;
	if (!g_6b8300) {
		return;
	}
	v18 = 0;
	do {
		v3 = v17 + 0x7e24 + (int) g_6b8300;
		if (strstr((char*) v3, (char*) 0x67dd10)) {
			v36 = v18;
		}
		v17 += 0x40;
		v18 += 1;
	} while (v17 < 0x200);
	v17 = fcn_00502cd0(*(unsigned int*) ((char*) gebaeude + 0x5d), 1, 0, 0xff);
	if (!v17) {
		return;
	}
	v4 = fcn_00502cd0(*(unsigned int*) ((char*) v17 + 0x14), 1, 4, 0x17);
	if (v4) {
		do {
			v16 += 1;
			v7[v16] = *v4;
			v4 = gm_NextEntityQueryMatch();
		} while (v4);
		v25 = v16;
	}
	v17 = d2_LoadForm(g_1040494 - 0x5f, 0x10a, (char*) 0x6ac720);
	if (v17 == -1) {
		return;
	}
	v38 = v17;
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, 0);
	}
	d2_SetForm(v17, 1);
	v17 = 0;
	if (1 <= v16) {
		do {
			v16 = d2_AddElementToWindow(0x1a, v17 * 0x32, v7[v17 + 1] + 0xdf,
				d2_CurrentWindowId);
			v8[v17] = v16;
			if (v24 == -1) {
				v24 = d2_CreateRadioGroup(1, v16);
				*(unsigned int*) (&((D2_CONTROL_TL*) (g_1015ea0))[v16].value_038) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*) (g_1015ea0))[v16].value_03c) = 1;
			} else {
				d2_AddToRadioGroup(v24, v16);
			}
			v17 += 1;
		} while (v17 < v25);
		v16 = v25;
	}
	v35 = v24 * 0x23;
	for (;;) {
		v18 = d3_PickFloorPoint(g_6b8300, (int) g_14ce8c0,
			(int) g_14ce8c2, 30.0f, pick);
		if (v18 != 0xffffffff && v6) {
			v19 = v18 & 0xffff;
			v16 = (int) v18 >> 0x10;
			v37 = v16;
			v34 = v19;
			D3DXMatrixTranspose(matrix, (float*) (d3_ActiveCamera + 0x18c));
			world[0] = matrix[8] * pick[2] + matrix[4] * pick[1] + matrix[0] * pick[0];
			world[1] = matrix[9] * pick[2] + matrix[5] * pick[1] + matrix[1] * pick[0];
			world[2] = matrix[10] * pick[2] + matrix[6] * pick[1] + matrix[2] * pick[0];
			world[0] += *(float*) (d3_ActiveCamera + 0x4c);
			world[1] += *(float*) (d3_ActiveCamera + 0x50);
			world[2] += *(float*) (d3_ActiveCamera + 0x54);
			d3_SetNodePosition(v6, world);
			if (*(unsigned char*) (*(int*) g_6b8300 * v16
					+ *(int*) (g_6b8300 + 0x14) + v19) == v36
				&& (v16 = plt_CheckZoneAvailability(v40, v19, v16,
						(unsigned char) ((char*) v26)[0x42])) != 0) {
				v16 = v25;
				v1 = 1;
				d3_SetSubtreeColor(v6, 0, 0, 0);
			}
			else {
				v16 = v25;
				v1 = 0;
				d3_SetSubtreeColor(v6, 0xc0, 0x40, 0x40);
			}
		}
		else {
			if (v1) {
				d3_SetSubtreeColor(v6, 0, 0, 0);
			}
			else {
				d3_SetSubtreeColor(v6, 0xc0, 0x40, 0x40);
			}
		}
		v4 = v26;
		if (g_14ce8cc && v18 != 0xffffffff && v1) {
			v20 = cm_SendChainRecordLookup(*(unsigned int*) ((char*) gebaeude + 1),
				v34, v37, *v26, 0, 0xffffffff);
			v17 = cm_GetCommandStatus(v20);
			while (!v17) {
				main_RunFrameLoop(0, 0x677c7);
				v17 = cm_GetCommandStatus(v20);
			}
			v17 = cm_GetCommandResult(v20);
			if (v17) {
				v39 = (int) eval_ObjektPreis2Credits(*v4, 100);
				v3 = (int) ((int) v39 * 0.5);
				if (v3 <= 0x400) {
					v3 = 0x400;
				}
				cm_RequestMoveCredits(0xffffffff,
					*(unsigned int*) (g_774970 * 0x21c
						+ 0x7f4ca4), g_773d75, v3);
				init_SetPflanzenMap(v17, 0);
				v17 = *(int*) ((char*) v17 + 0x14);
				if (v17) {
					place[0] = world[0];
					place[1] = world[1] - 60.0;
					place[2] = world[2];
					d3_SetNodePosition(v17, place);
					d3_AnimateObjectTransform(v17, world, v17 + 0x84, 0x32, 0x20);
				}
			}
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
		if (g_14ce8cc) {
			v17 = 0;
			if (1 <= v16) {
				do {
					if (d2_CurrentElementId == v8[v17]) {
						v23 = *(int*) (v35 * 4 + 0x102cbc8);
						break;
					}
					v17 += 1;
				} while (v17 < v16);
			}
		}
		if (g_14cf950 == 'N') {
			v23 += 1;
			if (v23 > v16 - 1) {
				v23 = 0;
			}
			d2_SelectRadioGroup(v24, v23);
		}
		else if (g_14cf950 == 'J') {
			v23 -= 1;
			if (v23 <= -1) {
				v23 = v16 - 1;
			}
			d2_SelectRadioGroup(v24, v23);
		}
		v23 = *(int*) (v35 * 4 + 0x102cbc8);
		if (v23 != v33) {
			v4 = (unsigned short*) plt_FindPlantInfo(v7[v23 + 1]);
			v26 = v4;
			if (v6) {
				d3_DestroyObject(v6);
			}
			fcn_0064d41a(v14, (char*) 0x6ac704, (char*) 0x7e1ae0,
				&v4[1]);
			v6 = d3_LoadObjectFile(v14, 0, 0);
			if (!v6) {
				fcn_0064d41a(v15, (char*) 0x6ac6c4, v14);
				ReportClientMessage(v15);
				g_774654 = 1;
			}
			else {
				unsigned char color[4] = { 0 };
				color[2] = 1;
				color[0] = 0xdc;
				*(unsigned char*) ((char*) v6 + 0x215) =
					*(unsigned char*) ((char*) v6 + 0x215) & 0x7f;
				d3_VisitObjectAttachments(v6, (int) color);
				*(unsigned char*) ((char*) v6 + 0x215) =
					*(unsigned char*) ((char*) v6 + 0x215) | 0x80;
			}
			v33 = v23;
		}
		if (!main_RunFrameLoop((void*) ob_HandleBepflanzung, 0x677cf)) {
			if (v6) {
				d3_DestroyObject(v6);
			}
			d2_ClearRadioGroup(v24);
			if (g_6a25b8 != -1) {
				d2_SetFormVisibility(g_6a25b8, 1);
			}
			d2_DestroyForm(v38);
			return;
		}
	}
}
