
/* GOLD twin of GOLDTL fcn_00457140 with the GOLD object layout: entity array
 * at 0x754 with 0x80-byte slots, parent at 0x1f8, flags byte at 0x211. */
// m is a double compared as !(m < b[i].y): that is the spelling that loads the
// float first and copies m for fld/fld st(1)/fcompp with the test ah,5 mask.

typedef struct Vec045bcc0 {
	float x;
	float y;
	float z;
	float w;
} Vec045bcc0;
// SIZE 0x10

typedef struct Ent045bcc0 {
	int active;
	char pad4[0x18 - 4];
	float x;
	float y;
	float z;
	char pad24[0x58 - 0x24];
	float value;
	char pad5c[0x80 - 0x5c];
} Ent045bcc0;

typedef struct Ov045bcc0 {
	char pad0[0x754];
	Ent045bcc0 ents[4];
	float height;
} Ov045bcc0;

typedef struct Obj045bcc0 {
	char pad0[0x4c];
	int x4c;
	char pad50[0x1ec - 0x50];
	Ov045bcc0* ov;
	char pad1f0[0x1f8 - 0x1f0];
	struct Obj045bcc0* parent;
	char pad1fc[0x211 - 0x1fc];
	unsigned char flags;
} Obj045bcc0;

typedef struct Api045bcc0 {
	char pad0[0x1d4];
	float base;
	char pad1d8[0x1f4 - 0x1d8];
	struct Box045bcc0*(__cdecl* query)(Obj045bcc0* o, void* ctx, char* data);
} Api045bcc0;

typedef struct Box045bcc0 {
	float x;
	float y;
	char pad8[0x50 - 8];
} Box045bcc0;

typedef struct Ctx045bcc0 {
	char pad0[0x10];
	Api045bcc0* api;
} Ctx045bcc0;

extern float g_5ebaa4;

void __cdecl fcn_00458a10(Obj045bcc0* o, int* p, Vec045bcc0* out);

float __cdecl fcn_0045bcc0(Obj045bcc0* o, Ctx045bcc0* ctx)
{
	Obj045bcc0* p;
	Ov045bcc0* ov;
	Box045bcc0* b;
	float res;
	double m;
	Vec045bcc0 pos;
	char found;
	int i;

	res = 0.0f;
	found = 0;
	fcn_00458a10(o, &o->x4c, &pos);
	if (o->parent != 0) {
		for (p = o->parent; p != 0; p = p->parent) {
			if ((p->flags & 4) && p->ov != 0) {
				ov = p->ov;
				for (i = 0; i < 4; i++) {
					if (found) {
						break;
					}
					if (ov->ents[i].active != 0 && ov->ents[i].x * ov->ents[i].x + ov->ents[i].y * ov->ents[i].y + ov->ents[i].z * ov->ents[i].z > 0.0f) {
						res = ov->ents[i].value;
						found = 1;
					}
				}
			}
		}
		if (found) {
			goto done;
		}
	}
	if (o->ov != 0) {
		if (o->flags & 0x20) {
			return pos.y - ctx->api->base + o->ov->height;
		}
		b = ctx->api->query(o, ctx, (char*)o->ov + 8);
		m = g_5ebaa4;
		for (i = 0; i < 8; i++) {
			if (!(m < b[i].y)) {
				m = (float)b[i].y;
			}
		}
		res = m + o->ov->height;
	}
done:
	return res;
}
