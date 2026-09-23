// GLOBAL: GOLDTL 0x662910
extern float g_662910;
// GLOBAL: GOLD 0x5eb7f0
extern float g_662910;

/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

void* __cdecl fcn_00508e40(int);
int __cdecl fcn_0050dac0(unsigned short);
void __cdecl fcn_004ae080(int, char*, int*, char**);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl fcn_0051af00(void*, int, ...);

/* Reproduction of the module's fcn_004ae130 (GOLDTL 0x4ae130), which the
 * original translation unit held in the same file as this function.  msvc6's
 * same-TU callee analysis is what keeps `w` in edx across the call site below;
 * without the body in view the allocator spills `w` to a callee-saved register
 * (object 267 bytes instead of 264).  The body is byte-identical to the real
 * function; only its name differs, so this file defines no duplicate symbol
 * (src/GOLDTL.fcn_004ae130.c owns the 0x4ae130 annotation). */
int __cdecl fcn_004ae130_tu(unsigned short a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) (0x7f4ca0 + o) != 0xffff
	    && *(unsigned char*) (0x7f4ca8 + o) > 0
	    && *(unsigned char*) (0x7f4ca2 + o) < 0xa) {
		return 1;
	}
	return 0;
}

// FUNCTION: GOLDTL 0x4af2f0
// SIZE: 264
// FUNCTION: GOLD 0x4af1b0
// SIZE: 264

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x200) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * docs/msvc6-c-shapes.md. */
#pragma optimize("y", off)
int __cdecl fcn_004af2f0(int a1, int a2, int a3, char* a4, int a5)
{
	char buf[0x200];
	unsigned short w;
	char* p;
	int n;
	int r;
	void* e;

	if (a1 != 2 || a2 == 0 || a3 == 8) {
		return 0;
	}
	e = fcn_00508e40(*(int*) ((char*) a2 + a3 * 8 + 4));
	if (e == 0) {
		return 0;
	}
	w = *(unsigned short*) e;
	if (fcn_004ae130_tu(w) == 0) {
		return 0;
	}
	r = fcn_0050dac0(w);
	n = 0x200;
	p = buf;
	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-c-shapes.md section 11, docs/codegen-walls.md section 6b);
	 * no msvc6 C spelling emits it.  Reproduced as a block-fill with ordinary
	 * named operands. */
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
	fcn_004ae080(a4, buf, &n, &p);
	n = fcn_0064eeec(a4 + n);
	fcn_0051af00(a5, buf,
	    fcn_0050b710((int) (((float) n * g_662910) * (float) r),
	    g_773d75),
	    g_773d75);
	return 1;
}
