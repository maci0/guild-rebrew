extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
extern int g_10405cc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67bd2c;

void __cdecl d3_ReleaseTexture(char* p);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0045c1e0 */
/* ADDRESS: GOLDDE 0x004511d0 */
void __cdecl d3_ReleaseAllRenderTextures(void)
{
	unsigned int i;
	char* p;

	p = d3_TextureBank;
	for (i = 0; i < d3_TextureBankCount; i++, p += 0x70) {
		while (*(int*) (p + 0x40) > 0) {
			d3_ReleaseTexture(p);
		}
	}
	m_FreeTracked(d3_TextureBank);
	d3_TextureBank = 0;
	g_10405cc = 0;
	g_10405c4 = 0;
	g_67bd2c = 0;
}
