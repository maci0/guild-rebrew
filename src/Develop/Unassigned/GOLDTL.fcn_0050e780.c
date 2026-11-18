


#include "Develop/Units/d2.v1/d2_dependency_node.h"

// SIZE 0x34


extern int g_85ab60;

int __cdecl fcn_0050e780(int i)
{
	int a;
	int b;
	int k;
	int n;
	int p;

	a = 0;
	b = 0;
	if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].depth != 0xffff) {
		return ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].depth;
	}
	if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a == 0) {
		return 0;
	}
	n = g_85ab60;
	for (k = 0; k < n; k++) {
		if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[k].item_id) {
			a = fcn_0050e780(k) + 1;
			break;
		}
	}
	p = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b;
	if (p == 0) {
		return a;
	}
	for (k = 0; k < n; k++) {
		if (p == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[k].item_id) {
			b = fcn_0050e780(k) + 1;
			break;
		}
	}
	return a > b ? a : b;
}
