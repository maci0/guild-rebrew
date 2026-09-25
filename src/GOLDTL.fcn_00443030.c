// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} Vec3;

// SIZE 0xc
typedef struct {
	int color;
	float f4;
	float f8;
} Pal;

// SIZE 0x60
typedef struct {
	Vec3 a;
	Vec3 b;
	Pal pal[6];
} Slot;

// SIZE 0x218
typedef struct {
	char p0[0x1f4];
	void* next;
	void* prev;
	char p1fc[0x10];
	void* level;
	char p210[4];
	unsigned char flags;
	char p215[3];
} Ent;

// SIZE 0x3dc
typedef struct {
	char p0[0x80];
	Ent* e80;
	Ent* e84;
	Ent* e88;
	Vec3 pos;
	Vec3 rot;
	void* xa4;
	void* xa8;
	int xac;
	int xb0;
	int xb4;
	int xb8;
	Vec3 amb;
	Vec3 dir;
	Pal tmpl;
	Pal pal[6];
	Slot slots[7];
	char p3c8[4];
	int x3cc;
	int x3d0;
	char p3d4[4];
	int x3d8;
} Level;

extern char g_1042340;
extern char g_1043060;
extern char g_1040640;
extern char g_1040960;

Ent* __cdecl fcn_00439750(int, const char*);
void __cdecl fcn_00438b40(Ent*, Vec3*);
void __cdecl fcn_00438cb0(Ent*, Vec3*);

// FUNCTION: GOLDTL 0x00443030
// SIZE: 512

char __cdecl fcn_00443030(Level* lv)
{
	Ent* e;
	int i;
	char* d;
	char* s;
	int n;

	if (lv == 0 || lv->e80 != 0 || lv->xa4 != 0) {
		return 0;
	}
	e = fcn_00439750(3, "MegaCam");
	lv->pos.x = 0.0f;
	lv->pos.y = 0.0f;
	lv->pos.z = -256.0f;
	fcn_00438b40(e, &lv->pos);
	lv->rot.y = 0.0f;
	lv->rot.x = 0.0f;
	lv->rot.z = 0.0f;
	fcn_00438cb0(e, &lv->rot);
	e->level = lv;
	e->flags |= 3;
	e->next = &g_1042340;
	e->prev = &g_1043060;
	lv->amb.x = 200.0f;
	lv->amb.y = 200.0f;
	lv->amb.z = 200.0f;
	lv->e88 = e;
	lv->e84 = e;
	lv->e80 = e;
	lv->xa4 = &g_1040640;
	lv->xa8 = &g_1040960;
	lv->x3d8 = 0;
	lv->xac = 0;
	lv->xb8 = 0;
	lv->xb4 = 0;
	lv->xb0 = 0;
	lv->dir.x = 0.0f;
	lv->dir.y = 0.0f;
	lv->dir.z = 0.0f;
	lv->tmpl.color = 0;
	lv->tmpl.f8 = 0.0f;
	lv->tmpl.f4 = 0.0f;
	for (i = 0; i < 6; i++) {
		lv->pal[i].color = lv->tmpl.color;
		lv->pal[i].f4 = lv->tmpl.f4;
		lv->pal[i].f8 = lv->tmpl.f8;
	}
	n = 0x48;
	s = (char*) lv->pal;
	for (i = 0; i < 7; i++) {
		lv->slots[i].a.x = lv->amb.x;
		lv->slots[i].a.y = lv->amb.y;
		lv->slots[i].a.z = lv->amb.z;
		lv->slots[i].b.x = lv->dir.x;
		lv->slots[i].b.y = lv->dir.y;
		lv->slots[i].b.z = lv->dir.z;
		d = (char*) lv->slots[i].pal;
		/*
		 * TODO: replace this inline-asm copy with proper C once a spelling is
		 * found; no msvc6 C memcpy form emits the prelude
		 * (docs/codegen-walls.md section 6b).
		 */
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
	lv->x3cc = 4;
	lv->x3d0 = 0xf;
	return 1;
}
