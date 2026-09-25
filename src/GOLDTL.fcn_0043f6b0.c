void* __cdecl fcn_0041db70(unsigned int size, const char* tag);
void __cdecl fcn_0043f640(char* cell, int a, unsigned char b);
void __cdecl fcn_0043c2c0(void* g);

static __inline void fill0(char* dst, int size)
{
	char* d;
	int n;

	d = dst;
	n = size;
	/*
	 * TODO: replace this inline-asm fill with proper C once a spelling is
	 * found; no msvc6 C memset form emits the prelude
	 * (docs/codegen-walls.md section 6b).
	 */
	__asm {
		mov edi, d
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
}

// SIZE 0x8038
typedef struct {
	unsigned int n;
	int x4;
	char p8[0x14];
	void* light;
	void* uvs;
	void* div0;
	void* div1;
	void* div2;
	char p30[0x70];
	char cells[8][8][0x1f4];
	char p7da0[0x294];
	unsigned char x8034;
	char p8035;
	unsigned char x8036;
	unsigned char x8037;
} Grid;

// FUNCTION: GOLDTL 0x0043f6b0
// SIZE: 297

void __cdecl fcn_0043f6b0(Grid* g)
{
	int i;
	int j;

	g->x8034 = 0xff;
	g->div0 = fcn_0041db70(g->n * g->n, "d3_fl:Divide0");
	g->div1 = fcn_0041db70(g->n * g->n >> 2, "d3_fl:Divide1");
	g->div2 = fcn_0041db70(g->n * g->n >> 4, "d3_fl:Divide2");
	g->light = fcn_0041db70(g->n * g->n, "d3_fl:Light");
	if (g->uvs == 0) {
		g->uvs = fcn_0041db70(g->n * g->n * 8, "d3fl:TexUVs");
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			fill0(g->cells[i][j], 0x1f4);
			fcn_0043f640(g->cells[i][j], g->x4, g->x8037 & 0xf);
		}
	}
	fcn_0043c2c0(g);
	g->x8036 |= 1;
}
