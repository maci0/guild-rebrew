#include <stdlib.h>

typedef struct VfsNode {
	char pad0[0x100];
	int count;
	void* base;
	struct VfsNode* next;
	struct VfsNode* child;
	char pad110[8];
	char flag;
} VfsNode;
/* SIZE 0x119 */

extern char g_6b7fe8;

int __cdecl fcn_0042e680(const void*, const void*);
int __cdecl fcn_0042e640(const void*, const void*);

/* ADDRESS: GOLDTL 0x0042e690 */
void* __cdecl fcn_0042e690(char* name, VfsNode* node, VfsNode** found, char recurse)
{
	VfsNode* hit;
	VfsNode* child;

	if (name == 0 || *name == 0 || node == 0) {
		return 0;
	}
	if (node->count > 0 && node->flag != 0) {
		hit = bsearch(name, node->base, node->count, 0x18,
		              g_6b7fe8 != 0 ? fcn_0042e680 : fcn_0042e640);
		if (hit != 0) {
			*found = node;
			return hit;
		}
	}
	if (recurse != 0) {
		for (child = node->child; child != 0; child = child->next) {
			hit = fcn_0042e690(name, child, found, 1);
			if (hit != 0) {
				return hit;
			}
		}
	}
	return 0;
}
