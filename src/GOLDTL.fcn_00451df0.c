// SIZE 0x40
typedef struct {
	float m[4][4];
} Mat;

// SIZE 0x10
typedef struct {
	float a;
	float b;
	float c;
	float d;
} Plane;

// SIZE 0x2a2
typedef struct {
	char p0[0x26c];
	Plane plane;
	char p27c[0x25];
	unsigned char flags;
} Model;

// SIZE 0x31c
typedef struct {
	char p0[0x318];
	Model* model;
} Inst;

// SIZE 0x88
typedef struct {
	char p0[8];
	Mat a;
	Mat b;
} Xform;

// SIZE 0x217
typedef struct {
	char p0[0x1cc];
	Inst* inst;
	char p1d0[0x1c];
	Xform* xf;
	char p1f0[0x26];
	unsigned char flags;
} Ent;

typedef struct Device Device;

typedef struct {
	char p0[0xc8];
	int (__stdcall* SetRenderState)(Device*, int, int);
} DeviceVtbl;

struct Device {
	DeviceVtbl* vtbl;
};

extern int g_6b8014;
extern Mat g_1040cc0;
extern Mat g_1040c80;
extern void* g_6b5de0;
extern int g_67a370;
extern char g_6b8000;

void __cdecl fcn_00438100(Ent*, int, int);
Mat* __stdcall fcn_005ebea2(Mat*, float*, Mat*);
Mat* __stdcall fcn_005ebbb9(Mat*, Mat*);
Plane* __stdcall fcn_005ee04a(Plane*, Plane*, Mat*);
Plane* __stdcall fcn_005ed45f(void*, Plane*);
void __cdecl fcn_004379a0(int, int, int, void (__cdecl*)(void), void*);
void __cdecl fcn_00451f80(void);

// FUNCTION: GOLDTL 0x00451df0

void __cdecl fcn_00451df0(Ent* e)
{
	Plane p;
	Mat m;
	Mat big;

	if (e == 0 || e->inst == 0 || e->inst->model == 0 || !(e->inst->model->flags & 4)) {
		return;
	}
	if (!(e->flags & 0x20) || !(e->flags & 0x40)) {
		fcn_00438100(e, g_6b8014, 0);
	}
	fcn_005ebea2(&m, 0, &e->xf->a);
	fcn_005ebbb9(&m, &m);
	fcn_005ee04a(&p, &e->inst->model->plane, &m);
	fcn_005ed45f(&big, &p);
	fcn_005ebea2(&m, 0, &e->xf->b);
	fcn_005ebbb9(&m, &m);
	fcn_005ee04a(&p, &e->inst->model->plane, &m);
	fcn_005ed45f(&g_1040cc0, &p);
	fcn_005ebea2(&g_1040c80, 0, &g_1040cc0);
	fcn_005ebbb9(&g_1040c80, &g_1040c80);
	((Device*)g_6b5de0)->vtbl->SetRenderState(((Device*)g_6b5de0), 0x16, 2);
	g_6b8000 = 1;
	fcn_004379a0(g_67a370, 0, 0x40, fcn_00451f80, &big);
	g_6b8000 = 0;
	((Device*)g_6b5de0)->vtbl->SetRenderState(((Device*)g_6b5de0), 0x16, 3);
}
