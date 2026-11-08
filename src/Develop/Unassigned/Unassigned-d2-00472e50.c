#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_772514;

#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_00476970(int a);
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

void __cdecl fcn_004772e0(int a, int b, int c, int d, int e);
typedef struct
{
	int i[0x3cc / 4];
} fcn_00472f10_Win;

extern int g_772568;
extern char s_67d890[];
extern char s_67d868[];

int __cdecl d2_GetResourceData(int id);
void __cdecl fcn_00475fd0(int surf);
void __cdecl fcn_0047cba0(int x, int y, int surf, int src, int mode);
void __cdecl fcn_00476060(int surf);

/* ADDRESS: GOLDTL 0x00472e50 */
void __cdecl fcn_00472e50(void)
{
	char* m;

	m = ((char*)g_1015f40) + g_772514 * 0x3cc;
	if (*(int*) (m + 0x290) == 0) {
		ReportClientMessage((const char*) 0x67d844);
		return;
	}
	if (*(int*) (m + 0x38) == 0) {
		ReportClientMessage((const char*) 0x67d818);
		return;
	}
	fcn_00476970(*(int*) (m + 0x38));
}

/* ADDRESS: GOLDTL 0x00472ea0 */
void __cdecl fcn_00472ea0(int a, int b, int c, int d)
{
	Win* w;

	w = &((Win*)g_1015f40)[g_772514];
	if (!w->used) {
		ReportClientMessage(s_67d844);
		return;
	}
	if (!w->surface) {
		ReportClientMessage(s_67d818);
		return;
	}
	fcn_004772e0(a, b, c, d, w->surface);
}

/* ADDRESS: GOLDTL 0x00472f10 */
void __cdecl d2_DrawShape(int x, int y, int id)
{
	fcn_00472f10_Win* w;
	int src;

	w = &((fcn_00472f10_Win*)g_1015f40)[g_772514];
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
		fcn_00475fd0(w->i[0x38 / 4]);
		fcn_0047cba0(x, y, w->i[0x38 / 4], src, g_772568);
		fcn_00476060(w->i[0x38 / 4]);
	}
}
