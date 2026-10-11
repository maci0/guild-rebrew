// FUNCTION: GOLDTL 0x00416060

#include <stdlib.h>

// SIZE 0x28
typedef struct {
	float x;
	float y;
	float z;
	float speed;
	float drift_a;
	float drift_b;
	char pad18[0x28 - 0x18];
} Flake;

// SIZE 0x94
typedef struct {
	int count;
	int count4;
	int count8;
	int countc;
	int mode;
	int zero14[9];
	Flake* flakes;
	int one3c;
	int zero40;
	int one44;
	int zero48;
	int one4c;
	int zero50;
	int zero54;
	int minus1;
	int tint[5];
	int cam70;
	int cam74;
	int cam78;
	int pad7c;
	int cam80;
	int cam84;
	int cam88;
	int pad8c;
	int handle;
} Snow;

// SIZE 4
typedef struct {
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
} LoadFlags;

extern int g_6b7fac;
extern int g_6b8014;
extern char g_677618[];
extern char g_677604[];
extern char g_6775f4[];

void* __cdecl m_AllocTracked(int size, char* tag);
void __cdecl m_FreeTracked(void* p);
int __cdecl fcn_0045c5b0(char* name, LoadFlags flags, int a3, int a4);
void __cdecl fcn_0045ce90(int h);

Snow* __cdecl fcn_00416060(int count)
{
	Snow* s;
	Flake* f;
	int i;
	int n;
	LoadFlags flags;
	LoadFlags* fill;

	s = (Snow*) m_AllocTracked(0x94, g_677618);
	i = 0;
	if (s == 0) {
		return 0;
	}
	s->count = count;
	s->count4 = count;
	s->count8 = count;
	s->countc = count;
	s->mode = 5;
	s->zero14[0] = 0;
	s->zero14[1] = 0;
	s->zero14[2] = 0;
	s->zero14[3] = 0;
	s->zero14[4] = 0;
	s->zero14[5] = 0;
	s->zero14[6] = 0;
	s->zero14[7] = 0;
	s->zero14[8] = 0;
	s->zero54 = 0;
	s->minus1 = -1;
	s->one3c = 0x3f800000;
	s->zero40 = 0;
	s->one44 = 0x3f800000;
	s->zero48 = 0;
	s->one4c = 0x3f800000;
	s->zero50 = 0;
	s->tint[0] = g_6b7fac;
	s->tint[1] = g_6b7fac;
	s->tint[2] = g_6b7fac;
	s->tint[3] = g_6b7fac;
	s->tint[4] = g_6b7fac;
	if (((char*)g_6b8014) != 0) {
		s->cam70 = *(int*) (((char*)g_6b8014) + 0x84);
		s->cam74 = *(int*) (((char*)g_6b8014) + 0x88);
		s->cam78 = *(int*) (((char*)g_6b8014) + 0x8c);
		s->cam80 = *(int*) (((char*)g_6b8014) + 0x4c);
		s->cam84 = *(int*) (((char*)g_6b8014) + 0x50);
		s->cam88 = *(int*) (((char*)g_6b8014) + 0x54);
	}
	if (count < 1) {
		count = 1;
	}
	s->flakes = (Flake*) m_AllocTracked(count * sizeof(Flake), g_677604);
	if (s->flakes == 0) {
		m_FreeTracked(s);
		return 0;
	}
	f = s->flakes;
	for (; i < s->count; i++) {
		count = rand();
		f->x = ((float) count * (1.0f / 32767.0f) - 0.5f) * 2.0f;
		count = rand();
		f->y = ((float) count * (1.0f / 32767.0f) - 0.5f) * 2.0f;
		count = rand();
		f->z = ((float) count * (1.0f / 32767.0f) - 0.5f) * 2.0f;
		count = rand();
		f->speed = (float) count * (0.5f / 32767.0f) + 0.75f;
		count = rand();
		f->drift_a = (float) count * (0.01f / 32767.0f) + 0.025f;
		count = rand();
		f->drift_b = (float) count * (0.01f / 32767.0f) + 0.025f;
		f++;
	}
	n = 4;
	fill = &flags;
	/* Block-fill prelude no msvc6 C spelling emits (docs/codegen-walls.md 6b). */
	__asm {
		mov edi, fill
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
	flags.b2 |= 2;
	s->handle = fcn_0045c5b0(g_6775f4, flags, 0, 0);
	if (s->handle != 0) {
		fcn_0045ce90(s->handle);
	}
	return s;
}
