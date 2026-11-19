


















typedef struct Tex {
	char pad0[0x20];
	int handle;
	char pad24[0x54 - 0x24];
	int size;
} Tex;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Unassigned/render_quad.h"

int __cdecl fcn_0047b8b0(int x, int y, int w, int h, RENDER_QUAD* q);
void __cdecl fcn_0047b9a0(RENDER_QUAD* q, unsigned char r, unsigned char g, unsigned char b);

RENDER_QUAD* __cdecl fcn_0047c1f0(float u, float v, int w, int h, Tex* tex, int x, int y)
{
	int cw;
	int ch;
	float du;
	float dv;
	int tw;
	int th;
	float z;
	float rhw;
	RENDER_QUAD* q;
	int i;

	du = 0.0f;
	dv = 0.0f;
	cw = w;
	ch = h;
	tw = tex->size;
	th = tex->size;
	if (d2_QueuedQuadCount >= 0x400) {
		return 0;
	}
	if (x + w < d2_ClipLeft || x > d2_ClipRight || y + h < g_7725fc || y > d2_ClipBottom) {
		return 0;
	}
	if (x < d2_ClipLeft) {
		du = (float)(d2_ClipLeft - x);
		x = d2_ClipLeft;
		cw = (int)(w - du);
	}
	if (y < g_7725fc) {
		dv = (float)(g_7725fc - y);
		y = g_7725fc;
		ch = (int)(h - dv);
	}
	if (x + cw > d2_ClipRight) {
		cw = d2_ClipRight - x;
	}
	if (ch + y > d2_ClipBottom) {
		ch = d2_ClipBottom - y;
	}
	q = &g_1552020[d2_QueuedQuadCount];
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
	z = 1.0f - d2_DrawDepthIndex * 0.001f;
	rhw = d2_DrawDepthIndex * 0.001f + 0.01f;
	for (i = 0; i < 6; i++) {
		q->v[i].z = z;
		q->v[i].rhw = rhw;
	}
	d2_QueuedQuadCount++;
	d2_DrawDepthIndex++;
	fcn_0047b9a0(q, 200, 200, 200);
	return q;
}
