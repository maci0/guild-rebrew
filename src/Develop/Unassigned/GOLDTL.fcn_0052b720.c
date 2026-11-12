extern unsigned short g_7725c4;
extern short g_14ce8c2;
extern short g_14ce8c0;
extern int g_7746c8;
extern int g_7746c4;
extern int g_6b8014;
extern int g_6b7fac;
extern int g_6b5cc0;
extern int g_6b5cbc;
extern int g_6b5c84;
extern int g_6b5c80;
extern int g_67a370;
extern int g_6772c0;
extern int g_6772bc;
extern float g_774690;
extern char g_14cf7d0;
extern char g_14cf7cd;
extern char g_14cf7cb;
extern char g_14cf7c8;
#include <math.h>

float* __stdcall fcn_005ebbb9(float* out, const float* in);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
float __cdecl fcn_004514d0(int a, int b);
void __cdecl fcn_00438b40(char* p, int* v);

/* ADDRESS: GOLDTL 0x0052b720 */
int __cdecl fcn_0052b720(void)
{
	unsigned short mode;
	short pos;
	short typ;
	int ret;
	int skipx;
	double f;
	float step;
	float v[4];
	float q[4];
	float d[4];
	float mat[16];

	mode = g_7725c4;
	skipx = 0;
	ret = 0;
	if (mode >= 1 && mode <= 8) {
		g_7725c4 = 0;
	}
	if (g_6b5cc0 != 0 || g_6b5cbc != 0) {
		return 0;
	}
	if (*(int*) 0x774750 != 0) {
		f = (double) (unsigned int) (g_6b7fac - *(int*) 0x774750) * 0.4;
	} else {
		f = 1.0f;
	}
	if (!(f < 4.0)) {
		f = 4.0;
	}
	*(int*) 0x774750 = g_6b7fac;
	step = (float) (f * 5.0);
	pos = g_14ce8c0;
	typ = g_14ce8c2;
	if ((typ == g_6b5c84
	    && pos < g_6b5c80 + 0x40)
	    || (typ < g_6b5c84 + 0x40
	    && pos == g_6b5c80)) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = 10.0f;
		}
		if (*(float*) 0x77474c < 50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c + step;
		}
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = -10.0f;
		}
		if (*(float*) 0x774744 > -50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 - step;
		}
		g_7725c4 = 5;
		goto done;
	}
	if ((typ == g_6b5c84
	    && pos > g_6772bc - 0x40)
	    || (typ < g_6b5c84 + 0x40
	    && pos == g_6772bc)) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = 10.0f;
		}
		if (*(float*) 0x77474c < 50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c + step;
		}
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = 10.0f;
		}
		if (*(float*) 0x774744 < 50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 + step;
		}
		g_7725c4 = 6;
		goto done;
	}
	if ((typ == g_6772c0
	    && pos > g_6772bc - 0x40)
	    || (typ > g_6772c0 - 0x40
	    && pos == g_6772bc)) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = -10.0f;
		}
		if (*(float*) 0x77474c > -50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c - step;
		}
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = 10.0f;
		}
		if (*(float*) 0x774744 < 50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 + step;
		}
		g_7725c4 = 8;
		goto done;
	}
	if ((typ == g_6772c0
	    && pos < g_6b5c80 + 0x40)
	    || (typ > g_6772c0 - 0x40
	    && pos == g_6b5c80)) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = -10.0f;
		}
		if (*(float*) 0x77474c > -50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c - step;
		}
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = -10.0f;
		}
		if (*(float*) 0x774744 > -50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 - step;
		}
		g_7725c4 = 7;
		goto done;
	}
	if (pos == g_6b5c80 || g_14cf7cb != 0) {
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = -10.0f;
		}
		if (*(float*) 0x774744 > -50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 - step;
		}
		g_7725c4 = 4;
		goto xdamp;
	}
	if (pos == g_6772bc || g_14cf7cd != 0) {
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = 10.0f;
		}
		if (*(float*) 0x774744 < 50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 + step;
		}
		g_7725c4 = 3;
		goto xdamp;
	}
	if (typ == g_6772c0 || g_14cf7d0 != 0) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = -10.0f;
		}
		if (*(float*) 0x77474c > -50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c - step;
		}
		skipx = 1;
		g_7725c4 = 1;
	} else if (typ == g_6b5c84 || g_14cf7c8 != 0) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = 10.0f;
		}
		if (*(float*) 0x77474c < 50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c + step;
		}
		skipx = 1;
		g_7725c4 = 2;
	}
	if (*(float*) 0x774744 > 0.0f) {
		*(float*) 0x774744 = *(float*) 0x774744 - step;
		if (*(float*) 0x774744 < 0.0f) {
			*(float*) 0x774744 = 0.0f;
		}
	} else if (*(float*) 0x774744 < 0.0f) {
		*(float*) 0x774744 = *(float*) 0x774744 + step;
		if (*(float*) 0x774744 > 0.0f) {
			*(float*) 0x774744 = 0.0f;
		}
	}
	if (skipx) {
		goto done;
	}
xdamp:
	if (*(float*) 0x77474c > 0.0f) {
		*(float*) 0x77474c = *(float*) 0x77474c - step;
		if (*(float*) 0x77474c < 0.0f) {
			*(float*) 0x77474c = 0.0f;
		}
	} else if (*(float*) 0x77474c < 0.0f) {
		*(float*) 0x77474c = *(float*) 0x77474c + step;
		if (*(float*) 0x77474c > 0.0f) {
			*(float*) 0x77474c = 0.0f;
		}
	}
done:
	if (g_6b8014 == 0) {
		goto end;
	}
	if (*(float*) 0x774744 == 0.0f && *(float*) 0x77474c == 0.0f) {
		goto end;
	}
	if (g_7746c8 != 0) {
		f = f * 0.5;
	} else if (g_7746c4 != 0) {
		f = f * 0.25;
	}
	step = (float) (*(float*) 0x6a2570 * f
	    * (g_774690 * 1.5 + 0.6));
	fcn_005ebbb9(mat, (float*) ((char*) g_6b8014 + 0x18c));
	d[0] = *(float*) 0x774744 * step * 1.1;
	d[1] = *(float*) 0x77474c * step * 1.1;
	q[0] = mat[8] * *(float*) 0x662d48
	    + mat[4] * *(float*) 0x662d44
	    + mat[0] * *(float*) 0x662d40;
	q[2] = mat[10] * *(float*) 0x662d48
	    + mat[6] * *(float*) 0x662d44
	    + mat[2] * *(float*) 0x662d40;
	if (sqrt((double) (q[0] * q[0] + q[2] * q[2])) < 0.1f) {
		v[1] = d[1];
		v[2] = 0.0f;
		q[0] = mat[0] * d[0] + mat[4] * v[1] + mat[8] * v[2];
		q[2] = mat[2] * d[0] + mat[6] * v[1] + mat[10] * v[2];
	} else {
		step = fcn_004514d0(0x662d40, (int) &q[0]);
		v[1] = 0.0f;
		v[2] = d[1];
		q[0] = d[0] * cos(-step) + d[1] * sin(-step);
		q[2] = d[1] * cos(-step) - d[0] * sin(-step);
	}
	q[1] = 0.0f;
	v[0] = *(float*) (g_6b8014 + 0x4c) + q[0];
	v[1] = *(float*) (g_6b8014 + 0x50);
	v[2] = *(float*) (g_6b8014 + 0x54) + q[2];
	if (CompareVector3WithinTolerance((float*) 0x773e24, v, 0.1f) == 0) {
		char* obj;
		float t;
		int n;

		obj = (char*) g_67a370;
		if (*(int*) (obj + 0xb0) != 0) {
			obj = (char*) *(int*) (obj + 0xb0);
			t = *(float*) obj + *(float*) (obj + 0x10) * 20.0f;
			if (v[0] < t) {
				v[0] = t;
			} else {
				n = *(int*) (obj + 0x20) - 20;
				t = *(float*) obj + (float) n * *(float*) (obj + 0x10);
				if (v[0] > t) {
					v[0] = t;
				}
			}
			t = *(float*) (obj + 8) + *(float*) (obj + 0x18) * 20.0f;
			n = *(int*) (obj + 0x20) - 20;
			t = *(float*) (obj + 8) + (float) n * *(float*) (obj + 0x18);
			if (!(v[2] > t)) {
				v[2] = t;
			}
			t = *(float*) (obj + 8) + *(float*) (obj + 0x18) * 20.0f;
			if (!(v[2] < t)) {
				v[2] = t;
			}
		}
		fcn_00438b40((char*) g_6b8014, (int*) v);
		ret = 1;
	}
	*(float*) 0x773e24 = q[0];
	*(float*) 0x773e28 = q[1];
	*(float*) 0x773e2c = q[2];
end:
	*(float*) 0x774748 = *(float*) 0x774744;
	*(float*) 0x773df4 = *(float*) 0x77474c;
	return ret;
}
