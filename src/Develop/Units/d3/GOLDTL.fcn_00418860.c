#include <math.h>
#include <string.h>

/* Scene camera; inferred owner in d3_camera.h. */
extern char* g_6b8014;
/* Sun-ray state shared with sonnenstrahlen.c. */
extern char* g_6b5cf8;
extern int g_6b5cfc;
extern int g_6b7fac;
extern int SonnenstrahlenStartZeit;

extern float flt_1;
extern float g_6628a8;
extern float g_6628c8;
extern float g_6628fc;
extern float g_662a7c;
extern float g_662b28;
extern double g_662950;
extern double g_662958;
extern double g_662b38;
extern double dbl_1_0;

int __cdecl fcn_00451840(float*, float*, float);
void __cdecl fcn_00438b40(char*, float*);
char* __cdecl fcn_00445600(char*, int, char*, char*);
void __cdecl fcn_00438cb0(char*, float*);
float __cdecl fcn_004187f0(float, float, float);
void __cdecl fcn_00418ae0(char*);

/* Light colour word passed by value; byte layout from fcn_0043a3f0. */
typedef struct SUNRAY_COLOR {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} SUNRAY_COLOR;

void __cdecl fcn_0043a3f0(char*, char*, SUNRAY_COLOR);

/* ADDRESS: GOLDTL 0x00418860 */
void __cdecl fcn_00418860(char* obj)
{
	float pos[3];
	float vec[3];
	float x;
	float result;
	float a;

	if (obj == 0 || *(int*) (obj + 0x1cc) == 0 || g_6b8014 == 0) {
		return;
	}
	a = *(float*) (g_6b8014 + 0x4c);
	vec[0] = a;
	a = *(float*) (g_6b8014 + 0x50);
	vec[1] = a;
	a = *(float*) (g_6b8014 + 0x54);
	vec[2] = a;
	if (fcn_00451840(vec, (float*) (obj + 0x4c), 0.0001f) == 0) {
		fcn_00438b40(obj, vec);
	}
	{
		char* light;

		light = fcn_00445600(0, 8, 0, "pLicht");
		if (light != 0) {
			a = *(float*) (light + 0x88) - *(float*) (obj + 0x88);
			if (fabs(a) >= 0.01) {
				pos[0] = 0.0f;
				pos[1] = (a > 0.0f ? 0.0002f : -0.0002f) + *(float*) (obj + 0x88);
				pos[2] = 0.0f;
				fcn_00438cb0(obj, pos);
			}
		}
	}
	a = (float) fmod(*(float*) (obj + 0x88) - *(float*) (g_6b8014 + 0x88), g_662958);
	if (a < g_6628a8) {
		a += g_6628c8;
	}
	a = (float) fmod(a, g_662958);
	if (a > g_6628fc) {
		a = g_6628fc - (a - g_6628fc);
	}
	x = fcn_004187f0(1.0995574f, 3.1415927f, a);
	a = (float) fmod(*(float*) (g_6b8014 + 0x84), g_662958);
	result = fcn_004187f0(-1.1780972f, 0.0f, (float) fmod(a, g_662958));
	if (g_6b5cfc == 1) {
		a = (float) (((double) (unsigned int) g_6b7fac - SonnenstrahlenStartZeit) * g_662b28);
		if (a >= dbl_1_0) {
			g_6b5cfc = 0;
		}
	} else if (g_6b5cfc == -1) {
		a = flt_1 - (float) (((double) (unsigned int) g_6b7fac - SonnenstrahlenStartZeit) * g_662b28);
		if (a <= g_662950) {
			g_6b5cfc = 0;
			fcn_00418ae0(obj);
			g_6b5cf8 = 0;
			return;
		}
	} else {
		a = flt_1;
	}
	{
		SUNRAY_COLOR color;

		memset(&color, 0, sizeof(color));
		color.c = 1;
		color.a = (unsigned char) (a * result * x * g_662a7c);
		fcn_0043a3f0(obj, *(char**) (obj + 0x1cc), color);
	}
}
