typedef struct Mat04497f0 {
	float m[4][4];
} Mat04497f0;
// SIZE 0x40

typedef struct Vec04497f0 {
	float x;
	float y;
	float z;
} Vec04497f0;

typedef struct Obj04497f0 {
	char pad0[0x1f8];
	struct Obj04497f0* parent;
} Obj04497f0;

// The x/y rows group their first two products in parentheses and the z row
// does not; that grouping is what places each faddp as in the reference.

typedef struct D3_MAT44 {
	float m[4][4];
} D3_MAT44;
// SIZE 0x40

typedef struct D3_VEC3 {
	float x;
	float y;
	float z;
} D3_VEC3;

typedef struct D3_NODE {
	char pad0[0x1fc];
	struct D3_NODE* parent;
} D3_NODE;

void __cdecl d3_MatrixToEulerAngles(void* a, int b);
void __cdecl d3_BuildViewMatrix(Obj04497f0* o, int a, int b, Mat04497f0* out);
void __cdecl d3_InvertMatrix4x4(Mat04497f0*, Mat04497f0*);
void __cdecl d3_TransposeMatrix4x4(Mat04497f0*, Mat04497f0*);
void __cdecl d3_MultiplyAffineMatrices(void*, Mat04497f0*, void*);
void __cdecl d3_ComposeObserverMatrix(D3_NODE* o, char* a, int b, D3_MAT44* out);
D3_MAT44* __stdcall fcn_005ebea2(D3_MAT44* out, float* det, D3_MAT44* in);
D3_MAT44* __stdcall D3DXMatrixTranspose(D3_MAT44* out, D3_MAT44* in);
void* __stdcall fcn_005eb970(void* out, void* in, D3_MAT44* m);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004497f0 */
void __cdecl d3_TransformWorldToParent(Obj04497f0* o, Vec04497f0* in, void* dir, Vec04497f0* out, int arg)
{
	Obj04497f0* p;
	Mat04497f0 inv;
	Mat04497f0 m;

	p = o->parent;
	if (p == 0) {
		out->x = in->x;
		out->y = in->y;
		out->z = in->z;
		d3_MatrixToEulerAngles(dir, arg);
		return;
	}
	d3_BuildViewMatrix(p, 0, 0, &m);
	d3_InvertMatrix4x4(&m, &inv);
	out->x = inv.m[1][0] * in->y + inv.m[0][0] * in->x + inv.m[2][0] * in->z + inv.m[3][0];
	out->y = inv.m[1][1] * in->y + inv.m[0][1] * in->x + inv.m[2][1] * in->z + inv.m[3][1];
	out->z = inv.m[1][2] * in->y + inv.m[0][2] * in->x + inv.m[2][2] * in->z + inv.m[3][2];
	d3_BuildViewMatrix(p, 0, 1, &m);
	d3_TransposeMatrix4x4(&m, &inv);
	d3_MultiplyAffineMatrices(dir, &inv, &m);
	d3_MatrixToEulerAngles(&m, arg);
}
#else
/* ADDRESS: GOLDTL 0x00445760 */
/* ADDRESS: GOLDDE 0x0043d4f0 */
void __cdecl d3_TransformWorldToParent(D3_NODE* node, D3_VEC3* in, void* dir, D3_VEC3* out, int outAngles)
{
	D3_NODE* p;
	D3_MAT44 inv;
	D3_MAT44 m;

	p = node->parent;
	if (p == 0) {
		out->x = in->x;
		out->y = in->y;
		out->z = in->z;
		d3_MatrixToEulerAngles(dir, outAngles);
		return;
	}
	d3_ComposeObserverMatrix(p, 0, 0, &m);
	fcn_005ebea2(&inv, 0, &m);
	out->x = (inv.m[1][0] * in->y + inv.m[0][0] * in->x) + inv.m[2][0] * in->z + inv.m[3][0];
	out->y = (inv.m[1][1] * in->y + inv.m[0][1] * in->x) + inv.m[2][1] * in->z + inv.m[3][1];
	out->z = inv.m[1][2] * in->y + inv.m[0][2] * in->x + inv.m[2][2] * in->z + inv.m[3][2];
	d3_ComposeObserverMatrix(p, 0, 1, &m);
	D3DXMatrixTranspose(&inv, &m);
	fcn_005eb970(&m, dir, &inv);
	d3_MatrixToEulerAngles(&m, outAngles);
}
#endif
