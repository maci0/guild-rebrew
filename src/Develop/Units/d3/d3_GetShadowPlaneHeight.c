/* GOLD twin of GOLDTL fcn_00457140 with the GOLD object layout: entity array
 * at 0x754 with 0x80-byte slots, parent at 0x1f8, flags byte at 0x211. */
/* m is a double compared as !(m < b[i].y): that is the spelling that loads the
 * float first and copies m for fld/fld st(1)/fcompp with the test ah,5 mask. */

typedef struct D3_SHADOW_VEC4 {
	float x;
	float y;
	float z;
	float w;
} D3_SHADOW_VEC4;
/* SIZE 0x10 */

typedef struct D3_SHADOW_ENT {
	int active;
	char pad4[0x18 - 4];
	float x;
	float y;
	float z;
	char pad24[0x58 - 0x24];
	float value;
	char pad5c[0x80 - 0x5c];
} D3_SHADOW_ENT;

typedef struct D3_SHADOW_OV {
	char pad0[0x754];
	D3_SHADOW_ENT ents[4];
	float height;
} D3_SHADOW_OV;

typedef struct D3_SHADOW_OBJ {
	char pad0[0x4c];
	int x4c;
	char pad50[0x1ec - 0x50];
	D3_SHADOW_OV* ov;
	char pad1f0[0x1f8 - 0x1f0];
	struct D3_SHADOW_OBJ* parent;
	char pad1fc[0x211 - 0x1fc];
	unsigned char flags;
} D3_SHADOW_OBJ;

typedef struct D3_SHADOW_API {
	char pad0[0x1d4];
	float base;
	char pad1d8[0x1f4 - 0x1d8];
	struct D3_SHADOW_BOX*(__cdecl* query)(D3_SHADOW_OBJ* o, void* ctx, char* data);
} D3_SHADOW_API;

typedef struct D3_SHADOW_BOX {
	float x;
	float y;
	char pad8[0x50 - 8];
} D3_SHADOW_BOX;

typedef struct D3_SHADOW_CTX {
	char pad0[0x10];
	D3_SHADOW_API* api;
} D3_SHADOW_CTX;

typedef struct D3_SHADOW_H_ENT {
	int active;
	char pad4[0x1c - 4];
	float x;
	float y;
	float z;
	char pad28[0x5c - 0x28];
	float value;
	char pad60[0x9c - 0x60];
} D3_SHADOW_H_ENT;

typedef struct D3_SHADOW_OVERLAY {
	char pad0[0x1384];
	D3_SHADOW_H_ENT ents[4];
	float height;
} D3_SHADOW_OVERLAY;

typedef struct D3_SHADOW_H_OBJ {
	char pad0[0x4c];
	int x4c;
	char pad50[0x1ec - 0x50];
	D3_SHADOW_OVERLAY* ov;
	char pad1f0[0x1fc - 0x1f0];
	struct D3_SHADOW_H_OBJ* parent;
	char pad200[0x215 - 0x200];
	unsigned char flags;
} D3_SHADOW_H_OBJ;

typedef struct D3_SHADOW_H_API {
	char pad0[0x1d4];
	float base;
	char pad1d8[0x1f0 - 0x1d8];
	struct D3_SHADOW_H_BOX*(__cdecl* query)(D3_SHADOW_H_OBJ* node, void* ctx, char* data);
} D3_SHADOW_H_API;

typedef struct D3_SHADOW_H_BOX {
	float x;
	float y;
	char pad8[0x50 - 8];
} D3_SHADOW_H_BOX;

typedef struct D3_SHADOW_H_CTX {
	char pad0[0x318];
	D3_SHADOW_H_API* api;
} D3_SHADOW_H_CTX;

extern float g_5ebaa4;
extern float g_662c94;

void __cdecl d3_TransformPoint(void* o, int* p, void* out);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0045bcc0 */
float __cdecl d3_GetShadowPlaneHeight(D3_SHADOW_OBJ* o, D3_SHADOW_CTX* ctx)
{
	D3_SHADOW_OBJ* p;
	D3_SHADOW_OV* ov;
	D3_SHADOW_BOX* b;
	float res;
	double m;
	D3_SHADOW_VEC4 pos;
	char found;
	int i;

	res = 0.0f;
	found = 0;
	d3_TransformPoint(o, &o->x4c, &pos);
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
#else
/* ADDRESS: GOLDTL 0x00457140 */
float __cdecl d3_GetShadowPlaneHeight(D3_SHADOW_H_OBJ* node, D3_SHADOW_H_CTX* ctx)
{
	D3_SHADOW_H_OBJ* p;
	D3_SHADOW_OVERLAY* ov;
	D3_SHADOW_H_BOX* b;
	float res;
	double m;
	D3_SHADOW_VEC4 pos;
	char found;
	int i;

	res = 0.0f;
	found = 0;
	d3_TransformPoint(node, &node->x4c, &pos);
	if (node->parent != 0) {
		for (p = node->parent; p != 0; p = p->parent) {
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
	if (node->ov != 0) {
		if (node->flags & 0x10) {
			return pos.y - ctx->api->base + node->ov->height;
		}
		b = ctx->api->query(node, ctx, (char*)node->ov + 8);
		m = g_662c94;
		for (i = 0; i < 8; i++) {
			if (!(m < b[i].y)) {
				m = b[i].y;
			}
		}
		res = (float)(m + node->ov->height);
	}
done:
	return res;
}
#endif
