#include <string.h>

/*
 * Tutorial chapter 3 task graph construction.
 *
 * Allocates 0x74-byte task nodes, clears them and fills the node header with
 * the chapter id, the name pointer, the handler entry and the layout numbers.
 * Every node owns its child slot at +0x70 (first node) or +0x58 (second node).
 *
 * Reconstructed range 0x581e20..0x581fbe: the root node and its first two
 * children. The native body continues at 0x581fbe with the rest of the graph
 * through 0x58326b; that part is not reconstructed here.
 */

#pragma optimize("y", off)

typedef struct TaskNode {
	int f[0x74 / 4];
} TaskNode;

void* __cdecl m_alloc(int, char*);

/* ADDRESS: GOLDTL 0x00581e20 */
TaskNode* __cdecl fcn_00581e20(void)
{
	TaskNode* root;
	TaskNode* n;

	root = (TaskNode*) m_alloc(0x74, (char*) 0x6a89dc);
	if (!root) {
		return 0;
	}
	memset(root, 0, 0x74);
	root->f[0] = 3;
	root->f[1] = 0x6e747233;
	root->f[2] = 0;
	root->f[3] = 0x3f72;
	root->f[4] = 0x6a8e6c;
	root->f[5] = 0;
	root->f[6] = 0;
	root->f[7] = 0;
	root->f[8] = 0;
	root->f[0xb] = -1;
	root->f[0xc] = 0x8e;
	root->f[0xd] = 0x57fd60;
	root->f[0xe] = 0;
	root->f[0x10] = 0;
	root->f[0x11] = 0;
	root->f[0x12] = 0xb;
	root->f[0x1a] = 0x5837;
	root->f[0x1b] = 0x1e00;
	root->f[0x1c] = (int) m_alloc(0x74, (char*) 0x6a8e7c);
	if (!root->f[0x1c]) {
		return 0;
	}
	n = (TaskNode*) root->f[0x1c];
	memset(n, 0, 0x74);
	n->f[0] = 3;
	n->f[1] = 0x63337331;
	n->f[2] = 2;
	n->f[3] = 0x3f74;
	n->f[4] = 0x6a8e3c;
	n->f[5] = 0x3f7a;
	n->f[6] = 0x6a8e28;
	n->f[9] = 0x3f79;
	n->f[0xa] = 0x6a8e14;
	n->f[7] = 0;
	n->f[8] = 0;
	n->f[0xb] = 0x429;
	n->f[0xc] = 0xd5;
	n->f[0xf] = 0x57ed10;
	n->f[0xd] = 0;
	n->f[0xe] = 0;
	n->f[0x10] = 0x1d;
	n->f[0x11] = 0x58c;
	n->f[0x12] = 0xb;
	n->f[0x1a] = 0x5837;
	n->f[0x1b] = 0x1e10;
	n->f[0x13] = 0;
	n->f[0x14] = 3;
	n->f[0x15] = 0;
	n->f[0x16] = (int) m_alloc(0x30, (char*) 0x6a8e50);
	return root;
}
