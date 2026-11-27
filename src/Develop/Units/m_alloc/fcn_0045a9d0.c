/*
 * D3SM point/triangle draw preparation for one mesh instance.
 *
 * Transforms the instance vertices by the active 4x4 matrix into a local point
 * buffer (stride 0x50: transformed xyz at +0x00, projected u/v at
 * +0x10/+0x14, depth byte at +0x42), then walks the triangle index list:
 * rejects triangles that fail the near-plane and viewport tests, clamps the
 * interpolated u/v against the viewport and emits the triangle through
 * fcn_00456080. The point buffer is released on exit.
 *
 * Native body: 0x0045a9d0, 2040 bytes, 624 instructions, no frame pointer,
 * frame sub esp,0x58, cdecl, two pointer arguments, char result.
 */

#include <math.h>

#define D3_MIN(a, b) ((b) < (a) ? (b) : (a))
#define D3_MAX(a, b) ((b) > (a) ? (b) : (a))

typedef struct {
	char pad0[0x1cc];
	void* mesh;			/* +0x1cc */
	char pad1d0[0x1ec - 0x1d0];
	float* matrix;			/* +0x1ec: 4x4 transform */
	char pad1f0[0x216 - 0x1f0];
	unsigned char flags;		/* +0x216 */
} Obj45a9d0;

typedef struct {
	char prefix[0x310];
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
	float ext[3];			/* +0x10: viewport extents */
	char pad1c[0x20 - 0x1c];
	int width;			/* +0x20 */
	int f24;			/* +0x24 */
	int f28;			/* +0x28 */
	char pad2c[0x30 - 0x2c];
	unsigned char flags;		/* +0x30 */
} Ctx45a9d0;

#include "Develop/Units/d3/d3_triangle_neighbors.h"

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* p);
int __cdecl d3_CalculateTriangleNormal(Point45a9d0* a, Point45a9d0* b, Point45a9d0* c,
	float* plane);
int __cdecl d3_RasterizeHeightTriangle(float* uvs, unsigned char* depths, int arg2,
	int width, unsigned char flags, int arg5, int steps);

/* ADDRESS: GOLDTL 0x0045a9d0 */
char __cdecl fcn_0045a9d0(Obj45a9d0* o, Ctx45a9d0* c)
{
	Mesh45a9d0* mesh;
	Arrays45a9d0* arrays;
	Point45a9d0* pts;
	Point45a9d0* p;
	Point45a9d0* p0;
	Point45a9d0* p1;
	Point45a9d0* p2;
	float* fp;
	float uvs[6];
	unsigned char depths[3];
	float scale[3];
	float depth;
	float area;
	float dmax;
	float dmin;
	float du;
	float dv;
	unsigned short* id;
	unsigned char flagbyte;
	unsigned char ext;
	unsigned char visible;
	int steps;
	int k;
	int n;
	int i;
	int maxi;
	int mini;
	int best;

	mesh = (Mesh45a9d0*) o->mesh;
	if (mesh == 0) {
		return 1;
	}
	if (o->matrix == 0) {
		return 1;
	}
	if ((c->flags & (o->flags & 3)) != 0 && (o->flags & 4) == 0) {
		return 1;
	}

	pts = (Point45a9d0*) m_alloc(mesh->count * 0x50, "d3sm:Points");
	/* pack the draw flags for the renderer */
	flagbyte = (unsigned char) ((2 * (((c->flags & (o->flags & 3)) == 0) |
	    (((o->flags & 8) == 8) * 2))) | ((o->flags & 4) == 4));
	steps = (int) (50.0f / c->ext[0] + 0.5f) / 4;
	if (steps > 4) {
		steps = 4;
	} else if (steps < 1) {
		steps = 1;
	}
	for (i = 0; i < 3; i++) {
		scale[i] = 1.0f / c->ext[i];
	}

	/* transform each instance vertex and project it into the viewport */
	for (i = 0; i < mesh->count; i++) {
		pts[i].x = ((Arrays45a9d0*) mesh->arrays)->verts[i * 3 + 2] *
		    o->matrix[10] +
		    ((Arrays45a9d0*) mesh->arrays)->verts[i * 3 + 1] *
		    o->matrix[6] +
		    o->matrix[2] * ((Arrays45a9d0*) mesh->arrays)->verts[i * 3] +
		    o->matrix[14];
		pts[i].y = ((Arrays45a9d0*) mesh->arrays)->verts[i * 3 + 2] *
		    o->matrix[11] +
		    ((Arrays45a9d0*) mesh->arrays)->verts[i * 3 + 1] *
		    o->matrix[7] +
		    o->matrix[3] * ((Arrays45a9d0*) mesh->arrays)->verts[i * 3] +
		    o->matrix[15];
		pts[i].z = ((Arrays45a9d0*) mesh->arrays)->verts[i * 3 + 2] *
		    o->matrix[12] +
		    ((Arrays45a9d0*) mesh->arrays)->verts[i * 3 + 1] *
		    o->matrix[8] +
		    o->matrix[4] * ((Arrays45a9d0*) mesh->arrays)->verts[i * 3] +
		    o->matrix[16];
		pts[i].u = (pts[i].x - c->x0) * scale[0] + 0.875f;
		pts[i].v = (pts[i].z - c->z0) * scale[2] + 0.875f;
		depth = (pts[i].y - c->y0) * scale[1];
		depth = D3_MIN(D3_MAX(depth, 1.0f), 254.0f);
		pts[i].depth = (unsigned char) (int) depth;
	}

	/* walk the triangles; reject and clip against near plane and viewport */
	for (i = 0; i < mesh->ntris; i++) {
		float plane[4];
		id = ((Arrays45a9d0*) mesh->arrays)->index + i * 3;
		p0 = (Point45a9d0*) ((char*) pts + id[0] * 0x50);
		p1 = (Point45a9d0*) ((char*) pts + id[1] * 0x50);
		p2 = (Point45a9d0*) ((char*) pts + id[2] * 0x50);

		d3_CalculateTriangleNormal(p0, p1, p2, plane);

		if (fabs(plane[1]) < 0.05 && (o->flags & 0x10) == 0) {
			ext = 1;
		} else {
			area = p2->u * p1->v - p1->u * p2->v +
			    p1->u * p0->v - p0->u * p1->v +
			    p0->u * p2->v - p2->u * p0->v;
			visible = (unsigned char) (area < 0.0f);
			ext = 0;
			if (!visible) {
				continue;
			}
		}
		if (!(p0->u >= 0.0f && p0->u < (float) c->width)) {
			continue;
		}
		if (!(p0->v >= 0.0f && p0->v < (float) c->width)) {
			continue;
		}
		if (!(p1->u >= 0.0f && p1->u < (float) c->width)) {
			continue;
		}
		if (!(p1->v >= 0.0f && p1->v < (float) c->width)) {
			continue;
		}
		if (!(p2->u >= 0.0f && p2->u < (float) c->width)) {
			continue;
		}
		if (!(p2->v >= 0.0f && p2->v < (float) c->width)) {
			continue;
		}

		if (ext != 0) {
			/* degenerate triangle: shift the extreme vertex and spread
			 * the plane offset over the two remaining vertices */
			dmax = -1.0e10f;
			dmin = 1.0e10f;
			arrays = (Arrays45a9d0*) mesh->arrays;
			for (k = 0; k < 3; k++) {
				p = &pts[arrays->index[i * 3 + k]];
				uvs[k * 2] = p->u;
				uvs[k * 2 + 1] = p->v;
				depths[k] = p->depth;
				if (p->y > dmax) {
					dmax = p->y;
					maxi = k;
				}
				if (p->y < dmin) {
					dmin = p->y;
					mini = k;
				}
			}
			best = mini;
			if (fabs(pts[arrays->index[i * 3 + g_662c7c[mini].next]].y +
			    pts[arrays->index[i * 3 + g_662c7c[mini].previous]].y - dmin * 2.0f) <
			    fabs(pts[arrays->index[i * 3 + g_662c7c[maxi].next]].y +
			    pts[arrays->index[i * 3 + g_662c7c[maxi].previous]].y - dmax * 2.0f)) {
				best = maxi;
			}
			du = plane[0] * 0.875f;
			uvs[best * 2] -= du;
			dv = plane[2] * 0.875f;
			uvs[best * 2 + 1] -= dv;
			n = (best + 1) % 3;
			uvs[n * 2] += du;
			uvs[n * 2 + 1] += dv;
			n = (best + 2) % 3;
			uvs[n * 2] += du;
			uvs[n * 2 + 1] += dv;
			for (k = 0; k < 3; k++) {
				uvs[k * 2] = D3_MAX(D3_MIN(uvs[k * 2], (float) (c->width - 1)), 0.0f);
				uvs[k * 2 + 1] = D3_MAX(D3_MIN(uvs[k * 2 + 1], (float) (c->width - 1)), 0.0f);
				depths[k] = pts[arrays->index[i * 3 + k]].depth;
			}
		} else {
			arrays = (Arrays45a9d0*) mesh->arrays;
			for (k = 0; k < 3; k++) {
				fp = &pts[arrays->index[i * 3 + k]].u;
				uvs[k * 2] = D3_MAX(D3_MIN(*fp, (float) (c->width - 1)), 0.0f);
				fp = &pts[arrays->index[i * 3 + k]].v;
				uvs[k * 2 + 1] = D3_MAX(D3_MIN(*fp, (float) (c->width - 1)), 0.0f);
				depths[k] = pts[arrays->index[i * 3 + k]].depth;
			}
		}
		d3_RasterizeHeightTriangle(uvs, depths, c->f28, c->width, flagbyte, c->f24,
		    steps);
	}

	m_FreeTracked(pts);
	return 1;
}
