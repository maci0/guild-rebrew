typedef struct DirtyRect {
	int x;
	int y;
	void* owner;
	int w;
	int h;
} DirtyRect;
// SIZE 0x14

extern int g_67d964;
extern int g_67d968;
extern int g_7725f8;
extern int g_7725fc;
extern DirtyRect* g_772588;

// FUNCTION: GOLDTL 0x465ff0
void __cdecl fcn_00465ff0(int x, int y, int w, int h, char* owner)
{
	int i;

	if (*(int*) (owner + 0x190) == 0 || owner + 0x1ac == 0) {
		return;
	}
	if (x > g_67d964) {
		x = g_67d964;
	}
	if (x & 1) {
		x--;
		w = (w + 2) & ~1;
	}
	if (y + h > g_67d968) {
		h = g_67d968 - y;
	}
	if (x + w > g_67d964) {
		w = g_67d964 - x;
	}
	if (y < g_7725fc) {
		y = g_7725fc;
	}
	if (x < g_7725f8) {
		x = g_7725f8;
	}
	if (w < 0) {
		w = 1;
	}
	if (h < 0) {
		h = 1;
	}
	for (i = 0; g_772588[i].owner != 0 && i < 0x400; i++) {
	}
	if (i < 0x400) {
		g_772588[i].x = x;
		g_772588[i].y = y;
		g_772588[i].w = w;
		g_772588[i].h = h;
		g_772588[i].owner = owner;
	}
}
