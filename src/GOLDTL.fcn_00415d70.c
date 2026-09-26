// FUNCTION: GOLDTL 0x00415d70
// SIZE: 739

typedef struct Device Device;
typedef struct VBuf VBuf;

// SIZE 0x14
typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
} Vertex;

// SIZE 0x14c
typedef struct {
	void *m[70];
	long (__stdcall *DrawPrimitive)(Device *self, int type, unsigned int start, unsigned int count);
	void *m71[5];
	long (__stdcall *SetVertexShader)(Device *self, unsigned int fvf);
	void *m77[6];
	long (__stdcall *SetStreamSource)(Device *self, unsigned int n, VBuf *vb, unsigned int stride);
} DeviceVtbl;

// SIZE 0x4
struct Device {
	DeviceVtbl *vtbl;
};

// SIZE 0x34
typedef struct {
	void *m[11];
	long (__stdcall *Lock)(VBuf *self, unsigned int off, unsigned int size, Vertex **out, unsigned int flags);
	long (__stdcall *Unlock)(VBuf *self);
} VBufVtbl;

// SIZE 0x4
struct VBuf {
	VBufVtbl *vtbl;
};

// SIZE 0x28
typedef struct {
	char pad0[8];
	float fade;
	char padc[0xc];
	float x0;
	float y0;
	float x1;
	float y1;
} Seg;

// SIZE 0x40
typedef struct {
	int count;
	char pad4[4];
	int count0;
	int count1;
	Seg *segs;
	float a0;
	float b0;
	float a;
	float b;
	float a1;
	float b1;
	unsigned int last;
	unsigned int t0;
	unsigned int t1;
	unsigned int u0;
	unsigned int u1;
} Lines;

extern void* g_6b5de0;
extern VBuf *g_6b5cb4;
extern int g_6b7fac;

void __cdecl fcn_00415710(Lines *, float);
void __cdecl fcn_00437160(int, int, int);
void __cdecl fcn_004372d0(int, int, int, int, int);
void __cdecl fcn_00437270(void);

void __cdecl fcn_00415d70(Lines *l)
{
	int span;
	int rem;
	float dt;
	Vertex *buf;
	unsigned int color;
	int c1;
	int c2;
	float z;
	Seg *s;
	int i;
	int k;
	int n;
	float fade;

	if (l == 0 || g_6b5cb4 == 0) {
		return;
	}
	if (l->t0 != l->t1) {
		if ((*(volatile unsigned int*)&g_6b7fac) >= l->t1) {
			l->count = l->count1;
		} else {
			span = l->t1 - l->t0;
			rem = l->t1 - (*(volatile unsigned int*)&g_6b7fac);
			l->count = (span - rem) * l->count1 / span + l->count0 * rem / span;
		}
	}
	if (l->u0 != l->u1) {
		if ((*(volatile unsigned int*)&g_6b7fac) >= l->u1) {
			l->a = l->a1;
			l->b = l->b1;
		} else {
			span = l->u1 - l->u0;
			rem = l->u1 - (*(volatile unsigned int*)&g_6b7fac);
			l->a = rem * l->a0 / span + (span - rem) * l->a1 / span;
			l->b = rem * l->b0 / span + (span - rem) * l->b1 / span;
		}
	}
	dt = ((*(volatile unsigned int*)&g_6b7fac) - l->last) * 0.1f;
	l->last = (*(volatile unsigned int*)&g_6b7fac);
	if (l->count == 0) {
		return;
	}
	fcn_00415710(l, dt);
	fcn_00437160(0, 0, 0);
	fcn_004372d0(0x80, 0, 0, 0, 0);
	((Device*)g_6b5de0)->vtbl->SetVertexShader(((Device*)g_6b5de0), 0x44);
	((Device*)g_6b5de0)->vtbl->SetStreamSource(((Device*)g_6b5de0), 0, g_6b5cb4, 0x14);
	n = l->count;
	fade = 1.0f - n * 0.0005f;
	c1 = (int) (128.0f * fade);
	c2 = (int) (fade * 96.0f);
	color = 0x80000000 | ((c2 & 0xff) << 16) | ((c1 & 0xff) << 8) | (c1 & 0xff);
	k = 0;
	s = l->segs;
	for (i = 0; i < l->count; s++, i++) {
		if (k == 0) {
			g_6b5cb4->vtbl->Lock(g_6b5cb4, 0, 0, &buf, 0x2000);
		}
		z = (1.0f - s->fade) * 0.025f;
		buf[k].x = s->x0;
		buf[k].y = s->y0;
		buf[k].z = z;
		buf[k].rhw = 1.0f;
		buf[k].color = color;
		k++;
		buf[k].x = s->x1;
		buf[k].y = s->y1;
		buf[k].z = z;
		buf[k].rhw = 1.0f;
		buf[k].color = color;
		k++;
		if (k >= 0x80) {
			g_6b5cb4->vtbl->Unlock(g_6b5cb4);
			((Device*)g_6b5de0)->vtbl->DrawPrimitive(((Device*)g_6b5de0), 2, 0, k / 2);
			k = 0;
		}
	}
	if (k != 0) {
		g_6b5cb4->vtbl->Unlock(g_6b5cb4);
		((Device*)g_6b5de0)->vtbl->DrawPrimitive(((Device*)g_6b5de0), 2, 0, k / 2);
	}
	fcn_00437270();
}
