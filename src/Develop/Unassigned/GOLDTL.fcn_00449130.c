extern float g_662cf8;
extern float g_66293c;
extern float g_6628fc;
extern float g_6628b0;
#include <math.h>
extern double g_6629c8;

extern int g_1041d0c;
extern int g_14ce8d8;
extern int g_14ce8d0;
extern int g_14ce8ec;
extern int g_14ce8e4;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern int g_14ce904;
extern int g_14ce900;
extern int g_14ce860;
extern int g_14ce864;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern short g_14cf900;
extern short g_14cf902;
extern char g_14cf72a;
extern char g_14cf71d;
extern char g_14cf70f;
extern char g_67ab48;
extern char g_67ab49;
extern int g_6772c4;
extern int g_6b85a8;
extern int g_6b85ac;
extern int g_6b8478;
extern int g_6b847c;
extern int g_6b8480;
extern int d3_ActiveCamera;

void __cdecl fcn_004127a0(int flag);
void __cdecl fcn_004125c0(int x, int y);
char __cdecl fcn_00448cc0(int obj, float* a1, float* a2, int g, char* a5,
	char* a6);
void __cdecl fcn_00438b40(int h, char* p);
void __cdecl fcn_00438cb0(int h, char* p);
void __cdecl UpdateSceneLighting(int a);
char __cdecl fcn_00448b10(void);

/* ADDRESS: GOLDTL 0x00449130 */
int __cdecl fcn_00449130(void)
{
	char v14;
	char v15;
	char v1;
	char v2;
	int v16;
	int v17;
	float v18;
	float v19;
	float v20;
	float v21;
	double d;
	float motion[3];
	char v7[12];
	float scale[2];
	float rotate[3];
	char v8[16];
	char v3;

	v14 = 0;
	v15 = 0;
	if (g_1041d0c == 0)
		return 0;
	v1 = g_14cf71d;
	motion[0] = 0.0f;
	motion[1] = 0.0f;
	motion[2] = 0.0f;
	rotate[0] = 0.0f;
	rotate[1] = 0.0f;
	rotate[2] = 0.0f;
	v2 = g_14cf72a;
	v21 = 0.0f;
	v19 = 0.0f;
	v20 = 0.0f;
	v18 = 0.0f;
	if (g_14ce8d8 != 0) {
		g_6b85a8 = (int) g_14ce8c0;
		g_6b85ac = (int) g_14ce8c2;
	}
	else if (g_14ce8d0 != 0
		&& *(int*) (g_1041d0c + 0x218) != 0
		&& *(int*) (g_1041d0c + 0x218) < 5
		&& g_1041d0c != g_6b8478
		&& g_1041d0c != g_6b847c
		&& g_1041d0c != g_6b8480) {
		if (g_6772c4 != 0) {
			g_6772c4 = 0;
			fcn_004127a0(0);
		}
		if (g_67ab48 != 0) {
			v15 = 1;
			v16 = (int) g_14cf900 - g_6b85a8;
		}
		else {
			v16 = 0;
		}
		if (g_67ab49 != 0) {
			v15 = 1;
			v17 = (int) g_14cf902 - g_6b85ac;
		}
		else {
			v17 = 0;
		}
		g_6b85a8 = (int) g_14cf900;
		g_6b85ac = (int) g_14cf902;
		v18 = (float) v16 / g_14ce860 * g_6628fc;
		v20 = (float) v17 / g_14ce864 * g_6628fc;
	}
	if (g_14ce8ec != 0) {
		g_6b85ac = (int) g_14cf902;
		g_6b85a8 = (int) g_14cf900;
	}
	else if (g_14ce8e4 != 0) {
		if (g_6772c4 != 0) {
			g_6772c4 = 0;
			fcn_004127a0(0);
		}
		if (g_67ab48 != 0) {
			v14 = 1;
			v16 = (int) g_14cf900 - g_6b85a8;
		}
		else {
			v16 = 0;
		}
		if (g_67ab49 != 0) {
			v14 = 1;
			v17 = (int) g_14cf902 - g_6b85ac;
		}
		else {
			v17 = 0;
		}
		v21 = (float) v16 / (float) (unsigned int) g_14ce860;
		v19 = (float) v17 / (float) (unsigned int) g_14ce864;
		d = (double) (unsigned int) g_14ce860;
		scale[0] = (float) d
			/ (((float) fabs((float) v16) + g_6629c8)
			* g_66293c);
		if (scale[0] > g_6628b0)
			scale[0] = g_6628b0;
		scale[1] = ((float) fabs((float) v17) + g_6629c8)
			* g_66293c
			/ (float) (unsigned int) g_14ce864;
		if (scale[1] > g_6628b0)
			scale[1] = g_6628b0;
		v21 = v21 * scale[0] * *(float*) 0x662d00;
		v19 = v19 * scale[1] * *(float*) 0x662cfc;
		g_6b85ac = (int) g_14cf902;
		g_6b85a8 = (int) g_14cf900;
	}
	if (g_14ce8e4 == 0 && g_14ce8d0 == 0 && g_6772c4 == 0) {
		g_6772c4 = 1;
		fcn_004127a0(1);
		fcn_004125c0((int) g_14ce8c0, (int) g_14ce8c2);
	}
	if (g_14ce904 != 0) {
		rotate[2] = rotate[2] + g_662cf8;
		v14 = 1;
	}
	else if (g_14ce900 != 0) {
		rotate[2] = rotate[2] - g_662cf8;
		v14 = 1;
	}
	if (g_14cf70f != 0) {
		v14 = 1;
	}
	else if (v14 == 0 && v15 == 0) {
		goto label_4495a3;
	}
	if (v2 != 0 || v1 != 0) {
		motion[1] = v18;
		rotate[1] = v19;
	}
	else {
		motion[0] = v20;
		motion[1] = v18;
		rotate[0] = v21;
		rotate[1] = (float) ((unsigned char) g_14cf70f * 0x28) + v19;
	}
	if (v14 != 0 || v15 != 0) {
		v3 = fcn_00448cc0(g_1041d0c, rotate, motion, d3_ActiveCamera, v8, v7);
		v15 = (char) ((unsigned char) v3 >> 1);
		v14 = v3 & 1;
		if (v14 != 0)
			fcn_00438b40(g_1041d0c, v8);
		if (v15 != 0)
			fcn_00438cb0(g_1041d0c, v7);
	}
label_4495a3:
	if (g_14ce8cc != 0) {
		UpdateSceneLighting(0);
		v14 = 1;
	}
	if (g_14ce8e0 != 0) {
		UpdateSceneLighting(0);
		v14 = 1;
	}
	if ((fcn_00448b10() | v14) == 0 && v15 == 0)
		return 0;
	return 1;
}
