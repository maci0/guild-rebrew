// FUNCTION: GOLD 0x00473970
// SIZE: 430

#include <string.h>

typedef struct
{
	char pad00[0x4];
	short x;
	short y;
	char pad08[0x18 - 0x8];
	int* list;
	short count;
	char pad1e[0x248 - 0x1e];
	short scroll;
	char pad24a[0x26c - 0x24a];
	int id;
	char pad270[0x27c - 0x270];
	short font;
	char pad27e[0x280 - 0x27e];
	int active;
	char pad284[0x3c4 - 0x284];
} fcn_00473970_Win;
// SIZE 0x3c4

typedef struct
{
	char pad00[0xc];
	void* owner;
	short x;
	short y;
	short w;
	short f16;
	int kind;
	short f1c;
	short f1e;
	short f20;
	short f22;
	short f24;
	char pad26[0x30 - 0x26];
	fcn_00473970_Win* parent;
	char pad34[0x40 - 0x34];
	int f40;
	char pad44[0x74 - 0x44];
	short font;
	char pad76[0x80 - 0x76];
	char text[0x2ec - 0x80];
} fcn_00473970_Ent;
// SIZE 0x2ec

extern fcn_00473970_Win g_00f8f120[]; /* 0x00f8f120 */
extern fcn_00473970_Ent* g_00f8f080; /* 0x00f8f080 */
extern short g_00f8f084; /* 0x00f8f084 */
extern short g_00fb9070; /* 0x00fb9070 */
extern short g_00fb9072; /* 0x00fb9072 */
extern short g_005fe73c; /* 0x005fe73c */
extern char s_005fe7ac[]; /* 0x005fe7ac */

void __cdecl fcn_004222b0(const char* msg);
int __cdecl fcn_0046c9e0(void);
int __cdecl fcn_0046ea00(char* s, int font);
void __cdecl fcn_004730d0(int slot, fcn_00473970_Win* parent);

int __cdecl fcn_00473970(int x, int y, char* text, int win)
{
	fcn_00473970_Win* w;
	int id;

	w = &g_00f8f120[win];
	if (w->active == 0) {
		return -1;
	}
	if (w->count >= 0x180) {
		fcn_004222b0(s_005fe7ac);
		return -1;
	}
	id = fcn_0046c9e0();
	strcpy(g_00f8f080[id].text, text);
	if (w->font != 0) {
		g_00f8f080[id].font = w->font;
	} else {
		g_00f8f080[id].font = g_005fe73c;
	}
	g_00f8f080[id].kind = 0x46;
	g_00f8f080[id].x = w->x + x;
	g_00f8f080[id].y = w->y - w->scroll + y;
	g_00f8f080[id].w = fcn_0046ea00(text, g_00f8f080[id].font) + 0x60;
	g_00f8f080[id].f16 = g_00f8f084;
	g_00f8f080[id].f1c = 2;
	g_00f8f080[id].parent = w;
	g_00f8f080[id].owner = w;
	g_00f8f080[id].f22 = 0;
	g_00f8f080[id].f24 = g_00fb9070;
	g_00f8f080[id].f1e = 0;
	g_00f8f080[id].f20 = g_00fb9072;
	g_00f8f080[id].f40 = g_00f8f080[w->id].f40;
	fcn_004730d0(id, w);
	w->list[w->count] = id;
	w->count++;
	return id;
}
