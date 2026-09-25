void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

// SIZE 0x5c
typedef struct {
	int x0;
	int w;
	int h;
	char pc[0x1c];
	int x28;
	char p2c[0x30];
} Desc;

// SIZE 0x20
typedef struct {
	char p0[0x10];
	int pitch;
	char p14[8];
	short* bits;
} Surf;

// SIZE 0x2f4
typedef struct {
	char p0[8];
	int x08;
	char pc[4];
	int x10;
	int x14;
	int x18;
	int x1c;
	int x20;
	char p24[4];
	int x28;
	int x2c;
	int x30;
	int x34;
	char p38[0x54];
	Surf* surf;
	char p90[0x264];
} Tile;

extern Tile* g_1015ea0;
extern int g_1040490;
extern int g_1040494;

int __cdecl fcn_00469890(void);
Surf* __cdecl fcn_004770a0(Desc*, int);
int __cdecl fcn_00475fd0(Surf*);
void __cdecl fcn_00476060(Surf*);

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

// FUNCTION: GOLDTL 0x00469140
// SIZE: 378

int __cdecl fcn_00469140(int a1, int a2, int w, int h, char* src)
{
	int idx;
	Desc desc;
	Surf* s;
	int i;

	idx = fcn_00469890();
	g_1015ea0[idx].x20 = 0x47;
	g_1015ea0[idx].x10 = a1;
	g_1015ea0[idx].x14 = a2;
	g_1015ea0[idx].x1c = h;
	g_1015ea0[idx].x18 = w;
	g_1015ea0[idx].x08 = -1;
	g_1015ea0[idx].x30 = 0;
	g_1015ea0[idx].x34 = g_1040490;
	g_1015ea0[idx].x28 = 0;
	g_1015ea0[idx].x2c = g_1040494;
	fill0((char*) &desc, 0x5c);
	desc.h = h;
	desc.w = w;
	desc.x28 = 0x17;
	g_1015ea0[idx].surf = fcn_004770a0(&desc, 0);
	s = g_1015ea0[idx].surf;
	if (fcn_00475fd0(s)) {
		for (i = 0; i < h; i++) {
			memcpy(s->bits + s->pitch * i, src + i * w * 2, w * 2);
		}
		fcn_00476060(g_1015ea0[idx].surf);
	}
	return idx;
}
