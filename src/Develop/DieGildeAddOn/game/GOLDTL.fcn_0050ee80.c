#include "game_data.h"
#include "client_data.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7f4c10;
#include "Develop/Units/d2.v1/d2_dependency_node.h"



















int __cdecl fcn_00502cd0(int, int, ...);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f280(int);
int __cdecl io_AppendText();
int __cdecl fcn_00500d20(void*, void*);

/* ADDRESS: GOLDTL 0x0050ee80 */
void __cdecl fcn_0050ee80(unsigned char* a, unsigned short* b)
{
	DEPENDENCY_DIAGRAM_NODE* p;
	char* q;
	int i;
	int st;
	int n;
	int found;
	int v1;
	int v2;
	int h;
	int y;
	int k;

	i = 0;
	v1 = *(int*) (0x1038150 + g_7f4c10 * 0x2bc);
	for (; i < g_85ab60; i++) {
		st = 0;
		if (*(unsigned char*) (lpObjektePROT + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id * 0x40 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) == 6) {
			if (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) != 0) {
				st = 1;
				for (q = fcn_005463a0(2, 0, 0xc, 3, *(int*) (a + 1)); q != 0;
				     q = he_fn_Handlung()) {
					if (*(int*) (q + 0xb4) == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) {
						st = 3;
						break;
					}
				}
			} else {
				n = 0;
				if (i > 0) {
					p = (DEPENDENCY_DIAGRAM_NODE*)g_7f3f00;
					for (k = i; k != 0; p++, k--) {
						if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a &&
						    (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
						     fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0) &&
						    *(int*) (g_1015ea0 + p->unk_24 * 0x2f4 + 0x60) == 0) {
							n++;
						} else if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b &&
							   (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
							    fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0) &&
							   *(int*) (g_1015ea0 + p->unk_24 * 0x2f4 + 0x60) == 0) {
							n++;
						}
					}
				}
				if ((n == 0 && ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a == 0) ||
				    (n == 1 && ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b == 0) ||
				    n == 2) {
					st = 2;
				}
			}
		} else {
			if (fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) != 0) {
				st = 1;
			} else if (*(unsigned short*) b != 0xfd ||
				   fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) == 0) {
				found = 0;
				if (i > 0) {
					p = (DEPENDENCY_DIAGRAM_NODE*)g_7f3f00;
					for (k = i; k != 0; p++, k--) {
						if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a &&
						    (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
						     fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0)) {
							found++;
						} else if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b &&
							   (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
							    fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0)) {
							found++;
						}
					}
				}
				if ((found == 0 && ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a == 0) ||
				    (found == 1 && ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b == 0) ||
				    found == 2) {
					st = 2;
					for (q = fcn_005463a0(2, 0, 2, 3, *(int*) (a + 1)); q != 0;
					     q = he_fn_Handlung()) {
						if (*(int*) (q + 0xb0) == *(int*) ((char*) b + 2) &&
						    *(unsigned short*) (q + 0xac) == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) {
							st = 3;
							break;
						}
					}
				}
			} else {
				st = 1;
			}
		}
		if (st != ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].state) {
			if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c != -1) {
				fcn_0046f280(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c = -1;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_20 = -1;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 = -1;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_28 = -1;
			}
			if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_2c != -1) {
				fcn_0046f280(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_2c);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_2c = -1;
			}
			h = d2_CurrentWindowId;
			if (st == 0) {
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c = v2;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_20 = fcn_0046f740(0, 0, 0x52b, v2);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 = fcn_0046f740(3, 3, 0x4fb, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c);
			} else if (st == 1) {
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c = v2;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_20 = fcn_0046f740(0, 0, 0x529, v2);
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id < 0x2dc) {
					y = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id + 0xdf;
				} else {
					y = 0xdf;
				}
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 = fcn_0046f740(3, 3, y, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c);
				*(int*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x64) = 1;
				*(int*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x5c) = 1;
				d2_CurrentWindowId = h;
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 0x18, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y + 0x32, 0x60, 0x11, 0x4510, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_2c = v2;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x28c) = 0x54;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x20) = 1;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x24) = 1;
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id < 0x2dc) {
					io_AppendText(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id * 2 + 0x9a8);
				}
			} else if (st == 2) {
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c = v2;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_20 = fcn_0046f740(0, 0, 0x52a, v2);
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id < 0x2dc) {
					y = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id + 0xdf;
				} else {
					y = 0xdf;
				}
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 = fcn_0046f740(3, 3, y, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c);
				*(int*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x5c) = 1;
				d2_CurrentWindowId = h;
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 0x18, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y + 0x32, 0x60, 0x11, 0x4510, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_2c = v2;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x28c) = 0x54;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x20) = 1;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x24) = 1;
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id < 0x2dc) {
					io_AppendText(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id * 2 + 0x9a8);
				}
				*(int*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x64) = 1;
			} else {
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c = v2;
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_20 = fcn_0046f740(0, 0, 0x529, v2);
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id < 0x2dc) {
					y = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id + 0xdf;
				} else {
					y = 0xdf;
				}
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 = fcn_0046f740(3, 3, y, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_28 = fcn_0046f740(3, 3, 0x4fc, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_1c);
				d2_CurrentWindowId = h;
				v2 = fcn_0046f100(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - 0x18, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y + 0x32, 0x60, 0x11, 0x4510, v1);
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_2c = v2;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x28c) = 0x54;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x20) = 1;
				*(int*) ((char*) g_1015f40 + v2 * 0x3cc + 0x24) = 1;
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id < 0x2dc) {
					io_AppendText(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id * 2 + 0x9a8);
				}
				*(int*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x64) = 1;
			}
			d2_CurrentWindowId = h;
			((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].state = st;
		}
		if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].state == 3) {
			if (*(unsigned char*) (lpObjektePROT + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id * 0x40 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) == 6) {
				if (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) != 0) {
					for (q = fcn_005463a0(2, 0, 0xc, 3, *(int*) (a + 1)); q != 0;
					     q = he_fn_Handlung()) {
						if (*(int*) (q + 0xb4) == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) {
							goto fnd;
						}
					}
				}
			} else {
				for (q = fcn_005463a0(2, 0, 2, 3, *(int*) (a + 1)); q != 0;
				     q = he_fn_Handlung()) {
					if (*(int*) (q + 0xb0) == *(int*) ((char*) b + 2) &&
					    *(unsigned short*) (q + 0xac) == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].item_id) {
						goto fnd;
					}
				}
			}
			*(int*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x1f4) = 0;
			goto next;
fnd:
			*(float*) (g_1015ea0 + ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].unk_24 * 0x2f4 + 0x1f4) =
				(float) fcn_00500d20(q + 0x44, (void*) &gm_GameTime) /
				(float) fcn_00500d20(q + 0x44, q + 0x52);
next:			;
		}
	}
}
unsigned char _dpad_7f3b40[960];
unsigned char _dpad_7f3f00[3328];
