/* GOLD twin of GOLDTL fcn_0045c290: the texture slot is 0x80 bytes here,
 * 0x70 in GOLDTL. */

/* SIZE 0x4 */
typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col;

#if defined(REBREW_GOLD)
#include "tex_slot.h"

extern TexSlot* g_fb9074;
extern unsigned int g_fb9084;
extern unsigned int g_fb91a8;

/* ADDRESS: GOLD 0x00460120 */
TexSlot* __cdecl d3_AllocTextureSlot(Col c, int* out)
{
	TexSlot* t;
	int i;

	if (g_fb91a8 == g_fb9084) {
		if (out != 0) {
			*out = -1;
		}
		return 0;
	}
	if (c.a >= 0xff && !c.c0) {
		for (i = 0, t = g_fb9074; t->refs > 0; i++, t++) {
		}
	} else {
		for (i = g_fb9084 - 1, t = &g_fb9074[i]; t->refs > 0; i--, t--) {
		}
	}
	if (out != 0) {
		*out = i;
	}
	return t;
}
#else
/* SIZE 0x70 */
typedef struct Tex {
	char name[0x40];
	int refs;
	char pad[0x2c];
} Tex;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x0045c290 */
Tex* __cdecl d3_AllocTextureSlot(Col c, int* out)
{
	Tex* t;
	int i;

	if ((*(unsigned int*)&g_10405c4) == d3_TextureBankCount) {
		if (out != 0) {
			*out = -1;
		}
		return 0;
	}
	if (c.a >= 0xff && !c.c0) {
		for (i = 0, t = ((Tex*)d3_TextureBank); t->refs > 0; i++, t++) {
		}
	} else {
		for (i = d3_TextureBankCount - 1, t = &((Tex*)d3_TextureBank)[i]; t->refs > 0; i--, t--) {
		}
	}
	if (out != 0) {
		*out = i;
	}
	return t;
}
#endif
