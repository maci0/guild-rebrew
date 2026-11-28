// The squared distance goes through dx/dy/dz statements; written as one
// expression c2 orders the CSE'd differences y before x.

#include <math.h>

typedef struct D3_SPHERE_VEC4 {
	float x;
	float y;
	float z;
	float w;
} D3_SPHERE_VEC4;
// SIZE 0x10

typedef struct D3_BOUNDING_CORNER {
	float x;
	float y;
	float z;
	char padc[0x50 - 0xc];
} D3_BOUNDING_CORNER;

typedef struct D3_BOUNDING_OBJ D3_BOUNDING_OBJ;

typedef struct D3_BOUNDING_API {
#if defined(REBREW_GOLD)
	char pad0[0x1f4];
#else
	char pad0[0x1f0];
#endif
	D3_BOUNDING_CORNER*(__cdecl* query)(D3_BOUNDING_OBJ* o, void* ctx, char* data);
} D3_BOUNDING_API;

typedef struct D3_BOUNDING_CTX {
#if defined(REBREW_GOLD)
	char pad0[0x10];
#else
	char pad0[0x318];
#endif
	D3_BOUNDING_API* api;
} D3_BOUNDING_CTX;

struct D3_BOUNDING_OBJ {
	char pad0[0x4c];
	int x4c;
	char pad50[0x68 - 0x50];
	float radius;
	char pad6c[0x1cc - 0x6c];
	D3_BOUNDING_CTX* ctx;
	char pad1d0[0x1ec - 0x1d0];
	char* ov;
	char pad1f0[0x218 - 0x1f0];
	int x218;
};

void __cdecl d3_TransformPointToView(D3_BOUNDING_OBJ* o, int arg, int* p, D3_SPHERE_VEC4* out);
void __cdecl d3_TransformPointToRef(D3_BOUNDING_OBJ* o, char* arg, int* p, D3_SPHERE_VEC4* out);
void __cdecl d3_UpdateObjectCameraTransform(D3_BOUNDING_OBJ* o, int arg, int z);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0043d860 */
char __cdecl d3_GetObjectBoundingSphere(D3_BOUNDING_OBJ* o, int arg, D3_SPHERE_VEC4* out, float* radius)
{
	D3_BOUNDING_CTX* ctx;
	D3_BOUNDING_CORNER* b;
	D3_BOUNDING_CORNER* q;
	D3_SPHERE_VEC4 c;
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
			d3_TransformPointToView(o, arg, &o->x4c, &c);
			r = o->radius;
			goto done;
		}
		ctx = o->ctx;
		if (ctx != 0 && ctx->api != 0) {
			d3_UpdateObjectCameraTransform(o, arg, 0);
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
#else
/* ADDRESS: GOLDTL 0x0043a820 */
/* ADDRESS: GOLDDE 0x004335e0 */
char __cdecl d3_GetObjectBoundingSphere(D3_BOUNDING_OBJ* o, char* arg, D3_SPHERE_VEC4* out, float* radius)
{
	D3_BOUNDING_CTX* ctx;
	D3_BOUNDING_CORNER* b;
	D3_BOUNDING_CORNER* q;
	D3_SPHERE_VEC4 c;
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
			d3_TransformPointToRef(o, arg, &o->x4c, &c);
			r = o->radius;
			goto done;
		}
		ctx = o->ctx;
		if (ctx != 0 && ctx->api != 0) {
			d3_UpdateObjectCameraTransform(o, (int)arg, 0);
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
#endif
