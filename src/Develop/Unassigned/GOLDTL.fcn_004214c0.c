/* Bidirectional path search: seeds the start and goal nodes, then alternates
   expansion steps (0x421ba0) until one side reaches the other's node. */

/* SIZE 0x1c */
typedef struct PathNode {
	int type;
	short mark;
	short pad06;
	float f;
	float g;
	float h;
	unsigned char flags;
	unsigned char pad15;
	unsigned short f16;
	unsigned short f18;
	unsigned short parent;
} PathNode;

typedef struct PathGrid {
	char pad00[0x20];
	int width;
	PathNode* nodes;
} PathGrid;

unsigned short __cdecl fcn_00421ba0(PathGrid* grid, unsigned short node);
void __cdecl fcn_00421f10(PathGrid* grid, unsigned short node);

/* ADDRESS: GOLDTL 0x004214c0 */
unsigned short __cdecl fcn_004214c0(PathGrid* grid, int x, int y, int goal_x, int goal_y, int kind)
{
	int t;
	int i;
	int level;
	unsigned short node;
	unsigned short goal;
	float* costs;

	level = 0;
	*(int*) 0x678c0c = level;
	*(int*) 0x678c08 = grid->width - 1;
	for (t = grid->width >> 1; t != 0; t >>= 1) {
		level++;
	}
	*(int*) 0x678c0c = level;
	((short*) 0x678c20)[0] = 0;
	((short*) 0x678c20)[1] = -(short) grid->width;
	((short*) 0x678c20)[2] = 0;
	((short*) 0x678c20)[3] = (short) grid->width;
	((short*) 0x678c20)[4] = -(short) grid->width;
	((short*) 0x678c20)[5] = -(short) grid->width;
	((short*) 0x678c20)[6] = (short) grid->width;
	((short*) 0x678c20)[7] = (short) grid->width;
	*(short*) 0x14cbc70 = 0;
	node = (y << level) + x;
	*(unsigned short*) 0x14cbc76 = node;
	*(unsigned short*) 0x14cbc74 = (goal_y << level) + goal_x;
	++*(short*) 0x14cbc72;
	grid->nodes[node].mark = *(short*) 0x14cbc72;
	grid->nodes[node].g = 0;
	grid->nodes[node].h = 0;
	grid->nodes[node].f = grid->nodes[node].h + grid->nodes[node].g;
	grid->nodes[node].flags = 5;
	grid->nodes[node].f16 = 0xffff;
	grid->nodes[node].f18 = 0xffff;
	grid->nodes[node].parent = 0xffff;
	if (*(unsigned short*) 0x14cbc76 == *(unsigned short*) 0x14cbc74) {
		return node;
	}
	goal = *(unsigned short*) 0x14cbc74;
	grid->nodes[goal].mark = *(short*) 0x14cbc72;
	grid->nodes[goal].g = 0;
	grid->nodes[goal].h = 0;
	grid->nodes[goal].f = grid->nodes[goal].h + grid->nodes[goal].g;
	grid->nodes[goal].flags = 9;
	grid->nodes[goal].f16 = 0xffff;
	grid->nodes[goal].f18 = 0xffff;
	grid->nodes[goal].parent = 0xffff;
	*(float*) 0x14cbc6c = ((float*) 0x678db8)[kind];
	*(float*) 0x14cbc78 = ((float*) 0x678dd0)[kind];
	costs = (float*) 0x678c50 + kind * 15;
	*(float**) 0x14cbc64 = costs;
	if (costs[grid->nodes[node].type] < 0.0 || costs[grid->nodes[goal].type] < 0.0) {
		return 0xffff;
	}
	*(float*) 0x14cbc80 = 0;
	for (i = 1; i < 15; i++) {
		if (costs[i] > 0.0) {
			*(float*) 0x14cbc80 += costs[i];
		}
	}
	*(float*) 0x14cbc80 = 7.0f;
	*(unsigned short*) 0x14cbc7c = *(unsigned short*) 0x14cbc74;
	*(unsigned char*) 0x14cbc60 = 4;
	*(unsigned char*) 0x14cbc68 = 8;
	node = fcn_00421ba0(grid, node);
	if (node == 0xffff) {
		return 0xffff;
	}
	for (;;) {
		if (node == *(unsigned short*) 0x14cbc74) {
			fcn_00421f10(grid, node);
			return *(unsigned short*) 0x14cbc76;
		}
		if ((grid->nodes[node].flags & 0xc) == 0xc) {
			fcn_00421f10(grid, node);
			grid->nodes[node].parent = *(unsigned short*) 0x14cbc7e;
			return *(unsigned short*) 0x14cbc76;
		}
		*(unsigned short*) 0x14cbc7c = *(unsigned short*) 0x14cbc76;
		*(unsigned char*) 0x14cbc60 = 8;
		*(unsigned char*) 0x14cbc68 = 4;
		goal = fcn_00421ba0(grid, *(unsigned short*) 0x14cbc74);
		if (goal == 0xffff) {
			return 0xffff;
		}
		if (goal == *(unsigned short*) 0x14cbc76) {
			return *(unsigned short*) 0x14cbc76;
		}
		if ((grid->nodes[goal].flags & 0xc) == 0xc) {
			fcn_00421f10(grid, *(unsigned short*) 0x14cbc7e);
			grid->nodes[*(unsigned short*) 0x14cbc7e].parent = goal;
			return *(unsigned short*) 0x14cbc76;
		}
		++*(short*) 0x14cbc70;
		*(unsigned short*) 0x14cbc7c = *(unsigned short*) 0x14cbc74;
		*(unsigned char*) 0x14cbc60 = 4;
		*(unsigned char*) 0x14cbc68 = 8;
		node = fcn_00421ba0(grid, node);
		if (node == 0xffff) {
			return 0xffff;
		}
	}
}
