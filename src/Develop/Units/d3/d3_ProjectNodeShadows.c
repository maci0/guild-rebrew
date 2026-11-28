/* per-node lighting/shadow vertex build: 8-vertex loop, d3_TransformPoint/fcn_00455140/fcn_00457140, IDev vtable slot 0x1f0, world matrix at [0x6b8014]+0x18c. */

#include "Develop/Units/d3/d3_camera.h"
#include "Develop/Units/d3/client_lighting.h"
extern char* g_6b86e0; extern float d3_UnitAxisVectors[3];
typedef struct D3_SHADOW_PROJ_VEC4 {
	float x;
	float y;
	float z;
	float w;
} D3_SHADOW_PROJ_VEC4;

typedef struct D3_SHADOW_CAMERA {
	char pad0[0x4c];
	float x;
	float y;
	float z;
	char pad58[0x18c - 0x58];
	float m00;
	float m01;
	float m02;
	char pad98[0x19c - 0x198];
	float m10;
	float m11;
	float m12;
	char padd8[0x1ac - 0x1a8];
	float m20;
	float m21;
	float m22;
	char padb8[0x1bc - 0x1b8];
	float tx;
	float ty;
	float tz;
} D3_SHADOW_CAMERA;

typedef struct D3_SHADOW_QUERY_API {
	char pad0[0x1f0];
	float* (__cdecl* query)(char*, char*, char*);
} D3_SHADOW_QUERY_API;

void __cdecl d3_UpdateObjectCameraTransform(char*, char*, int);
void __cdecl d3_TransformPoint(char*, char*, D3_SHADOW_PROJ_VEC4*);
void __cdecl d3_TransformDirection(char*, float*, D3_SHADOW_PROJ_VEC4*);
float __cdecl d3_GetShadowPlaneHeight(char*, char*, char*);
unsigned char __cdecl d3_TestBoxAgainstFrustum(float*, int, int);
void __cdecl d3_UpdateNodeShadowMap(char*, char*, int, float);

/* ADDRESS: GOLDTL 0x00456ef0 */
/* ADDRESS: GOLDDE 0x0044c6b0 */
void __cdecl d3_ProjectNodeShadows(char* node)
{
	D3_SHADOW_PROJ_VEC4 position;
	D3_SHADOW_PROJ_VEC4 direction;
	D3_SHADOW_PROJ_VEC4 r;
	float h;
	D3_SHADOW_PROJ_VEC4 d;
	float t;
	D3_SHADOW_CAMERA* cam;
	float* base;
	float* q;
	char* s;
	char* ctx;
	int i;

	*(unsigned char*) (node + 0x216) &= 0x7f;
	if (!(*(unsigned char*) (node + 0x215) & 1)) {
		return;
	}
	if (*(char**) (node + 0x1ec) == 0) {
		return;
	}
	if (!(*(unsigned char*) (node + 0x216) & 0x20)) {
		d3_UpdateObjectCameraTransform(node, (*(unsigned char*) (node + 0x214) & 0x20) ? 0 : d3_ActiveCamera, 0);
	}
	for (s = g_6b86e0; s != 0; s = *(char**) (s + 0x1f0)) {
		ctx = *(char**) (node + 0x1cc);
		if (ctx == 0) {
			break;
		}
		d3_TransformPoint(s, s + 0x4c, &position);
		d3_TransformDirection(s, d3_UnitAxisVectors, &direction);
		h = d3_GetShadowPlaneHeight(node, ctx, s);
		base = ((D3_SHADOW_QUERY_API*) *(char**) (ctx + 0x318))->query(
		    node, ctx, *(char**) (node + 0x1ec) + 8);
		q = base;
		i = 8;
		do {
			if (*(unsigned char*) (s + 0x215) & 4) {
				t = -((q[1] - h) / direction.y);
				r.x = direction.x * t + q[0];
				r.y = direction.y * t + q[1];
				r.z = direction.z * t + q[2];
			} else {
				d.x = position.x - q[0];
				d.y = position.y - q[1];
				d.z = position.z - q[2];
				t = -((position.y - h) / d.y);
				r.x = d.x * t + position.x;
				r.y = d.y * t + position.y;
				r.z = d.z * t + position.z;
			}
			cam = (D3_SHADOW_CAMERA*) d3_ActiveCamera;
			d.x = r.x - cam->x;
			d.y = r.y - cam->y;
			d.z = r.z - cam->z;
			q[0] = d.z * cam->m20 + d.y * cam->m10 + d.x * cam->m00 + cam->tx;
			cam = (D3_SHADOW_CAMERA*) d3_ActiveCamera; q[1] = d.z * cam->m21 + d.y * cam->m11 + d.x * cam->m01 + cam->ty;
			cam = (D3_SHADOW_CAMERA*) d3_ActiveCamera; q[2] = d.z * cam->m22 + d.y * cam->m12 + d.x * cam->m02 + cam->tz;
			q += 0x14;
			i--;
		} while (i != 0);
		if (!(d3_TestBoxAgainstFrustum(base, 0, 0) & 0x40)) {
			*(unsigned char*) (node + 0x216) |= 0x80;
			d3_UpdateNodeShadowMap(node, s, d3_CurrentFloor, h);
		}
	}
}
