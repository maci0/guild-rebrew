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

typedef struct Tex Tex;

typedef struct {
	char p0[0x38];
	int (__stdcall* GetLevelDesc)(Tex*, int, void*);
} TexVtbl;

struct Tex {
	TexVtbl* vtbl;
};

// SIZE 0x20
typedef struct {
	char pad0[0x18];
	int width;
	int height;
} TexDesc;

extern int g_772608;
extern int g_772614;
extern void* g_6b5de0;

int __cdecl fcn_0047b8b0(int, int, int, int, Quad*);
void __cdecl fcn_0047b9f0(Quad*, int);
void __cdecl fcn_0047c4e0(void);
void __cdecl fcn_004372d0(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0047c7b0 */
void __cdecl fcn_0047c7b0(int x, int y, int w, int h, Tex* tex, float alpha)
{
	TexDesc desc;
	Quad q;
	float t;
	int i;
	void* ptr;
	VBVtbl* vt;

	((Tex*) tex)->vtbl->GetLevelDesc(tex, 0, &desc);
	if (fcn_0047b8b0(x, y, w, h, &q) == 0) {
		return;
	}
	fcn_0047b9f0(&q, (int) (alpha * 255.0f));
	t = g_772608 * 0.001f;
	for (i = 0; i < 6; i++) {
		q.vs.v[i].z = 1.0f - t;
		q.vs.v[i].w = t + 0.01f;
	}
	vt = ((VB*) g_772614)->vtbl;
	q.vs.v[0].u = 0.0f;
	q.vs.v[0].v = 0.0f;
	q.vs.v[1].u = (float) w / desc.width;
	q.vs.v[1].v = 0.0f;
	q.vs.v[2].u = 0.0f;
	q.vs.v[2].v = (float) h / desc.height;
	q.vs.v[3].u = (float) w / desc.width;
	q.vs.v[3].v = 0.0f;
	q.vs.v[4].u = (float) w / desc.width;
	q.vs.v[4].v = (float) h / desc.height;
	q.vs.v[5].u = 0.0f;
	q.vs.v[5].v = (float) h / desc.height;
	if (vt->Lock(((VB*) g_772614), 0, 0x18, &ptr, 0x2000) < 0) {
		return;
	}
	*(Verts*) ptr = q.vs;
	((VB*) g_772614)->vtbl->Unlock(((VB*) g_772614));
	fcn_0047c4e0();
	((Device*) g_6b5de0)->vtbl->SetRenderState(((Device*) g_6b5de0), 7, 0);
	((Device*) g_6b5de0)->vtbl->SetRenderState(((Device*) g_6b5de0), 0x88, 0);
	fcn_004372d0(0xfe, 0, 0, 1, 1);
	if (((Device*) g_6b5de0)->vtbl->BeginScene(((Device*) g_6b5de0)) >= 0) {
		((Device*) g_6b5de0)->vtbl->SetTexture(((Device*) g_6b5de0), 0, (int) tex);
		((Device*) g_6b5de0)->vtbl->DrawPrimitive(((Device*) g_6b5de0), 4, 0, 2);
		((Device*) g_6b5de0)->vtbl->EndScene(((Device*) g_6b5de0));
	}
	((Device*) g_6b5de0)->vtbl->SetRenderState(((Device*) g_6b5de0), 0x88, 1);
	g_772608++;
}
