typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} Vtx47ba20;

extern int g_772604;
extern int g_772608;
extern int g_7725f8;
extern int g_7725fc;
extern int g_67d964;
extern int g_67d968;

void __cdecl fcn_0047c560(int a, int b, int c);
int __cdecl fcn_0047b8b0(int x, int y, int w, int h, Vtx47ba20* v);
void __cdecl fcn_0047b9a0(Vtx47ba20* v, unsigned char r, unsigned char g,
                          unsigned char b);

/* ADDRESS: GOLDTL 0x0047ba20 */
int __cdecl fcn_0047ba20(int x, int y, char* a2, float scale)
{
	char* rec;
	Vtx47ba20* v;
	float* tex;
	int* q;
	int w;
	int h;
	int base;
	float ox;
	float oy;
	float term;
	float zt;
	float rho;
	float inv;
	float fw;
	float fh;
	float val;

	ox = 0.0f;
	oy = 0.0f;
	if (a2 == 0)
		return 0;
	w = *(unsigned short*) (a2 + 2);
	h = *(unsigned short*) (a2 + 6);
	if (g_772604 >= 0x400) {
		fcn_0047c560(0, 0, 0);
		if (g_772604 >= 0x400)
			return 0;
	}
	base = g_772604 * 0xac;
	rec = (char*) (base + 0x1552020);
	if (g_7725f8 > (float) w * scale + (float) x)
		return 0;
	if (x > g_67d964)
		return 0;
	if (g_7725fc > (float) h * scale + (float) y)
		return 0;
	if (y > g_67d968)
		return 0;
	if (x < g_7725f8) {
		ox = (float) (g_7725f8 - x);
		x = g_7725f8;
		w = (int) ((float) w - ox);
	}
	if (y < g_7725fc) {
		oy = (float) (g_7725fc - y);
		y = g_7725fc;
		h = (int) ((float) h - oy);
	}
	if ((float) g_67d964 < (float) w * scale + (float) x)
		w = g_67d964 - x;
	if ((float) g_67d968 < (float) h * scale + (float) y)
		h = (int) ((float) (g_67d968 - y) / scale);
	if (w < 1 || h < 1)
		return 0;
	if (!fcn_0047b8b0(x, y, (int) ((float) w * scale + 0.5f),
	                  (int) ((float) h * scale + 0.5f), (Vtx47ba20*) rec))
		return 0;
	q = *(int**) (a2 + 0x28);
	q = (int*) *q;
	*(int*) (rec + 0xa8) = q[8];
	val = (float) q[1];
	inv = 1.0f / val;
	ox = ox * inv;
	oy = inv * oy;
	term = (float) g_772608 * 0.001f;
	zt = 1.0f - term;
	rho = term + 0.01f;
	fw = (float) w / val;
	fh = (float) h / val;
	tex = (float*) *(int**) (a2 + 0x30);
	v = (Vtx47ba20*) rec;
	v[0].z = zt;
	v[0].rhw = rho;
	v[0].u = ox + tex[0];
	v[0].v = oy + tex[1];
	v[1].z = zt;
	v[1].rhw = rho;
	v[1].u = fw + tex[0] + ox;
	v[1].v = oy + tex[1];
	v[2].z = zt;
	v[2].rhw = rho;
	v[2].u = ox + tex[0];
	v[2].v = fh + tex[1] + oy;
	v[3].z = zt;
	v[3].rhw = rho;
	v[3].u = fw + tex[0] + ox;
	v[3].v = oy + tex[1];
	v[4].z = zt;
	v[4].rhw = rho;
	v[4].u = fw + tex[0] + ox;
	v[4].v = fh + tex[1] + oy;
	v[5].z = zt;
	v[5].rhw = rho;
	v[5].u = ox + tex[0];
	v[5].v = fh + tex[1] + oy;
	fcn_0047b9a0(v, 200, 200, 200);
	g_772604 = g_772604 + 1;
	g_772608 = g_772608 + 1;
	return (int) rec;
}
