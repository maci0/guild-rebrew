// FUNCTION: GOLDTL 0x00451f80
// SIZE: 632

typedef struct Mat_451f80 {
	float m[16];
} Mat_451f80;
// SIZE 0x40

typedef struct Dev_451f80 Dev_451f80;
typedef struct DevVtbl_451f80 {
	char pad0[0x94];
	int (__stdcall* SetTransform)(Dev_451f80* self, int state, void* m);
	char pad98[0xf4 - 0x98];
	int (__stdcall* SetTexture)(Dev_451f80* self, int stage, int tex);
} DevVtbl_451f80;
struct Dev_451f80 {
	DevVtbl_451f80* vtbl;
};

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

extern char* g_6b8014;
extern Dev_451f80* g_6b5de0;
extern int g_6b8064;
extern Node_451f80* g_6b8068;
extern int g_1052bac;
extern int g_1042a08;
extern Mat_451f80 g_1040c80;
extern Mat_451f80 g_1040cc0;

Mesh_451f80* __cdecl fcn_00436930(char* o, float* r);
void __cdecl fcn_00438100(char* e, char* cam, int force);
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
			fcn_00438100(e, g_6b8014, 0);
		}
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 8, parent);
		fcn_005ec410(&t, -*(float*) (g_6b8014 + 0x4c), -*(float*) (g_6b8014 + 0x50), -*(float*) (g_6b8014 + 0x54));
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 0x15fc, &t);
		fcn_005eb970(*(char**) (e + 0x1ec) + 0x15fc, *(char**) (e + 0x1ec) + 0x15fc, g_6b8014 + 0x18c);
		if (!(fcn_00438270(e, o, *(char**) (e + 0x1ec) + 0x15fc) & 0x40)) {
			f += *(float*) (*(char**) (o + 0x318) + 0x1dc);
			g = *(float*) (*(char**) (e + 0x1ec) + 0x15f8);
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
						fcn_00450e90(f, g, o + 0x280, &g_1040cc0, &g_1040c80);
						g_6b5de0->vtbl->SetTransform(g_6b5de0, 0x100, *(char**) (e + 0x1ec) + 0x15fc);
						set = 1;
					}
					g_6b5de0->vtbl->SetTexture(g_6b5de0, 0, *(int*) (mat + 0x50));
					fcn_004372d0(mat[0x58], ((mat[0x54] & 1) << 1) | (mat[0x5a] & 1), *(int*) (mat + 0x6c), (mat[0x5a] >> 1) & 1, (mat[0x54] >> 3) & 1);
					mesh->vtbl->DrawSubset(mesh, i);
				}
			}
		}
	}
	g_1052bac += *(int*) (o + 0x310);
	g_1042a08 += *(int*) (o + 0x314);
	return 1;
}
