// FUNCTION: GOLD 0x43d860
// The squared distance goes through dx/dy/dz statements; written as one
// expression c2 orders the CSE'd differences y before x.

#include <math.h>

typedef struct Vec043d860 {
	float x;
	float y;
	float z;
	float w;
} Vec043d860;
// SIZE 0x10

typedef struct Box043d860 {
	float x;
	float y;
	float z;
	char padc[0x50 - 0xc];
} Box043d860;

typedef struct Obj043d860 Obj043d860;

typedef struct Api043d860 {
	char pad0[0x1f4];
	Box043d860*(__cdecl* query)(Obj043d860* o, void* ctx, char* data);
} Api043d860;

typedef struct Ctx043d860 {
	char pad0[0x10];
	Api043d860* api;
} Ctx043d860;

struct Obj043d860 {
	char pad0[0x4c];
	int x4c;
	char pad50[0x68 - 0x50];
	float radius;
	char pad6c[0x1cc - 0x6c];
	Ctx043d860* ctx;
	char pad1d0[0x1ec - 0x1d0];
	char* ov;
	char pad1f0[0x218 - 0x1f0];
	int x218;
};


void __cdecl fcn_00458b10(Obj043d860* o, int arg, int* p, Vec043d860* out);
void __cdecl fcn_00439870(Obj043d860* o, int arg, int z);

char __cdecl fcn_0043d860(Obj043d860* o, int arg, Vec043d860* out, float* radius)
{
	Ctx043d860* ctx;
	Box043d860* b;
	Box043d860* q;
	Vec043d860 c;
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
			fcn_00458b10(o, arg, &o->x4c, &c);
			r = o->radius;
			goto done;
		}
		ctx = o->ctx;
		if (ctx != 0 && ctx->api != 0) {
			fcn_00439870(o, arg, 0);
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
