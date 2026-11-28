

typedef struct SceneMatrix {
	float m[16];
} SceneMatrix;
// SIZE 0x40

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* SetTransformFn)(D3D_DEVICE_VIEW*, int, void*);
typedef int (__stdcall* SetTextureFn)(D3D_DEVICE_VIEW*, int, int);









typedef struct D3MeshObject D3MeshObject;
typedef struct D3MeshObjectVtbl {
	void* QueryInterface;
	void* AddRef;
	void* Release;
	int (__stdcall* DrawSubset)(D3MeshObject* self, int i);
} D3MeshObjectVtbl;
struct D3MeshObject {
	D3MeshObjectVtbl* vtbl;
};

typedef struct AlphaRenderNode {
	char* e;
	char* world;
	D3MeshObject* mesh;
	unsigned char* mat;
	float f10;
	float f14;
	int idx;
	int f1c;
	int f20;
	struct AlphaRenderNode* prev;
	struct AlphaRenderNode* next;
} AlphaRenderNode;
// SIZE 0x2c

#include "Develop/Units/d3/d3_camera.h"

extern int g_6b8064;
extern void* g_6b8068;
extern int d3_RenderedVertexCount;
extern int d3_RenderedFaceCount;
extern float g_1040c80[16];
extern float g_1040cc0[16];

D3MeshObject* __cdecl d3_GetObjectMesh(char* o, float* r);
void __cdecl d3_UpdateObjectCameraTransform(char* e, char* cam, int force);
unsigned char __cdecl d3_TestObjectFrustum(char* e, char* o, char* world);
void* __cdecl m_PoolAlloc(int* pool, int size, int grow);
void __stdcall fcn_005eb970(void* out, void* a, void* b);
void __stdcall fcn_005ec410(SceneMatrix* out, float x, float y, float z);
void __cdecl d3_SelectActiveObjectLights(float a, float b, char* c, SceneMatrix* d, SceneMatrix* e);
void __cdecl d3_SetRenderMaterialState(unsigned char a, unsigned char b, int c, unsigned char d, unsigned char e);

/* ADDRESS: GOLDDE 0x00447830 */
char __cdecl d3_VisitRenderSceneNode(char* e, void* parent)
{
	char* o;
	unsigned char* mat;
	AlphaRenderNode* node;
	AlphaRenderNode* prev;
	D3MeshObject* mesh;
	SceneMatrix t;
	float f;
	float g;
	int i;
	char set;
	char* detail;

	o = *(char**) (e + 0x1cc);
	if (*(char**) (o + 0x318) != 0 && *(int*) (*(char**) (o + 0x318) + 0x264) != 0 && *(int*) (e + 0x1ec) != 0) {
		mesh = d3_GetObjectMesh(o, &f);
		prev = 0;
		set = 0;
		if (!(e[0x216] & 0x20)) {
			d3_UpdateObjectCameraTransform(e, d3_ActiveCamera, 0);
		}
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 8, parent);
		fcn_005ec410(&t, -*(float*) (d3_ActiveCamera + 0x4c), -*(float*) (d3_ActiveCamera + 0x50), -*(float*) (d3_ActiveCamera + 0x54));
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 0x15fc, &t);
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 0x15fc, d3_ActiveCamera + 0x18c);
		if (!(d3_TestObjectFrustum(e, o, *(char**) (e + 0x1ec) + 0x15fc) & 0x40)) {
			detail = *(char**) (o + 0x318);
			f += *(float*) (detail + 0x1dc);
			g = *(float*) (*(char**) (e + 0x1ec) + 0x15f8);
			if (*(int*) (e + 0x220) == 1) {
				g = -g;
			}
			for (i = 0; i < *(int*) (detail + 0x1e4); detail = *(char**) (o + 0x318), i++) {
				mat = (*(unsigned char***) (o + 0x31c))[*(int*) (detail + 0x1e4) + i];
				if (mesh != *(D3MeshObject**) (detail + 0x268) && (mat[0x58] < 0xff || (mat[0x5a] & 1))) {
					node = (AlphaRenderNode*) m_PoolAlloc(&g_6b8064, 0x2c, 0x10);
					node->e = e;
					node->world = *(char**) (e + 0x1ec) + 0x15fc;
					node->mesh = mesh;
					node->mat = (char*) mat;
					node->f10 = f;
					node->f14 = g;
					node->idx = i | 0x80000000;
					node->f1c = (e[0x215] & 0x20) ? *(int*) (o + 0x49c) : *(int*) (mat + 0x58);
					node->f20 = *(int*) (o + 0x324) | *(int*) (mat + 0x6c);
					node->prev = prev;
					if (prev != 0) {
						node->next = prev->next;
						prev = node;
					} else {
						node->next = (AlphaRenderNode*) g_6b8068;
						g_6b8068 = (void*) node;
					}
				} else {
					if (!set) {
						d3_SelectActiveObjectLights(f, g, o + 0x280, (SceneMatrix*) g_1040cc0, (SceneMatrix*) g_1040c80);
						((SetTransformFn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTransform)((D3D_DEVICE_VIEW*)g_6b5de0, 0x100, *(char**) (e + 0x1ec) + 0x15fc);
						set = 1;
					}
					((SetTextureFn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])((D3D_DEVICE_VIEW*)g_6b5de0, 0, *(int*) (mat + 0x50));
					d3_SetRenderMaterialState(mat[0x58], ((mat[0x54] & 1) << 1) | (mat[0x5a] & 1), *(int*) (mat + 0x6c), (mat[0x5a] >> 1) & 1, (mat[0x54] >> 3) & 1);
					mesh->vtbl->DrawSubset(mesh, i);
				}
			}
		}
	}
	d3_RenderedVertexCount += *(int*) (o + 0x310);
	d3_RenderedFaceCount += *(int*) (o + 0x314);
	return 1;
}
