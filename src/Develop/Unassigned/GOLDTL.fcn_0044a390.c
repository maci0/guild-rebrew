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
