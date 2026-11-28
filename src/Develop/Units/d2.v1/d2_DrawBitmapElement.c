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

extern char* d2_Controls;

void* __cdecl d2_QueueTexturedQuad(int x, int y, int w, int h, int a5, Rect4* r);
void __cdecl d2_SetQuadVertexColor(void* p, int r, int g, int b);

/* ADDRESS: GOLDTL 0x00469320 */
void __cdecl d2_DrawBitmapElement(int slot)
{
	Rect4 rc;
	void* p;

	rc.left = 0;
	rc.right = *(int*) (((Slot*)d2_Controls)[slot].surf + 0x54);
	rc.top = 0;
	rc.bottom = *(int*) (((Slot*)d2_Controls)[slot].surf + 0x58);
	p = d2_QueueTexturedQuad(((Slot*)d2_Controls)[slot].x, ((Slot*)d2_Controls)[slot].y, ((Slot*)d2_Controls)[slot].w, ((Slot*)d2_Controls)[slot].h,
		*(int*) (((Slot*)d2_Controls)[slot].surf + 0x20), &rc);
	if (p) {
		d2_SetQuadVertexColor(p, 0xff, 0xff, 0xff);
	}
}
