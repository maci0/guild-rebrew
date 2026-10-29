#include <math.h>

void __cdecl fcn_005ebbb9(float* out, int src, float scale);
int __cdecl fcn_00451840(int a, float* p, float b);
int __cdecl fcn_004514d0(float* a, float* b);
void __cdecl fcn_00438b40(int a, int b);

/* ADDRESS: GOLDTL 0x0052b720 */
int __cdecl fcn_0052b720(void)
{
	unsigned short mode;
	int pos;
	int typ;
	int ret;
	double f;
	float step;
	float* vx;
	float* vy;
	float mat[16];
	float ax;
	float ay;
	float px;
	float py;
	float pz;
	float dist;
	float ang;
	float a;
	float b;

	ret = 0;
	mode = *(unsigned short*) 0x7725c4;
	if (mode >= 1 && mode <= 8) {
		*(unsigned short*) 0x7725c4 = 0;
	}
	if (*(int*) 0x6b5cc0 != 0 || *(int*) 0x6b5cbc != 0) {
		return 0;
	}
	if (*(int*) 0x774750 != 0) {
		f = (double) (*(int*) 0x6b7fac - *(int*) 0x774750) * 0.4;
	} else {
		f = 1.0;
	}
	if (f < 4.0) {
		f = 4.0;
	}
	*(int*) 0x774750 = *(int*) 0x6b7fac;
	step = (float) (f * 5.0);
	typ = (int) *(short*) 0x14ce8c2;
	pos = (int) *(short*) 0x14ce8c0;
	vx = (float*) 0x77474c;
	vy = (float*) 0x774744;
	if ((typ == *(int*) 0x6b5c84
	    && pos < *(int*) 0x6b5c80 + 0x40)
	    || (typ < *(int*) 0x6b5c84 + 0x40
	    && pos == *(int*) 0x6b5c80)) {
		if (*vx == 0.0f) {
			*vx = 10.0f;
		}
		if (*vx < 50.0) {
			*vx = *vx + step;
		}
		if (*vy == 0.0f) {
			*vy = -10.0f;
		}
		if (*vy > -50.0) {
			*vy = *vy - step;
		}
		*(unsigned short*) 0x7725c4 = 5;
		goto done;
	}
	if ((typ == *(int*) 0x6b5c84
	    && pos > *(int*) 0x6772bc - 0x40)
	    || (typ < *(int*) 0x6b5c84 + 0x40
	    && pos == *(int*) 0x6772bc)) {
		if (*vx == 0.0f) {
			*vx = 10.0f;
		}
		if (*vx < 50.0) {
			*vx = *vx + step;
		}
		if (*vy == 0.0f) {
			*vy = 10.0f;
		}
		if (*vy < 50.0) {
			*vy = *vy + step;
		}
		*(unsigned short*) 0x7725c4 = 6;
		goto done;
	}
	if ((typ == *(int*) 0x6772c0
	    && pos > *(int*) 0x6772bc - 0x40)
	    || (typ > *(int*) 0x6772c0 - 0x40
	    && pos == *(int*) 0x6772bc)) {
		if (*vx == 0.0f) {
			*vx = -10.0f;
		}
		if (*vx > -50.0) {
			*vx = *vx - step;
		}
		if (*vy == 0.0f) {
			*vy = 10.0f;
		}
		if (*vy < 50.0) {
			*vy = *vy + step;
		}
		*(unsigned short*) 0x7725c4 = 8;
		goto done;
	}
	if ((typ == *(int*) 0x6772c0
	    && pos < *(int*) 0x6b5c80 + 0x40)
	    || (typ > *(int*) 0x6772c0 - 0x40
	    && pos == *(int*) 0x6b5c80)) {
		if (*vx == 0.0f) {
			*vx = -10.0f;
		}
		if (*vx > -50.0) {
			*vx = *vx - step;
		}
		if (*vy == 0.0f) {
			*vy = -10.0f;
		}
		if (*vy > -50.0) {
			*vy = *vy - step;
		}
		*(unsigned short*) 0x7725c4 = 7;
		goto done;
	}
	if (pos == *(int*) 0x6b5c80 || *(char*) 0x14cf7cb != 0) {
		if (*vy == 0.0f) {
			*vy = -10.0f;
		}
		if (*vy > -50.0) {
			*vy = *vy - step;
		}
		*(unsigned short*) 0x7725c4 = 4;
		goto done;
	}
	if (pos == *(int*) 0x6772bc || *(char*) 0x14cf7cd != 0) {
		if (*vy == 0.0f) {
			*vy = 10.0f;
		}
		if (*vy < 50.0) {
			*vy = *vy + step;
		}
		*(unsigned short*) 0x7725c4 = 3;
		goto done;
	}
	if (typ == *(int*) 0x6772c0 || *(char*) 0x14cf7d0 != 0) {
		if (*vx == 0.0f) {
			*vx = -10.0f;
		}
		if (*vx > -50.0) {
			*vx = *vx - step;
		}
		*(unsigned short*) 0x7725c4 = 1;
	} else if (typ == *(int*) 0x6b5c84 || *(char*) 0x14cf7c8 != 0) {
		if (*vx == 0.0f) {
			*vx = 10.0f;
		}
		if (*vx < 50.0) {
			*vx = *vx + step;
		}
		*(unsigned short*) 0x7725c4 = 2;
	}
	if (*vy <= 0.0f) {
		if (*vy < 0.0f) {
			*vy = *vy + step;
			if (*vy > 0.0f) {
				*vy = 0.0f;
			}
		}
	} else {
		*vy = *vy - step;
		if (*vy < 0.0f) {
			*vy = 0.0f;
		}
	}
	if (*(unsigned short*) 0x7725c4 != 0
	    && *(unsigned short*) 0x7725c4 <= 2) {
		goto done;
	}
	if (*vx <= 0.0f) {
		if (*vx < 0.0f) {
			*vx = *vx + step;
			if (*vx > 0.0f) {
				*vx = 0.0f;
			}
		}
	} else {
		*vx = *vx - step;
		if (*vx < 0.0f) {
			*vx = 0.0f;
		}
	}
done:
	if (*(int*) 0x6b8014 != 0
	    && (*vy == 0.0f || *vx == 0.0f)) {
		if (*(int*) 0x7746c8 != 0) {
			f = f * 0.5;
		} else if (*(int*) 0x7746c4 != 0) {
			f = f * 0.25;
		}
		fcn_005ebbb9(mat, *(int*) 0x6b8014 + 0x18c,
		    *(float*) 0x6a2570 * (float) f
		    * (*(float*) 0x774690 * 1.5 + 0.6));
		ax = *vy * mat[0] * 1.1f;
		ay = *vx * mat[0] * 1.1f;
		px = mat[8] * 0.0f + mat[4] * 0.0f + mat[0] * 1.0f;
		pz = mat[9] * 0.0f + mat[5] * 0.0f + mat[1] * 1.0f;
		dist = (float) sqrt((double) (px * px + pz * pz));
		if (dist < 0.1f) {
			ang = fcn_004514d0((float*) 0x662d40, &dist);
			a = (float) sin(-ang);
			b = (float) cos(-ang);
			ax = ay * b + ax * a;
			ay = ay * b - ax * a;
		} else {
			ax = mat[0] * 0.0f + mat[4] * ax + mat[8] * ay;
			ay = mat[1] * 0.0f + mat[5] * ax + mat[9] * ay;
		}
		px = ax + *(float*) (*(int*) 0x6b8014 + 0x4c);
		py = *(float*) (*(int*) 0x6b8014 + 0x50);
		pz = ay + *(float*) (*(int*) 0x6b8014 + 0x54);
		if (fcn_00451840(0x773e24, &px, 0.1f) == 0) {
			fcn_00438b40(*(int*) 0x6b8014, (int) &pz);
			py = 1.0f;
		}
		*(float*) 0x773e24 = pz;
		*(float*) 0x773e28 = 0.0f;
		*(float*) 0x773e2c = ax;
	}
	*(float*) 0x774748 = *vy;
	*(float*) 0x773df4 = *vx;
	(void) mode;
	(void) mat;
	return ret;
}
