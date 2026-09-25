// SIZE 0x1c
typedef struct {
	float x;
	float y;
	float z;
	float w;
	int color;
	float u;
	float v;
} Vert;

// SIZE 0xa8
typedef struct {
	Vert v[6];
} Verts;

// SIZE 0xac
typedef struct {
	Verts vs;
	int pad;
} Quad;

typedef struct VB VB;

typedef struct {
	char p0[0x2c];
	int (__stdcall* Lock)(VB*, int, int, void**, int);
	int (__stdcall* Unlock)(VB*);
} VBVtbl;

struct VB {
	VBVtbl* vtbl;
};

typedef struct Device Device;

typedef struct {
	char p0[0x88];
	int (__stdcall* BeginScene)(Device*);
	int (__stdcall* EndScene)(Device*);
	char p90[0x38];
	int (__stdcall* SetRenderState)(Device*, int, int);
	char pcc[0x28];
	int (__stdcall* SetTexture)(Device*, int, int);
	char pf8[0x20];
	int (__stdcall* DrawPrimitive)(Device*, int, int, int);
} DeviceVtbl;

struct Device {
	DeviceVtbl* vtbl;
};

extern int g_772608;
extern VB* g_772614;
extern Device* g_6b5de0;

int __cdecl fcn_0047b8b0(int, int, int, int, Quad*);
void __cdecl fcn_0047b9f0(Quad*, int);
void __cdecl fcn_0047c4e0(void);
void __cdecl fcn_004372d0(int, int, int, int, int);

// FUNCTION: GOLDTL 0x0047c9c0
// SIZE: 402

void __cdecl fcn_0047c9c0(int a1, int a2, int a3, int a4, int tex, float alpha)
{
	Quad q;
	float t;
	int i;

	if (fcn_0047b8b0(a1, a2, a3, a4, &q) == 0) {
		return;
	}
	fcn_0047b9f0(&q, (int) (alpha * 255.0f));
	t = g_772608 * 0.001f;
	for (i = 0; i < 6; i++) {
		q.vs.v[i].z = 1.0f - t;
		q.vs.v[i].w = t + 0.01f;
	}
	{
		void* ptr;

		if (g_772614->vtbl->Lock(g_772614, 0, 0x18, &ptr, 0x2000) < 0) {
			return;
		}
		*(Verts*) ptr = q.vs;
	}
	g_772614->vtbl->Unlock(g_772614);
	fcn_0047c4e0();
	fcn_004372d0(0xfe, 0, 0, 1, 1);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 0);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 0x88, 0);
	if (g_6b5de0->vtbl->BeginScene(g_6b5de0) >= 0) {
		g_6b5de0->vtbl->SetTexture(g_6b5de0, 0, tex);
		g_6b5de0->vtbl->DrawPrimitive(g_6b5de0, 4, 0, 2);
		g_6b5de0->vtbl->EndScene(g_6b5de0);
	}
	g_772608++;
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 1);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 0x88, 1);
}
