#include "client_data.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern int g_14cf900[]; extern short g_14cf902; extern char g_67d908[];
#include "Develop/Units/d2.v1/d2_gui.h"
#include "client_types.h"
extern Group_102cbc4 g_102cbc4[8];
/* Refreshes the current selection/building view state. */

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f890;
extern int g_100f800;
extern int g_67d388;
extern int g_6b5c8c;
extern int g_772578;
extern int g_100f84c;
extern int g_100f1d0;
extern int g_100f1e4;
extern int g_67d8d0;

int __cdecl fcn_0046aee0(int x, int y);
void __cdecl fcn_004748b0(void);
void __cdecl fcn_00473b10(void);
void __cdecl fcn_004234e0(int handle, char* text, int a, int b, int c, int d, int e);
void __cdecl fcn_00472380(int object, int selected);
void __cdecl fcn_0046e790(int index);

/* ADDRESS: GOLDTL 0x00474e80 */
void __cdecl d2_ProcessMouseInput(void)
{
	int v4;
	int v7;
	int v6;
	int v8;
	int v2;
	int found;
	unsigned int* v1;
	int* v5;
	int* groupCursor;

	if (g_6772c4 != 0) {
		d2_MouseX = *(short*) g_14cf900;
		d2_MouseY = g_14cf902;
	}
	g_100f890 = fcn_0046aee0(d2_MouseX, d2_MouseY);
	fcn_004748b0();
	if (g_67d388 != -1) {
		d2_HoveredWindow = g_67d388;
		g_100f800 = -1;
		v4 = 0;
		v7 = ((D2_WIN*) g_1015f40)[g_67d388].count;
		if (v7 > 0) {
			v5 = ((D2_WIN*) g_1015f40)[g_67d388].children;
			do {
				if (*v5 == d2_CurrentElementId) {
					g_100f800 = v4;
					break;
				}
				v4 += 1;
				v5 = v5 + 1;
			} while (v4 < v7);
		}
	} else {
		d2_HoveredWindow = -1;
	}
	fcn_00473b10();
	if (g_14ce8d8 != 0) {
		v7 = d2_CurrentElementId;
		if (g_100f890 != -1) {
			v4 = (int) &((D2_CONTROL_TL*) g_1015ea0)[d2_CurrentElementId];
			if ((*(int*) (v4 + 0x58) != 0 || *(int*) (v4 + 0x5c) != 0) &&
			    *(int*) (v4 + 0x20) != 0x45) {
				g_100f1dc = g_100f890;
				g_6b5c8c = 1;
				v1 = *(unsigned int**) (v4 + 0x50);
				if (v1 != 0) {
					if (v1[0x67] != 0 && v1[0x66] == 0) {
						g_100f884 = *v1;
					}
				} else {
					g_100f884 = -1;
				}
				if (*(int*) (v4 + 0x58) != 0) {
					*(int*) (v4 + 0x38) = *(int*) (v4 + 0x38) ^ 1;
					((D2_CONTROL_TL*) ((int) g_1015ea0))[d2_CurrentElementId].value_03c =
						((D2_CONTROL_TL*) ((int) g_1015ea0))[d2_CurrentElementId].value_038;
					fcn_004234e0(g_772578, g_67d908, 1, 0x3f, 0x7f, 0, 0);
				} else if (g_100f890 != 1) {
					fcn_004234e0(g_772578, g_67d908, 1, 0x3f, 0x7f, 0, 0);
				} else {
					fcn_004234e0(g_772578, (char*) 0x67d8f0, 1, 0x3f, 0x7f, 0, 0);
				}
				v7 = d2_CurrentElementId;
				found = 0;
				v4 = 0;
				do {
					if (found != 0) {
						break;
					}
					v6 = 0;
					if (g_102cbc4[v4].count > 0) {
						groupCursor = g_102cbc4[v4].ids;
						do {
							if (*groupCursor == v7) {
								v8 = 0;
								if (g_102cbc4[v4].count > 0) {
									v5 = g_102cbc4[v4].ids;
									do {
										v2 = *v5;
										if (v2 != v7) {
											fcn_00472380(v2, 0);
										} else {
											fcn_00472380(v2, 1);
											g_102cbc4[v4].sel = v8;
										}
										v8 += 1;
										v5 = v5 + 1;
										v7 = d2_CurrentElementId;
									} while (v8 < g_102cbc4[v4].count);
								}
								found = 1;
							}
							v6 += 1;
							groupCursor = groupCursor + 1;
						} while (v6 < g_102cbc4[v4].count);
					}
					v4++;
				} while (v4 < 8);
				if (g_100f1dc != g_100f84c) {
					g_100f84c = g_100f1dc;
				}
				g_100f1d0 = g_100f800;
			}
		}
		if (v7 != -1) {
			g_100f1e4 = (int) &((D2_CONTROL_TL*) g_1015ea0)[v7];
		}
	} else {
		g_100f1dc = -1;
		g_100f1e4 = 0;
		g_100f1d0 = -1;
	}
	g_67d8d0 = -1;
	g_67d8d4 = -1;
	v7 = 0;
	v5 = (int*) 0x100f204;
	for (;;) {
		if (d2_MouseX >= v5[-1] &&
		    d2_MouseX <= v5[-1] + v5[1] &&
		    d2_MouseY >= *v5 &&
		    d2_MouseY <= *v5 + v5[2] &&
		    v5[4] != 0) {
			g_67d8d4 = v7;
			if (g_14ce8d8 != 0) {
				g_67d8d0 = v7;
			}
			break;
		}
		v5 += 6;
		v7 += 1;
		if ((int) v5 >= 0x100f504) {
			break;
		}
	}
	if (d2_HoveredWindow != -1) {
		v4 = (int) &g_1015f40[d2_HoveredWindow];
		if (g_14ce8d0 != 0 &&
		    (*(unsigned char*) (v4 + 0x14) & 0x20) != 0 &&
		    *(int*) (v4 + 0xc) + *(int*) (v4 + 4) - 0xc < d2_MouseX &&
		    d2_MouseY > *(int*) (v4 + 8) + 0xa &&
		    d2_MouseY < *(int*) (v4 + 0x10) + *(int*) (v4 + 8) - 0xa) {
			v7 = ((d2_MouseY - *(int*) (v4 + 8) - 0xc) * *(int*) (v4 + 0x254)) /
			     (*(int*) (v4 + 0x10) - 0x18) + 4;
			*(int*) (v4 + 0x258) = v7;
			*(int*) (v4 + 0x248) = v7 / d2_FontHeight;
			*(int*) (v4 + 0x44) = *(int*) (v4 + 0x48 + (v7 / d2_FontHeight) * 4);
			if (v7 != *(int*) (v4 + 0x25c)) {
				fcn_0046e790(d2_HoveredWindow);
			}
		}
	}
}
