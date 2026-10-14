
// m is a double compared as !(m < b[i].y): that is the spelling that loads the
// float first and copies m for fld/fld st(1)/fcompp with the test ah,5 mask.

typedef struct Vec0457140 {
	float x;
	float y;
	float z;
	float w;
} Vec0457140;
// SIZE 0x10

typedef struct Ent0457140 {
	int active;
	char pad4[0x1c - 4];
	float x;
	float y;
	float z;
	char pad28[0x5c - 0x28];
	float value;
	char pad60[0x9c - 0x60];
} Ent0457140;

typedef struct Ov0457140 {
	char pad0[0x1384];
	Ent0457140 ents[4];
	float height;
} Ov0457140;

typedef struct Obj0457140 {
	char pad0[0x4c];
	int x4c;
	char pad50[0x1ec - 0x50];
	Ov0457140* ov;
	char pad1f0[0x1fc - 0x1f0];
	struct Obj0457140* parent;
	char pad200[0x215 - 0x200];
	unsigned char flags;
} Obj0457140;

typedef struct Api0457140 {
	char pad0[0x1d4];
	float base;
	char pad1d8[0x1f0 - 0x1d8];
	struct Box0457140*(__cdecl* query)(Obj0457140* o, void* ctx, char* data);
} Api0457140;

typedef struct Box0457140 {
	float x;
	float y;
	char pad8[0x50 - 8];
} Box0457140;

typedef struct Ctx0457140 {
	char pad0[0x318];
	Api0457140* api;
} Ctx0457140;

extern float g_662c94;

void __cdecl fcn_00455350(Obj0457140* o, int* p, Vec0457140* out);

float __cdecl fcn_00457140(Obj0457140* o, Ctx0457140* ctx)
{
	Obj0457140* p;
	Ov0457140* ov;
	Box0457140* b;
	float res;
	double m;
	Vec0457140 pos;
	char found;
	int i;

	res = 0.0f;
	found = 0;
	fcn_00455350(o, &o->x4c, &pos);
	if (o->parent != 0) {
		for (p = o->parent; p != 0; p = p->parent) {
			if ((p->flags & 1) && p->ov != 0) {
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
		if (o->flags & 0x10) {
			return pos.y - ctx->api->base + o->ov->height;
		}
		b = ctx->api->query(o, ctx, (char*)o->ov + 8);
		m = g_662c94;
		for (i = 0; i < 8; i++) {
			if (!(m < b[i].y)) {
				m = b[i].y;
			}
		}
		res = m + o->ov->height;
	}
done:
	return res;
}
