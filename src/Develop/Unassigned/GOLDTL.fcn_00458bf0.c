// SIZE 0x40
typedef struct {
	float m[4][4];
} Mat;

typedef struct Ent Ent;

// SIZE 0x218
struct Ent {
	char p0[0x4c];
	float x;
	float y;
	float z;
	char p58[0x134];
	Mat world;
	char p1cc[0x24];
	Ent* next;
	char p1f4[0x22];
	unsigned char flags;
	char p217;
};

typedef struct Device Device;

typedef struct {
	char p0[0x94];
	int (__stdcall* SetTransform)(Device*, int, Mat*);
	char p98[0x30];
	int (__stdcall* SetRenderState)(Device*, int, int);
	char pcc[0x64];
	int (__stdcall* SetVertexShader)(Device*, int);
} DeviceVtbl;

struct Device {
	DeviceVtbl* vtbl;
};

extern void* g_6b5de0;
#include "GOLDTL.fcn_00458bf0_gconf.h"
extern char* g_6b86ec;
extern char* g_1041d00;

Mat* __stdcall fcn_005ec410(Mat*, float, float, float);
Mat* __stdcall fcn_005eb970(Mat*, Mat*, Mat*);
void __cdecl fcn_004372d0(int, int, int, int, int);
void __cdecl fcn_00458d20(Ent*);


/* ADDRESS: GOLDTL 0x00458bf0 */
void __cdecl fcn_00458bf0(Ent* n)
{
	Mat m;
	Ent* e;

	fcn_005ec410(&m, -n->x, -n->y, -n->z);
	fcn_005eb970(&m, &m, &n->world);
	((Device*)g_6b5de0)->vtbl->SetTransform(((Device*)g_6b5de0), 0x100, &m);
	((Device*)g_6b5de0)->vtbl->SetVertexShader(((Device*)g_6b5de0), 0x142);
	fcn_004372d0(0x7f, 0, 0, 1, 0);
	if (!g_6b89bc) {
		((Device*)g_6b5de0)->vtbl->SetRenderState(((Device*)g_6b5de0), 0x13, 1);
		((Device*)g_6b5de0)->vtbl->SetRenderState(((Device*)g_6b5de0), 0x14, 4);
	}
	for (e = ((Ent*)g_6b86ec); e != 0; e = e->next) {
		if (e->flags & 0x80) {
			fcn_00458d20(e);
		}
	}
	for (e = ((Ent*)g_1041d00); e != 0; e = e->next) {
		if (e->flags & 0x80) {
			fcn_00458d20(e);
		}
	}
	if (!g_6b89bc) {
		((Device*)g_6b5de0)->vtbl->SetRenderState(((Device*)g_6b5de0), 0x13, 5);
		((Device*)g_6b5de0)->vtbl->SetRenderState(((Device*)g_6b5de0), 0x14, 6);
	}
}
