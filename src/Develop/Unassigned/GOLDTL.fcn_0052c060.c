#include <math.h>

/* SIZE 0xc */
typedef struct {
	float x;
	float y;
	float z;
} Vec3;

/* SIZE 0x10 */
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

/* SIZE 0x90 */
typedef struct View {
	char pad0[0x4c];
	Vec3 pos;
	char pad58[0x84 - 0x58];
	Vec3 rot;
	char pad90[0x18c - 0x90];
	float mat[16];
} View;

/* SIZE 0x21c */
typedef struct {
	char pad0[0x21c];
} Entity;

extern int g_6b5cbc;
extern int g_14ce8e8;
extern int g_774774;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_6772bc;
extern int g_6772c0;
extern int g_6772c4;
extern int g_774754;
extern int g_773e38;
extern int g_774758;
extern int g_773df8;
extern int g_773e00;
extern int g_773df0;
extern int g_773e34;
extern int g_77464c;
extern int g_6b8014;
extern short g_14cf900;
extern short g_14cf902;
extern int g_14ce8d0;
extern int g_14ce900;
extern int g_14ce904;
extern int g_77475c;
extern int g_774760;
extern int g_774644;
extern int g_773e3c;
extern int g_7766b4;
extern float g_774690;
extern float g_774764;
extern float g_774694;
extern float g_774770;
extern float g_774768;
extern float g_77476c;
extern float g_6a2558;
extern float g_6a255c;
extern float g_6a2560;
extern float g_6a2564;
extern float g_662d40[3];
extern float g_6628a8;
extern float g_662a3c;
extern float g_662a98;
extern float g_66430c;
extern double g_665df8;
extern double g_665e08;
extern double g_6629c8;
extern double g_662950;
extern float g_665e00;
extern float g_665e04;
extern float g_665e10;
extern char* g_67a370;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern float g_773e14;
extern float g_773e18;
extern float g_773e1c;

void __cdecl fcn_004125c0(int, int);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl fcn_00438b40(void*, void*);
void __cdecl fcn_00438cb0(void*, void*);
char* __cdecl fcn_00509570(void*);
void __cdecl fcn_0052ac60(float);
float* __stdcall fcn_005ebbb9(float*, const float*);
float __cdecl fcn_004514d0(float*, float*);

/* ADDRESS: GOLDTL 0x0052c060 */
int __cdecl fcn_0052c060(void)
{
	Vec4 v;
	Vec4 q;
	Vec4 d;
	Vec3 rot;
	Vec4 pos;
	float mat[16];
	int dt;
	int n;
	int ret;
	float f;
	float ang;
	float t;
	float t2;
	short s902;
	char* ent;
	View* cam;

	if (g_6b5cbc != 0) {
		return 0;
	}
	cam = (View*) g_6b8014;
	s902 = g_14cf902;
	if (g_14ce8e8 != 0) {
		if (g_774774 == 0) {
			g_774754 = (int) g_14ce8c0;
			g_773e38 = (int) g_14ce8c0;
			g_774758 = (int) g_14ce8c2;
			g_773df8 = (int) g_14ce8c2;
			g_773e00 = g_6772bc;
			g_773df0 = g_6772c0;
			g_773e34 = g_6b5c80;
			g_77464c = g_6b5c84;
			g_774774 = 1;
			g_6772c4 = 0;
			g_6772bc = 0x7d00;
			g_6772c0 = 0x7d00;
			g_6b5c80 = -0x7d00;
			g_6b5c84 = -0x7d00;
		}
		if (g_14ce8d0 == 0) {
			goto L4;
		}
		if (g_77475c == 0) {
			g_77475c = 1;
			g_774764 = g_774690;
			g_774644 = (int) g_14cf900;
			g_773e3c = (int) s902;
			g_774768 = g_774694;
			g_774770 = cam->pos.y - ((g_6a2560 - g_6a2558) * g_774764 + g_6a255c);
			g_6772c0 = g_773e3c - (int) ((1.0 - g_774768) * g_665e10);
			g_6b5c84 = g_773e3c - (int) (-g_774768 * g_665e10);
			g_77476c = cam->rot.y;
		}
	}
L2:
	if (g_14ce8d0 != 0 && g_14ce8e8 != 0) {
		goto main;
	}
L4:
	if (g_77475c != 0) {
		g_77475c = 0;
		g_773df8 = (int) s902;
		n = g_773df8 - g_773e3c;
		g_6772bc = 0x7d00;
		g_6772c0 = 0x7d00;
		g_774764 = g_774764 + n * 0.004;
		g_773e38 = (int) g_14cf900;
		g_6b5c80 = -0x7d00;
		g_6b5c84 = -0x7d00;
	}
	if (g_14ce8e8 != 0) {
		goto main;
	}
	if (g_774774 != 0) {
		g_6772c0 = g_773df0;
		g_6b5c80 = g_773e34;
		g_6772bc = g_773e00;
		g_6b5c84 = g_77464c;
		g_6772c4 = 1;
		g_774774 = 0;
		fcn_004125c0(g_774754, g_774758);
		g_774754 = 0;
		g_774758 = 0;
		return 0;
	}

main:
	if (cam == 0) {
		goto tail;
	}
	if (g_14ce8e8 == 0) {
		goto afterFirst;
	}
	if (g_14ce8d0 == 0) {
		goto afterFirst;
	}
	if (g_77475c == 0) {
		goto afterFirst;
	}
	dt = g_14ce904 - g_14ce900;
	f = (float) dt * g_662a98;
	f = f + s902;
	f = f - g_773e3c;
	f = f * g_665e04;
	g_774690 = g_774764 + f;
	pos.x = cam->pos.x;
	pos.y = cam->pos.y;
	pos.z = cam->pos.z;
	pos.y = (g_6a2560 - g_6a2558) * g_774690 + g_774770;
	g_774694 = g_774768 + f;
	rot.x = cam->rot.x;
	rot.y = cam->rot.y;
	rot.z = cam->rot.z;
	rot.x = (g_6a2564 - g_6a255c) * g_774694 + g_6a255c;
	rot.y = g_77476c - ((int) g_14cf900 - g_774644) * g_665e00;
	if (CompareVector3WithinTolerance((float*) &cam->pos, (float*) &pos, 0.1f) == 0
	    || CompareVector3WithinTolerance((float*) &cam->rot, (float*) &rot, 0.001f) == 0) {
		fcn_00438b40((void*) g_6b8014, &pos);
		fcn_00438cb0((void*) g_6b8014, &rot);
		ent = fcn_00509570(&((Entity*) g_7f4ca0)[g_774970]);
		if (ent != 0) {
			*(float*) (ent + 0x88) = g_774694;
			*(int*) (ent + 0x8c) = *(int*) &((View*) g_6b8014)->pos.x;
			*(int*) (ent + 0x90) = *(int*) &((View*) g_6b8014)->pos.y;
			*(int*) (ent + 0x94) = *(int*) &((View*) g_6b8014)->pos.z;
			*(int*) (ent + 0x9c) = *(int*) &((View*) g_6b8014)->rot.x;
			*(int*) (ent + 0xa0) = *(int*) &((View*) g_6b8014)->rot.y;
			*(int*) (ent + 0xa4) = *(int*) &((View*) g_6b8014)->rot.z;
		}
	}
afterFirst:
	cam = (View*) g_6b8014;
	if (cam == 0) {
		goto tail;
	}
	if (g_77475c != 0) {
		goto predict;
	}
	dt = g_14ce904 - g_14ce900;
	if (dt == 0) {
		goto predict;
	}
	g_774690 = g_774690 + (float) dt * 0.1f;
	if (g_774690 > 1.0) {
		g_774690 = (float) 1.0;
	}
	if (g_774690 < 0.0) {
		g_774690 = (float) 0.0;
	}
	fcn_0052ac60(g_774690);
	ent = fcn_00509570(&((Entity*) g_7f4ca0)[g_774970]);
	if (ent != 0) {
		*(float*) (ent + 0x88) = g_774694;
		*(int*) (ent + 0x8c) = *(int*) &((View*) g_6b8014)->pos.x;
		*(int*) (ent + 0x90) = *(int*) &((View*) g_6b8014)->pos.y;
		*(int*) (ent + 0x94) = *(int*) &((View*) g_6b8014)->pos.z;
		*(int*) (ent + 0x9c) = *(int*) &((View*) g_6b8014)->rot.x;
		*(int*) (ent + 0xa0) = *(int*) &((View*) g_6b8014)->rot.y;
		*(int*) (ent + 0xa4) = *(int*) &((View*) g_6b8014)->rot.z;
	}
predict:
	cam = (View*) g_6b8014;
	if (cam == 0) {
		goto tail;
	}
	if (g_14ce8e8 == 0) {
		goto tail;
	}
	if (g_14ce8d0 != 0) {
		goto tail;
	}
	fcn_005ebbb9(mat, cam->mat);
	q.y = 0.0f;
	t = (float) g_7766b4 * g_665df8;
	d.x = (float) ((int) g_14cf900 - g_773e38) * t;
	d.y = -((float) ((int) g_14cf902 - g_773df8)) * t;
	q.x = mat[8] * g_662d40[2] + mat[4] * g_662d40[1] + mat[0] * g_662d40[0];
	q.z = mat[10] * g_662d40[2] + mat[6] * g_662d40[1] + mat[2] * g_662d40[0];
	if ((float) sqrt((double) (q.x * q.x + q.z * q.z)) < 0.1f) {
		v.y = d.y;
		v.z = 0.0f;
		q.x = mat[0] * d.x + mat[4] * d.y + mat[8] * 0.0f;
		q.z = mat[2] * d.x + mat[6] * d.y + mat[10] * 0.0f;
	} else {
		ang = -fcn_004514d0(g_662d40, &q.x);
		v.y = 0.0f;
		v.z = d.y;
		q.x = d.x * (float) cos(ang) + d.y * (float) sin(ang);
		q.z = d.y * (float) cos(ang) - d.x * (float) sin(ang);
	}
	v.x = d.x;
	v.x = cam->pos.x + q.x;
	v.y = cam->pos.y;
	v.z = cam->pos.z + d.y;
	if (CompareVector3WithinTolerance(&g_773e14, (float*) &v, 0.1f) == 0) {
		if (*(int*) (g_67a370 + 0xb0) != 0) {
			ent = *(char**) (g_67a370 + 0xb0);
			t = *(float*) ent + *(float*) (ent + 0x10) * g_66430c;
			if (v.x < t) {
				v.x = t;
			}
			n = *(int*) (ent + 0x20) - 20;
			t = *(float*) ent + (float) n * *(float*) (ent + 0x10);
			if (v.x > t) {
				v.x = t;
			}
			t = *(float*) (ent + 8) + *(float*) (ent + 0x18) * g_66430c;
			n = *(int*) (ent + 0x20) - 20;
			t2 = *(float*) (ent + 8) + (float) n * *(float*) (ent + 0x18);
			if (v.z <= t2) {
				v.z = t2;
			}
			if (v.z >= t) {
				v.z = t;
			}
		}
		fcn_00438b40((void*) g_6b8014, &v);
		ent = fcn_00509570(&((Entity*) g_7f4ca0)[g_774970]);
		if (ent != 0) {
			*(int*) (ent + 0x8c) = *(int*) &((View*) g_6b8014)->pos.x;
			*(int*) (ent + 0x90) = *(int*) &((View*) g_6b8014)->pos.y;
			*(int*) (ent + 0x94) = *(int*) &((View*) g_6b8014)->pos.z;
			*(int*) (ent + 0x9c) = *(int*) &((View*) g_6b8014)->rot.x;
			*(int*) (ent + 0xa0) = *(int*) &((View*) g_6b8014)->rot.y;
			*(int*) (ent + 0xa4) = *(int*) &((View*) g_6b8014)->rot.z;
		}
	}
	g_773e14 = v.x;
	g_773e18 = v.y;
	g_773e1c = v.z;
	g_773e38 = (int) g_14cf900;
	g_773df8 = (int) g_14cf902;
	g_774760 = 1;
tail:
	ret = g_774760 - g_14ce900 + g_14ce904 + g_77475c;
	return ret;
}
