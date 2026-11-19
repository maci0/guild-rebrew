

typedef struct Mat_451f80 {
	float m[16];
} Mat_451f80;
// SIZE 0x40

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* Transform451f80Fn)(D3D_DEVICE_VIEW*, int, void*);
typedef int (__stdcall* Texture451f80Fn)(D3D_DEVICE_VIEW*, int, int);









typedef struct Mesh_451f80 Mesh_451f80;
typedef struct MeshVtbl_451f80 {
	void* QueryInterface;
	void* AddRef;
	void* Release;
	int (__stdcall* DrawSubset)(Mesh_451f80* self, int i);
} MeshVtbl_451f80;
struct Mesh_451f80 {
	MeshVtbl_451f80* vtbl;
};

typedef struct Node_451f80 {
	char* e;
	char* world;
	Mesh_451f80* mesh;
	unsigned char* mat;
	float f10;
	float f14;
	int idx;
	int f1c;
	int f20;
	struct Node_451f80* prev;
	struct Node_451f80* next;
} Node_451f80;
// SIZE 0x2c

#include "Develop/Units/d3/d3_camera.h"

extern int g_6b8064;
extern Node_451f80* g_6b8068;
extern int d3_RenderedVertexCount;
extern int g_1042a08;
extern float g_1040c80[16];
extern float g_1040cc0[16];

Mesh_451f80* __cdecl fcn_00436930(char* o, float* r);
void __cdecl d3_UpdateObjectCameraTransform(char* e, char* cam, int force);
unsigned char __cdecl fcn_00438270(char* e, char* o, char* world);
void* __cdecl m_PoolAlloc(int* pool, int size, int grow);
void __stdcall fcn_005eb970(void* out, void* a, void* b);
void __stdcall fcn_005ec410(Mat_451f80* out, float x, float y, float z);
void __cdecl fcn_00450e90(float a, float b, char* c, Mat_451f80* d, Mat_451f80* e);
void __cdecl fcn_004372d0(unsigned char a, unsigned char b, int c, unsigned char d, unsigned char e);

char __cdecl fcn_00451f80(char* e, void* parent)
{
	char* o;
	unsigned char* mat;
	Node_451f80* node;
	Node_451f80* prev;
	Mesh_451f80* mesh;
	Mat_451f80 t;
	float f;
	float g;
	int i;
	char set;

	o = *(char**) (e + 0x1cc);
	if (*(char**) (o + 0x318) != 0 && *(int*) (*(char**) (o + 0x318) + 0x264) != 0 && *(int*) (e + 0x1ec) != 0) {
		mesh = fcn_00436930(o, &f);
		prev = 0;
		set = 0;
		if (!(e[0x216] & 0x20)) {
			d3_UpdateObjectCameraTransform(e, d3_ActiveCamera, 0);
		}
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 8, parent);
		fcn_005ec410(&t, -*(float*) (d3_ActiveCamera + 0x4c), -*(float*) (d3_ActiveCamera + 0x50), -*(float*) (d3_ActiveCamera + 0x54));
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 0x15fc, &t);
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 0x15fc, d3_ActiveCamera + 0x18c);
		if (!(fcn_00438270(e, o, *(char**) (e + 0x1ec) + 0x15fc) & 0x40)) {
			g = *(float*) (*(char**) (e + 0x1ec) + 0x15f8);
			f += *(float*) (*(char**) (o + 0x318) + 0x1dc);
			if (*(int*) (e + 0x220) == 1) {
				g = -g;
			}
			for (i = 0; i < *(int*) (*(char**) (o + 0x318) + 0x1e4); i++) {
				mat = (*(unsigned char***) (o + 0x31c))[*(int*) (*(char**) (o + 0x318) + 0x1e4) + i];
				if (mesh != *(Mesh_451f80**) (*(char**) (o + 0x318) + 0x268) && (mat[0x58] < 0xff || (mat[0x5a] & 1))) {
					node = (Node_451f80*) m_PoolAlloc(&g_6b8064, 0x2c, 0x10);
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
						node->next = g_6b8068;
						g_6b8068 = node;
					}
				} else {
					if (!set) {
						fcn_00450e90(f, g, o + 0x280, (Mat_451f80*) g_1040cc0, (Mat_451f80*) g_1040c80);
						((Transform451f80Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTransform)((D3D_DEVICE_VIEW*)g_6b5de0, 0x100, *(char**) (e + 0x1ec) + 0x15fc);
						set = 1;
					}
					((Texture451f80Fn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])((D3D_DEVICE_VIEW*)g_6b5de0, 0, *(int*) (mat + 0x50));
					fcn_004372d0(mat[0x58], ((mat[0x54] & 1) << 1) | (mat[0x5a] & 1), *(int*) (mat + 0x6c), (mat[0x5a] >> 1) & 1, (mat[0x54] >> 3) & 1);
					mesh->vtbl->DrawSubset(mesh, i);
				}
			}
		}
	}
	d3_RenderedVertexCount += *(int*) (o + 0x310);
	g_1042a08 += *(int*) (o + 0x314);
	return 1;
}
