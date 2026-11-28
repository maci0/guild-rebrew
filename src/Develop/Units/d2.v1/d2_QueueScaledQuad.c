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

void __cdecl d2_FlushQueuedQuads(int a, int b, int c);
int __cdecl d2_BuildQuadVertices(int x, int y, int w, int h, Vtx47ba20* v);
void __cdecl d2_SetQuadVertexColor(Vtx47ba20* v, unsigned char r, unsigned char g,
                          unsigned char b);

/* ADDRESS: GOLDTL 0x0047ba20 */
/* ADDRESS: GOLDDE 0x0046aa10 */
int __cdecl d2_QueueScaledQuad(int x, int y, char* image, float scale)
{
	char* rec;
	Vtx47ba20* v;
	float* tex;
	int* q;
	int w;
	int h;
	int tw;
	int base;
	float ox;
	float oy;
	float term;
	float zt;
	float rho;
	float inv;
	float fw;
	float fh;

	rec = 0;
	ox = 0.0f;
	oy = 0.0f;
	if (image != 0) {
		w = *(unsigned short*) (image + 2);
		h = *(unsigned short*) (image + 6);
		if (d2_QueuedQuadCount >= 0x400) {
			d2_FlushQueuedQuads(0, 0, 0);
			if (d2_QueuedQuadCount >= 0x400)
				return 0;
		}
		base = d2_QueuedQuadCount * 0xac;
		rec = (char*) (base + 0x1552020);
		if ((float) w * scale + (float) x < (float) d2_ClipLeft ||
		    x > d2_ClipRight ||
		    (float) h * scale + (float) y < (float) g_7725fc ||
		    y > d2_ClipBottom)
			return 0;
		if (x < d2_ClipLeft) {
			ox = (float) (d2_ClipLeft - x);
			x = d2_ClipLeft;
			w = (int) ((float) *(unsigned short*) (image + 2) - ox);
		}
		if (y < g_7725fc) {
			oy = (float) (g_7725fc - y);
			y = g_7725fc;
			h = (int) ((float) *(unsigned short*) (image + 6) - oy);
		}
		if ((float) w * scale + (float) x > (float) d2_ClipRight)
			w = d2_ClipRight - x;
		if ((float) h * scale + (float) y > (float) d2_ClipBottom)
			h = (int) ((float) (d2_ClipBottom - y) / scale);
		if (w <= 0 || h <= 0)
			return 0;
		if (!d2_BuildQuadVertices(x, y, (int) ((float) w * scale + 0.5f),
		                  (int) ((float) h * scale + 0.5f), (Vtx47ba20*) rec))
			return 0;
		q = *(int**) (image + 0x28);
		q = (int*) *q;
		*(int*) (rec + 0xa8) = q[8];
		q = *(int**) (image + 0x28);
		q = (int*) *q;
		tw = q[1];
		inv = 1.0f / (float) tw;
		ox = ox * inv;
		oy = inv * oy;
		term = (float) d2_DrawDepthIndex * 0.001f;
		zt = 1.0f - term;
		v = (Vtx47ba20*) rec;
		v[0].z = zt;
		rho = term + 0.01f;
		v[0].rhw = rho;
		tex = (float*) *(int**) (image + 0x30);
		v[0].u = ox + tex[0];
		tex = (float*) *(int**) (image + 0x30);
		v[0].v = oy + tex[1];
		v[1].z = zt;
		v[1].rhw = rho;
		tex = (float*) *(int**) (image + 0x30);
		fw = (float) w / (float) tw;
		v[1].u = fw + tex[0] + ox;
		tex = (float*) *(int**) (image + 0x30);
		v[1].v = oy + tex[1];
		v[2].z = zt;
		v[2].rhw = rho;
		tex = (float*) *(int**) (image + 0x30);
		v[2].u = ox + tex[0];
		tex = (float*) *(int**) (image + 0x30);
		fh = (float) h / (float) tw;
		v[2].v = fh + tex[1] + oy;
		v[3].z = zt;
		v[3].rhw = rho;
		tex = (float*) *(int**) (image + 0x30);
		v[3].u = fw + tex[0] + ox;
		tex = (float*) *(int**) (image + 0x30);
		v[3].v = oy + tex[1];
		v[4].z = zt;
		v[4].rhw = rho;
		tex = (float*) *(int**) (image + 0x30);
		v[4].u = fw + tex[0] + ox;
		tex = (float*) *(int**) (image + 0x30);
		v[4].v = fh + tex[1] + oy;
		v[5].z = zt;
		v[5].rhw = rho;
		tex = (float*) *(int**) (image + 0x30);
		v[5].u = ox + tex[0];
		tex = (float*) *(int**) (image + 0x30);
		v[5].v = fh + tex[1] + oy;
		d2_SetQuadVertexColor(v, 200, 200, 200);
		d2_QueuedQuadCount = d2_QueuedQuadCount + 1;
		d2_DrawDepthIndex = d2_DrawDepthIndex + 1;
	}
	return (int) rec;
}
