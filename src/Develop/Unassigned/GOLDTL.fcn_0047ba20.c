typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} Vtx47ba20;

#include "Develop/DieGildeAddOn/game/game_data.h"

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
	h = *(unsigned short*) (a2 + 6);
	w = *(unsigned short*) (a2 + 2);
	if (d2_QueuedQuadCount >= 0x400) {
		fcn_0047c560(0, 0, 0);
		if (d2_QueuedQuadCount >= 0x400)
			return 0;
	}
	base = d2_QueuedQuadCount * 0xac;
	rec = (char*) (base + 0x1552020);
	if (d2_ClipLeft > (float) w * scale + (float) x)
		return 0;
	if (x > d2_ClipRight)
		return 0;
	if (g_7725fc > (float) h * scale + (float) y)
		return 0;
	if (y > d2_ClipBottom)
		return 0;
	if (x < d2_ClipLeft) {
		ox = (float) (d2_ClipLeft - x);
		x = d2_ClipLeft;
		w = (int) ((float) w - ox);
	}
	if (y < g_7725fc) {
		oy = (float) (g_7725fc - y);
		y = g_7725fc;
		h = (int) ((float) *(unsigned short*) (a2 + 6) - oy);
	}
	if ((float) d2_ClipRight < (float) w * scale + (float) x)
		w = d2_ClipRight - x;
	if ((float) d2_ClipBottom < (float) h * scale + (float) y)
		h = (int) ((float) (d2_ClipBottom - y) / scale);
	if (w < 1 || h < 1)
		return 0;
	if (!fcn_0047b8b0(x, y, (int) ((float) w * scale + 0.5f),
	                  (int) ((float) h * scale + 0.5f), (Vtx47ba20*) rec))
		return 0;
	q = *(int**) (a2 + 0x28);
	q = (int*) *q;
	*(int*) (rec + 0xa8) = q[8];
	q = *(int**) (a2 + 0x28);
	q = (int*) *q;
	val = (float) q[1];
	inv = 1.0f / val;
	ox = ox * inv;
	oy = inv * oy;
	term = (float) d2_DrawDepthIndex * 0.001f;
	zt = 1.0f - term;
	rho = term + 0.01f;
	v = (Vtx47ba20*) rec;
	v[0].z = zt;
	v[0].rhw = rho;
	tex = (float*) *(int**) (a2 + 0x30);
	v[0].u = ox + tex[0];
	tex = (float*) *(int**) (a2 + 0x30);
	v[0].v = oy + tex[1];
	v[1].z = zt;
	v[1].rhw = rho;
	tex = (float*) *(int**) (a2 + 0x30);
	fw = (float) w / val;
	v[1].u = fw + tex[0] + ox;
	tex = (float*) *(int**) (a2 + 0x30);
	v[1].v = oy + tex[1];
	v[2].z = zt;
	v[2].rhw = rho;
	tex = (float*) *(int**) (a2 + 0x30);
	v[2].u = ox + tex[0];
	tex = (float*) *(int**) (a2 + 0x30);
	fh = (float) h / val;
	v[2].v = fh + tex[1] + oy;
	v[3].z = zt;
	v[3].rhw = rho;
	tex = (float*) *(int**) (a2 + 0x30);
	v[3].u = fw + tex[0] + ox;
	tex = (float*) *(int**) (a2 + 0x30);
	v[3].v = oy + tex[1];
	v[4].z = zt;
	v[4].rhw = rho;
	tex = (float*) *(int**) (a2 + 0x30);
	v[4].u = fw + tex[0] + ox;
	tex = (float*) *(int**) (a2 + 0x30);
	v[4].v = fh + tex[1] + oy;
	v[5].z = zt;
	v[5].rhw = rho;
	tex = (float*) *(int**) (a2 + 0x30);
	v[5].u = ox + tex[0];
	tex = (float*) *(int**) (a2 + 0x30);
	v[5].v = fh + tex[1] + oy;
	fcn_0047b9a0(v, 200, 200, 200);
	d2_QueuedQuadCount = d2_QueuedQuadCount + 1;
	d2_DrawDepthIndex = d2_DrawDepthIndex + 1;
	return (int) rec;
}
