extern char* g_6b8014;
extern float g_1052bc0;
extern float g_1052bc8;
extern float g_10432a4;
extern float g_1042584;
extern float g_6628a8;
extern float g_6628a0;
extern double g_662e68;

float* __stdcall fcn_005ebbb9(float* out, const float* in);

/* ADDRESS: GOLDTL 0x0045bad0 */
/* Projects the target point into the grid and walks the grid line until a cell
 * of the map holds at least the requested value. */
int __cdecl fcn_0045bad0(char* e, int gx, int gy, int* ox, int* oy)
{
	float m[16];
	float u;
	float v;
	float x0;
	float y0;
	float z0;
	float px;
	float py;
	float pz;
	float t;
	float lim;
	int ix;
	int iy;
	int iw;
	unsigned char b;

	if (e == 0) {
		return 0;
	}
	x0 = (*(float*) (g_6b8014 + 0x4c) - *(float*) (e + 0)) / *(float*) (e + 0x10);
	y0 = (*(float*) (g_6b8014 + 0x50) - *(float*) (e + 4)) / *(float*) (e + 0x14);
	z0 = (*(float*) (g_6b8014 + 0x54) - *(float*) (e + 8)) / *(float*) (e + 0x18);
	u = ((float) gx - g_1052bc0) / g_10432a4;
	v = ((float) gy - g_1052bc8) / g_1042584;
	fcn_005ebbb9(m, (float*) (g_6b8014 + 0x18c));
	px = m[4] * v + m[0] * u + m[12];
	py = m[5] * v + m[1] * u + m[13];
	pz = m[6] * v + m[2] * u + m[14];
	px = px / *(float*) (e + 0x10);
	py = py / *(float*) (e + 0x14);
	pz = pz / *(float*) (e + 0x18);
	if (fabs(px) < g_662e68 && fabs(pz) < g_662e68) {
		ix = (int) x0;
		iy = (int) y0;
		if (y0 > 0.0f) {
			iw = *(int*) (e + 0x20);
			b = *(unsigned char*) (*(int*) (e + 0x28) + iy * iw + ix);
			if ((float) b < y0) {
				return 0;
			}
		}
		*ox = ix;
		*oy = iy;
		return 1;
	}
	t = fabs(px);
	if (!(t > fabs(pz))) {
		t = fabs(pz);
	}
	t = g_6628a0 / t;
	px = px * t;
	py = py * t;
	pz = pz * t;
	if (x0 < 0.0f) {
		return 0;
	}
	iw = *(int*) (e + 0x20);
	lim = (float) iw;
	for (;;) {
		if (!(x0 < lim)) {
			break;
		}
		if (y0 < 0.0f) {
			return 0;
		}
		if (!(y0 < lim)) {
			return 0;
		}
		ix = (int) x0;
		iy = (int) y0;
		b = *(unsigned char*) (*(int*) (e + 0x28) + iy * iw + ix);
		if (!((float) b < y0)) {
			*ox = ix;
			*oy = iy;
			return 1;
		}
		x0 = x0 + px;
		y0 = y0 + py;
		z0 = z0 + pz;
		if (!(x0 >= 0.0f)) {
			return 0;
		}
	}
	return 0;
}
