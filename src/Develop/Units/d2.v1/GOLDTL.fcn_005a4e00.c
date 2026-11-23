
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/Units/d2.v1/d2_window_view.h"
extern int g_14ab694;
int __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
int __cdecl io_AppendText();
int __cdecl fcn_00533a60(int, int, int*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0046f280(int);
void __cdecl d2_DestroyElement(int);
int __cdecl fcn_0050d640(int, char*, unsigned int, char**);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_0050dd00(int, int*, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_005a4bb0(char*);
void __cdecl fcn_005a4960(char*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005a4e00 */
void __cdecl fcn_005a4e00(char* building)
{
	int items[16][3];
	int ids[16];
	char* out[16];
	int tmp[8];
	int v1;
	int v2;
	int v3;
	int close_btn;
	int n;
	int h;
	int i;
	int j;
	int count;
	int sum;
	int v;
	int first;
	char* p;

	count = 0;
	first = 1;
	for (i = 0; i < 16; i++) {
		items[i][0] = -1;
		items[i][1] = -1;
		items[i][2] = 0;
	}
	d2_SetOverlayAnimation(0, 0);
	h = fcn_00470820(0, 0, (char*) 0x6aac2c);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x73b, 0x73f);
	fcn_00533f40(0x206, 0x167, d2_CurrentWindowId, fcn_00472830(h, 2),
	    0x78, &v3, &v2, &v1);
	*(int*) &((D2_WIN*) g_1015f40)[d2_CurrentWindowId].pad3a8[0x0] = 0xe;
	*(int*) &((D2_WIN*) g_1015f40)[d2_CurrentWindowId].pad3a8[0x4] = 0x18;
	*(int*) &((D2_WIN*) g_1015f40)[d2_CurrentWindowId].pad3a8[0x8] = 0xe;
	*(int*) &((D2_WIN*) g_1015f40)[d2_CurrentWindowId].pad3a8[0xc] = 0xe;
	d2_SetForm(h, 1);
	io_AppendText(0x18d9);
	d2_SetForm(h, 3);
	fcn_00533a60(d2_CurrentWindowId, 0, tmp, 1, g_14ab694);
	close_btn = tmp[0];
	while (fcn_005373e0((void*) fcn_005a4e00, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (first) {
			d2_SetForm(h, 2);
			for (i = 0; i < 16; i++) {
				if (items[i][0] != -1) {
					fcn_0046f280(items[i][0]);
					d2_DestroyElement(items[i][1]);
					items[i][0] = -1;
					items[i][1] = -1;
					items[i][2] = 0;
				}
			}
			io_AppendText((int) g_6811b0);
			n = fcn_0050d640(*(unsigned short*) (building + 0x27), building, 0xffff, out);
			for (i = 0; i < 16; i++) {
				ids[i] = -1;
			}
			count = 0;
			for (j = 0; j < n; j++) {
				for (i = 0; i <= count; i++) {
					if (((ENTITY_RECORD*) g_7f4ca0)[ids[i]].entity_id == *(int*) (out[j] + 0xb0)) {
						break;
					}
					if (ids[i] == -1) {
						p = gm_LookupEntityRecordById(*(int*) (out[j] + 0xb0));
						if (p != 0) {
							ids[i] = *(unsigned short*) p;
							count++;
						}
						break;
					}
				}
			}
			d2_SetForm(h, 2);
			io_AppendText(0x18de,
			    *(unsigned short*) (g_8680b4 + g_773d75 * 0x2f4) * 2 + 0x9a8);
			if (count == 0) {
				io_AppendText(0x48d);
			}
			fcn_0050dd00(count, ids, 0);
			for (i = 0; i < count; i++) {
				v = fcn_0050d640(*(unsigned short*) (building + 0x27), building,
				    ids[i], out);
				sum = 0;
				for (j = 0; j < v; j++) {
					sum += *(int*) (out[j] + 0xb4);
				}
				items[i][1] = fcn_00472250(h, 2,
				    io_AppendText(0x18df, ids[i], v, sum));
			}
		}
		first = 0;
		if (g_100f1dc == 2) {
			if (d2_CurrentElementId == close_btn) {
				fcn_005a4bb0(building);
			}
			else {
				for (i = 0; i < count; i++) {
					if (d2_CurrentElementId == items[i][1]) {
						fcn_005a4960(building, ids[i]);
						first = 1;
					}
				}
			}
		}
	}
	fcn_00471e30(h);
	fcn_00532ef0();
}
