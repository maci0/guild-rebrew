#pragma optimize("y", off)

#include <string.h>

extern int g_10405c4;

void* __cdecl fcn_0045c290(int c, int* out);
char* __cdecl strncpy(char* d, const char* s, unsigned int n);
void __cdecl fcn_0045bda0(char* a, int b, int c);

/* ADDRESS: GOLDTL 0x0045d0d0 */
int* __cdecl fcn_0045d0d0(char* a0, int a1, int a2, int a3, int a4, unsigned char a5, unsigned char a6, char a7)
{
	int* p;
	int out;
	int n;
	unsigned char b;


	p = (int*) fcn_0045c290(a4, &out);
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
	strncpy((char*) p, a0, 0x3f);
	p[0x19] = a1;
	p[0x1a] = a1;
	p[0x16] = a4;
	p[0x11] = (a1 * a1 - 1) | (a1 - 1);
	p[0x14] = 0;
	p[0x13] = 0;
	p[0x1b] = ((a4 >> 8 & 0xff) << 8 | (a4 >> 8 & 0xff)) << 8 | (a4 >> 8 & 0xff);
	p[0x17] = 0;
	p[0x18] = a2;
	p[0x10] = 1;
	p[0x12] = -1;
	b = (unsigned char) ((((unsigned char*) p)[0x54] & 0xfc) ^ (a5 & 1));
	((unsigned char*) p)[0x56] = (unsigned char) (((((unsigned char*) p)[0x56] ^ a6) & 0x1f) ^ ((unsigned char*) p)[0x56]);
	((unsigned char*) p)[0x54] = (unsigned char) ((((((a7 == 0) << 2) ^ b) & 4) ^ b));
	g_10405c4++;
	fcn_0045bda0((char*) p, a2, a3);
	return p;
}
