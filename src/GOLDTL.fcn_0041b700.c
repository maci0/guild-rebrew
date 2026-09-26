// FUNCTION: GOLDTL 0x0041b700
// SIZE: 190

typedef struct Vb Vb;

// SIZE 0x34
typedef struct {
	void* m[12];
	long (__stdcall* Unlock)(Vb* self);
} VbVtbl;

// SIZE 0x4
struct Vb {
	VbVtbl* vtbl;
};

typedef struct Device Device;

// SIZE 0x14c
typedef struct {
	void* m0[34];
	long (__stdcall* BeginScene)(Device* self);
	long (__stdcall* EndScene)(Device* self);
	void* m36[14];
	long (__stdcall* SetRenderState)(Device* self, int state, unsigned int value);
	void* m51[19];
	long (__stdcall* DrawPrimitive)(Device* self, int type, unsigned int start, unsigned int count);
	void* m71[5];
	long (__stdcall* SetVertexShader)(Device* self, unsigned int handle);
	void* m77[6];
	long (__stdcall* SetStreamSource)(Device* self, unsigned int stream, Vb* vb, unsigned int stride);
} DeviceVtbl;

// SIZE 0x4
struct Device {
	DeviceVtbl* vtbl;
};

extern int g_6777ac;
extern void* g_6b5de0;
extern void* g_6b5df4;
void __cdecl fcn_0041d9e0(const char* msg);

void __cdecl fcn_0041b700(void)
{
	if (g_6777ac == -1) {
		fcn_0041d9e0("dd_EndLines called w/o dd_BeginLines!");
	}
	if (g_6777ac >= 0) {
		((Vb*)g_6b5df4)->vtbl->Unlock(((Vb*)g_6b5df4));
		if (g_6777ac > 0 && (*(Device**)&g_6b5de0)->vtbl->BeginScene((*(Device**)&g_6b5de0)) >= 0) {
			(*(Device**)&g_6b5de0)->vtbl->SetVertexShader((*(Device**)&g_6b5de0), 0x44);
			(*(Device**)&g_6b5de0)->vtbl->SetStreamSource((*(Device**)&g_6b5de0), 0, ((Vb*)g_6b5df4), 0x14);
			(*(Device**)&g_6b5de0)->vtbl->SetRenderState((*(Device**)&g_6b5de0), 7, 0);
			(*(Device**)&g_6b5de0)->vtbl->DrawPrimitive((*(Device**)&g_6b5de0), 2, 0, g_6777ac / 2);
			(*(Device**)&g_6b5de0)->vtbl->EndScene((*(Device**)&g_6b5de0));
		}
	}
	g_6777ac = -1;
}
