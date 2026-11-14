extern float g_6ad620;
extern float g_6660f0;
extern float g_6660e8;
extern float g_6628cc;
extern int g_1043370;
extern int g_6b7fac;

char __cdecl fcn_0045b990(int, float*, int*, int*, float*);
int __cdecl fcn_005ea2d0(int, float*, float*, int, int, int*, int*);

/* Projectile integration step. Native facts (all from disassembly):
 * obj is stack arg1; stack arg2 is never read (positions are the
 * obj+0x30/0x34/0x38 float triple via edi, not the second parameter).
 * Constants: g_6660f0=0.006756757, g_6660e8=9.81, g_6ad620=1.5,
 * 1.2 at 0x6660f8, 0.5 at 0x6628cc, 39.37008 at 0x6660e0.
 * Sign idiom (fcomp vs 0.0): (v>0 ? 1.0 : -1.0).
 * States: obj+0x5c 1 flying, 2 impact, 3 expired.
 */
/* ADDRESS: GOLDTL 0x005e9da0 */
int __cdecl fcn_005e9da0(char* obj)
{
	float step;
	float inv;
	float f[3];
	float q[3];
	float m[3];
	float r[3];
	float t[3];
	float pf[3];
	float v[3];
	float h;
	int remain;
	int n;
	int ox;
	int oy;
	int nx;
	int ny;
	int map;

	map = g_1043370;
	step = g_6660f0 * g_6660e8;
	inv = g_6660f0 / *(float*) (obj + 0x54);
	if (*(int*) (obj + 0x5c) != 1) {
		return 0;
	}
	remain = g_6b7fac - *(int*) (obj + 0x60);
	if (fcn_0045b990(map, (float*) (obj + 0x30), &ox, &oy, &h) == 0) {
		*(int*) (obj + 0x5c) = 3;
		*(int*) (obj + 0x58) = 0;
		return 0;
	}
	f[0] = *(float*) (obj + 0x50) * *(float*) (obj + 0x40) * *(float*) (obj + 0x40) * (*(float*) (obj + 0x40) > 0.0f ? 1.0f : -1.0f) * g_6ad620 * 1.2f * g_6628cc;
	f[1] = ((*(float*) (obj + 0x44) > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * *(float*) (obj + 0x44) * *(float*) (obj + 0x44) * g_6628cc;
	f[2] = *(float*) (obj + 0x50) * (*(float*) (obj + 0x48) > 0.0f ? 1.0f : -1.0f) * g_6ad620 * 1.2f * *(float*) (obj + 0x48) * *(float*) (obj + 0x48) * g_6628cc;
	n = 0;
	while (n < remain) {
		v[0] = *(float*) (obj + 0x10);
		v[1] = *(float*) (obj + 0x14);
		v[2] = *(float*) (obj + 0x18);
		q[0] = ((v[0] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[0] * v[0] * g_6628cc;
		q[1] = ((v[1] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[1] * v[1] * g_6628cc;
		q[2] = ((v[2] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[2] * v[2] * g_6628cc;
		m[0] = (q[0] + f[0]) * inv;
		m[1] = (q[1] + f[1]) * inv - step;
		m[2] = (q[2] + f[2]) * inv;
		v[0] += m[0];
		v[1] += m[1];
		v[2] += m[2];
		r[0] = ((v[0] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[0] * v[0] * g_6628cc;
		r[1] = ((v[1] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[1] * v[1] * g_6628cc;
		r[2] = ((v[2] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[2] * v[2] * g_6628cc;
		pf[0] = *(float*) (obj + 0x30);
		pf[1] = *(float*) (obj + 0x34);
		pf[2] = *(float*) (obj + 0x38);
		*(int*) (obj + 0x60) += 1;
		*(int*) (obj + 0x64) += 1;
		t[0] = (r[0] + f[0]) * inv;
		t[1] = (r[1] + f[1]) * inv - step;
		t[2] = (r[2] + f[2]) * inv;
		v[0] = (t[0] + m[0]) * g_6628cc + *(float*) (obj + 0x10);
		v[1] = (t[1] + m[1]) * g_6628cc + *(float*) (obj + 0x14);
		v[2] = (t[2] + m[2]) * g_6628cc + *(float*) (obj + 0x18);
		*(float*) (obj + 0x10) = v[0];
		*(float*) (obj + 0x14) = v[1];
		*(float*) (obj + 0x18) = v[2];
		pf[0] += v[0] * 39.37008f * g_6660f0;
		pf[1] += v[1] * 39.37008f * g_6660f0;
		pf[2] += v[2] * 39.37008f * g_6660f0;
		nx = ox;
		ny = oy;
		if (fcn_005ea2d0(map, (float*) (obj + 0x30), pf, ox, oy, &nx, &ny) != 0 && *(unsigned int*) (obj + 0x64) > 0x32) {
			*(float*) (obj + 0x30) = pf[0];
			*(float*) (obj + 0x34) = pf[1];
			*(float*) (obj + 0x38) = pf[2];
			*(int*) (obj + 0x5c) = 2;
			*(float*) (obj + 0x58) =
				(*(float*)(obj + 0x18) * *(float*)(obj + 0x18) + *(float*)(obj + 0x14) * *(float*)(obj + 0x14) + *(float*)(obj + 0x10) * *(float*)(obj + 0x10)) * *(float*) (obj + 0x54) * g_6628cc;
			return 0;
		}
		*(float*) (obj + 0x30) = pf[0];
		*(float*) (obj + 0x34) = pf[1];
		*(float*) (obj + 0x38) = pf[2];
		ox = nx;
		oy = ny;
		n++;
	}
	return 1;
}
