#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int d2_CurrentWindowId;

#include "Develop/Units/Error/error_message.h"
void __cdecl d2_ClearSurface(int a);
typedef struct Win {
	int pad0;
	int left;
	int x;
	short h;
	short pad0e;
	int margin;
	unsigned char flags;
	char pad15[0x28 - 0x15];
	int* children;
	int count;
	char pad30[0x38 - 0x30];
	int surface;
	char* text;
	char pad40[0x254 - 0x40];
	int view;
	int base;
	int sel;
	int off;
	int pos;
	int scroll;
	char pad26c[0x290 - 0x26c];
	int used;
	char pad294[0x3a0 - 0x294];
	void* tex;
	float alpha;
	char pad3a8[0x3b8 - 0x3a8];
	int hot[3];
	char pad3c4[0x3cc - 0x3c4];
} Win;

extern char s_67d844[];
extern char s_67d818[];

void __cdecl d2_ClearSurfaceRect(int a, int b, int c, int d, int e);
typedef struct
{
	int i[0x3cc / 4];
} D2_PAINTBOX_WIN;

extern int d2_ResourceOffset;
extern char s_67d890[];
extern char s_67d868[];

int __cdecl d2_GetResourceData(int id);
void __cdecl d2_LockSurface(int surf);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, int src, int mode);
void __cdecl d2_UnlockSurface(int surf);

/* ADDRESS: GOLDTL 0x00472e50 */
void __cdecl d2_ClearPaintbox(void)
{
	char* m;

	m = ((char*)g_1015f40) + d2_CurrentWindowId * 0x3cc;
	if (*(int*) (m + 0x290) == 0) {
		ReportClientMessage((const char*) 0x67d844);
		return;
	}
	if (*(int*) (m + 0x38) == 0) {
		ReportClientMessage((const char*) 0x67d818);
		return;
	}
	d2_ClearSurface(*(int*) (m + 0x38));
}

/* ADDRESS: GOLDTL 0x00472ea0 */
void __cdecl d2_ClearPaintboxRect(int a, int b, int c, int d)
{
	Win* w;

	w = &((Win*)g_1015f40)[d2_CurrentWindowId];
	if (!w->used) {
		ReportClientMessage(s_67d844);
		return;
	}
	if (!w->surface) {
		ReportClientMessage(s_67d818);
		return;
	}
	d2_ClearSurfaceRect(a, b, c, d, w->surface);
}

/* ADDRESS: GOLDTL 0x00472f10 */
void __cdecl d2_DrawShape(int x, int y, int id)
{
	D2_PAINTBOX_WIN* w;
	int src;

	w = &((D2_PAINTBOX_WIN*)g_1015f40)[d2_CurrentWindowId];
	if (w->i[0x290 / 4] == 0) {
		ReportClientMessage(s_67d890);
		return;
	}
	if (w->i[0x38 / 4] == 0) {
		ReportClientMessage(s_67d868);
		return;
	}
	src = d2_GetResourceData(id);
	if (src != 0) {
		d2_LockSurface(w->i[0x38 / 4]);
		d2_DrawSpriteFromSet(x, y, w->i[0x38 / 4], src, d2_ResourceOffset);
		d2_UnlockSurface(w->i[0x38 / 4]);
	}
}
