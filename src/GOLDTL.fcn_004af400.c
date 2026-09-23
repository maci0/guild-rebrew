/* Owned (both targets) by src/GOLDTL.fcn_004af2f0.c. */
extern float g_662910;

// GLOBAL: GOLDTL 0x99ec10
extern int g_99ec10;
// GLOBAL: GOLD 0x91aaf0
extern int g_99ec10;

/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

/* Callees of this translation unit; see src/GOLDTL.fcn_004af2f0.c, the
 * sibling in the same address family. */
void* __cdecl fcn_0050e4a0(int);
void* __cdecl fcn_00502cd0(void*, int, ...);
void* __cdecl fcn_00502850(void);
void __cdecl fcn_004ae080(char*, char*, int*, char**);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl fcn_0051af00(void*, int, ...);

// FUNCTION: GOLDTL 0x4af400
// SIZE: 289
// FUNCTION: GOLD 0x4af2c0
// SIZE: 289

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x20c) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * docs/msvc6-c-shapes.md.
 *
 * The out-length of fcn_004ae080 lives in the dead a4 argument home
 * ([ebp+0x14]) while the frame keeps only three slots.  msvc6 only packs it
 * there when the local is declared in its own block after the block-fill
 * (declaring it with the other locals spends a fourth slot and compiles the
 * frame to 0x210); the same block shape is what keeps the caller's copy of
 * a4 in esi, so the tail adds the length in edx instead of reusing esi. */
#pragma optimize("y", off)
int __cdecl fcn_004af400(int a1, int a2, int a3, char* a4, int a5)
{
	char buf[0x200];
	char* p;
	int v = 0;
	int len;
	void* e;
	unsigned short k;

	e = fcn_0050e4a0(1);
	if (e == 0)
		return 0;
	e = fcn_00502cd0(*(int*) ((char*) e + 0x5d), 2, 6, 0, 0x115);
	if (e == 0)
		return 0;
	e = fcn_00502cd0(*(int*) ((char*) e + 0x14), 1, 5);
	while (e != 0) {
		k = *(unsigned short*) e;
		if (*(unsigned char*) (g_99ec10 + k * 0x40 + k) == 9) {
			v = *(int*) ((char*) e + 0xe);
			break;
		}
		e = fcn_00502850();
	}
	len = 0x200;
	p = buf;
	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-c-shapes.md section 11, docs/codegen-walls.md section 6b);
	 * no msvc6 C spelling emits it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, p
		mov ebx, len
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
	{
		int n;

		fcn_004ae080(a4, buf, &n, &p);
		n = fcn_0064eeec(a4 + n);
		fcn_0051af00(a5, buf,
		    fcn_0050b710((int) (((float) n * g_662910) * (float) v),
		    g_773d75),
		    g_773d75);
	}
	return 1;
}
