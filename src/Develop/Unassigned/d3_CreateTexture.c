#pragma optimize("y", off)

#include <string.h>

extern int g_10405c4;

void* __cdecl d3_AllocTextureSlot(int c, int* out);
char* __cdecl strncpy(char* d, const char* s, unsigned int n);
void __cdecl d3_CreateTextureSurface(char* a, int b, int c);

/* ADDRESS: GOLDTL 0x0045d0d0 */
int* __cdecl d3_CreateTexture(char* name, int texSize, int format, int mipFlag, int colorKey, unsigned char flagBit0, unsigned char frameDelay, char noMipmaps)
{
	int* p;
	int n;
	unsigned char b;
	int g;


	p = (int*) d3_AllocTextureSlot(colorKey, &n);
	if (p == 0) {
		return 0;
	}
	n = 4;
	/* Reviewed original operand-homed fill (inline fill/copy block). */
	__asm {
		mov edi, p
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
	strncpy((char*) p, name, 0x3f);
	p[0x19] = texSize;
	p[0x1a] = texSize;
	p[0x11] = (texSize * texSize - 1) | (texSize - 1);
	p[0x16] = colorKey;
	p[0x13] = 0;
	p[0x14] = 0;
	g = ((unsigned char*) &colorKey)[1];
	p[0x1b] = (g << 8 | g) << 8 | g;
	p[0x17] = 0;
	p[0x18] = format;
	p[0x10] = 1;
	p[0x12] = -1;
	b = (unsigned char) ((((unsigned char*) p)[0x54] & 0xfc) ^ (flagBit0 & 1));
	((unsigned char*) p)[0x56] = (unsigned char) (((((unsigned char*) p)[0x56] ^ frameDelay) & 0x1f) ^ ((unsigned char*) p)[0x56]);
	((unsigned char*) p)[0x54] = (unsigned char) ((((((noMipmaps == 0) << 2) ^ b) & 4) ^ b));
	g_10405c4++;
	d3_CreateTextureSurface((char*) p, format, mipFlag);
	return p;
}
