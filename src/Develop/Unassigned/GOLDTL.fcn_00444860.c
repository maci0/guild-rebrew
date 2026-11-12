#include <math.h>

extern int g_14ce860;
extern int g_14ce864;
extern float g_10432a4;
extern float g_1052bc0;
extern float g_1052bc8;
extern int g_67a370;

extern void __cdecl fcn_004379a0(int, int, int, void*, void*);
extern int __cdecl fcn_00444ff0(int, int*);

typedef struct {
	int x;
	int y;
} pick_point;

typedef struct {
	int obj;
	float pos[4][4];
	float uv[4][2];
	pick_point edge[4];
	unsigned char found;
} pick_ctx;

typedef struct {
	float w1;
	float w2;
	float t1;
	float e1x;
	float e1y;
	float e1z;
	float e2x;
	float e2y;
	float e2z;
	float qx;
	float qy;
	float min[2];
	int ic;
	int ib;
	int ia;
	float dx;
	float dy;
	float dz;
	float ay;
	pick_ctx ctx;
} pick_frame;

/* ADDRESS: GOLDTL 0x00444860 */
unsigned char __cdecl fcn_00444860(float x, float y, int obj, int index,
	float* outx, float* outy)
{
	pick_frame fr;
	float ax;
	float az;
	float n1;
	float n2;
	float n3;
	float den;
	float t;
	float r;
	float r2;
	float qz;
	int i;
	int j;
	int id;

	if (!index)
		return 0;
	fr.ctx.obj = index;
	fr.ctx.edge[0].x = g_14ce860 - 1;
	fr.ctx.edge[0].y = g_14ce864 - 1;
	fr.ctx.edge[1].x = 0;
	fr.ctx.edge[1].y = g_14ce864 - 1;
	fr.ctx.edge[2].x = g_14ce860 - 1;
	fr.ctx.edge[2].y = 0;
	fr.ctx.edge[3].x = 0;
	fr.ctx.edge[3].y = 0;
	fr.ctx.found = 0;
	fcn_004379a0(g_67a370, obj, 0x40, (void*) fcn_00444ff0, &fr.ctx);
	if (!fr.ctx.found)
		return 0;

	fr.min[0] = 1.0e10f;
	fr.min[1] = 1.0e10f;
	for (i = 0; i < 4; i++) {
		if (!(fr.ctx.uv[i][0] > fr.min[0]))
			fr.min[0] = fr.ctx.uv[i][0];
		if (!(fr.ctx.uv[i][1] > fr.min[1]))
			fr.min[1] = fr.ctx.uv[i][1];
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 2; j++)
			fr.ctx.uv[i][j] -= fr.min[j];
		fr.ctx.uv[i][1] = 1.0f - fr.ctx.uv[i][1];
	}

	fr.ia = -1;
	fr.ib = -1;
	fr.ic = -1;
	fr.w1 = 1.0e10f;
	fr.w2 = -1.0e10f;
	fr.t1 = -1.0e10f;
	for (i = 0; i < 4; i++) {
		float fx = (float) fabs(fr.ctx.uv[i][0]);
		float fy = (float) fabs(fr.ctx.uv[i][1]);

		if (fy - fx > fr.t1) {
			fr.t1 = fy - fx;
			fr.ia = i;
		}
		if (fx + fy > fr.w2) {
			fr.w2 = fx + fy;
			fr.ib = i;
		}
		if (fx + fy < fr.w1) {
			fr.w1 = fx + fy;
			fr.ic = i;
		}
	}
	if (fr.ia == -1 || fr.ib == -1 || fr.ic == -1)
		return 0;
	if (fr.ia == fr.ib || fr.ia == fr.ic || fr.ib == fr.ic)
		return 0;
	for (id = 0; id == fr.ia || id == fr.ib || id == fr.ic; id++)
		;

	ax = fr.ctx.pos[fr.ia][0];
	fr.ay = fr.ctx.pos[fr.ia][1];
	az = fr.ctx.pos[fr.ia][2];
	fr.e1x = ax - fr.ctx.pos[fr.ib][0];
	fr.e1y = fr.ay - fr.ctx.pos[fr.ib][1];
	fr.e1z = az - fr.ctx.pos[fr.ib][2];
	fr.e2x = ax - fr.ctx.pos[fr.ic][0];
	fr.e2y = fr.ay - fr.ctx.pos[fr.ic][1];
	fr.e2z = az - fr.ctx.pos[fr.ic][2];
	n1 = fr.e2z * fr.e1y - fr.e2y * fr.e1z;
	n2 = fr.e2x * fr.e1z - fr.e2z * fr.e1x;
	fr.t1 = fr.e2y * fr.e1x;
	fr.w1 = fr.e2x * fr.e1y;
	n3 = fr.t1 - fr.w1;
	fr.dx = x - g_1052bc0;
	fr.dy = -(y - g_1052bc8);
	fr.dz = g_10432a4;
	den = fr.dz * n3 + fr.dy * n2 + fr.dx * n1;
	if (!((float) fabs(den) > 1e-7))
		return 0;
	t = (n3 * az + n2 * fr.ay + n1 * ax + (n3 + n2 + n1) * 0.0f) / den;
	fr.qx = ax - t * fr.dx;
	fr.qy = fr.ay - t * fr.dy;
	qz = az - t * fr.dz;
	r = (fr.qx * fr.e1y - fr.qy * fr.e1x)
		/ (fr.e2x * fr.e1y - fr.e2y * fr.e1x);
	fr.qx = fr.qx + r * -fr.e2x;
	fr.qy = fr.qy + r * -fr.e2y;
	qz = qz + r * -fr.e2z;
	r2 = (fr.qx / fr.e1x + fr.qy / fr.e1y + qz / fr.e1z)
		* (1.0f / 3.0f);
	fr.w1 = r;
	fr.w2 = r2;
	if (r2 + r > 1.0) {
		ax = fr.ctx.pos[id][0];
		fr.ay = fr.ctx.pos[id][1];
		az = fr.ctx.pos[id][2];
		fr.e1x = ax - fr.ctx.pos[fr.ib][0];
		fr.e1y = fr.ay - fr.ctx.pos[fr.ib][1];
		fr.e1z = az - fr.ctx.pos[fr.ib][2];
		fr.e2x = ax - fr.ctx.pos[fr.ic][0];
		fr.e2y = fr.ay - fr.ctx.pos[fr.ic][1];
		fr.e2z = az - fr.ctx.pos[fr.ic][2];
		n1 = fr.e2z * fr.e1y - fr.e2y * fr.e1z;
		n2 = fr.e2x * fr.e1z - fr.e2z * fr.e1x;
		fr.t1 = fr.e2y * fr.e1x;
		fr.w1 = fr.e2x * fr.e1y;
		n3 = fr.t1 - fr.w1;
		den = fr.dz * n3 + fr.dy * n2 + fr.dx * n1;
		if (!((float) fabs(den) > 1e-7))
			return 0;
		t = (n3 * az + n2 * fr.ay + n1 * ax
			+ (n3 + n2 + n1) * 0.0f) / den;
		fr.qx = ax - t * fr.dx;
		fr.qy = fr.ay - t * fr.dy;
		qz = az - t * fr.dz;
		r = (fr.qx * fr.e1y - fr.qy * fr.e1x)
			/ (fr.e2x * fr.e1y - fr.e2y * fr.e1x);
		fr.qx = fr.qx + r * -fr.e2x;
		fr.qy = fr.qy + r * -fr.e2y;
		qz = qz + r * -fr.e2z;
		r2 = (fr.qx / fr.e1x + fr.qy / fr.e1y + qz / fr.e1z)
			* (1.0f / 3.0f);
		fr.w1 = r;
		fr.w2 = r2;
		if (!(r2 >= 0.0f))
			return 0;
		if (!(r2 <= 1.0f))
			return 0;
		if (!(r >= 0.0f))
			return 0;
		if (!(r <= 1.0f))
			return 0;
		*outx = ((float) fabs(fr.ctx.uv[fr.ib][0])
			- (float) fabs(fr.ctx.uv[fr.ia][0])) * (1.0f - r2)
			+ (float) fabs(fr.ctx.uv[fr.ia][0]);
		*outy = 1.0 - (((float) fabs(fr.ctx.uv[fr.ic][1])
			- (float) fabs(fr.ctx.uv[fr.ia][1])) * (1.0f - r)
			+ (float) fabs(fr.ctx.uv[fr.ia][1]));
		return 1;
	} else {
		if (!(r2 >= 0.0f))
			return 0;
		if (!(r2 <= 1.0f))
			return 0;
		if (!(r >= 0.0f))
			return 0;
		if (!(r <= 1.0f))
			return 0;
		*outx = ((float) fabs(fr.ctx.uv[fr.ib][0])
			- (float) fabs(fr.ctx.uv[fr.ia][0])) * r2
			+ (float) fabs(fr.ctx.uv[fr.ia][0]);
		*outy = 1.0 - (((float) fabs(fr.ctx.uv[fr.ic][1])
			- (float) fabs(fr.ctx.uv[fr.ia][1])) * r
			+ (float) fabs(fr.ctx.uv[fr.ia][1]));
		return 1;
	}
	return 0;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
