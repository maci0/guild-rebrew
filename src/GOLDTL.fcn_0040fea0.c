

typedef struct Buf40fea0 Buf40fea0;

/* 0xa4 bytes at g_14cfb60. */
// SIZE 0xa4
struct Buf40fea0 {
	int head;
	char pad4[0x30];
	float f10;
	float f50;
	float f30;
	int v60;
	int v64;
	int v68;
	char pad4c[0x34];
	float one;
	char pad84[8];
	float f255;
	int n14;
	int na0;
	int nb4;
	unsigned char b9c;
	unsigned char b9d;
	unsigned char b9e;
	unsigned char b9f;
	unsigned char flags;
	unsigned char pada1[3];
};

extern Buf40fea0 g_14cfb60;
extern int g_662d60;
extern int g_662d64;
extern int g_662d68;
extern float g_662d70[4];

void __cdecl fcn_00454460(int a, float* b, int c, int d, int tag, float e, Buf40fea0* buf);

/* The 24-byte fill is the hand-written alignment prelude (lea ecx,[edi+edi*2]
 * / and 3 / sub ebx,ecx / jle / rep stosb / rep stosd / rep stosb). A plain
 * memset emits only two reps. Same block as m_init. */
#pragma optimize("y", off)
void __cdecl fcn_0040fea0(union { int* p; unsigned char b[4]; int bits; } u, int* a1, int* a2, int* a3, int* a4, unsigned char* a5, unsigned char* a6)
{
	int len;

	len = 0xa4;
	__asm {
		mov edi, offset g_14cfb60
		mov ebx, len
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short fea0_aligned
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	fea0_aligned:
		add ecx, ebx
		rep stosb
	}
	g_14cfb60.head = *u.p;
	g_14cfb60.f10 = 10.0f;
	g_14cfb60.f50 = 50.0f;
	g_14cfb60.f30 = 30.0f;
	g_14cfb60.v60 = g_662d60;
	g_14cfb60.v64 = g_662d64;
	g_14cfb60.v68 = g_662d68;
	g_14cfb60.one = 1.0f;
	g_14cfb60.f255 = 255.0f;
	g_14cfb60.n14 = 0x14;
	g_14cfb60.na0 = 0xa0;
	g_14cfb60.nb4 = 0xb4;
	g_14cfb60.b9e = 0xff;
	g_14cfb60.b9d = 0xff;
	g_14cfb60.b9c = 0xff;
	g_14cfb60.b9f = 0;
	g_14cfb60.flags |= 0x20;
	/* Blend bit 0 of byte 2 with *a6, then set bit 1. The xor form keeps
	 * the old byte in al so it cannot rise above the 0xff stores. */
	u.b[2] = (unsigned char) (((u.b[2] ^ *a6) & 1) ^ u.b[2]);
	u.b[2] = (unsigned char) (u.b[2] | 2);
	u.b[0] = *a5;
	fcn_00454460(*a1, g_662d70, *a2, *a4, u.bits, (float) *a3, &g_14cfb60);
}
#pragma optimize("", on)
