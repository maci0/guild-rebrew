// FUNCTION: GOLDTL 0x47bf80

// SIZE 0x1c
typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} Vtx;

// SIZE 0xac
typedef struct {
	Vtx v[6];
	int tex;
} Quad;

// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect47bf;

extern int g_772604;
extern int g_772608;
extern int g_7725f8;
extern int g_7725fc;
extern int g_67d964;
extern int g_67d968;
extern Quad g_1552020[0x400];

void __cdecl fcn_0047c560(int a, int b, int c);
int __cdecl fcn_0047b8b0(int x, int y, int w, int h, Quad* q);
void __cdecl fcn_0047b9a0(Quad* q, unsigned char r, unsigned char g, unsigned char b);

Quad* __cdecl fcn_0047bf80(int x, int y, int w, int h, int tex, Rect47bf* src)
{
	int cw;
	int ch;
	float fu;
	float fv;
	int rw;
	int rh;
	float u0;
	float v0;
	float u1;
	float v1;
	float t;
	int i;
	int n;
	Quad* q;

	fu = 0.0f;
	fv = 0.0f;
	cw = w;
	ch = h;
	if (src == 0) {
		rw = w;
		rh = h;
	} else {
		rw = src->right - src->left;
		rh = src->bottom - src->top;
	}
	n = g_772604;
	if (n >= 0x400) {
		fcn_0047c560(0, 0, 0);
		n = g_772604;
		if (n >= 0x400) {
			return 0;
		}
	}
	if (x + w < g_7725f8 || x > g_67d964 || y + h < g_7725fc || y > g_67d968) {
		return 0;
	}
	if (x < g_7725f8) {
		fu = (float) (g_7725f8 - x);
		x = g_7725f8;
		cw = (int) (w - fu);
	}
	if (y < g_7725fc) {
		fv = (float) (g_7725fc - y);
		y = g_7725fc;
		ch = (int) (h - fv);
	}
	if (cw + x > g_67d964) {
		cw = g_67d964 - x;
	}
	if (ch + y > g_67d968) {
		ch = g_67d968 - y;
	}
	q = &g_1552020[n];
	if (fcn_0047b8b0(x, y, cw, ch, q) == 0) {
		return 0;
	}
	q->tex = tex;
	u0 = fu / w;
	v0 = fv / h;
	q->v[0].u = u0;
	q->v[0].v = v0;
	u1 = (float) cw / rw + u0;
	q->v[1].u = u1;
	q->v[1].v = v0;
	q->v[2].u = u0;
	v1 = (float) ch / rh + v0;
	q->v[2].v = v1;
	q->v[3].u = u1;
	q->v[3].v = v0;
	q->v[4].u = u1;
	q->v[4].v = v1;
	q->v[5].u = u0;
	q->v[5].v = v1;
	t = g_772608 * 0.001f;
	for (i = 0; i < 6; i++) {
		q->v[i].z = 1.0f - t;
		q->v[i].rhw = t + 0.01f;
	}
	g_772604 = n + 1;
	g_772608++;
	fcn_0047b9a0(q, 200, 200, 200);
	return q;
}
