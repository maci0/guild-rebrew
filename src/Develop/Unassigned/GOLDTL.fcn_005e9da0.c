extern float g_6ad620;
extern float g_6660f0;
extern float g_6660e8;
extern int g_1043370;
extern int g_6b7fac;

int __cdecl fcn_0045b990(int, float*, int*, int*, float*);
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
int __cdecl fcn_005e9da0(char* obj, float* pos)
{
	float step;
	float inv;
	float fx;
	float fy;
	float fz;
	float qx;
	float qy;
	float qz;
	float mx;
	float my;
	float mz;
	float rx;
	float ry;
	float rz;
	float tx;
	float ty;
	float tz;
	float sx;
	float sy;
	float sz;
	float pf[3];
	float h;
	int remain;
	int n;
	int ox;
	int oy;
	int nx;
	int ny;

	(void) pos;
	step = g_6660f0 * g_6660e8;
	inv = g_6660f0 / *(float*) (obj + 0x54);
	if (*(int*) (obj + 0x5c) != 1) {
		return 0;
	}
	remain = g_6b7fac - *(int*) (obj + 0x60);
	if (fcn_0045b990(g_1043370, (float*) (obj + 0x30), &ox, &oy, &h) == 0) {
		*(int*) (obj + 0x5c) = 3;
		*(int*) (obj + 0x58) = 0;
		return 0;
	}
	fx = (float) (*(float*) (obj + 0x40) > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * *(float*) (obj + 0x40) * *(float*) (obj + 0x40) * g_6ad620 * 1.2f * 0.5f;
	fy = (float) (*(float*) (obj + 0x44) > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * *(float*) (obj + 0x44) * *(float*) (obj + 0x44) * g_6ad620 * 1.2f * 0.5f;
	fz = (float) (*(float*) (obj + 0x48) > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * *(float*) (obj + 0x48) * *(float*) (obj + 0x48) * g_6ad620 * 1.2f * 0.5f;
	n = 0;
	while (n < remain) {
		float vx = *(float*) (obj + 0x10);
		float vy = *(float*) (obj + 0x14);
		float vz = *(float*) (obj + 0x18);
		float wx = *(float*) (obj + 0x30);
		float wy = *(float*) (obj + 0x34);
		float wz = *(float*) (obj + 0x38);

		sx = vx > 0.0f ? 1.0f : -1.0f;
		sy = vy > 0.0f ? 1.0f : -1.0f;
		sz = vz > 0.0f ? 1.0f : -1.0f;
		qx = sx * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * vx * vx * 0.5f;
		qy = sy * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * vy * vy * 0.5f;
		qz = sz * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * vz * vz * 0.5f;
		mx = (qx + fx) * inv;
		my = (qy + fy) * inv - step;
		mz = (qz + fz) * inv;
		mx = mx + vx;
		my = my + vy;
		mz = mz + vz;
		sx = mx > 0.0f ? 1.0f : -1.0f;
		sy = my > 0.0f ? 1.0f : -1.0f;
		sz = mz > 0.0f ? 1.0f : -1.0f;
		rx = sx * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * mx * mx * 0.5f;
		ry = sy * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * my * my * 0.5f;
		rz = sz * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * mz * mz * 0.5f;
		tx = (rx + fx) * inv;
		ty = (ry + fy) * inv - step;
		tz = (rz + fz) * inv;
		*(int*) (obj + 0x60) += 1;
		*(int*) (obj + 0x64) += 1;
		vx = tx * 0.5f + vx;
		vy = ty * 0.5f + vy;
		vz = tz * 0.5f + vz;
		*(float*) (obj + 0x10) = vx;
		*(float*) (obj + 0x14) = vy;
		*(float*) (obj + 0x18) = vz;
		pf[0] = vx * 39.37008f * g_6660f0 + wx;
		pf[1] = vy * 39.37008f * g_6660f0 + wy;
		pf[2] = vz * 39.37008f * g_6660f0 + wz;
		nx = ox;
		ny = oy;
		if (fcn_005ea2d0(g_1043370, (float*) (obj + 0x30), pf, ox, oy, &nx, &ny) != 0 && *(unsigned int*) (obj + 0x64) > 0x32) {
			*(float*) (obj + 0x30) = pf[0];
			*(float*) (obj + 0x34) = pf[1];
			*(float*) (obj + 0x38) = pf[2];
			*(int*) (obj + 0x5c) = 2;
			*(float*) (obj + 0x58) =
				(vx * vx + vy * vy + vz * vz) * *(float*) (obj + 0x54) * 0.5f;
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
