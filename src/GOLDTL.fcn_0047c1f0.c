// FUNCTION: GOLDTL 0x0047c1f0

typedef struct Vtx {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} Vtx;
// SIZE 0x1c

typedef struct Quad {
	Vtx v[6];
	int tex;
} Quad;
// SIZE 0xac

typedef struct Tex {
	char pad0[0x20];
	int handle;
	char pad24[0x54 - 0x24];
	int size;
} Tex;

extern int g_772604;
extern int g_772608;
extern int g_7725f8;
extern int g_7725fc;
extern int g_67d964;
extern int g_67d968;
extern Quad g_1552020[0x400];

int __cdecl fcn_0047b8b0(int x, int y, int w, int h, Quad* q);
void __cdecl fcn_0047b9a0(Quad* q, unsigned char r, unsigned char g, unsigned char b);

Quad* __cdecl fcn_0047c1f0(float u, float v, int w, int h, Tex* tex, int x, int y)
{
	float du;
	float dv;
	int cw;
	int ch;
	int tw;
	int th;
	float z;
	float rhw;
	Quad* q;
	int i;

	du = 0.0f;
	dv = 0.0f;
	cw = w;
	ch = h;
	tw = tex->size;
	th = tex->size;
	if (g_772604 >= 0x400) {
		return 0;
	}
	if (x + w < g_7725f8 || x > g_67d964 || y + h < g_7725fc || y > g_67d968) {
		return 0;
	}
	if (x < g_7725f8) {
		du = g_7725f8 - x;
		x = g_7725f8;
		cw = w - du;
	}
	if (y < g_7725fc) {
		dv = g_7725fc - y;
		y = g_7725fc;
		ch = h - dv;
	}
	if (cw + x > g_67d964) {
		cw = g_67d964 - x;
	}
	if (y + ch > g_67d968) {
		ch = g_67d968 - y;
	}
	q = &g_1552020[g_772604];
	if (fcn_0047b8b0(x, y, cw, ch, q) == 0) {
		return 0;
	}
	du = du / w;
	q->tex = tex->handle;
	dv = dv / h;
	q->v[0].u = du + u;
	q->v[0].v = dv + v;
	q->v[1].u = (float) cw / tw + du + u;
	q->v[1].v = q->v[0].v;
	q->v[2].u = q->v[0].u;
	q->v[2].v = (float) ch / th + dv + v;
	q->v[3].u = q->v[1].u;
	q->v[3].v = q->v[0].v;
	q->v[4].u = q->v[1].u;
	q->v[4].v = q->v[2].v;
	q->v[5].u = q->v[0].u;
	q->v[5].v = q->v[2].v;
	z = 1.0f - g_772608 * 0.001f;
	rhw = g_772608 * 0.001f + 0.01f;
	for (i = 0; i < 6; i++) {
		q->v[i].z = z;
		q->v[i].rhw = rhw;
	}
	g_772604++;
	g_772608++;
	fcn_0047b9a0(q, 200, 200, 200);
	return q;
}
