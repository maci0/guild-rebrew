#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x70
typedef struct {
	char name[0x40];
	int x40;
	int x44;
	int x48;
	int x4c;
	int x50;
	unsigned char flags;
	char p55[3];
	int x58;
	unsigned char x5c;
	char p5d[3];
	int x60;
	int x64;
	int x68;
	int x6c;
} Tex;

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
extern int g_10405c0;

Tex* __cdecl d3_AllocTextureSlot(int, int);


/* ADDRESS: GOLDTL 0x0045d1e0 */
/* ADDRESS: GOLDDE 0x00452190 */
Tex* __cdecl d3_CloneTexture(Tex* src, int color, char recurse)
{
	Tex* p;
	int n;
	int c;
	unsigned int i;

	if (src == 0) {
		return 0;
	}
	p = d3_AllocTextureSlot(color, 0);
	if (p != 0) {
		n = 0x70;
		/*
		 * TODO: replace this inline-asm copy with proper C once a spelling is
		 * found; recorded C copy probes did not emit the prelude
		 * (archived docs/codegen-walls.md section 6b).
		 */
		__asm {
			mov edi, p
			mov esi, src
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
		p->x58 = color;
		c = ((unsigned char*) &color)[1];
		p->x40 = 1;
		p->x4c = (int) src;
		p->x6c = (((c << 8) | c) << 8) | c;
		p->flags |= 2;
		if (src->flags & 2) {
			p->x44 = src->x44;
		} else {
			p->x44 = src - ((Tex*)d3_TextureBank);
		}
		g_10405c4++;
		if (p->x48 != -1 && p->x5c > 0 && recurse) {
			p->x48 = g_10405c0;
			for (i = 0; i < d3_TextureBankCount; i++) {
				if (((Tex*)d3_TextureBank)[i].x40 > 0 && ((Tex*)d3_TextureBank)[i].x48 == src->x48) {
					d3_CloneTexture(&((Tex*)d3_TextureBank)[i], color, 0);
				}
			}
			g_10405c0++;
		}
	}
	return p;
}
