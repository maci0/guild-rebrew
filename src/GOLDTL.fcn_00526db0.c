// FUNCTION: GOLDTL 0x00526db0

#include <string.h>

// SIZE 0x5c
typedef struct {
	int flags;
	int width;
	int height;
	char padc[0x1c];
	int format;
	char pad2c[0x30];
} SurfaceDesc;

// SIZE 0xc
typedef struct {
	int handle;
	int width;
	int height;
} Surface;

// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int visible;
	char pad60[0x2f4 - 0x60];
} Control;

extern int g_1040490;
extern int g_1040494;
extern int g_6a25a8;
extern int g_6a2598;
extern int g_14ce860;
extern int g_14ce864;
extern int g_774674;
extern int g_774678;
extern int g_77467c;
extern unsigned char g_77534c;
extern int g_6a24d8[];
extern int g_7ea380[15];
extern int g_6a25ac;
extern int g_1040480;
extern int g_6a3764;
extern int g_774684;
extern int g_6a25fc;
extern char* g_1015ea0;

void __cdecl fcn_0047a040(int, int, int, int);
int __cdecl fcn_00475290(int, int, int, int, int);
int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_00471c80(int, int);
char* __cdecl fcn_00465ba0(char*, int);
Surface* __cdecl fcn_004770a0(SurfaceDesc*, int);
int __cdecl fcn_00475fd0(Surface*);
void __cdecl fcn_0047a710(int, int, char*, Surface*);
void __cdecl fcn_00476060(Surface*);
int __cdecl fcn_0047b640(int, int, int, int, Surface*, int);
void __cdecl fcn_00475f80(Surface*);
void __cdecl m_FreeTracked(char*);
void __cdecl fcn_00476970(Surface*);
int __cdecl fcn_00469c30(int, int, int);
void __cdecl fcn_00472170(int, int);

void __cdecl fcn_00526db0(char* name)
{
	SurfaceDesc desc2;
	SurfaceDesc desc;
	int n;
	SurfaceDesc* p;
	char* data;
	Surface* s;

	fcn_0047a040(0, 0, g_1040494, g_1040490);
	g_6a25a8 = fcn_00475290(g_1040494 - 0x50, 0x11, 0x30, 0x30, 0);
	g_6a2598 = fcn_0046e940(4, 0xa, 0x288, 0x30, 0);
	fcn_00471c80(g_6a2598, 1);
	data = fcn_00465ba0(name, 0);
	n = sizeof(desc);
	p = &desc;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (docs/codegen-walls.md 6b).
	 */
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
	desc.width = g_14ce860;
	desc.height = g_14ce864;
	desc.format = 0x15;
	s = fcn_004770a0(&desc, 0x20);
	if (s != 0) {
		if (fcn_00475fd0(s) != 0) {
			fcn_0047a710(0, 0, data + *(int*) (data + 0x45), s);
			fcn_00476060(s);
		}
		g_774674 = fcn_0047b640(s->width - 0x80, 0, 0x80, s->height - 0x80, s, 0);
		g_774678 = fcn_0047b640(s->width - 0x100, s->height - 0x80, 0x100, 0x80, s, 0);
		g_77467c = fcn_0047b640(g_6a24d8[g_77534c], 0, 0x288, 0x40, s, 0);
		fcn_00475f80(s);
	}
	m_FreeTracked(data);
	memset(g_7ea380, 0xff, sizeof(g_7ea380));
	(*(char**)&g_6a25ac) = name;
	(*(Rect*)&g_1040480) = (*(Rect*)&g_6a3764);
	memset(&desc2, 0, sizeof(desc2));
	desc2.width = 0x68;
	desc2.height = 0x6e;
	desc2.format = 0x15;
	(*(Surface**)&g_774684) = fcn_004770a0(&desc2, 3);
	fcn_00476970((*(Surface**)&g_774684));
	g_6a25fc = fcn_00469c30(0x286, 0x23c, 0x544);
	((Control*)g_1015ea0)[g_6a25fc].visible = 1;
	fcn_00472170(g_6a25fc, 0);
}
