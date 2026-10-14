typedef struct Slot {
	char pad0[0x10];
	int x;
	int y;
	int w;
	int h;
	char pad20[0x8c - 0x20];
	char* surf;
	char pad90[0x2f4 - 0x90];
} Slot;
// SIZE 0x2f4

typedef struct Rect4 {
	int left;
	int top;
	int right;
	int bottom;
} Rect4;
// SIZE 0x10

extern char* g_1015ea0;

void* __cdecl fcn_0047bf80(int x, int y, int w, int h, int a5, Rect4* r);
void __cdecl fcn_0047b9a0(void* p, int r, int g, int b);

/* ADDRESS: GOLDTL 0x00469320 */
void __cdecl fcn_00469320(int slot)
{
	Rect4 rc;
	void* p;

	rc.left = 0;
	rc.right = *(int*) (((Slot*)g_1015ea0)[slot].surf + 0x54);
	rc.top = 0;
	rc.bottom = *(int*) (((Slot*)g_1015ea0)[slot].surf + 0x58);
	p = fcn_0047bf80(((Slot*)g_1015ea0)[slot].x, ((Slot*)g_1015ea0)[slot].y, ((Slot*)g_1015ea0)[slot].w, ((Slot*)g_1015ea0)[slot].h, *(int*) (((Slot*)g_1015ea0)[slot].surf + 0x20), &rc);
	if (p) {
		fcn_0047b9a0(p, 0xff, 0xff, 0xff);
	}
}
