// FUNCTION: GOLDTL 0x445760
// SIZE: 320
// The x/y rows group their first two products in parentheses and the z row
// does not; that grouping is what places each faddp as in the reference.

typedef struct Mat0445760 {
	float m[4][4];
} Mat0445760;
// SIZE 0x40

typedef struct Vec0445760 {
	float x;
	float y;
	float z;
} Vec0445760;

typedef struct Obj0445760 {
	char pad0[0x1fc];
	struct Obj0445760* parent;
} Obj0445760;

void __cdecl fcn_004519d0(void* a, int b);
void __cdecl fcn_004557c0(Obj0445760* o, int a, int b, Mat0445760* out);
Mat0445760* __stdcall fcn_005ebea2(Mat0445760* out, float* det, Mat0445760* in);
Mat0445760* __stdcall fcn_005ebbb9(Mat0445760* out, Mat0445760* in);
void* __stdcall fcn_005eb970(void* out, void* in, Mat0445760* m);

void __cdecl fcn_00445760(Obj0445760* o, Vec0445760* in, void* dir, Vec0445760* out, int arg)
{
	Obj0445760* p;
	Mat0445760 inv;
	Mat0445760 m;

	p = o->parent;
	if (p == 0) {
		out->x = in->x;
		out->y = in->y;
		out->z = in->z;
		fcn_004519d0(dir, arg);
		return;
	}
	fcn_004557c0(p, 0, 0, &m);
	fcn_005ebea2(&inv, 0, &m);
	out->x = (inv.m[1][0] * in->y + inv.m[0][0] * in->x) + inv.m[2][0] * in->z + inv.m[3][0];
	out->y = (inv.m[1][1] * in->y + inv.m[0][1] * in->x) + inv.m[2][1] * in->z + inv.m[3][1];
	out->z = inv.m[1][2] * in->y + inv.m[0][2] * in->x + inv.m[2][2] * in->z + inv.m[3][2];
	fcn_004557c0(p, 0, 1, &m);
	fcn_005ebbb9(&inv, &m);
	fcn_005eb970(&m, dir, &inv);
	fcn_004519d0(&m, arg);
}
