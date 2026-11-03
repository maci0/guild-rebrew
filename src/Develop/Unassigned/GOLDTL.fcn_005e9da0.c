extern float g_6ad620;
extern float g_6660f0;
extern float g_6660e8;
extern int g_1043370;
extern int g_6b7fac;

char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
int __cdecl fcn_005ea2d0(int, float*, int*, int, int, int*, int*);


/* One projectile integration step for obj: accumulated X/Y/Z forces plus
 * gravity, position step, then the collision state (1 flying, 2 impact,
 * 3 expired). Partial body: all three branches are present, the exact force
 * expression below is reconstructed from the pdg and still needs a byte-level
 * review. */
/* ADDRESS: GOLDTL 0x005e9da0 */
int __cdecl fcn_005e9da0(char* obj, float* pos)
{
	float step;
	float inv;
	float fx;
	float fy;
	float fz;
	float ax;
	float ay;
	float az;
	float dtx;
	float dty;
	float dtz;
	int remain;
	int hit;
	int px;
	int py;
	int pz;
	int oldx;
	int oldy;
	int n;

	step = g_6660f0 * g_6660e8;
	inv = g_6660f0 / *(float*) (obj + 0x54);
	if (*(int*) (obj + 0x5c) != 1) {
		return 0;
	}
	remain = g_6b7fac - *(int*) (obj + 0x60);
	hit = fcn_0045b990(g_1043370, (float*) (obj + 0x30), &px, &py, &n);
	if (hit == 0) {
		*(int*) (obj + 0x5c) = 3;
		*(int*) (obj + 0x58) = 0;
		return 0;
	}
	if (*(float*) (obj + 0x40) > 0.0f) {
		fx = 1.0f;
	} else {
		fx = -1.0f;
	}
	fy = *(float*) (obj + 0x50) * *(float*) (obj + 0x40) * *(float*) (obj + 0x40) * fx * g_6ad620 * 1.2f * 0.5f;
	if (*(float*) (obj + 0x44) > 0.0f) {
		fx = 1.0f;
	} else {
		fx = -1.0f;
	}
	fz = fx * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * *(float*) (obj + 0x44) * *(float*) (obj + 0x44) * 0.5f;
	if (*(float*) (obj + 0x48) > 0.0f) {
		fx = 1.0f;
	} else {
		fx = -1.0f;
	}
	ax = *(float*) (obj + 0x50) * *(float*) (obj + 0x48) * *(float*) (obj + 0x48) * fx * g_6ad620 * 1.2f * 0.5f;
	n = 0;
	while (n < remain) {
		float vx = *(float*) (obj + 0x10);
		float vy = *(float*) (obj + 0x14);
		float vz = *(float*) (obj + 0x18);
		float sx;
		float sy;
		float sz;
		float nx;
		float ny;
		float nz;

		sx = vx > 0.0f ? 1.0f : -1.0f;
		sy = vy > 0.0f ? 1.0f : -1.0f;
		sz = vz > 0.0f ? 1.0f : -1.0f;
		dtx = sy * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * vy * vy * 0.5f + fz;
		dty = (sx * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * vx * vx * 0.5f + fy) * inv;
		dtz = (sz * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * vz * vz * 0.5f + ax) * inv;
		nx = dty + vx;
		ny = dtx * inv - step + vy;
		nz = dtz + vz;
		sx = nx > 0.0f ? 1.0f : -1.0f;
		sy = ny > 0.0f ? 1.0f : -1.0f;
		sz = nz > 0.0f ? 1.0f : -1.0f;
		dtx = sx * *(float*) (obj + 0x50) * g_6ad620 * 1.2f * nx * nx * 0.5f;
		sy = sy * *(float*) (obj + 0x50) * g_6ad620;
		sz = sz * *(float*) (obj + 0x50) * g_6ad620;
		*(int*) (obj + 0x60) += 1;
		*(int*) (obj + 100) += 1;
		ay = sy * 1.2f * ny * ny * 0.5f + fz;
		az = (sz * 1.2f * nz * nz * 0.5f + ax) * inv;
		vx = ((dtx + fy) * inv + dty) * 0.5f + *(float*) (obj + 0x10);
		*(float*) (obj + 0x10) = vx;
		vy = ((ay * inv - step) + dtx) * 0.5f + *(float*) (obj + 0x14);
		*(float*) (obj + 0x14) = vy;
		vz = (az + dtz) * 0.5f + *(float*) (obj + 0x18);
		*(float*) (obj + 0x18) = vz;
		px = (int) (vx * 39.37008f * 0.006756757f + *pos);
		py = (int) (vy * 39.37008f * 0.006756757f + *(float*) (obj + 0x34));
		pz = (int) (vz * 39.37008f * 0.006756757f + *(float*) (obj + 0x38));
		hit = fcn_005ea2d0(g_1043370, pos, &n, px, py, &oldx, &oldy);
		if (hit != 0 && *(unsigned int*) (obj + 100) > 0x32) {
			*pos = (float) n;
			*(int*) (obj + 0x5c) = 2;
			*(int*) (obj + 0x34) = py;
			*(int*) (obj + 0x38) = pz;
			*(float*) (obj + 0x58) =
				(*(float*) (obj + 0x10) * *(float*) (obj + 0x10) +
				 *(float*) (obj + 0x14) * *(float*) (obj + 0x14) +
				 *(float*) (obj + 0x18) * *(float*) (obj + 0x18)) * *(float*) (obj + 0x54) * 0.5f;
			return 0;
		}
		*(int*) (obj + 0x34) = py;
		*(int*) (obj + 0x38) = pz;
		n++;
		*pos = (float) n;
	}
	return 1;
}
