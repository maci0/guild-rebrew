int __cdecl fcn_0046f740(int, int, int, int); int __cdecl fcn_00470820(int, int, char*);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl gm_CheckZunftPreismanipulation(char*);
int __cdecl fcn_004eb3e0(int, int*);
int __cdecl io_AppendText();
int __cdecl fcn_00525f60(void*, int);
int __cdecl fcn_00526120(void*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_005373e0(void*, int);
extern int g_100f1dc; extern char * g_1015ea0; extern int d2_CurrentWindowId; extern unsigned short g_774970; extern char g_7f4ca0[];
/* ADDRESS: GOLDTL 0x005aa480 */
void __cdecl fcn_005aa480(void)
{
	int sel[3];
	int pos[7][2] = {
		{0x40, 0x50},
		{0xc0, 0x50},
		{0x140, 0x50},
		{0x1c0, 0x50},
		{0x80, 0xb8},
		{0x100, 0xb8},
		{0x180, 0xb8}
	};
	int pa[5];
	int pb[5];
	int ids[7];
	int cur;
	int i;
	int j;
	int n;
	int h;
#include "Develop/DieGildeAddOn/game/entity_record.h"
	n = gm_CheckZunftPreismanipulation((char*) ((unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) *(unsigned short*) &g_774970]));
	if (n != 1) {
		if (n == -1) {
			fcn_00526120((void*) *(int*) 0x14aad38, 0);
			return;
		}
		fcn_00525f60((void*) ((unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) *(unsigned short*) &g_774970]), 3);
		return;
	}
	h = fcn_00470820(0, 0, "LOCATIONS\\ZUNFTHAUS\\LEVEL1");
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 0);
	fcn_005340f0(*(int*) &d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x1643);
	d2_SetForm(h, 2);
	i = 0;
	do {
		n = fcn_0046f740(pos[i][0] - 0x28, pos[i][1] - 0x46, i + 0x5a2, *(int*) &d2_CurrentWindowId);
		ids[i] = n;
		i++;
		((D2_CONTROL_TL*)*(void**)&g_1015ea0)[n].value_05c = 1;
	} while (i < 7);
	cur = 0;
	((D2_CONTROL_TL*)*(void**)&g_1015ea0)[ids[0]].value_03c = 1;
	d2_SetForm(h, 3);
	n = (unsigned int) *(unsigned short*) &g_774970;
	if (((ENTITY_RECORD*)g_7f4ca0)[n].gender == 0) {
		n = ((ENTITY_RECORD*)g_7f4ca0)[n].unk_165[4] + 0x253;
	} else {
		n = ((ENTITY_RECORD*)g_7f4ca0)[n].unk_165[4] + 0x27b;
	}
	io_AppendText(0x1644, n, 3, 0x1649);
	d2_SetForm(h, 4);
	fcn_00533a60(*(int*) &d2_CurrentWindowId, 0, sel, 3,
	    *(char**) 0x14aac34, *(char**) 0x14aac38, *(char**) 0x14aac3c);
	*(int*) &g_100f1dc = -1;
	do {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) &g_100f1dc != -1) {
			n = *(int*) 0x67d370;
			if (n == sel[2]) {
				*(int*) 0x774654 = 1;
			} else if (n == sel[0]) {
				n = *(unsigned short*) &g_774970;
				pb[0] = 3;
				pb[1] = cur + 1;
				pb[2] = 1;
				fcn_004eb3e0((int) ((unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) n]), pb);
				*(int*) 0x774654 = 1;
			} else if (n == sel[1]) {
				pa[0] = 3;
				pa[1] = cur + 1;
				pa[2] = -1;
				fcn_004eb3e0((int) ((unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) *(unsigned short*) &g_774970]), pa);
				*(int*) 0x774654 = 1;
			} else {
				j = 0;
				do {
					if (n == ids[j] && cur != j) {
						((D2_CONTROL_TL*)*(void**)&g_1015ea0)[ids[cur]].value_03c = 0;
						cur = j;
						((D2_CONTROL_TL*)*(void**)&g_1015ea0)[ids[j]].value_03c = 1;
						d2_SetForm(h, 3);
						io_AppendText(0x6811b0);
						n = (unsigned int) *(unsigned short*) &g_774970;
						if (((ENTITY_RECORD*)g_7f4ca0)[n].gender == 0) {
							n = ((ENTITY_RECORD*)g_7f4ca0)[n].unk_165[4] + 0x253;
						} else {
							n = ((ENTITY_RECORD*)g_7f4ca0)[n].unk_165[4] + 0x27b;
						}
						io_AppendText(0x1644, n, 3, j + 0x1649);
						break;
					}
					j++;
				} while (j < 7);
			}
		}
	} while (fcn_005373e0((void*) fcn_005aa480, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_00532ef0();
}
