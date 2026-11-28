#include <string.h>

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_10404c0[32];
extern int g_10405c0;
extern int g_10405c8;
extern volatile int gm_GameTicks;
extern int g_6b8af0;

void __cdecl d3_ReleaseTexture(char* p);

/* ADDRESS: GOLDTL 0x0045c110 */
void __cdecl d3_ShutdownTextures(void)
{
	unsigned int i;
	unsigned int fill_size;
	char* p;

	p = d3_TextureBank;
	for (i = 0; i < d3_TextureBankCount; i++, p += 0x70) {
		while (*(int*) (p + 0x40) > 0) {
			d3_ReleaseTexture(p);
		}
	}
	fill_size = d3_TextureBankCount * 0x70;
	__asm {
		mov edi, d3_TextureBank
		mov ebx, fill_size
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short Lfill
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	Lfill:
		add ecx, ebx
		rep stosb
	}
	g_10405c4 = 0;
	g_10404c0[3] = 0;
	g_10404c0[2] = 0;
	g_10404c0[1] = 0;
	g_10404c0[0] = 0;
	g_10405c0 = 0;
	g_10405c8 = gm_GameTicks;
	g_6b8af0 = 0;
}
