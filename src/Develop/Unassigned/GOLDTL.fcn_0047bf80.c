


















// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect47bf;

extern int d2_QueuedQuadCount;
extern int d2_DrawDepthIndex;
extern int d2_ClipLeft;
extern int g_7725fc;
extern int d2_ClipRight;
extern int d2_ClipBottom;
#include "Develop/Unassigned/render_quad.h"

void __cdecl fcn_0047c560(int a, int b, int c);
int __cdecl fcn_0047b8b0(int x, int y, int w, int h, RENDER_QUAD* q);
void __cdecl d2_SetQuadVertexColor(RENDER_QUAD* q, unsigned char r, unsigned char g, unsigned char b);

RENDER_QUAD* __cdecl d2_QueueTexturedQuad(int x, int y, int w, int h, int tex, Rect47bf* src)
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
	float depth;
	int i;
	int quadIndex;
	RENDER_QUAD* quad;

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
	quadIndex = d2_QueuedQuadCount;
	if (quadIndex >= 0x400) {
		fcn_0047c560(0, 0, 0);
		quadIndex = d2_QueuedQuadCount;
		if (quadIndex >= 0x400) {
			return 0;
		}
	}
	if (x + w < d2_ClipLeft || x > d2_ClipRight || y + h < g_7725fc || y > d2_ClipBottom) {
		return 0;
	}
	if (x < d2_ClipLeft) {
		fu = (float) (d2_ClipLeft - x);
		x = d2_ClipLeft;
		cw = (int) (w - fu);
	}
	if (y < g_7725fc) {
		fv = (float) (g_7725fc - y);
		y = g_7725fc;
		ch = (int) (h - fv);
	}
	if (cw + x > d2_ClipRight) {
		cw = d2_ClipRight - x;
	}
	if (ch + y > d2_ClipBottom) {
		ch = d2_ClipBottom - y;
	}
	quad = &g_1552020[quadIndex];
	if (fcn_0047b8b0(x, y, cw, ch, quad) == 0) {
		return 0;
	}
	quad->tex = tex;
	u0 = fu / w;
	v0 = fv / h;
	quad->v[0].u = u0;
	quad->v[0].v = v0;
	u1 = (float) cw / rw + u0;
	quad->v[1].u = u1;
	quad->v[1].v = v0;
	quad->v[2].u = u0;
	v1 = (float) ch / rh + v0;
	quad->v[2].v = v1;
	quad->v[3].u = u1;
	quad->v[3].v = v0;
	quad->v[4].u = u1;
	quad->v[4].v = v1;
	quad->v[5].u = u0;
	quad->v[5].v = v1;
	depth = d2_DrawDepthIndex * 0.001f;
	for (i = 0; i < 6; i++) {
		quad->v[i].z = 1.0f - depth;
		quad->v[i].rhw = depth + 0.01f;
	}
	d2_QueuedQuadCount = quadIndex + 1;
	d2_DrawDepthIndex++;
	d2_SetQuadVertexColor(quad, 200, 200, 200);
	return quad;
}
