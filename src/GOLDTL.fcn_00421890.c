// FUNCTION: GOLDTL 0x00421890
// SIZE: 779
// Path search setup: seeds the start and goal nodes of the grid and runs the
// expansion step (0x421ba0) until it reaches the goal or runs out.

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

extern int g_678c08;
extern int g_678c0c;
extern short g_678c20[8];
extern float g_678c50[][15];
extern float g_678db8[];
extern float g_678dd0[];
extern unsigned char g_14cbc60;
extern float* g_14cbc64;
extern unsigned char g_14cbc68;
extern float g_14cbc6c;
extern short g_14cbc70;
extern short g_14cbc72;
extern unsigned short g_14cbc74;
extern unsigned short g_14cbc76;
extern float g_14cbc78;
extern unsigned short g_14cbc7c;
extern unsigned short g_14cbc7e;
extern float g_14cbc80;

unsigned short __cdecl fcn_00421ba0(PathGrid* grid, unsigned short node);
void __cdecl fcn_00421f10(PathGrid* grid, unsigned short node);

unsigned short __cdecl fcn_00421890(PathGrid* grid, int x, int y, int goal_x, int goal_y, int kind)
{
	int t;
	int i;
	unsigned short goal;
	unsigned short node;
	float* costs;

	g_678c0c = 0;
	g_678c08 = grid->width - 1;
	for (t = grid->width >> 1; t != 0; t >>= 1) {
		g_678c0c++;
	}
	g_678c20[0] = 0;
	g_678c20[1] = -(short) grid->width;
	g_678c20[2] = 0;
	g_678c20[3] = (short) grid->width;
	g_678c20[4] = -(short) grid->width;
	g_678c20[5] = -(short) grid->width;
	g_678c20[6] = (short) grid->width;
	g_678c20[7] = (short) grid->width;
	g_14cbc70 = 0;
	node = (y << g_678c0c) + x;
	g_14cbc76 = node;
	g_14cbc74 = (goal_y << g_678c0c) + goal_x;
	g_14cbc72++;
	grid->nodes[node].mark = g_14cbc72;
	grid->nodes[node].g = 0;
	grid->nodes[node].h = 0;
	grid->nodes[node].f = grid->nodes[node].h + grid->nodes[node].g;
	grid->nodes[node].flags = 5;
	grid->nodes[node].f16 = 0xffff;
	grid->nodes[node].f18 = 0xffff;
	grid->nodes[node].parent = 0xffff;
	if (g_14cbc76 == g_14cbc74) {
		return node;
	}
	goal = g_14cbc74;
	grid->nodes[goal].mark = g_14cbc72;
	grid->nodes[goal].g = 0;
	grid->nodes[goal].h = 0;
	grid->nodes[goal].f = grid->nodes[goal].h + grid->nodes[goal].g;
	grid->nodes[goal].flags = 9;
	grid->nodes[goal].f16 = 0xffff;
	grid->nodes[goal].f18 = 0xffff;
	grid->nodes[goal].parent = 0xffff;
	g_14cbc6c = g_678db8[kind];
	g_14cbc78 = g_678dd0[kind];
	costs = g_678c50[kind];
	g_14cbc64 = costs;
	if (costs[grid->nodes[node].type] < 0.0 || costs[grid->nodes[goal].type] < 0.0) {
		return 0xffff;
	}
	g_14cbc80 = 0;
	for (i = 1; i < 15; i++) {
		if (costs[i] > 0.0) {
			g_14cbc80 += costs[i];
		}
	}
	g_14cbc80 = 7.0f;
	g_14cbc7c = g_14cbc74;
	g_14cbc60 = 4;
	g_14cbc68 = 8;
	node = fcn_00421ba0(grid, node);
	while (node != 0xffff) {
		if (node == g_14cbc74) {
			fcn_00421f10(grid, node);
			return g_14cbc76;
		}
		if ((grid->nodes[node].flags & 0xc) == 0xc) {
			fcn_00421f10(grid, node);
			grid->nodes[node].parent = g_14cbc7e;
			return g_14cbc76;
		}
		g_14cbc70++;
		g_14cbc7c = g_14cbc74;
		g_14cbc60 = 4;
		g_14cbc68 = 8;
		node = fcn_00421ba0(grid, node);
	}
	return 0xffff;
}
