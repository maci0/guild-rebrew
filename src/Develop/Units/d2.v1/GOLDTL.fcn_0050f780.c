

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int width;
	int height;
	char pad14[0x3cc - 0x14];
} Slot;

// SIZE 0x2bc
typedef struct {
	int owner;
	char pad4[0x2bc - 4];
} Item;

// SIZE 0x34
#include "Develop/Units/d2.v1/d2_dependency_node.h"









extern int g_7f4c10;
extern volatile int g_6b7fac;
extern int g_7f3ee8;
extern Item g_1038150[];
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char g_699a9c[];
extern int g_85ab60;


int __cdecl fcn_00470820(int a, int b, int c);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_AppendText(char* fmt, int a, int b);
int __cdecl d2_BuildDependencyDiagram(unsigned char* a, unsigned short* b, int w, int h);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_0050ee80(unsigned char* a, unsigned short* b);
void __cdecl fcn_0050f750(int a, int b, int c, int d);

int __cdecl d2_OpenDependencyDiagram(int arg, unsigned char* a, unsigned short* b)
{
	Slot* s;
	int i;
	int j;

	g_7f4c10 = fcn_00470820(0, 0, arg);
	d2_CenterDialogWindows(g_7f4c10);
	g_7f3ee8 = g_6b7fac;
	s = &((Slot*)g_1015f40)[g_1038150[g_7f4c10].owner];
	d2_SetForm(0, 1);
	if (*b == 0xfd) {
		io_AppendText(g_699a9c, 0x19, *a * 14 + 0x48e);
	} else {
		io_AppendText(g_699a9c, 0x19, *b * 2 + 0x9a8);
	}
	d2_SetForm(0, 3);
	if (d2_BuildDependencyDiagram(a, b, s->width, s->height)) {
		fcn_00471e30(g_7f4c10);
		return -1;
	}
	fcn_0050ee80(a, b);
	for (i = 0; i < g_85ab60; i++) {
		for (j = 0; j < i; j++) {
			if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a) {
				fcn_0050f750(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].x + 0x18, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].y + 0x30, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x + 0x18,
					     ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y + 0x18);
			} else if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b) {
				fcn_0050f750(((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].x + 0x18, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].y + 0x30, ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x + 0x18,
					     ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y + 0x18);
			}
		}
	}
	return g_7f4c10;
}
