// FUNCTION: GOLDTL 0x472960
// SIZE: 705

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x24];
	void* surf;
	char pad3c[0x290 - 0x3c];
	int active;
	char pad294[0x3cc - 0x294];
} Win472960;

extern Win472960 g_1015f40[];
extern int g_772514;
extern int g_772558;

void __cdecl fcn_0041d9e0(char*);
void __cdecl fcn_00475fd0(void*);
int __cdecl fcn_00476b10(int x, int y, unsigned char r, unsigned char g, unsigned char b, void* s);
void __cdecl fcn_00476060(void*);

void __cdecl fcn_00472960(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	Win472960* w;

	w = &g_1015f40[g_772514];
	if (w->active == 0) {
		return;
	}
	if (w->surf == 0) {
		fcn_0041d9e0("d2_Plot:Window is not a paintbox!");
		return;
	}
	if (x < (unsigned char) g_772558 || x > w->w - (unsigned char) g_772558
	    || y < (unsigned char) g_772558 || y > w->h - (unsigned char) g_772558) {
		return;
	}
	fcn_00475fd0(w->surf);
	switch ((unsigned char) g_772558) {
	case 0:
		fcn_00476b10(x, y, r, g, b, w->surf);
		break;
	case 1:
		fcn_00476b10(x - 1, y, r, g, b, w->surf);
		fcn_00476b10(x + 1, y, r, g, b, w->surf);
		fcn_00476b10(x, y + 1, r, g, b, w->surf);
		fcn_00476b10(x, y - 1, r, g, b, w->surf);
		fcn_00476b10(x, y, r, g, b, w->surf);
		break;
	case 2:
		fcn_00476b10(x - 1, y, r, g, b, w->surf);
		fcn_00476b10(x + 1, y, r, g, b, w->surf);
		fcn_00476b10(x - 2, y, r, g, b, w->surf);
		fcn_00476b10(x + 2, y, r, g, b, w->surf);
		fcn_00476b10(x, y, r, g, b, w->surf);
		fcn_00476b10(x, y + 1, r, g, b, w->surf);
		fcn_00476b10(x, y - 1, r, g, b, w->surf);
		fcn_00476b10(x, y + 2, r, g, b, w->surf);
		fcn_00476b10(x, y - 2, r, g, b, w->surf);
		fcn_00476b10(x + 1, y + 1, r, g, b, w->surf);
		fcn_00476b10(x - 1, y - 1, r, g, b, w->surf);
		fcn_00476b10(x - 1, y + 1, r, g, b, w->surf);
		fcn_00476b10(x + 1, y - 1, r, g, b, w->surf);
		break;
	}
	fcn_00476060(w->surf);
}
