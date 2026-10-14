

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

void __cdecl fcn_004519d0(void* a, int b);
void __cdecl fcn_00458d90(Obj04497f0* o, int a, int b, Mat04497f0* out);
void __cdecl fcn_00454060(Mat04497f0*, Mat04497f0*);
void __cdecl fcn_00454030(Mat04497f0*, Mat04497f0*);
void __cdecl fcn_00453ed0(void*, Mat04497f0*, void*);

void __cdecl fcn_004497f0(Obj04497f0* o, Vec04497f0* in, void* dir, Vec04497f0* out, int arg)
{
	Obj04497f0* p;
	Mat04497f0 inv;
	Mat04497f0 m;

	p = o->parent;
	if (p == 0) {
		out->x = in->x;
		out->y = in->y;
		out->z = in->z;
		fcn_004519d0(dir, arg);
		return;
	}
	fcn_00458d90(p, 0, 0, &m);
	fcn_00454060(&m, &inv);
	out->x = inv.m[1][0] * in->y + inv.m[0][0] * in->x + inv.m[2][0] * in->z + inv.m[3][0];
	out->y = inv.m[1][1] * in->y + inv.m[0][1] * in->x + inv.m[2][1] * in->z + inv.m[3][1];
	out->z = inv.m[1][2] * in->y + inv.m[0][2] * in->x + inv.m[2][2] * in->z + inv.m[3][2];
	fcn_00458d90(p, 0, 1, &m);
	fcn_00454030(&m, &inv);
	fcn_00453ed0(dir, &inv, &m);
	fcn_004519d0(&m, arg);
}
