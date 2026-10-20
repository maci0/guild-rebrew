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
void __cdecl fcn_0044a390(MeshBox* m)
{
	Vert* v;
	int i;
	int n;
	float r;
	float d;
	float cx;
	float cy;
	float cz;
	float bb[6];
	float dx;
	float dy;
	float dz;

	n = m->vert_count;
	v = m->verts;
	r = 0.0f;
	for (i = n; i > 0; i--) {
		d = v->px * v->px + v->py * v->py + v->pz * v->pz;
		if (r < d)
			r = d;
		v++;
	}
	m->center_x = 0.0f;
	m->center_y = 0.0f;
	m->center_z = 0.0f;
	m->diagonal = (float) sqrt(r);
	m->radius = (float) sqrt(r);
	if (n > 0) {
		bb[0] = 1e10f;
		bb[1] = 1e10f;
		bb[2] = 1e10f;
		bb[3] = *(float*) 0x662c6c;
		bb[4] = -1e10f;
		bb[5] = -1e10f;
		v = m->verts;
		for (i = n; i > 0; i--) {
			if (v->px < bb[0])
				bb[0] = v->px;
			if (v->py < bb[1])
				bb[1] = v->py;
			if (v->pz < bb[2])
				bb[2] = v->pz;
			if (bb[4] < v->px)
				bb[4] = v->px;
			if (bb[5] < v->py)
				bb[5] = v->py;
			if (bb[3] < v->pz)
				bb[3] = v->pz;
			v++;
		}
		m->verts[m->vert_count].px = bb[0];
		m->verts[m->vert_count].py = bb[1];
		m->verts[m->vert_count].pz = bb[2];
		m->verts[m->vert_count + 1].px = bb[4];
		m->verts[m->vert_count + 1].py = bb[1];
		m->verts[m->vert_count + 1].pz = bb[2];
		m->verts[m->vert_count + 2].px = bb[0];
		m->verts[m->vert_count + 2].py = bb[5];
		m->verts[m->vert_count + 2].pz = bb[2];
		m->verts[m->vert_count + 3].px = bb[4];
		m->verts[m->vert_count + 3].py = bb[5];
		m->verts[m->vert_count + 3].pz = bb[2];
		m->verts[m->vert_count + 4].px = bb[0];
		m->verts[m->vert_count + 4].py = bb[1];
		m->verts[m->vert_count + 4].pz = bb[3];
		m->verts[m->vert_count + 5].px = bb[4];
		m->verts[m->vert_count + 5].py = bb[1];
		m->verts[m->vert_count + 5].pz = bb[3];
		m->verts[m->vert_count + 6].px = bb[0];
		m->verts[m->vert_count + 6].py = bb[5];
		m->verts[m->vert_count + 6].pz = bb[3];
		m->verts[m->vert_count + 7].px = bb[4];
		m->verts[m->vert_count + 7].py = bb[5];
		m->verts[m->vert_count + 7].pz = bb[3];
		dx = bb[4] - bb[0];
		dy = bb[5] - bb[1];
		dz = bb[3] - bb[2];
		m->diagonal = (float) sqrt(dz * dz + dy * dy + dx * dx);
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
		m->center_x = cx * *(float*) 0x662a34;
		m->center_y = cy * *(float*) 0x662a34;
		m->center_z = cz * *(float*) 0x662a34;
	}
	r = 0.0f;
	v = m->verts;
	for (i = n; i > 0; i--) {
		dx = v->px - m->center_x;
		dy = v->py - m->center_y;
		dz = v->pz - m->center_z;
		d = dx * dx + dy * dy + dz * dz;
		if (r < d)
			r = d;
		v++;
	}
	m->spread = (float) sqrt(r);
}
