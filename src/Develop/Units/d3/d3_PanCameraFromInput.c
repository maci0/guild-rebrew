extern const float d3_UnitAxisVectors[3];
extern unsigned short d2_CursorStateId;
extern short io_ActiveCursorY;
extern short io_ActiveCursorX;
extern int d2_InteriorBuilding;
extern int d2_VisitedBuilding;
extern int d3_ActiveCamera;
extern volatile int gm_GameTicks;
extern int d3_ActiveCameraAnimation;
extern int d3_CameraAnimating;
extern int d2_MouseTopBoundary;
extern int g_6b5c80;
extern int d3_ActiveScene;
extern int d2_MouseBottomBoundary;
extern int d2_MouseRightBoundary;
extern float d3_CameraHeightFraction;
extern char g_14cf7d0;
extern char g_14cf7cd;
extern char g_14cf7cb;
extern char g_14cf7c8;
#include <math.h>

float* __stdcall D3DXMatrixTranspose(float* out, const float* in);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
float __cdecl d3_WrapYawDelta(int a, int b);
void __cdecl d3_SetNodePosition(char* p, int* v);

/* ADDRESS: GOLDTL 0x0052b720 */
/* ADDRESS: GOLDDE 0x00514440 */
int __cdecl d3_PanCameraFromInput(void)
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

	mode = d2_CursorStateId;
	skipx = 0;
	ret = 0;
	if (mode >= 1 && mode <= 8) {
		d2_CursorStateId = 0;
	}
	if (d3_ActiveCameraAnimation != 0 || d3_CameraAnimating != 0) {
		return 0;
	}
	if (*(int*) 0x774750 != 0) {
		f = (double) (unsigned int) (gm_GameTicks - *(int*) 0x774750) * 0.4;
	} else {
		f = 1.0f;
	}
	if (!(f < 4.0)) {
		f = 4.0;
	}
	step = (float) (f * 5.0);
	pos = io_ActiveCursorX;
	*(int*) 0x774750 = gm_GameTicks;
	typ = io_ActiveCursorY;
	if ((typ == d2_MouseTopBoundary
	    && pos < g_6b5c80 + 0x40)
	    || (typ < d2_MouseTopBoundary + 0x40
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
		d2_CursorStateId = 5;
		goto done;
	}
	if ((typ == d2_MouseTopBoundary
	    && pos > d2_MouseRightBoundary - 0x40)
	    || (typ < d2_MouseTopBoundary + 0x40
	    && pos == d2_MouseRightBoundary)) {
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
		d2_CursorStateId = 6;
		goto done;
	}
	if ((typ == d2_MouseBottomBoundary
	    && pos > d2_MouseRightBoundary - 0x40)
	    || (typ > d2_MouseBottomBoundary - 0x40
	    && pos == d2_MouseRightBoundary)) {
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
		d2_CursorStateId = 8;
		goto done;
	}
	if ((typ == d2_MouseBottomBoundary
	    && pos < g_6b5c80 + 0x40)
	    || (typ > d2_MouseBottomBoundary - 0x40
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
		d2_CursorStateId = 7;
		goto done;
	}
	if (pos == g_6b5c80 || g_14cf7cb != 0) {
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = -10.0f;
		}
		if (*(float*) 0x774744 > -50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 - step;
		}
		d2_CursorStateId = 4;
		goto xdamp;
	}
	if (pos == d2_MouseRightBoundary || g_14cf7cd != 0) {
		if (*(float*) 0x774744 == 0.0f) {
			*(float*) 0x774744 = 10.0f;
		}
		if (*(float*) 0x774744 < 50.0) {
			*(float*) 0x774744 = *(float*) 0x774744 + step;
		}
		d2_CursorStateId = 3;
		goto xdamp;
	}
	if (typ == d2_MouseBottomBoundary || g_14cf7d0 != 0) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = -10.0f;
		}
		if (*(float*) 0x77474c > -50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c - step;
		}
		skipx = 1;
		d2_CursorStateId = 1;
	} else if (typ == d2_MouseTopBoundary || g_14cf7c8 != 0) {
		if (*(float*) 0x77474c == 0.0f) {
			*(float*) 0x77474c = 10.0f;
		}
		if (*(float*) 0x77474c < 50.0) {
			*(float*) 0x77474c = *(float*) 0x77474c + step;
		}
		skipx = 1;
		d2_CursorStateId = 2;
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
	if (d3_ActiveCamera == 0) {
		goto end;
	}
	if (*(float*) 0x774744 == 0.0f && *(float*) 0x77474c == 0.0f) {
		goto end;
	}
	if (d2_InteriorBuilding != 0) {
		f = f * 0.5;
	} else if (d2_VisitedBuilding != 0) {
		f = f * 0.25;
	}
	step = (float) (*(float*) 0x6a2570 * f
	    * (d3_CameraHeightFraction * 1.5 + 0.6));
	D3DXMatrixTranspose(mat, (float*) ((char*) d3_ActiveCamera + 0x18c));
	d[0] = *(float*) 0x774744 * step * 1.1;
	d[1] = *(float*) 0x77474c * step * 1.1;
	q[0] = mat[8] * d3_UnitAxisVectors[2]
	    + mat[4] * d3_UnitAxisVectors[1]
	    + mat[0] * d3_UnitAxisVectors[0];
	q[2] = mat[10] * d3_UnitAxisVectors[2]
	    + mat[6] * d3_UnitAxisVectors[1]
	    + mat[2] * d3_UnitAxisVectors[0];
	if (sqrt((double) (q[0] * q[0] + q[2] * q[2])) < 0.1f) {
		v[1] = d[1];
		v[2] = 0.0f;
		q[0] = mat[0] * d[0] + mat[4] * v[1] + mat[8] * v[2];
		q[2] = mat[2] * d[0] + mat[6] * v[1] + mat[10] * v[2];
	} else {
		step = d3_WrapYawDelta((int) d3_UnitAxisVectors, (int) &q[0]);
		v[1] = 0.0f;
		v[2] = d[1];
		q[0] = d[0] * cos(-step) + d[1] * sin(-step);
		q[2] = d[1] * cos(-step) - d[0] * sin(-step);
	}
	q[1] = 0.0f;
	v[0] = *(float*) (d3_ActiveCamera + 0x4c) + q[0];
	v[1] = *(float*) (d3_ActiveCamera + 0x50);
	v[2] = *(float*) (d3_ActiveCamera + 0x54) + q[2];
	if (CompareVector3WithinTolerance((float*) 0x773e24, v, 0.1f) == 0) {
		char* obj;
		float t;
		int n;

		obj = (char*) d3_ActiveScene;
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
		d3_SetNodePosition((char*) d3_ActiveCamera, (int*) v);
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
