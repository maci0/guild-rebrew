#include <math.h>

typedef unsigned char u8;

extern int g_1041d0c;
extern int g_1041d68;
extern int g_14ce8d0;
extern int g_14ce8e4;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern unsigned int g_14ce860;
extern unsigned int g_14ce864;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern char g_14cf72a;
extern char g_14cf71d;
extern char g_67ab48;
extern char g_67ab49;
extern char g_6b85a0;
extern int g_6b85b0;
extern int g_6b85b4;
extern int g_6b85b8;
extern int g_6b85bc;
extern int g_6b8478;
extern int g_6b847c;
extern int g_6b8480;
extern int g_6b8484;

int __cdecl fcn_00449600(int a);
int __cdecl fcn_00448cc0(int self, float* dir, float* view, int pos,
	float* outA, float* outB);
void __cdecl fcn_00438b40(int h, float* p);
void __cdecl fcn_00438cb0(int h, float* p);
void __cdecl UpdateSceneLighting(int a);
int __cdecl fcn_00448b10(void);

/* ADDRESS: GOLDTL 0x00449630 */
int __cdecl fcn_00449630(void)
{
	char changed;
	char dirty;
	float f04;
	int dx;
	int dy;
	float f10;
	float f14;
	float a18[2];
	float ang;
	int handle;
	float p28[3];
	float p34[3];
	float p44[4];
	int h;
	short mx;
	short my;
	unsigned int w;
	unsigned int ht;
	float r;
	float s;
	u8 ok;

	h = g_1041d0c;
	dirty = 0;
	changed = 0;
	if (h == 0)
		return 0;
	handle = fcn_00449600(g_1041d68);
	ang = *(float*) 0x6628a8;
	mx = g_14ce8c0;
	ht = g_14ce864;
	w = g_14ce860;
	my = g_14ce8c2;
	p28[0] = 0.0f;
	p28[1] = 0.0f;
	p28[2] = 0.0f;
	p34[0] = 0.0f;
	p34[1] = 0.0f;
	p34[2] = 0.0f;
	f04 = 0.0f;
	f10 = 0.0f;
	f14 = 0.0f;
	if (g_14ce8d0 != 0) {
		if (g_6b85b8 == 0) {
			g_6b85b0 = (int) mx;
			g_6b85b8 = 1;
			g_6b85b4 = (int) my;
		}
		else if (*(int*) (h + 0x218) != 0 && h != g_6b8478
			&& h != g_6b847c && h != g_6b8480) {
			if (g_67ab48 != 0) {
				changed = 1;
				dx = (int) mx - g_6b85b0;
			}
			else
				dx = 0;
			if (g_67ab49 != 0) {
				changed = 1;
				dy = (int) my - g_6b85b4;
			}
			else
				dy = 0;
			g_6b85b0 = (int) mx;
			g_6b85b4 = (int) my;
			ang = (float) dx / (float) w * *(float*) 0x6628fc;
			f14 = (float) dy / (float) ht * *(float*) 0x6628fc;
			h = g_1041d0c;
		}
	}
	if (g_14ce8e4 != 0) {
		if (g_6b85bc == 0) {
			g_6b85bc = 1;
			g_6b85b0 = (int) mx;
			g_6b85b4 = (int) my;
			goto check;
		}
		if (g_67ab48 != 0) {
			dx = (int) mx - g_6b85b0;
			dirty = 1;
		}
		else
			dx = 0;
		if (g_67ab49 != 0) {
			dy = (int) my - g_6b85b4;
			dirty = 1;
		}
		else
			dy = 0;
		f04 = dx / (double) w;
		g_6b85b4 = (int) my;
		g_6b85b0 = (int) mx;
		f10 = (float) ht;
		a18[0] = (double) dy / f10;
		r = ((float) fabs((float) dx) + 1.0f) * 30.0f / (double) w;
		if (3.0f < r)
			r = 3.0f;
		s = ((float) fabs((float) dy) + 1.0f) * 30.0f / (float) ht;
		if (3.0f < s)
			s = 3.0f;
		f10 = r * f04 * 256.0f;
		f04 = s * a18[0] * -256.0f;
		if (dirty != 0)
			goto body;
	}
check:
	if (changed == 0)
		goto out;
body:
	if (h == g_6b8484) {
		if (g_14cf72a == 0 && g_14cf71d == 0) {
			p28[1] = ang;
			p28[0] = f14;
			goto both;
		}
		p28[2] = ang;
		if (g_14cf72a == 0 && g_14cf71d == 0)
			goto both;
		p34[2] = f04;
		goto call;
	}
	if (g_14cf72a != 0) {
		p28[1] = ang;
		p34[2] = f04;
		goto call;
	}
	if (g_14cf71d != 0) {
		p28[0] = ang;
		p34[2] = f04;
		goto call;
	}
	p28[2] = ang;
both:
	p34[0] = f10;
	p34[1] = f04;
call:
	ok = (u8) fcn_00448cc0(h, p34, p28, handle, p44, a18);
	dirty = (char) (ok & 1);
	changed = (char) (ok >> 1);
	if (dirty != 0)
		fcn_00438b40(g_1041d0c, p44);
	if (changed != 0 && g_1041d0c != g_6b8478
		&& g_1041d0c != g_6b847c && g_1041d0c != g_6b8480)
		fcn_00438cb0(g_1041d0c, a18);
out:
	if (g_6b85b8 != 0 && g_14ce8cc != 0) {
		g_6b85b8 = 0;
		UpdateSceneLighting(1);
		dirty = 1;
	}
	if (g_6b85bc != 0 && g_14ce8e0 != 0) {
		g_6b85bc = 0;
		UpdateSceneLighting(1);
		dirty = 1;
	}
	ok = (u8) fcn_00448b10();
	if ((ok | dirty) == 0 && changed == 0)
		return 0;
	return 1;
}
