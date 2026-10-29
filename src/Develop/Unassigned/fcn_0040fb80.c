#include <string.h>

typedef struct
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

typedef struct
{
	float x00;
	float x04;
	float x08;
	int   pad0c;
	float x10;
	float x14;
	float x18;
	int   pad1c;
	int   pad20;
	int   pad24;
	int   pad28;
	int   pad2c;
	int   x30;
	int   pad34;
	float x38;
	float x3c;
	float x40;
	int   pad44;
	float x48;
	unsigned char x4c;
	unsigned char x4d;
	unsigned char x4e;
	unsigned char x4f;
	char pad50[4];
} PARTICLE;

typedef struct
{
	unsigned char pad00[0x28];
	PARTICLE *items;
} EMITTER;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, float a, int b, void (__cdecl* cb)(void));
void __cdecl fcn_0040f9d0(void);
int __cdecl fcn_0064d3f8(void);

/* ADDRESS: GOLDTL 0x0040fb80 */
int* __cdecl fcn_0040fb80(int* a1)
{
	Bytes4 f;
	EMITTER* s;
	int i;
	float v;

	memset(&f, 0, sizeof(f));
	f.c |= 3;
	f.a = 0x7f;
	s = (EMITTER*) fcn_004524e0(100, "blut", f, 1.0f, *a1, fcn_0040f9d0);
	for (i = 0; i < 100; i++) {
		s->items[i].x38 = 0.0f;
		s->items[i].x3c = (float) i * 0.16f;
		s->items[i].x40 = 0.0f;
		s->items[i].x10 = s->items[i].x38;
		s->items[i].x14 = s->items[i].x3c;
		s->items[i].x18 = s->items[i].x40;
		s->items[i].x00 = (float) (fcn_0064d3f8() * 3.051851e-05f * 0.2 - 0.1);
		s->items[i].x04 = (float) (0.1 - (fcn_0064d3f8() * 3.051851e-05f + 1.0) * 0.2);
		v = s->items[i].x04;
		s->items[i].x08 = (float) (-0.5 - v);
		s->items[i].x4f = (unsigned char) (0.0 > s->items[i].x3c * 1.5 - 20.0 ? 0.0 : s->items[i].x3c * 1.5 - 20.0);
	}
	return (int*) s;
}
