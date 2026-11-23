#include <math.h>
#include <string.h>

extern char* d3_ActiveCamera;
extern char* g_6b5cf8;
extern volatile int g_6b7fac;
extern int SonnenstrahlenAktiv;
extern int SonnenstrahlenStartZeit;

int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
char* __cdecl fcn_00449690(char*, int, char*, char*);
float __cdecl fcn_004187f0(float, float, float);
void __cdecl fcn_00417560(char*);
typedef struct SUNRAY_COLOR {
	unsigned char a, b, c, d;
} SUNRAY_COLOR;
void __cdecl d3_ChangeObjectTransparency(char*, char*, SUNRAY_COLOR);

/* ADDRESS: GOLD 0x004172e0 */
void __cdecl fcn_004172e0(char* object)
{
	float position[4];
	float x;
	float result;
	float a;

	if (object == 0 || *(int*) (object + 0x1cc) == 0 || d3_ActiveCamera == 0) {
		return;
	}
	a = *(float*) (d3_ActiveCamera + 0x4c);
	position[0] = a;
	a = *(float*) (d3_ActiveCamera + 0x50);
	position[1] = a;
	a = *(float*) (d3_ActiveCamera + 0x54);
	position[2] = a;
	if (!CompareVector3WithinTolerance(position, (float*) (object + 0x4c), 0.0001f)) {
		fcn_00438b40(object, position);
	}
	{
		char* light;
		float rotation[3];

		light = fcn_00449690(0, 8, 0, "pLicht");
		if (light != 0) {
			a = *(float*) (light + 0x88) - *(float*) (object + 0x88);
			if (fabs(a) >= 0.009999999776482582) {
				rotation[1] = (a > 0.0f ? 0.0002f : -0.0002f) + *(float*) (object + 0x88);
				rotation[0] = 0.0f;
				rotation[2] = 0.0f;
				d3_SetObjectRotation(object, rotation);
			}
		}
	}
	{
		char* camera;
		float v;
		camera = d3_ActiveCamera;
		a = (float) fmod(*(float*) (object + 0x88) - *(float*) (camera + 0x88), 6.2831854820251465);
		if (a < 0.0f) {
			a += 6.2831855f;
		}
		v = (float) fmod(a, 6.2831854820251465);
		a = v > 3.1415927f ? 3.1415927f - (v - 3.1415927f) : v;
		x = fcn_004187f0(1.0995574f, 3.1415927f, a);
		a = (float) fmod(*(float*) (camera + 0x84), 6.2831854820251465);
		result = fcn_004187f0(-1.1780972f, 0.0f, (float) fmod(a, 6.2831854820251465));
	}
	if (SonnenstrahlenAktiv == 1) {
		a = (float) ((double) (unsigned int) g_6b7fac - SonnenstrahlenStartZeit) * 0.002f;
		if (a >= 1.0) {
			SonnenstrahlenAktiv = 0;
		}
	} else if (SonnenstrahlenAktiv == -1) {
		a = 1.0f - (float) ((double) (unsigned int) g_6b7fac - SonnenstrahlenStartZeit) * 0.002f;
		if (a <= 0.0f) {
			SonnenstrahlenAktiv = 0;
			fcn_00417560(object);
			g_6b5cf8 = 0;
			return;
		}
	} else {
		a = 1.0f;
	}
	{
		SUNRAY_COLOR color;

		a *= result;
		memset(&color, 0, sizeof(color));
		color.c = 1;
		color.a = (unsigned char) (a * x * 128.0f);
		d3_ChangeObjectTransparency(object, *(char**) (object + 0x1cc), color);
	}
}
