// FUNCTION: GOLDTL 0x43a820
// SIZE: 416
// The squared distance goes through dx/dy/dz statements; written as one
// expression c2 orders the CSE'd differences y before x.

#include <math.h>

typedef struct Vec043a820 {
	float x;
	float y;
	float z;
	float w;
} Vec043a820;
// SIZE 0x10

typedef struct Box043a820 {
	float x;
	float y;
	float z;
	char padc[0x50 - 0xc];
} Box043a820;

typedef struct Obj043a820 Obj043a820;

typedef struct Api043a820 {
	char pad0[0x1f0];
	Box043a820*(__cdecl* query)(Obj043a820* o, void* ctx, char* data);
} Api043a820;

typedef struct Ctx043a820 {
	char pad0[0x318];
	Api043a820* api;
} Ctx043a820;

struct Obj043a820 {
	char pad0[0x4c];
	int x4c;
	char pad50[0x68 - 0x50];
	float radius;
	char pad6c[0x1cc - 0x6c];
	Ctx043a820* ctx;
	char pad1d0[0x1ec - 0x1d0];
	char* ov;
	char pad1f0[0x218 - 0x1f0];
	int x218;
};


void __cdecl fcn_00455450(Obj043a820* o, int arg, int* p, Vec043a820* out);
void __cdecl fcn_00438100(Obj043a820* o, int arg, int z);

char __cdecl fcn_0043a820(Obj043a820* o, int arg, Vec043a820* out, float* radius)
{
	Ctx043a820* ctx;
	Box043a820* b;
	Box043a820* q;
	Vec043a820 c;
	float r;
	float d;
	float* pz;
	float dx;
	float dy;
	float dz;
	char ok;
	int i;

	ok = 0;
	if (o != 0 && (out != 0 || radius != 0)) {
		if (o->x218 == 0) {
			fcn_00455450(o, arg, &o->x4c, &c);
			r = o->radius;
			goto done;
		}
		ctx = o->ctx;
		if (ctx != 0 && ctx->api != 0) {
			fcn_00438100(o, arg, 0);
			b = ctx->api->query(o, ctx, o->ov + 0x48);
			if (b != 0) {
				c.x = b->x;
				c.y = b->y;
				pz = &b->z;
				c.z = *pz;
				for (q = b + 1, i = 7; i != 0; i--, q++) {
					c.x += q->x;
					c.y += q->y;
					c.z += q->z;
				}
				c.x = c.x * 0.125f;
				c.y = c.y * 0.125f;
				c.z = c.z * 0.125f;
				r = 0.0f;
				for (i = 8; i != 0; i--, pz += 20) {
					dx = c.x - pz[-2];
					dy = c.y - pz[-1];
					dz = c.z - pz[0];
					d = dx * dx + dy * dy + dz * dz;
					if (!(r > d)) {
						r = d;
					}
				}
				r = (float)sqrt(r);
			done:
				ok = 1;
				if (radius != 0) {
					*radius = r;
				}
				if (out != 0) {
					out->x = c.x;
					out->y = c.y;
					out->z = c.z;
				}
			}
		}
	}
	return ok;
}
