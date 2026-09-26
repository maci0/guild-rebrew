// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} Trip;

// SIZE 0x60
typedef struct {
	int hdr[6];
	char data[0x48];
} Slot;

extern int g_67a960;
extern int g_6b805c;
extern float g_10425fc;
extern float g_104329c;
#include "client_types.h"
extern Pal_1041d20 g_1041d20[6];
extern char g_1041d80[];

// FUNCTION: GOLDTL 0x00445e40
// SIZE: 127

void __cdecl fcn_00445e40(int idx)
{
	char* dst;
	volatile int n;

	if (g_67a960 >= 0) {
		((Trip*)g_1041d20)[g_67a960].a = g_6b805c;
		((Trip*)g_1041d20)[g_67a960].b = (*(int*)&g_10425fc);
		((Trip*)g_1041d20)[g_67a960].c = (*(int*)&g_104329c);
	}
	n = 0x48;
	dst = ((Slot*)g_1041d80)[idx].data;
	/*
	 * TODO: replace this inline-asm copy with proper C once a spelling is
	 * found; no msvc6 C memcpy form emits the prelude
	 * (docs/codegen-walls.md section 6b).
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
