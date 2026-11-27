#include <math.h>

/* SIZE 0x18 */
typedef struct Vert {
	float px;
	float py;
	float pz;
	float nx;
	float ny;
	float nz;
} Vert;

/* Mesh view used by the bounding-box pass; native offsets proven. */
typedef struct MeshBox {
	char pad0[0x40];
	Vert* verts;
	int vert_count;
	char* faces;
	int face_count;
	char pad50[0x18];
	float center_x;
	float center_y;
	float center_z;
	char pad74[0x160];
	float radius;
	float diagonal;
	float spread;
} MeshBox;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0044ce40 */
void __cdecl d3_RecalculateObjectBounds(char* object)
{
	float radius;
	float length;
	float mn[4], mx[4];
	float dx, dy, dz;
	float sx, sy, sz;
	float* p;
	float* corners;
	int n;
	int i;

	radius = 0.0f;
	n = *(int*) (object + 0x44);
	if (n > 0) {
		p = *(float**) (object + 0x40);
		for (i = n; i > 0; i--, p += 6) {
			length = (float) sqrt(p[2] * p[2] + p[0] * p[0] + p[1] * p[1]);
			if (length > radius)
				radius = length;
		}
	}
	*(float*) (object + 0x1d8) = radius;
	*(float*) (object + 0x1d4) = radius;
	*(float*) (object + 0x68) = 0.0f;
	*(float*) (object + 0x6c) = 0.0f;
	*(float*) (object + 0x70) = 0.0f;
	if (n <= 0)
		return;
	mx[0] = -1.0e10f;
	mx[2] = -1.0e10f;
	mx[1] = -1.0e10f;
	mn[0] = 1.0e10f;
	mn[1] = 1.0e10f;
	mn[2] = 1.0e10f;
	corners = *(float**) (object + 0x40);
	for (p = corners, i = n; i > 0; i--, p += 6) {
		if (!(mn[0] < p[0])) mn[0] = p[0];
		if (!(p[1] > mn[1])) mn[1] = p[1];
		if (!(p[2] > mn[2])) mn[2] = p[2];
		if (!(mx[0] > p[0])) mx[0] = p[0];
		if (!(p[1] < mx[1])) mx[1] = p[1];
		if (!(mx[2] > p[2])) mx[2] = p[2];
	}
	corners[n * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 1] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 2] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 1) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 7] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 8] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 2) * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 13] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 14] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 3) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 19] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 20] = mn[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 4) * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 25] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 26] = mx[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 5) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 31] = mn[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 32] = mx[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 6) * 6] = mn[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 37] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 38] = mx[2];
	(*(float**) (object + 0x40))[(*(int*) (object + 0x44) + 7) * 6] = mx[0];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 43] = mx[1];
	(*(float**) (object + 0x40))[*(int*) (object + 0x44) * 6 + 44] = mx[2];
	corners = *(float**) (object + 0x40) + *(int*) (object + 0x44) * 6;
	dy = mx[1] - mn[1];
	dz = mx[2] - mn[2];
	dx = mx[0] - mn[0];
	*(float*) (object + 0x1d8) = (float) sqrt(dz * dz + dy * dy + dx * dx);
	sx = sy = sz = 0.0f;
	for (i = 8, p = corners; i > 0; i--, p += 6) {
		sx += p[0];
		sy += p[1];
		sz += p[2];
	}
	*(float*) (object + 0x68) = sx * 0.125f;
	*(float*) (object + 0x6c) = sy * 0.125f;
	*(float*) (object + 0x70) = sz * 0.125f;
}
#else
/* ADDRESS: GOLDTL 0x0044a390 */
void __cdecl d3_RecalculateObjectBounds(MeshBox* m)
{
	Vert* v;
	int i;
	int n;
	float r;
	float d;
	float cx;
	float cy;
	float cz;
	float min_v[4];
	float max_v[4];

	n = m->vert_count;
	r = 0.0f;
	if (n > 0) {
		v = m->verts;
		for (i = n; i > 0; i--) {
			d = v->pz * v->pz + v->px * v->px + v->py * v->py;
			if (d > r)
				r = d;
			v++;
		}
	}
	m->center_x = 0.0f;
	m->center_y = 0.0f;
	m->center_z = 0.0f;
	m->diagonal = (float) sqrt(d); /* Native reloads the last squared distance. */
	m->radius = (float) sqrt(d);
	if (n > 0) {
		max_v[2] = -1e10f;
		max_v[0] = -1e10f;
		max_v[1] = -1e10f;
		min_v[0] = 1e10f;
		min_v[1] = 1e10f;
		min_v[2] = 1e10f;
		v = m->verts;
		for (i = n; i > 0; i--) {
			if (!(min_v[0] < v->px))
				min_v[0] = v->px;
			if (!(v->py > min_v[1]))
				min_v[1] = v->py;
			if (!(v->pz > min_v[2]))
				min_v[2] = v->pz;
			if (!(max_v[0] > v->px))
				max_v[0] = v->px;
			if (!(v->py < max_v[1]))
				max_v[1] = v->py;
			if (!(max_v[2] > v->pz))
				max_v[2] = v->pz;
			v++;
		}
		m->verts[n].px = min_v[0];
		m->verts[m->vert_count].py = min_v[1];
		m->verts[m->vert_count].pz = min_v[2];
		m->verts[m->vert_count + 1].px = max_v[0];
		m->verts[m->vert_count + 1].py = min_v[1];
		m->verts[m->vert_count + 1].pz = min_v[2];
		m->verts[m->vert_count + 2].px = min_v[0];
		m->verts[m->vert_count + 2].py = max_v[1];
		m->verts[m->vert_count + 2].pz = min_v[2];
		m->verts[m->vert_count + 3].px = max_v[0];
		m->verts[m->vert_count + 3].py = max_v[1];
		m->verts[m->vert_count + 3].pz = min_v[2];
		m->verts[m->vert_count + 4].px = min_v[0];
		m->verts[m->vert_count + 4].py = min_v[1];
		m->verts[m->vert_count + 4].pz = max_v[2];
		m->verts[m->vert_count + 5].px = max_v[0];
		m->verts[m->vert_count + 5].py = min_v[1];
		m->verts[m->vert_count + 5].pz = max_v[2];
		m->verts[m->vert_count + 6].px = min_v[0];
		m->verts[m->vert_count + 6].py = max_v[1];
		m->verts[m->vert_count + 6].pz = max_v[2];
		m->verts[m->vert_count + 7].px = max_v[0];
		m->verts[m->vert_count + 7].py = max_v[1];
		m->verts[m->vert_count + 7].pz = max_v[2];
		max_v[0] -= min_v[0];
		max_v[1] -= min_v[1];
		max_v[2] -= min_v[2];
		m->diagonal = (float) sqrt(max_v[0] * max_v[0] + max_v[1] * max_v[1] + max_v[2] * max_v[2]);
		cx = 0.0f;
		cy = 0.0f;
		cz = 0.0f;
		v = &m->verts[m->vert_count];
		for (i = 8; i > 0; i--) {
			cx += v->px;
			cy += v->py;
			cz += v->pz;
			v++;
		}
		m->center_x = cx * 0.125f;
		m->center_y = cy * 0.125f;
		m->center_z = cz * 0.125f;
	}
	r = 0.0f;
	n = m->vert_count;
	if (n > 0) {
		v = m->verts;
		for (i = n; i > 0; i--) {
			float dx = v->px - m->center_x;
			float dy = v->py - m->center_y;
			float dz = v->pz - m->center_z;
			d = dz * dz + dy * dy + dx * dx;
			if (d > r)
				r = d;
			v++;
		}
	}
	m->spread = (float) sqrt(r);
}
#endif
