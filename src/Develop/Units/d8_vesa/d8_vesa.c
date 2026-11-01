extern int g_6777ac;

struct vertex_41b5f0 {
	float x;
	float y;
	float z;
	float rhw;
	int color;
};

extern char g_6b5df0[];

#include "Develop/Units/Error/error_message.h"
typedef struct Vb Vb;

typedef struct {
	void* m[12];
	long (__stdcall* Unlock)(Vb* self);
} VbVtbl;

struct Vb {
	VbVtbl* vtbl;
};

typedef struct Device Device;

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

struct Device {
	DeviceVtbl* vtbl;
};

extern void* g_6b5de0;
extern void* g_6b5df4;

/* dd_Line: queues a screen-space line as two vertices. */
/* ADDRESS: GOLDTL 0x0041b5f0 */
void __cdecl dd_Line(int x1, int y1, int x2, int y2, int color)
{
	if (g_6777ac == -1) {
		ReportClientMessage("dd_Line called w/o dd_BeginLines!");
	}
	if (g_6777ac < 0x40) {
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].x = (float) x1;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].y = (float) y1;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].z = 0.0f;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].rhw = 1.0f;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].color = color;
		g_6777ac++;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].x = (float) x2;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].y = (float) y2;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].z = 0.0f;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].rhw = 1.0f;
		(*(struct vertex_41b5f0**)g_6b5df0)[g_6777ac].color = color;
		g_6777ac++;
	} else {
		ReportClientMessage("Too many lines in dd_Line(): Increase dd_MAX_LINES in d8_vesa.c!");
	}
}

/* ADDRESS: GOLDTL 0x0041b700 */
void __cdecl dd_EndLines(void)
{
	if (g_6777ac == -1) {
		ReportClientMessage("dd_EndLines called w/o dd_BeginLines!");
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
