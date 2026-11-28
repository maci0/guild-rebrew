

#include <string.h>

extern int g_10405cc;
extern unsigned int d3_TextureBankCount;
extern int g_67bd2c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* d3_TextureBank;
extern int g_10404c0[32];
extern int g_10405c0;
extern int g_1040540[32];
extern int g_10405c8;
extern volatile int gm_GameTicks;
extern char g_67bd38[];

void* __cdecl m_alloc(int, void*);

void __cdecl d3_InitTextures(unsigned int n, int levels)
{
	g_10405cc = 0;
	d3_TextureBankCount = n;
	g_67bd2c = levels;
	g_10405c4 = 0;
	(*(void**)&d3_TextureBank) = m_alloc(n * 0x70, g_67bd38);
	memset(g_10404c0, 0, sizeof(g_10404c0));
	g_10405c0 = 0;
	memset(g_1040540, 0, sizeof(g_1040540));
	g_10405c8 = gm_GameTicks;
}
