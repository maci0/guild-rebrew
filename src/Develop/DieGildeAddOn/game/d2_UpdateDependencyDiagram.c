#include "game_data.h"
#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7f4c10;
#include "Develop/Units/d2.v1/d2_dependency_node.h"
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"

















int __cdecl gm_QueryEntities(int, int, ...);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_CloseWindow(int);
int __cdecl io_AppendText();
int __cdecl gm_GetElapsedMinutes(void*, void*);

/* ADDRESS: GOLDTL 0x0050ee80 */
/* ADDRESS: GOLDDE 0x004f9bc0 */
void __cdecl d2_UpdateDependencyDiagram(unsigned char* a, unsigned short* b)
{
	DEPENDENCY_DIAGRAM_NODE* p;
	char* q;
	int i;
	int st;
	int n;
	int v1;
	int windowId;
	int h;
	int y;
	int k;

	i = 0;
	v1 = *(int*) (0x1038150 + g_7f4c10 * 0x2bc);
	for (; i < g_85ab60; i++) {
		st = 0;
		if (((OBJECT_PROTOTYPE *)lpObjektePROT)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id].kind == 6) {
			if (gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) != 0) {
				st = 1;
				for (q = he_StartHandlungSearch(2, 0, 0xc, 3, *(int*) (a + 1)); q != 0;
				     q = he_fn_Handlung()) {
					if (*(int*) (q + 0xb4) == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) {
						goto set_st3;
					}
				}
			} else {
				n = 0;
				if (i > 0) {
					p = (DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes;
					for (k = i; k != 0; p++, k--) {
						if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_a &&
						    (gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
						     gm_QueryEntities(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0) &&
						    *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[p->unk_24].value_060)) == 0) {
							n++;
						} else if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_b &&
							   (gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
							    gm_QueryEntities(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0) &&
							   *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[p->unk_24].value_060)) == 0) {
							n++;
						}
					}
				}
				if ((n == 0 && ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_a == 0) ||
				    (n == 1 && ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_b == 0) ||
				    n == 2) {
					st = 2;
				}
			}
		} else {
			if (gm_QueryEntities(*(int*) ((char*) b + 0x14), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) != 0) {
				st = 1;
			} else if (*(unsigned short*) b != 0xfd ||
				   gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) == 0) {
				n = 0;
				if (i > 0) {
					p = (DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes;
					for (k = i; k != 0; p++, k--) {
						if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_a &&
						    (gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
						     gm_QueryEntities(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0)) {
							n++;
						} else if (p->item_id == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_b &&
							   (gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, p->item_id) != 0 ||
							    gm_QueryEntities(*(int*) ((char*) b + 0x14), 1, 0, p->item_id) != 0)) {
							n++;
						}
					}
				}
				if ((n == 0 && ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_a == 0) ||
				    (n == 1 && ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].parent_b == 0) ||
				    n == 2) {
					st = 2;
					for (q = he_StartHandlungSearch(2, 0, 2, 3, *(int*) (a + 1)); q != 0;
					     q = he_fn_Handlung()) {
						if (*(int*) (q + 0xb0) == *(int*) ((char*) b + 2) &&
						    *(unsigned short*) (q + 0xac) == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) {
							goto set_st3;
						}
					}
				}
			} else {
				st = 1;
			}
		}
		goto skip_st3;
set_st3:
		st = 3;
skip_st3:
		if (st != ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].state) {
			if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c != -1) {
				d2_CloseWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c = -1;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_20 = -1;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24 = -1;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_28 = -1;
			}
			if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_2c != -1) {
				d2_CloseWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_2c);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_2c = -1;
			}
			h = d2_CurrentWindowId;
			if (st == 0) {
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c = windowId;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_20 = d2_AddElementToWindow(0, 0, 0x52b, windowId);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24 = d2_AddElementToWindow(3, 3, 0x4fb, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c);
			} else if (st == 1) {
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c = windowId;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_20 = d2_AddElementToWindow(0, 0, 0x529, windowId);
				if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id < 0x2dc) {
					y = ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id + 0xdf;
				} else {
					y = 0xdf;
				}
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24 = d2_AddElementToWindow(3, 3, y, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c);
				*(int*) (&((D2_CONTROL_TL*)d2_Controls)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24].value_064) = 1;
				*(int*) (&((D2_CONTROL_TL*)d2_Controls)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24].value_05c) = 1;
				d2_CurrentWindowId = h;
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 0x18, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y + 0x32, 0x60, 0x11, 0x4510, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_2c = windowId;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x28c) = 0x54;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x20) = 1;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x24) = 1;
				if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id < 0x2dc) {
					io_AppendText(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id * 2 + 0x9a8);
				}
			} else if (st == 2) {
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c = windowId;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_20 = d2_AddElementToWindow(0, 0, 0x52a, windowId);
				if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id < 0x2dc) {
					y = ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id + 0xdf;
				} else {
					y = 0xdf;
				}
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24 = d2_AddElementToWindow(3, 3, y, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c);
				*(int*) (&((D2_CONTROL_TL*)d2_Controls)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24].value_05c) = 1;
				d2_CurrentWindowId = h;
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 0x18, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y + 0x32, 0x60, 0x11, 0x4510, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_2c = windowId;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x28c) = 0x54;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x20) = 1;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x24) = 1;
				if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id < 0x2dc) {
					io_AppendText(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id * 2 + 0x9a8);
				}
			} else {
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 4, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y - 4, 0x36, 0x36, 0x400, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c = windowId;
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_20 = d2_AddElementToWindow(0, 0, 0x529, windowId);
				if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id < 0x2dc) {
					y = ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id + 0xdf;
				} else {
					y = 0xdf;
				}
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24 = d2_AddElementToWindow(3, 3, y, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_28 = d2_AddElementToWindow(3, 3, 0x4fc, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_1c);
				d2_CurrentWindowId = h;
				windowId = d2_CreateChildWindow(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].x - 0x18, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].y + 0x32, 0x60, 0x11, 0x4510, v1);
				((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_2c = windowId;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x28c) = 0x54;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x20) = 1;
				*(int*) ((char*) d2_Windows + windowId * 0x3cc + 0x24) = 1;
				if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id < 0x2dc) {
					io_AppendText(((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id * 2 + 0x9a8);
				}
				*(int*) (&((D2_CONTROL_TL*)d2_Controls)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24].value_064) = 1;
			}
			d2_CurrentWindowId = h;
			((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].state = st;
		}
		if (((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].state == 3) {
			if (((OBJECT_PROTOTYPE *)lpObjektePROT)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id].kind == 6) {
				if (gm_QueryEntities(*(int*) (a + 0x5d), 1, 0, ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) != 0) {
					for (q = he_StartHandlungSearch(2, 0, 0xc, 3, *(int*) (a + 1)); q != 0;
					     q = he_fn_Handlung()) {
						if (*(int*) (q + 0xb4) == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) {
							goto fnd;
						}
					}
				}
			} else {
				for (q = he_StartHandlungSearch(2, 0, 2, 3, *(int*) (a + 1)); q != 0;
				     q = he_fn_Handlung()) {
					if (*(int*) (q + 0xb0) == *(int*) ((char*) b + 2) &&
					    *(unsigned short*) (q + 0xac) == ((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].item_id) {
						goto fnd;
					}
				}
			}
			*(int*) (&((D2_CONTROL_TL*)d2_Controls)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24].value_1f4) = 0;
			goto next;
fnd:
			*(float*) (&((D2_CONTROL_TL*)d2_Controls)[((DEPENDENCY_DIAGRAM_NODE*)d2_DependencyDiagramNodes)[i].unk_24].value_1f4) =
				(float) gm_GetElapsedMinutes(q + 0x44, (void*) &gm_GameTime) /
				(float) gm_GetElapsedMinutes(q + 0x44, q + 0x52);
next:			;
		}
	}
}
unsigned char _dpad_7f3b40[960];
unsigned char _dpad_7f3f00[3328];
