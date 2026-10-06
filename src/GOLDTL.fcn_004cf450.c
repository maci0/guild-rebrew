// FUNCTION: GOLDTL 0x4cf450

#include <string.h>

// SIZE 0x10
typedef struct {
	char* obj;
	int handle;
	int a;
	int b;
} Slot4cf450;

// SIZE 0xc
typedef struct {
	unsigned char b0;
	unsigned char r0 : 2;
	unsigned char a : 1;
	unsigned char c : 1;
	unsigned char b : 1;
	unsigned char r1 : 3;
	unsigned char pad2[6];
	unsigned char r2 : 1;
	unsigned char e : 1;
	unsigned char r3 : 6;
	unsigned char pad9[3];
} Flags4cf450;

// SIZE 0x58
typedef struct {
	int type;
	float pos[3];
	float f10;
	float rot[3];
	char pad20[0x58 - 0x20];
} Ent4cf450;

// SIZE 0xb4
typedef struct {
	char pad0[0xb0];
	int map;
} Game4cf450;

extern int g_67a370;
extern Slot4cf450 g_9b9ec0[32];

char* __cdecl fcn_00442910(int parent, float* pos, float* dir, char* name);
char __cdecl fcn_0045b920(int map, int x, int y, float* out);
int __cdecl fcn_004339e0(char* obj, Flags4cf450 fl, int n, Ent4cf450* ents);

#pragma optimize("y", off)
Slot4cf450* __cdecl fcn_004cf450(float* pos, int x, int y)
{
	Ent4cf450 ents[4];
	float s[4];
	float p[4];
	float d[3];
	Flags4cf450 fl;
	float w[4];
	int map;
	int i;
	char* o;

	d[0] = 0.0f;
	d[1] = 0.0f;
	d[2] = 0.0f;
	map = ((Game4cf450*)g_67a370)->map;
	for (i = 0; i < 32; i++) {
		if (g_9b9ec0[i].obj == 0) {
			goto found;
		}
	}
	return 0;
found:
	p[0] = pos[0];
	p[1] = pos[1] + 60.0;
	p[2] = pos[2];
	o = fcn_00442910(0, p, d, "ob_BOMBE");
	g_9b9ec0[i].obj = o;
	o[0x215] |= 1;
	fcn_0045b920(map, x, y, w);
	w[0] -= pos[0];
	w[1] -= pos[1];
	w[2] -= pos[2];
	memset(ents, 0, sizeof(ents));
	s[0] = w[0] * 0.5;
	s[1] = w[1] * 0.5;
	s[2] = w[2] * 0.5;
	s[1] += 50.0;
	{
		int dst;
		int n;

		n = 12;
		dst = (int) &fl;
		__asm {
		mov edi, dst
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
	fl.a = 1;
	fl.b = 1;
	fl.e = 1;
	fl.c = 1;
	ents[1].pos[0] = s[0];
	ents[1].pos[1] = s[1];
	ents[1].pos[2] = s[2];
	w[1] -= 60.0;
	ents[1].rot[0] = 3.14159274f;
	ents[1].rot[1] = 3.14159274f;
	ents[1].rot[2] = 3.14159274f;
	ents[2].pos[0] = w[0];
	ents[2].pos[1] = w[1];
	ents[2].pos[2] = w[2];
	ents[2].rot[0] = 3.14159274f;
	ents[2].rot[1] = 3.14159274f;
	ents[2].rot[2] = 3.14159274f;
	ents[3].pos[0] = w[0];
	ents[3].pos[1] = w[1];
	ents[3].pos[2] = w[2];
	ents[3].rot[0] = 3.14159274f;
	ents[3].rot[1] = 3.14159274f;
	ents[3].rot[2] = 3.14159274f;
	ents[0].type = 0x12;
	ents[1].type = 0x12;
	ents[2].type = 1;
	g_9b9ec0[i].handle = fcn_004339e0(g_9b9ec0[i].obj, fl, 4, ents);
	g_9b9ec0[i].a = x;
	g_9b9ec0[i].b = y;
	return &g_9b9ec0[i];
}
