/*
 * D3SM point/triangle draw preparation for one mesh instance.
 *
 * Transforms the instance vertices by the active 4x4 matrix into a local point
 * buffer (stride 0x50: transformed xyz at +0x00, projected u/v at +0x10/+0x14,
 * depth byte at +0x42), then walks the triangle index list: rejects triangles
 * that fail the near-plane and viewport tests, clips the interpolated u/v
 * against the viewport, and emits the triangle through fcn_00456080. The point
 * buffer is released on exit.
 *
 * Native body: 0x0045a9d0, 2040 bytes, 624 instructions, no frame pointer,
 * frame sub esp,0x58, cdecl, two pointer arguments.
 */

#include <math.h>

typedef struct {
	char pad0[0x1cc];
	void* mesh;			/* +0x1cc */
	char pad1d0[0x1ec - 0x1d0];
	float* matrix;			/* +0x1ec: 4x4 transform */
	char pad1f0[0x216 - 0x1f0];
	unsigned char flags;		/* +0x216 */
} Obj45a9d0;

typedef struct {
	int count;			/* +0x310: point count */
	int ntris;			/* +0x314: triangle count */
	void* arrays;			/* +0x318 */
} Mesh45a9d0;

typedef struct {
	char pad0[0x27c];
	float* verts;			/* +0x27c: 3 floats per vertex */
	unsigned short* index;		/* +0x280: 3 indices per triangle */
} Arrays45a9d0;

typedef struct {
	float x;			/* +0x00 */
	float y;			/* +0x04 */
	float z;			/* +0x08 */
	char pad0c[4];
	float u;			/* +0x10 */
	float v;			/* +0x14 */
	char pad18[0x42 - 0x18];
	unsigned char depth;		/* +0x42 */
	char pad43[0x50 - 0x43];
} Point45a9d0;

typedef struct {
	float x0;			/* +0x00 */
	float y0;			/* +0x04 */
	float z0;			/* +0x08 */
	char pad0c[4];
	float x1;			/* +0x10 */
	float y1;			/* +0x14 */
	float z1;			/* +0x18 */
	char pad1c[0x20 - 0x1c];
	int width;			/* +0x20 */
	int f24;			/* +0x24 */
	int f28;			/* +0x28 */
	char pad2c[0x30 - 0x2c];
	unsigned char flags;		/* +0x30 */
} Ctx45a9d0;

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* p);
int __cdecl fcn_00451d70(Point45a9d0* a, Point45a9d0* b, Point45a9d0* c,
	float* plane);
int __cdecl fcn_00456080(float* uvs, unsigned char* depths, int arg2,
	int width, unsigned char flags, int arg5, int steps);

/* ADDRESS: GOLDTL 0x0045a9d0 */
int __cdecl fcn_0045a9d0(Obj45a9d0* o, Ctx45a9d0* c)
{
	Mesh45a9d0* mesh;
	Arrays45a9d0* arr;
	Point45a9d0* pts;
	float* src;
	float* m;
	unsigned short* id;
	float uvs[6];
	unsigned char depths[3];
	float plane[4];
	float scale[3];
	float sx;
	float sy;
	float sz;
	float dx;
	float dy;
	float area;
	float dmax;
	float dmin;
	unsigned char flagbyte;
	unsigned char flags;
	int steps;
	int w;
	int i;
	int j;
	int k;
	int n;
	int maxi;
	int mini;
	int v0;
	int v1;
	int v2;
	int inside;
	int edge;

	mesh = (Mesh45a9d0*) o->mesh;
	if (mesh == 0) {
		return 1;
	}
	if (o->matrix == 0) {
		return 1;
	}
	flags = o->flags;
	if ((c->flags & flags & 3) != 0 && (flags & 4) == 0) {
		return 1;
	}
	arr = (Arrays45a9d0*) mesh->arrays;
	pts = (Point45a9d0*) m_alloc(mesh->count * 0x50, "d3sm:Points");

	/* the clip step count follows the viewport depth scale */
	steps = (int) (50.0f / c->x1 + 0.5f);
	steps = steps / 4;
	if (steps > 4) {
		steps = 4;
	} else if (steps < 1) {
		steps = 1;
	}

	/* one over each viewport extent */
	scale[0] = 1.0f / c->x1;
	scale[1] = 1.0f / c->y1;
	scale[2] = 1.0f / c->z1;

	/* pack the draw flags for the renderer */
	flagbyte = (unsigned char) ((2 * (((c->flags & flags & 3) == 0) |
	    (((flags & 8) == 8) ? 2 : 0))) | ((flags & 4) == 4));

	m = o->matrix;

	/* transform each instance vertex and project it into the viewport */
	for (i = 0; i < mesh->count; i++) {
		src = arr->verts + i * 3;
		sx = src[0];
		sy = src[1];
		sz = src[2];
		pts[i].x = ((sz * m[10] + sy * m[6]) + sx * m[2]) + m[14];
		pts[i].y = ((sz * m[11] + sy * m[7]) + sx * m[3]) + m[15];
		pts[i].z = ((sz * m[12] + sy * m[8]) + sx * m[4]) + m[16];
		pts[i].u = (pts[i].x - c->x0) * scale[0] + 0.875f;
		pts[i].v = (pts[i].z - c->z0) * scale[2] + 0.875f;
		dx = (pts[i].y - c->y0) * scale[1];
		if (dx > 254.0f) {
			dx = 254.0f;
		}
		if (dx < 1.0f) {
			dx = 1.0f;
		}
		pts[i].depth = (unsigned char) (int) dx;
	}

	w = c->width;

	/* walk the triangles; reject and clip against near plane and viewport */
	for (j = 0; j < mesh->ntris; j++) {
		Point45a9d0* p0;
		Point45a9d0* p1;
		Point45a9d0* p2;

		id = arr->index + j * 3;
		v0 = id[0];
		v1 = id[1];
		v2 = id[2];
		p0 = (Point45a9d0*) ((char*) pts + v0 * 0x50);
		p1 = (Point45a9d0*) ((char*) pts + v1 * 0x50);
		p2 = (Point45a9d0*) ((char*) pts + v2 * 0x50);

		fcn_00451d70(p0, p1, p2, plane);

		edge = 0;
		if (fabs(plane[1]) >= 0.05 && (flags & 0x10) == 0) {
			area = p0->u * (p1->v - p2->v) +
			    p1->u * (p2->v - p0->v) +
			    p2->u * (p0->v - p1->v);
			if (area >= 0.0f) {
				inside = 1;
			} else {
				inside = 0;
			}
			edge = 1;
		} else {
			inside = 1;
		}
		if (inside == 0) {
			continue;
		}
		if (!(p0->u >= 0.0f && p0->u < (float) w)) {
			continue;
		}
		if (!(p0->v >= 0.0f && p0->v < (float) w)) {
			continue;
		}
		if (!(p1->u >= 0.0f && p1->u < (float) w)) {
			continue;
		}
		if (!(p1->v >= 0.0f && p1->v < (float) w)) {
			continue;
		}
		if (!(p2->u >= 0.0f && p2->u < (float) w)) {
			continue;
		}
		if (!(p2->v >= 0.0f && p2->v < (float) w)) {
			continue;
		}

		if (edge == 0) {
			uvs[0] = p0->u;
			uvs[1] = p0->v;
			uvs[2] = p1->u;
			uvs[3] = p1->v;
			uvs[4] = p2->u;
			uvs[5] = p2->v;
			depths[0] = p0->depth;
			depths[1] = p1->depth;
			depths[2] = p2->depth;
			fcn_00456080(uvs, depths, c->f28, w, flagbyte, c->f24,
			    steps);
			continue;
		}

		/* clipped triangle: interpolate the u/v of the extreme depths */
		for (k = 0; k < 3; k++) {
			Point45a9d0* p;

			p = (Point45a9d0*) ((char*) pts +
			    arr->index[j * 3 + k] * 0x50);
			uvs[k * 2] = p->u;
			uvs[k * 2 + 1] = p->v;
			depths[k] = p->depth;
		}
		dmax = -1e10f;
		dmin = 1e10f;
		maxi = 0;
		mini = 0;
		for (k = 0; k < 3; k++) {
			Point45a9d0* p;

			p = (Point45a9d0*) ((char*) pts +
			    arr->index[j * 3 + k] * 0x50);
			if (p->y > dmax) {
				dmax = p->y;
				maxi = k;
			}
			if (p->y < dmin) {
				dmin = p->y;
				mini = k;
			}
		}
		dx = (uvs[maxi * 2] - uvs[mini * 2]) * 0.875f;
		dy = (uvs[maxi * 2 + 1] - uvs[mini * 2 + 1]) * 0.875f;
		uvs[maxi * 2] -= dx;
		uvs[maxi * 2 + 1] -= dy;
		n = (maxi + 1) % 3;
		uvs[n * 2] += dx;
		uvs[n * 2 + 1] += dy;
		n = (maxi + 2) % 3;
		uvs[n * 2] += dx;
		uvs[n * 2 + 1] += dy;
		for (k = 0; k < 3; k++) {
			if (uvs[k * 2] > (float) (w - 1)) {
				uvs[k * 2] = (float) (w - 1);
			}
			if (uvs[k * 2] < 0.0f) {
				uvs[k * 2] = 0.0f;
			}
			if (uvs[k * 2 + 1] > (float) (w - 1)) {
				uvs[k * 2 + 1] = (float) (w - 1);
			}
			if (uvs[k * 2 + 1] < 0.0f) {
				uvs[k * 2 + 1] = 0.0f;
			}
		}
		fcn_00456080(uvs, depths, c->f28, w, flagbyte, c->f24, steps);
	}

	m_FreeTracked(pts);
	return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_fcn_0045a9d0[496] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
