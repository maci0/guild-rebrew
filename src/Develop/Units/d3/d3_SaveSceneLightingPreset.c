// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} Trip;
#include "Develop/Units/d3/d3_object.h"
// SIZE 0x60
typedef struct {
	int hdr[6];
	char data[0x48];
} Slot;

extern int g_67a960;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_10425fc;
extern float g_104329c;
#include "Develop/client_types.h"
extern Pal_1041d20 g_1041d20[6];
extern char g_1041d80[];


/* ADDRESS: GOLDTL 0x00445e40 */
void __cdecl d3_SaveSceneLightingPreset(int idx)
{
	char* dst;
	int n;

	if (g_67a960 >= 0) {
		((Trip*)g_1041d20)[g_67a960].a = d3_FogColor;
		((Trip*)g_1041d20)[g_67a960].b = (*(int*)&g_10425fc);
		((Trip*)g_1041d20)[g_67a960].c = (*(int*)&g_104329c);
	}
	n = 0x48;
	dst = (char*)((D3_SCENE_SLOT*)g_1041d80)[idx].pal;
	/*
	 * TODO: replace this inline-asm copy with proper C once a spelling is
	 * found; recorded C copy probes did not emit the prelude
	 * (archived docs/codegen-walls.md section 6b).
	 */
	__asm {
		mov edi, dst
		mov esi, offset g_1041d20
		mov ebx, n
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep movsb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep movsd
	L1:
		add ecx, ebx
		rep movsb
	}
}
