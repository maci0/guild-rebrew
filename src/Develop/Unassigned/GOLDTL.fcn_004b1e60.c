typedef struct Pair {
	int a;
	int b;
} Pair;

typedef struct Slot {
	int x0;
	Pair p[4];
	char pad24[0x20];
} Slot;
// SIZE 0x44

typedef struct Text {
	char name[0x60];
	int x60;
	int x64;
	int x68;
	char pad6c[8];
} Text;
// SIZE 0x74

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;
extern char g_868060[];
extern int g_67fca4;
extern int g_67fcb0;
extern char g_7728d4;

int __cdecl sprintf(char* buf, const char* fmt, ...);
int __cdecl txt_FindTextBank(const char* name);
int __cdecl txt_ReloadTextFile(const char* name);

/* ADDRESS: GOLDTL 0x004b1e60 */
void __cdecl hst_LoadHistoryText(void)
{
	char buf[0x40];
	int n;
	int i;
	int j;

	for (i = 0; i < 4; i++) {
		((Slot*)g_1007bc0)[i].x0 = 0;
		for (j = 0; j < 4; j++) {
			((Slot*)g_1007bc0)[i].p[j].a = -1;
			((Slot*)g_1007bc0)[i].p[j].b = 0xffff;
		}
	}
	hst_HistoryTextBase = -1;
	g_67fca4 = -1;
	sprintf(buf, "historie\\text_H_%s", ((char(*)[0x2f4])g_868060)[g_773d75]);
	if (((Text*)txt_TextBanks)[txt_FindTextBank(buf)].x68 == 0 && txt_ReloadTextFile(buf) == 0) {
		g_7728d4 = 0;
		return;
	}
	i = txt_FindTextBank(buf);
	n = 0x10;
	hst_HistoryTextBase = ((Text*)txt_TextBanks)[i].x60;
	g_67fca4 = ((Text*)txt_TextBanks)[i].x64;
	g_67fca8 = ((Text*)txt_TextBanks)[i].x60;
	/* block-fill prelude, see docs/codegen-walls.md section 6b */
	__asm {
		mov edi, offset g_1007ba0
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	g_67fcac = -1;
	g_67fcb0 = -1;
}
