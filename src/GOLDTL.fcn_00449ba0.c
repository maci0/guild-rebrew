#include <string.h>

// SIZE 0x288
typedef struct {
	char name[0x44];
	int x44;
	char p48[4];
	int x4c;
	char p50[0x190];
	int refs;
	int count;
	char p1e8[0x9c];
	int* tex;
} Mesh;

// SIZE 0x4a4
typedef struct {
	char p0[0x310];
	int x310;
	int x314;
	Mesh* mesh;
	int* cur;
	char p320[0x180];
	char b4a0;
	char b4a1;
} Obj;

// SIZE 0x4a4
typedef struct {
	char p0[0xf4];
	char xf4[0x310];
	int x404;
	int x408;
	void* x40c;
	char p410[0x94];
} Sub;

// SIZE 0x163d
typedef struct {
	Sub subs[3];
	char pdec[0xf4];
	Obj obj;
	char p1384[0x2b8];
	unsigned char count;
} Set;

// SIZE 0x1f0
typedef struct {
	char p0[0x1cc];
	void* cur;
	char p1d0[0x1c];
	Set* set;
} Ent;

Mesh* __cdecl fcn_00449b60(int);
void* __cdecl m_AllocTracked(unsigned int, const char*);
void __cdecl fcn_0045c310(int, int);
void* __cdecl fcn_004382e0(Ent*);

/*
 * TODO: replace this inline-asm copy with proper C once a spelling is
 * found; no msvc6 C memcpy form emits the prelude
 * (docs/codegen-walls.md section 6b).
 */
static __inline void copy0(void* dst, void* src, int size)
{
	void* d;
	void* s;
	int n;

	n = size;
	s = src;
	d = dst;
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

// FUNCTION: GOLDTL 0x00449ba0

void __cdecl fcn_00449ba0(Ent* e, Obj* o, int id)
{
	char buf[0x100];
	Mesh* m;
	int i;

	m = fcn_00449b60(id);
	if (m == 0) {
		return;
	}
	o->x310 = m->x44;
	o->x314 = m->x4c;
	o->mesh = m;
	o->b4a0 = 0;
	o->b4a1 = 0;
	o->cur = m_AllocTracked(m->count * 8, "d3_io:CurTexSet");
	for (i = 0; i < m->count; i++) {
		o->cur[i] = m->tex[i];
		if (o->cur[i] != 0) {
			fcn_0045c310(o->cur[i], 1);
		}
	}
	copy0(o->cur + m->count, o->cur, m->count * 4);
	for (i = 0; i < m->count; i++) {
		if (o->cur[i] == 0) {
			strcpy(buf, "Error attaching Stock-Object \"");
			strcat(buf, m->name);
			strcat(buf, "\": Not all Textures used/found!");
			break;
		}
	}
	if (o != &e->set->obj) {
		e->set->count++;
		if (e->cur == 0) {
			e->cur = fcn_004382e0(e);
			if (e->cur == 0) {
				for (i = 0; e->cur == 0 && i < 3; i++) {
					if (e->set->subs[i].x408 > 0 && e->set->subs[i].x404 > 0 && e->set->subs[i].x40c != 0) {
						e->cur = e->set->subs[i].xf4;
					}
				}
			}
		}
	}
	m->refs++;
}
