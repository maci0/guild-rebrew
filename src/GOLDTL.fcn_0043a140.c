#include <string.h>

typedef struct V8 {
	float v[8];
} V8;

typedef struct V6 {
	float v[6];
} V6;

typedef struct Obj {
	char name[0x4c];
	V8 a;
	V6 b;
	V6 c;
	char body[0xf0];
	char pad18c[0x1cc - 0x18c];
	int f1cc;
	int f1d0;
	char pad1d4[0x1e8 - 0x1d4];
	char* light;
	char* ext;
	char pad1f0[0x214 - 0x1f0];
	unsigned char flags[0x14];
} Obj;
// SIZE 0x228

void* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_00439e70(Obj* o);
void __cdecl fcn_00439fa0(Obj* o);
void __cdecl fcn_00438b40(Obj* o, V8* v);
void __cdecl fcn_00438cb0(Obj* o, V6* v);
void __cdecl fcn_00449f90(Obj* o, int a, int id);

// FUNCTION: GOLDTL 0x43a140
// SIZE: 688
Obj* __cdecl fcn_0043a140(Obj* src)
{
	Obj* o;
	Obj* r;
	unsigned char* p;

	r = 0;
	if (src) {
	o = fcn_0041db70(0x228, "d3:CloneObject");
	if (*(int*) ((char*) src + 0x218) >= 5) {
		o->light = fcn_0041db70(0x1ac, "d3:CloneObject(lightinfo)");
	}
	fcn_00439e70(o);
	strcpy(o->name, src->name);
	strcat(o->name, "_");
	o->a.v[0] = src->a.v[0];
	o->a.v[1] = src->a.v[1];
	o->a.v[2] = src->a.v[2];
	o->a.v[3] = src->a.v[3];
	o->a.v[4] = src->a.v[4];
	o->a.v[5] = src->a.v[5];
	o->a.v[6] = src->a.v[6];
	o->a.v[7] = src->a.v[7];
	o->c.v[0] = src->c.v[0];
	o->c.v[1] = src->c.v[1];
	o->c.v[2] = src->c.v[2];
	o->c.v[3] = src->c.v[3];
	o->c.v[4] = src->c.v[4];
	o->c.v[5] = src->c.v[5];
	o->b.v[0] = src->b.v[0];
	o->b.v[1] = src->b.v[1];
	o->b.v[2] = src->b.v[2];
	o->b.v[3] = src->b.v[3];
	o->b.v[4] = src->b.v[4];
	o->b.v[5] = src->b.v[5];
	o->f1d0 = 0;
	o->f1cc = 0;
	if (src->light) {
		char* d;
		char* s;
		int n;

		n = 0x188;
		s = src->light;
		d = o->light;
		__asm {
			mov edi, d
			mov esi, s
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	{
		char* d;
		char* s;
		int n;

		n = 0xf0;
		s = src->body;
		d = o->body;
		__asm {
			mov edi, d
			mov esi, s
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L2:
			add ecx, ebx
			rep movsb
		}
	}
	{
		unsigned char* d;
		unsigned char* s;
		int n;

		n = 0x14;
		s = src->flags;
		d = p = o->flags;
		__asm {
			mov edi, d
			mov esi, s
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L3
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L3:
			add ecx, ebx
			rep movsb
		}
	}
	if (src->ext) {
		fcn_00439fa0(o);
		*(int*) (o->ext + 0x15f4) = *(int*) (src->ext + 0x15f4);
		*(int*) (o->ext + 0x15f8) = *(int*) (src->ext + 0x15f8);
		if (*(unsigned char*) (src->ext + 0x163c) > 0) {
			fcn_00449f90(o, 0, *(int*) (src->ext + 0x40c));
		}
	}
	{
		unsigned char a;
		unsigned char b;

		a = p[0];
		b = o->flags[1];
		o->flags[1] = b & 0xef;
		p[0] = (a & 0xfc) | 4;
	}
	fcn_00438b40(o, &o->a);
	fcn_00438cb0(o, &o->c);
	r = o;
	}
	return r;
}
