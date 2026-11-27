

// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} StockVec3;

// SIZE 0x10
typedef struct {
	float a;
	float b;
	float c;
	float d;
} StockPlane;

// SIZE 0x18
typedef struct {
	StockVec3 pos;
	StockVec3 n;
} StockVertex;

// SIZE 0x18
typedef struct {
	int uv[6];
} StockUv;

// SIZE 0x38
typedef struct {
	StockUv uv;
	int idx[3];
	int mat;
	int tex;
	StockVec3 n;
} StockFace;

// SIZE 0x70
typedef struct {
	char pad0[0x54];
	unsigned char flags;
	char pad55[0x1b];
} StockMaterial;

// SIZE 0x2a4
typedef struct {
	char pad0[0x40];
	StockVertex* verts;
	int nverts;
	StockFace* faces;
	int nfaces;
	char pad50[0x1e4 - 0x50];
	int ntex;
	char pad1e8[0x204 - 0x1e8];
	StockVec3 box[8];
	int f264;
	int f268;
	StockPlane plane;
	char pad27c[8];
	StockMaterial** texmat;
	int* facemat;
	StockUv* uvs;
	char pad290[0x2a1 - 0x290];
	unsigned char flags;
	char pad2a2[2];
} StockObjectData;

extern char* g_104049c;

void __cdecl d3_RecalculateObjectBounds(StockObjectData* m);
void __cdecl d3_RecalculateMeshNormals(StockObjectData* m);
int __cdecl d3_BuildStockObjectMesh(StockObjectData* m);
void __cdecl d3_GenerateVertexExpandedMesh(StockObjectData* m);
void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);
StockPlane* __stdcall D3DXPlaneFromPoints(StockPlane* out, StockVec3* a, StockVec3* b, StockVec3* c);
StockPlane* __stdcall D3DXPlaneNormalize(StockPlane* out, StockPlane* in);

void __cdecl d3_FinalizeStockObjectMesh(StockObjectData* m, char normals)
{
	StockVec3 pts[3];
	int i;
	int j;
	int k;

	d3_RecalculateObjectBounds(m);
	if (normals) {
		d3_RecalculateMeshNormals(m);
	}
	for (i = 0; i < 8; i++) {
		m->box[i].x = m->verts[m->nverts + i].pos.x;
		m->box[i].y = m->verts[m->nverts + i].pos.y;
		m->box[i].z = m->verts[m->nverts + i].pos.z;
	}
	m->f264 = d3_BuildStockObjectMesh(m);
	m->f268 = 0;
	if (m->flags & 2) {
		d3_GenerateVertexExpandedMesh(m);
	}
	m->flags &= ~4;
	for (i = 0; i < m->nfaces; i++) {
		if (m->faces[i].mat >= 0 && (((StockMaterial*)g_104049c)[m->faces[i].mat].flags & 0x10)) {
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
	m->texmat = (StockMaterial**) m_alloc(m->ntex * 4, "d3io:StockObjectTextures");
	for (i = 0; i < m->ntex; i++) {
		for (j = 0; j < m->nfaces; j++) {
			if (m->faces[j].tex == i && m->faces[j].mat >= 0) {
				m->texmat[i] = &((StockMaterial*)g_104049c)[m->faces[j].mat];
				break;
			}
		}
	}
	m->facemat = (int*) m_alloc(m->nfaces * 4, "d3io:StockObjectMaterials");
	m->uvs = (StockUv*) m_alloc(m->nfaces * 24, "d3io:StockObjectUVs");
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
