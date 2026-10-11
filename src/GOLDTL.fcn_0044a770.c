// FUNCTION: GOLDTL 0x44a770

// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} Vec3a770;

// SIZE 0x10
typedef struct {
	float a;
	float b;
	float c;
	float d;
} Plane44a770;

// SIZE 0x18
typedef struct {
	Vec3a770 pos;
	Vec3a770 n;
} Vert44a770;

// SIZE 0x18
typedef struct {
	int uv[6];
} Uv44a770;

// SIZE 0x38
typedef struct {
	Uv44a770 uv;
	int idx[3];
	int mat;
	int tex;
	Vec3a770 n;
} Face44a770;

// SIZE 0x70
typedef struct {
	char pad0[0x54];
	unsigned char flags;
	char pad55[0x1b];
} Mat44a770;

// SIZE 0x2a4
typedef struct {
	char pad0[0x40];
	Vert44a770* verts;
	int nverts;
	Face44a770* faces;
	int nfaces;
	char pad50[0x1e4 - 0x50];
	int ntex;
	char pad1e8[0x204 - 0x1e8];
	Vec3a770 box[8];
	int f264;
	int f268;
	Plane44a770 plane;
	char pad27c[8];
	Mat44a770** texmat;
	int* facemat;
	Uv44a770* uvs;
	char pad290[0x2a1 - 0x290];
	unsigned char flags;
	char pad2a2[2];
} Obj44a770;

extern char* g_104049c;

void __cdecl fcn_0044a390(Obj44a770* m);
void __cdecl fcn_0044a290(Obj44a770* m);
int __cdecl fcn_0044aec0(Obj44a770* m);
void __cdecl fcn_0044a9f0(Obj44a770* m);
void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);
Plane44a770* __stdcall D3DXPlaneFromPoints(Plane44a770* out, Vec3a770* a, Vec3a770* b, Vec3a770* c);
Plane44a770* __stdcall D3DXPlaneNormalize(Plane44a770* out, Plane44a770* in);

void __cdecl fcn_0044a770(Obj44a770* m, char normals)
{
	Vec3a770 pts[3];
	int i;
	int j;
	int k;

	fcn_0044a390(m);
	if (normals) {
		fcn_0044a290(m);
	}
	for (i = 0; i < 8; i++) {
		m->box[i].x = m->verts[m->nverts + i].pos.x;
		m->box[i].y = m->verts[m->nverts + i].pos.y;
		m->box[i].z = m->verts[m->nverts + i].pos.z;
	}
	m->f264 = fcn_0044aec0(m);
	m->f268 = 0;
	if (m->flags & 2) {
		fcn_0044a9f0(m);
	}
	m->flags &= ~4;
	for (i = 0; i < m->nfaces; i++) {
		if (m->faces[i].mat >= 0 && (((Mat44a770*)g_104049c)[m->faces[i].mat].flags & 0x10)) {
			for (k = 0; k < 3; k++) {
				pts[k].x = m->verts[m->faces[i].idx[k]].pos.x;
				pts[k].y = m->verts[m->faces[i].idx[k]].pos.y;
				pts[k].z = m->verts[m->faces[i].idx[k]].pos.z;
			}
			D3DXPlaneFromPoints(&m->plane, &pts[0], &pts[1], &pts[2]);
			D3DXPlaneNormalize(&m->plane, &m->plane);
			m->flags |= 4;
			break;
		}
	}
	m->texmat = (Mat44a770**) m_alloc(m->ntex * 4, "d3io:StockObjectTextures");
	for (i = 0; i < m->ntex; i++) {
		for (j = 0; j < m->nfaces; j++) {
			if (m->faces[j].tex == i && m->faces[j].mat >= 0) {
				m->texmat[i] = &((Mat44a770*)g_104049c)[m->faces[j].mat];
				break;
			}
		}
	}
	m->facemat = (int*) m_alloc(m->nfaces * 4, "d3io:StockObjectMaterials");
	m->uvs = (Uv44a770*) m_alloc(m->nfaces * 24, "d3io:StockObjectUVs");
	for (i = 0; i < m->nfaces; i++) {
		m->facemat[i] = m->faces[i].tex;
		for (k = 0; k < 6; k++) {
			m->uvs[i].uv[k] = m->faces[i].uv.uv[k];
		}
	}
	m_FreeTracked(m->verts);
	m->verts = 0;
	m_FreeTracked(m->faces);
	m->faces = 0;
}
