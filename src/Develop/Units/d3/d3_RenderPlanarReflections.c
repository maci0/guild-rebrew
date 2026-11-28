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

#include "Develop/Units/d8_vesa/d3d_device_view.h"










#include "Develop/Units/d3/d3_camera.h"
extern float g_1040cc0[16];
extern float g_1040c80[16];

extern int d3_ActiveScene;
extern char g_6b8000;

void __cdecl d3_UpdateObjectCameraTransform(Ent*, char*, int);
Mat* __stdcall fcn_005ebea2(Mat*, float*, Mat*);
Mat* __stdcall D3DXMatrixTranspose(Mat*, Mat*);
Plane* __stdcall fcn_005ee04a(Plane*, Plane*, Mat*);
Plane* __stdcall fcn_005ed45f(void*, Plane*);
void __cdecl d3_VisitSceneObjects(int, int, int, void (__cdecl*)(void), void*);
void __cdecl d3_VisitRenderSceneNode(void);


/* ADDRESS: GOLDTL 0x00451df0 */
void __cdecl d3_RenderPlanarReflections(Ent* e)
{
	Plane p;
	Mat m;
	Mat big;

	if (e == 0 || e->inst == 0 || e->inst->model == 0 || !(e->inst->model->flags & 4)) {
		return;
	}
	if (!(e->flags & 0x20) || !(e->flags & 0x40)) {
		d3_UpdateObjectCameraTransform(e, d3_ActiveCamera, 0);
	}
	fcn_005ebea2(&m, 0, &e->xf->a);
	D3DXMatrixTranspose(&m, &m);
	fcn_005ee04a(&p, &e->inst->model->plane, &m);
	fcn_005ed45f(&big, &p);
	fcn_005ebea2(&m, 0, &e->xf->b);
	D3DXMatrixTranspose(&m, &m);
	fcn_005ee04a(&p, &e->inst->model->plane, &m);
	fcn_005ed45f((Mat*) g_1040cc0, &p);
	fcn_005ebea2((Mat*) g_1040c80, 0, (Mat*) g_1040cc0);
	D3DXMatrixTranspose((Mat*) g_1040c80, (Mat*) g_1040c80);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x16, 2);
	g_6b8000 = 1;
	d3_VisitSceneObjects(d3_ActiveScene, 0, 0x40, d3_VisitRenderSceneNode, &big);
	g_6b8000 = 0;
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x16, 3);
}
